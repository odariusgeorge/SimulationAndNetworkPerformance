# Casino Games

This program is used for showing how random numbers, probability, and Monte Carlo simulation works. 

## Getting Started

You will need to download the project from moodle platform or via github.

### Prerequisites

You will need to have: compiler-drivers of the GNU Compiler Collection like g++ or gcc. 

### Installing

Go to the directory of the project. 

Make an executable of the project with the following command: g++ -o executable main.cpp

Now run the executable: ./executable 

Now there's an "infinite" loop and you can run the program as many as you like. You can exit the loop by typing every key excluding [1,2,3,4,5].

If you type 1 : you will "play" and analyze Asso Game
If you type 2 : you will "play" and analyze Grande Game
If you type 3 : you will "play" and analyze Cuori Game
If you type 4 : you will "play" and analyze Completare Game
If you type 5 : you will "play" and analyze George's Game

### If i would have a casino I would choose...

The "Cuori" Game.
The simulation of this game:
After 1.000.000 (one million) trials we have:
Number of trials: 1000000
Number of wins: 586636
Number of losses: 413364
Estimated probability of winning: 0.586636
Estimated balance: -249895
So the casino is winning with this game: 249895 euros after one million
plays.

We see that the players percentage win is more than 0.5, so how the casino is not losing money?
That's because they are not "losing" everytime the players are "winning"; they are just giving the euro back 
to players. And the percentage of having two hearts cards out of three is not that big. So in this way they are
keeping the players at the table until they are losing money. 

### Smart move, heh?


## Running environment

The simulation was run on my personal laptop. MacOS Operating System.

## Known Problems

So far I was not capable to find any problem beside that problem with the "Completare Game" when 
the casino is losing money just because the reward is way to big for that probability of winning.

## Authors

* **Darius-George Oanea**



