#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <string>
#include <iterator>
#include <algorithm>
#define FILENAME   "/Users/george/Projects/Personal/SimulationPerformance/WirelessStreaming/soccer.txt"
#define START      0.0
using namespace std;
FILE   *fp;
long long counter = 0;
long long lost = 0;
double arrival   = START;
double delay;
double service;
double waiting;
double departure = START;
struct {
    double delay;
    double wait;
    double service;
    double interarrival;
} sum = {0.0, 0.0, 0.0};
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
bool condition(float x) {
    return x < delay;
}
void resetStats() {
    counter = 0;
    arrival = START;
    departure = START;
    sum.delay = 0.0;
    sum.wait = 0.0;
    sum.service = 0.0;
    delay = 0.0;
    lost = 0;
}
void case6Mbps() {
    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    }
    resetStats();
    while (!feof(fp)) {
        counter++;
        arrival = GetArrival(fp);
        if (arrival < departure) {
            delay = departure - arrival;
        }
        else
            delay      = 0.0;
        service      = GetService(fp);
        service=service/750000; //(6Mb = 750000B)
        waiting         = delay + service;
        departure    = arrival + waiting;
        sum.delay   += delay;
        sum.wait    += waiting;
        sum.service += service;
    }
    sum.interarrival = arrival - START;
}
void case6MbpsNoQueue() {
    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    }
    resetStats();
    while (!feof(fp)) {
        counter++;
        arrival = GetArrival(fp);
        if (arrival < departure) {
            lost++;
            GetService(fp);
            continue;
        }
        else
            delay      = 0.0;
        service      = GetService(fp);
        service=service/750000; //(6Mb = 750000B)
        waiting         = delay + service;
        departure    = arrival + waiting;
        sum.delay   += delay;
        sum.wait    += waiting;
        sum.service += service;
    }
    sum.interarrival = arrival - START;
}
void case6MbpsQueue10() {
    vector<float> events;
    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    }
    resetStats();
    while (!feof(fp)) {
        counter++;
        arrival = GetArrival(fp);
        events.push_back(arrival);
        events.erase(remove_if(events.begin(),events.end(), condition),events.end());
        if (arrival < departure || events.size() > 10 ) {
            lost++;
            GetService(fp);
            departure = arrival + waiting;
            continue;
        }
        else
        {delay = 0.0;}

        service      = GetService(fp);
        service=service/750000; //(6Mb = 750000B)
        waiting         = delay + service;
        departure    = arrival + waiting;
        sum.delay   += delay;
        sum.wait    += waiting;
        sum.service += service;
    }
    sum.interarrival = arrival - START;
}
//15916.371623
//31434.872580

//568696
//526102
//593417
void case6MbpsQueue20() {
    vector<float> events;
    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    }
    resetStats();
    while (!feof(fp)) {
        counter++;
        arrival = GetArrival(fp);
        events.erase(remove_if(events.begin(),events.end(), condition),events.end());
        if ( (arrival < departure) && (events.size() > 20 )) {
            lost ++;
            delay = departure - arrival;
        }
        service = GetService(fp);
        service=service/750000; //(6Mb = 6 000 000) 6 000 000
        waiting      = delay + sum.delay;
        departure    = arrival + waiting;
        events.push_back(departure);
        sum.delay   += delay;
        sum.wait    += waiting;
        sum.service += service;
    }
    sum.interarrival = arrival - START;
}
void case11Mbps() {
    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    }
    resetStats();
    while (!feof(fp)) {
        counter++;
        arrival = GetArrival(fp);
        if (arrival < departure) {
            delay = departure - arrival;
        }
        else
            delay      = 0.0;
        service      = GetService(fp);
        service=service/1375000; //(6Mb = 1375000B)
        waiting         = delay + service;
        departure    = arrival + waiting;
        sum.delay   += delay;
        sum.wait    += waiting;
        sum.service += service;
    }
    sum.interarrival = arrival - START;
}
void case30Mbps() {
    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    }
    resetStats();
    while (!feof(fp)) {
        counter++;
        arrival = GetArrival(fp);
        if (arrival < departure) {
            delay = departure - arrival;
        }
        else
            delay      = 0.0;
        service      = GetService(fp);
        service=service/3750000; //(30Mb = 3750000B)
        waiting         = delay + service;
        departure    = arrival + waiting;
        sum.delay   += delay;
        sum.wait    += waiting;
        sum.service += service;
    }
    sum.interarrival = arrival - START;
}
void case50Mbps() {
    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    }
    resetStats();
    while (!feof(fp)) {
        counter++;
        arrival = GetArrival(fp);
        if (arrival < departure) {
            delay = departure - arrival;
        }
        else
            delay      = 0.0;
        service      = GetService(fp);
        service=service/6250000; //(50Mb = 6250000B)
        waiting         = delay + service;
        departure    = arrival + waiting;
        sum.delay   += delay;
        sum.wait    += waiting;
        sum.service += service;
    }
    sum.interarrival = arrival - START;
}
void print() {
    printf("\nfor %ld jobs\n", counter);
    printf("   average interarrival time = %8.6f\n", sum.interarrival / counter);
    printf("   average service time .... = %8.6f\n", sum.service / counter);
    printf("   service time ............ = %8.6f\n", sum.service);
    printf("   delay time .............. = %8.6f\n", sum.delay);
    printf("   average delay ........... = %8.6f\n", sum.delay / counter);
    printf("   average wait ............ = %8.6f\n", sum.wait / counter);
    printf("   packets lost ............ = %8.6lld\n", lost);
    printf("   average # in the queue .. = %6.2f\n", sum.delay / departure);
}
int main()
{
//    case6Mbps();
//    print();
//    case11Mbps();
//    print();
//    case30Mbps();
//    print();
//    case50Mbps();
//    print();
//    fclose(fp);
//    case6MbpsNoQueue();
//    print();
//    case6MbpsQueue10();
//    print();
    case6MbpsQueue20();
    print();
    return (0);
}