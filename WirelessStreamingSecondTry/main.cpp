#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iterator>
#define FILENAME   "/Users/george/Projects/Personal/SimulationPerformance/WirelessStreaming/soccer.txt"
#define START      0.0
double arrival   = START;
using namespace std;
vector <float> packages;
double GetArrival(FILE *fp)
{
    double a;
    fscanf(fp, "%lf", &a);
    return (a);
}
double GetService(FILE *fp)
{
    double s;
    fscanf(fp, "%lf\n", &s);
    return (s);
}
int main(void) {

    FILE   *fp;                                  /* input data file      */
    long   index     = 0;                        /* job index            */
                       /* arrival time         */
    double delay;                                /* delay in queue       */
    double service;                              /* service time         */
    double wait;                                 /* delay + service      */
    double departure = START;                    /* departure time       */
    struct {                                     /* sum of ...           */
        double delay;                              /*   delay times        */
        double wait;                               /*   wait times         */
        double service;                            /*   service times      */
        double interarrival;                       /*   interarrival times */
    } sum = {0.0, 0.0, 0.0};

    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open input file %s\n", FILENAME);
        return (1);
    }
    int jobs_lost = 0;
    int jobs_done = 0;
    while (!feof(fp)) {
        float come = GetArrival(fp);
        if ((packages.size() > 1) && (packages[0] < come)) {
                while((packages.size() > 1) && (packages[0] < come)) {
                    packages.erase(packages.begin());
                    jobs_done ++ ;
                }
        }
        index++;
        if (packages.size() > 30 )
        {
            arrival = come;
            delay  = departure - arrival;     /* delay in queue    */
            sum.delay   += delay;
            jobs_lost ++;
            arrival = come;
            GetService(fp);
            continue;
        }
        else {
            arrival = come;
            service      = GetService(fp);
            service /= 750000;
            wait         = delay + service;
            departure    = arrival + wait;             /* time of departure */
            delay = departure - arrival;
            sum.delay   += delay;
            sum.wait    += wait;
            sum.service += service;
            packages.push_back(departure);
        }
    }
    sum.interarrival = arrival - START;

    printf("\nfor %ld jobs\n", index);
    printf("   average interarrival time = %8.6f\n", sum.interarrival / (index-jobs_lost));
    printf("   average service time .... = %8.6f\n", sum.service / (index-jobs_lost));
    printf("   average delay ........... = %8.6f\n", sum.delay / (index-jobs_lost));
    printf("   average wait ............ = %8.6f\n", sum.wait / (index-jobs_lost));
    printf("   packages lost ........... = %8.6lu\n", jobs_lost);
    printf("   packages done ........... = %8.6lu\n", jobs_done);
    fclose(fp);
    return (0);
}
