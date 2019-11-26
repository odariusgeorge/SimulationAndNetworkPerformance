#include <stdio.h>

#define FILENAME   "/Users/george/Projects/Personal/SimulationPerformance/SSQ1/ssq1-input.txt"              /* input data file */
#define START      0.0

/* =========================== */
double GetArrival(FILE *fp)                 /* read an arrival time */
/* =========================== */
{
    double a;

    fscanf(fp, "%lf", &a);
    return (a);
}

/* =========================== */
double GetService(FILE *fp)                 /* read a service time */
/* =========================== */
{
    double s;

    fscanf(fp, "%lf\n", &s);
    return (s);
}

/* ============== */
int main(void)
/* ============== */
{
    FILE   *fp;                                  /* input data file      */
    long   index     = 0;                        /* job index            */
    double arrival   = START;                    /* arrival time         */
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

    while (!feof(fp)) {
        index++;
        arrival      = GetArrival(fp);
        if (arrival < departure)
            delay      = departure - arrival;        /* delay in queue    */
        else
            delay      = 0.0;                        /* no delay          */
        service      = GetService(fp);
        wait         = delay + service;
        departure    = arrival + wait;             /* time of departure */
        sum.delay   += delay;
        sum.wait    += wait;
        sum.service += service;
    }
    sum.interarrival = arrival - START;

    printf("\nfor %ld jobs\n", index);
    printf("   average interarrival time = %8.6f\n", sum.interarrival / index);
    printf("   average service time .... = %8.6f\n", sum.service / index);
    printf("   average delay ........... = %8.6f\n", sum.delay / index);
    printf("   average wait ............ = %8.6f\n", sum.wait / index);

    fclose(fp);
    return (0);
}