#include <stdio.h>
#include <vector>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <fstream>
#define FILENAME   "/Users/george/Projects/Personal/SimulationPerformance/WirelessStreaming/soccer.txt"
using namespace std;
double arrival, delay, service, waiting, departure;
vector <float> packages;
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
void simulationModes() {
    cout<< "Choose 1 if you want to check the statictics of 6Mbps Internet Speed and Variable Buffer Size\n";
    cout<< "Choose 2 if you want to check the statictics of 11Mbps Internet Speed and 50 Buffer Size\n";
    cout<< "Choose 3 if you want to check the statictics of 30Mbps Internet Speed and 50 Buffer Size\n";
    cout<< "Choose 4 if you want to check the statictics of 54Mbps Internet Speed and 50 Buffer Size\n";
    cout<< "Choose anything else if you want to exit\n";
}
void resetStats() {
    packages.clear();
    delay = 0.0;
    service = 0.0;
    service = 0.0;
    waiting = 0.0;
    departure = 0.0;
    arrival = 0.0;
    sum.service = 0.0;
    sum.delay = 0.0;
    sum.wait = 0.0;
    sum.interarrival = 0.0;
}
void case6MbpsBuffer50() {
    resetStats();
    FILE   *fp;
    long   index     = 0;
    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    }
    int jobs_lost = 0;
    int jobs_done = 0;
    while (!feof(fp)) {
        double come = GetArrival(fp);

        if ((packages.size() > 0) && (packages[0] < come)) {
            while((packages.size() > 0) && (packages[0] < come)) {
                packages.erase(packages.begin());
                jobs_done ++ ;
            }

        }
        index++;
        if (packages.size() >= 50 )
        {
            jobs_lost ++;
            GetService(fp);
            continue;
        }
        else {
            arrival = come;
            if (departure > arrival)
            {delay = departure - arrival;  }
            else
            {
                delay = 0.0;
            }
            service      = GetService(fp);
            service /= 750000;
            waiting        = delay + service;
            departure    = arrival + delay + service;
            sum.delay   += delay;
            sum.wait    += waiting;
            sum.service += service;
            if (!packages.empty()) {
                if ( arrival > packages.back() )
                    packages.push_back(arrival + service + packages.back());
                else {
                    packages.push_back(service + packages.back());
                }
            } else {
                packages.push_back(arrival + service);
            }

        }
    }
    sum.interarrival = arrival - 0.0;
    jobs_done ++;
    printf("\nfor %ld jobs\n", index);
    printf("   average interarrival time = %8.6f\n", sum.interarrival / (jobs_done));
    printf("   average service time .... = %8.6f\n", sum.service / (jobs_done));
    printf("   average delay ........... = %8.6f\n", sum.delay / (jobs_done));
    printf("   average wait ............ = %8.6f\n", sum.wait / (jobs_done));
    printf("   packages lost ........... = %8.6d\n", jobs_lost);
    printf("   packages done ........... = %8.6d\n", jobs_done);
}
void case6MbpsChangeBuffer() {
    vector<pair<int,int> > values;
    vector<pair<int,double > > lost;
    pair<int,int> value;
    pair<int,double > lost_value;
    for (int i=0;i<=300;i+=10) {
        value.first = i;
        lost_value.first = i;
        resetStats();
        FILE   *fp;
        fp = fopen(FILENAME, "r");
        if (fp == NULL) { fprintf(stderr, "Cannot open input file %s\n", FILENAME); }
        int jobs_lost = 0, jobs_done = 0, index = 0;
        while (!feof(fp)) {
            index++;
            double come = GetArrival(fp);
            while((packages.size() > 0) && (packages[0] < come)) {
                packages.erase(packages.begin());
                jobs_done ++ ; }
            if (packages.size() >= i )
            { jobs_lost ++; GetService(fp); continue; } else {
                arrival = come;
                service = GetService(fp);
                service /= 750000;
                packages.push_back(!packages.empty() ?
                                   (arrival > packages.back() ? arrival + service : service) + packages.back() :
                                   arrival + service);
            }
        }
        jobs_done+=packages.size();
        value.second = jobs_done;
        lost_value.second = double((double)jobs_lost*100.00/double(index));
        values.push_back(value);
        lost.push_back(lost_value);
    }
    ofstream h("/Users/george/Projects/Personal/SimulationPerformance/WirelessStreamingSecondTry/packetloss.out");
    ofstream g("/Users/george/Projects/Personal/SimulationPerformance/WirelessStreamingSecondTry/soccer.txt");
    for(pair<int, double> it:lost) {
        h<<it.first<<" "<<double(it.second)<<"\n";
    }
    for(pair<int,int> it:values) {
        g<<it.first<<" "<<it.second<<"\n";
    }
    cout<<"Computation may take some time..."<<"\n";
    for (pair<int,int> it:values) {
        cout<<"Buffer size: "<<it.first<<" "<<"Packets done: "<<it.second<<"\n";
    }
}
void case11MbpsBuffer50() {
    resetStats();
    FILE   *fp;
    long   index     = 0;
    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    }
    int jobs_lost = 0;
    int jobs_done = 0;
    while (!feof(fp)) {
        double come = GetArrival(fp);
        while((packages.size() > 0) && (packages[0] < come)) {
            packages.erase(packages.begin());
            jobs_done ++ ;
        }

        index++;
        if (packages.size() >= 50 )
        {
            jobs_lost ++;
            GetService(fp);
            continue;
        } else {
            arrival = come;
            if(!packages.empty()) { delay = packages.back() - arrival; }
            sum.delay += delay;
            service = GetService(fp);
            service /= 1375000;
            packages.push_back( !packages.empty() ?
                                (arrival > packages.back() ? arrival + service : service) + packages.back() :
                                arrival + service);
        }
    }
    jobs_done+=packages.size();
    std::cout << std::setprecision(4) << std::fixed;
    cout<<"\nFor "<<index<<" packets:"<<"\n";
    cout<<"Buffer size: 50 packets"<<"\n";
    cout<<"Wireless speed: 11000000 bps"<<"\n";
    cout<<"Packets lost = "<<jobs_lost<<"\n";
    cout<<"Packets done = "<<jobs_done<<"\n";
    cout<<"Lost traffic = "<<jobs_lost*100.00/index<<"%\n";
    cout<<"Average delay = "<<double(sum.delay/(double)jobs_done)<<" s\n";
    cout<< "\n";
}
void case30MbpsBuffer50() {
    resetStats();
    FILE   *fp;
    long   index     = 0;
    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    }
    int jobs_lost = 0;
    int jobs_done = 0;
    while (!feof(fp)) {
        double come = GetArrival(fp);
        while((packages.size() > 0) && (packages[0] < come)) {
            packages.erase(packages.begin());
            jobs_done ++ ;
        }

        index++;
        if (packages.size() >= 50 )
        {
            jobs_lost ++;
            GetService(fp);
            continue;
        } else {
            arrival = come;
            if(!packages.empty()) { delay = packages.back() - arrival; }
            sum.delay += delay;
            service = GetService(fp);
            service /= 3750000;
            packages.push_back( !packages.empty() ?
                                (arrival > packages.back() ? arrival + service : service) + packages.back() :
                                arrival + service);
        }
    }
    jobs_done+=packages.size();
    std::cout << std::setprecision(4) << std::fixed;
    cout<<"\nFor "<<index<<" packets:"<<"\n";
    cout<<"Buffer size: 50 packets"<<"\n";
    cout<<"Wireless speed: 30000000 bps"<<"\n";
    cout<<"Packets lost = "<<jobs_lost<<"\n";
    cout<<"Packets done = "<<jobs_done<<"\n";
    cout<<"Lost traffic = "<<jobs_lost*100.00/index<<"%\n";
    cout<<"Average delay = "<<double(sum.delay/(double)jobs_done)<<" s\n";
    cout<< "\n";
}
void case54MbpsBuffer50() {
    resetStats();
    FILE   *fp;
    fp = fopen(FILENAME, "r");
    if (fp == NULL) { fprintf(stderr, "Cannot open input file %s\n", FILENAME); }
    int jobs_lost = 0, jobs_done = 0, index = 0;
    while (!feof(fp)) {
        index++;
        double come = GetArrival(fp);
            while((packages.size() > 0) && (packages[0] < come)) {
                packages.erase(packages.begin());
                jobs_done ++ ; }
        if (packages.size() >= 50 )
        { jobs_lost ++; GetService(fp); continue; } else {
            arrival = come;
            if(!packages.empty()) { delay = packages.back() - arrival; }
            sum.delay += delay;
            service = GetService(fp);
            service /= 6750000;
            packages.push_back(!packages.empty() ?
                               (arrival > packages.back() ? arrival + service : service) + packages.back() :
                               arrival + service);
        }
    }
    jobs_done+=packages.size();
    std::cout << std::setprecision(4) << std::fixed;
    cout<<"\nFor "<<index<<" packets:"<<"\n";
    cout<<"Buffer size: 50 packets"<<"\n";
    cout<<"Wireless speed: 54000000 bps"<<"\n";
    cout<<"Packets lost = "<<jobs_lost<<"\n";
    cout<<"Packets done = "<<jobs_done<<"\n";
    cout<<"Lost traffic = "<<jobs_lost*100.00/index<<"%\n";
    cout<<"Average delay = "<<double(sum.delay/(double)jobs_done)<<" s\n";
    cout<< "\n";
}
int main() {
    int userchoice=1;
    while(userchoice >= 1 && userchoice < 5) {
        simulationModes();
        cin >> userchoice;
        switch (userchoice) {
            case 1: case6MbpsChangeBuffer(); break;
            case 2: case11MbpsBuffer50(); break;
            case 3: case30MbpsBuffer50(); break;
            case 4: case54MbpsBuffer50(); break;
        }
    }
    return 0;
}
