#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <cmath>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
#define DEBUG 1
#define MAX_INT 2147483647
#define NUMGAMES 1000000
using namespace std;
string suit[] = {"Diamonds", "Hearts", "Spades", "Clubs"};
string facevalue[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
string drawnCards[52];
int numberOfCardsDrawn = 0;
void gameModes() {
    cout<< "Choose 1 if you want to check the statictics of Asso Game\n";
    cout<< "Choose 2 if you want to check the statictics of Grande Game\n";
    cout<< "Choose 3 if you want to check the statictics of Cuori Game\n";
    cout<< "Choose 4 if you want to check the statictics of Completare Game\n";
    cout<< "Choose 5 if you want to check the statictics of George's Game\n";
    cout<< "Choose 6 if you want to check the statictics of Asso Game Infinite Deck\n";
    cout<< "Choose 7 if you want to check the statictics of Grande Game Infinite Deck\n";
    cout<< "Choose 8 if you want to check the statictics of Cuori Game Infinite Deck\n";
    cout<< "Choose 9 if you want to check the statictics of Completare Game Infinite Deck\n";
    cout<< "Choose 10 if you want to check the statictics of George's Game Infinite Deck\n";
    cout<< "Choose 11 if you want to check the statictics of New Game\n";
    cout<< "Choose 12 if you want to check the statictics of New Game Infinite Deck\n";

    cout<< "Choose anything else if you want to exit\n";
}
float Uniform01()
{
    float randomnumber;
    randomnumber = (float) 1.0 * random();
    randomnumber = (float) randomnumber / (1.0 * MAX_INT);
    return randomnumber;
}
int EquiLikely(int low,int high)
{
    float randomnumber;
    int answer;

    randomnumber = Uniform01();
    answer = low + randomnumber*(high - low + 1);

#ifdef DEBUG
    printf("EquiLikely(%d,%d) uses %8.6f to return %d\n",
           low, high, randomnumber, answer);
#endif

    return answer;
}
pair<string,int> drawCard () {
    pair<string,int> card;
    int cardvalue = EquiLikely(0,12);
    int cardsuit = EquiLikely(0,3);
    card.first += facevalue[cardvalue];
    card.first += " of ";
    card.first += suit[cardsuit];
    card.second = cardvalue;
    return card;
}
bool isMyCardAlreadyDrawn (pair<string,int> card) {
    for(int i = 0; i < 52; i++) {
        if(card.first.compare(drawnCards[i]) == 0) {
            return true;
        }
    }
    return false;
}
pair<string,int> getCard () {
    pair<string,int> card = drawCard();
    while (isMyCardAlreadyDrawn(card) == true) {
        card = drawCard();
    }
    drawnCards[numberOfCardsDrawn] = card.first;
    numberOfCardsDrawn++;
    return card;
}
string suitOfCard(pair<string,int> card) {
    if (card.first.find("Diamonds") != std::string::npos)
        return "Diamonds";
    if (card.first.find("Hearts") != std::string::npos)
        return "Hearts";
    if (card.first.find("Spades") != std::string::npos)
        return "Spades";
    if (card.first.find("Clubs") != std::string::npos)
        return "Clubs";
    return "";
}
void case1() {
    pair <string,int> drawnCard1;
    int games, wins, losses;
    games = 0;
    wins = 0;
    losses = 0;
    int balance = 0;
    while (games < NUMGAMES) {
        balance -= 1;
        drawnCards->erase();
        numberOfCardsDrawn = 0;
        drawnCard1 = getCard();
#ifdef DEBUG
        cout << "Card was: " << (drawnCard1.first) << "\n";
#endif
        if (drawnCard1.second == 12) /* instant win */
        {
#ifdef DEBUG
            printf("Winner!\n");
#endif
            wins++;
            balance += 10;
        } else {
            losses++;
#ifdef DEBUG
            printf("Lost!\n");
#endif
        }


        games++;
#ifdef DEBUG
        printf("\n");
#endif
    }
    printf("\n");
    printf("Asso Game\n");
    printf("Number of trials: %d\n", NUMGAMES);
    printf("Number of wins: %d\n", wins);
    printf("Number of losses: %d\n", losses);
    printf("Estimated probability of winning: %8.6f\n", 1.0 * wins / games);
    printf("Estimated balance: %d\n", balance);
}
void case1InfiniteDeck() {
    pair <string,int> drawnCard1;
    int games, wins, losses;
    games = 0;
    wins = 0;
    losses = 0;
    int balance = 0;
    while (games < NUMGAMES) {
        balance -= 1;
        drawnCard1 = drawCard();
#ifdef DEBUG
        cout << "Card was: " << (drawnCard1.first) << "\n";
#endif
        if (drawnCard1.second == 12) /* instant win */
        {
#ifdef DEBUG
            printf("Winner!\n");
#endif
            wins++;
            balance += 10;
        } else {
            losses++;
#ifdef DEBUG
            printf("Lost!\n");
#endif
        }


        games++;
#ifdef DEBUG
        printf("\n");
#endif
    }
    printf("\n");
    printf("Asso Game Infinite\n");
    printf("Number of trials: %d\n", NUMGAMES);
    printf("Number of wins: %d\n", wins);
    printf("Number of losses: %d\n", losses);
    printf("Estimated probability of winning: %8.6f\n", 1.0 * wins / games);
    printf("Estimated balance: %d\n", balance);
}
void case2() {
    pair <string,int> drawnCard1;
    pair <string,int> drawnCard2;
    int games, wins, losses;
    games = 0;
    wins = 0;
    losses = 0;
    int balance = 0;
    while (games < NUMGAMES) {
        balance -= 1;
        drawnCards->erase();
        numberOfCardsDrawn = 0;
        drawnCard1 = getCard();
        drawnCard2 = getCard();
#ifdef DEBUG
            cout << "Cards were: " << (drawnCard1.first) << " & " << (drawnCard2.first) << "\n";
#endif
            if (drawnCard2.second > drawnCard1.second) /* instant win */
            {
#ifdef DEBUG
                printf("Winner!\n");
#endif
                wins++;
                balance += 2;
            } else {
                losses++;
#ifdef DEBUG
                printf("Lost!\n");
#endif
            }

        games++;
#ifdef DEBUG
        printf("\n");
#endif
    }
    printf("\n");
    printf("Grande Game\n");
    printf("Number of trials: %d\n", NUMGAMES);
    printf("Number of wins: %d\n", wins);
    printf("Number of losses: %d\n", losses);
    printf("Estimated probability of winning: %8.6f\n", 1.0 * wins / games);
    printf("Estimated balance: %d\n", balance);
}
void case2InfiniteDeck() {
    pair <string,int> drawnCard1;
    pair <string,int> drawnCard2;
    int games, wins, losses;
    games = 0;
    wins = 0;
    losses = 0;
    int balance = 0;
    while (games < NUMGAMES) {
        balance -= 1;
        drawnCard1 = drawCard();
        drawnCard2 = drawCard();
#ifdef DEBUG
        cout << "Cards were: " << (drawnCard1.first) << " & " << (drawnCard2.first) << "\n";
#endif
        if (drawnCard2.second > drawnCard1.second) /* instant win */
        {
#ifdef DEBUG
            printf("Winner!\n");
#endif
            wins++;
            balance += 2;
        } else {
            losses++;
#ifdef DEBUG
            printf("Lost!\n");
#endif
        }

        games++;
#ifdef DEBUG
        printf("\n");
#endif
    }
    printf("\n");
    printf("Grande Game Infinite Deck\n");
    printf("Number of trials: %d\n", NUMGAMES);
    printf("Number of wins: %d\n", wins);
    printf("Number of losses: %d\n", losses);
    printf("Estimated probability of winning: %8.6f\n", 1.0 * wins / games);
    printf("Estimated balance: %d\n", balance);
}
void case3() {
    pair <string,int> drawnCard1;
    pair <string,int> drawnCard2;
    pair <string,int> drawnCard3;
    int games, wins, losses;
    games = 0;
    wins = 0;
    losses = 0;
    int balance = 0;
    while (games < NUMGAMES) {
        balance -= 1;
        drawnCards->erase();
        numberOfCardsDrawn = 0;
        drawnCard1 = getCard();
        drawnCard2 = getCard();
        drawnCard3 = getCard();
#ifdef DEBUG
        cout << "Cards were: " << (drawnCard1.first) << " & " << (drawnCard2.first) << " & " << (drawnCard3.first) << "\n";
#endif
        if ( (drawnCard1.first.find("Hearts") != std::string::npos ) || (drawnCard2.first.find("Hearts") != std::string::npos) || (drawnCard3.first.find("Hearts") != std::string::npos) )
        {
#ifdef DEBUG
            printf("Winner!\n");
#endif
            wins++;
            if (drawnCard1.first.find("Hearts") != std::string::npos) {balance++;}
            if (drawnCard2.first.find("Hearts") != std::string::npos) {balance++;}
            if (drawnCard3.first.find("Hearts") != std::string::npos) {balance++;}
        } else {
            losses++;
#ifdef DEBUG
            printf("Lost!\n");
#endif
        }

        games++;
#ifdef DEBUG
        printf("\n");
#endif
    }
    printf("\n");
    printf("Cuori Game\n");
    printf("Number of trials: %d\n", NUMGAMES);
    printf("Number of wins: %d\n", wins);
    printf("Number of losses: %d\n", losses);
    printf("Estimated probability of winning: %8.6f\n", 1.0 * wins / games);
    printf("Estimated balance: %d\n", balance);
}
void case3InfiniteDeck() {
    pair <string,int> drawnCard1;
    pair <string,int> drawnCard2;
    pair <string,int> drawnCard3;
    int games, wins, losses;
    games = 0;
    wins = 0;
    losses = 0;
    int balance = 0;
    while (games < NUMGAMES) {
        balance -= 1;
        drawnCard1 = drawCard();
        drawnCard2 = drawCard();
        drawnCard3 = drawCard();
#ifdef DEBUG
        cout << "Cards were: " << (drawnCard1.first) << " & " << (drawnCard2.first) << " & " << (drawnCard3.first) << "\n";
#endif
        if ( (drawnCard1.first.find("Hearts") != std::string::npos ) || (drawnCard2.first.find("Hearts") != std::string::npos) || (drawnCard3.first.find("Hearts") != std::string::npos) )
        {
#ifdef DEBUG
            printf("Winner!\n");
#endif
            wins++;
            if (drawnCard1.first.find("Hearts") != std::string::npos) {balance++;}
            if (drawnCard2.first.find("Hearts") != std::string::npos) {balance++;}
            if (drawnCard3.first.find("Hearts") != std::string::npos) {balance++;}
        } else {
            losses++;
#ifdef DEBUG
            printf("Lost!\n");
#endif
        }

        games++;
#ifdef DEBUG
        printf("\n");
#endif
    }
    printf("\n");
    printf("Cuori Game Infinite Deck\n");
    printf("Number of trials: %d\n", NUMGAMES);
    printf("Number of wins: %d\n", wins);
    printf("Number of losses: %d\n", losses);
    printf("Estimated probability of winning: %8.6f\n", 1.0 * wins / games);
    printf("Estimated balance: %d\n", balance);
}
void case4() {
    pair <string,int> drawnCard1;
    pair <string,int> drawnCard2;
    pair <string,int> drawnCard3;
    pair <string,int> drawnCard4;
    int games, wins, losses;
    games = 0;
    wins = 0;
    losses = 0;
    int balance = 0;
    while (games < NUMGAMES) {
        balance -= 1;
        drawnCards->erase();
        numberOfCardsDrawn = 0;
        drawnCard1 = getCard();
        drawnCard2 = getCard();
        drawnCard3 = getCard();
        drawnCard4 = getCard();
#ifdef DEBUG
        cout << "Cards were: " << (drawnCard1.first) << " & " << (drawnCard2.first) << " & " << (drawnCard3.first) << " & " << (drawnCard4.first) << "\n";
#endif
        string f1 = suitOfCard(drawnCard1);
        string f2 = suitOfCard(drawnCard2);
        string f3 = suitOfCard(drawnCard3);
        string f4 = suitOfCard(drawnCard4);
        set <string> myset;
        myset.insert(f1);
        myset.insert(f2);
        myset.insert(f3);
        myset.insert(f4);
        if (myset.size()==4) /* instant win */
        {
#ifdef DEBUG
            printf("Winner!\n");
#endif
            wins++;
            balance += 20;
        } else {
            losses++;
#ifdef DEBUG
            printf("Lost!\n");
#endif
        }

        games++;
#ifdef DEBUG
        printf("\n");
#endif
    }
    printf("\n");
    printf("Completare Game\n");
    printf("Number of trials: %d\n", NUMGAMES);
    printf("Number of wins: %d\n", wins);
    printf("Number of losses: %d\n", losses);
    printf("Estimated probability of winning: %8.6f\n", 1.0 * wins / games);
    printf("Estimated balance: %d\n", balance);
}
void case4InfiniteDeck() {
    pair <string,int> drawnCard1;
    pair <string,int> drawnCard2;
    pair <string,int> drawnCard3;
    pair <string,int> drawnCard4;
    int games, wins, losses;
    games = 0;
    wins = 0;
    losses = 0;
    int balance = 0;
    while (games < NUMGAMES) {
        balance -= 1;
        drawnCard1 = drawCard();
        drawnCard2 = drawCard();
        drawnCard3 = drawCard();
        drawnCard4 = drawCard();
#ifdef DEBUG
        cout << "Cards were: " << (drawnCard1.first) << " & " << (drawnCard2.first) << " & " << (drawnCard3.first) << " & " << (drawnCard4.first) << "\n";
#endif
        string f1 = suitOfCard(drawnCard1);
        string f2 = suitOfCard(drawnCard2);
        string f3 = suitOfCard(drawnCard3);
        string f4 = suitOfCard(drawnCard4);
        set <string> myset;
        myset.insert(f1);
        myset.insert(f2);
        myset.insert(f3);
        myset.insert(f4);
        if (myset.size()==4) /* instant win */
        {
#ifdef DEBUG
            printf("Winner!\n");
#endif
            wins++;
            balance += 20;
        } else {
            losses++;
#ifdef DEBUG
            printf("Lost!\n");
#endif
        }

        games++;
#ifdef DEBUG
        printf("\n");
#endif
    }
    printf("\n");
    printf("Completare Game Infinite Deck\n");
    printf("Number of trials: %d\n", NUMGAMES);
    printf("Number of wins: %d\n", wins);
    printf("Number of losses: %d\n", losses);
    printf("Estimated probability of winning: %8.6f\n", 1.0 * wins / games);
    printf("Estimated balance: %d\n", balance);
}
void case5() {
    pair <string,int> drawnCard1;
    pair <string,int> drawnCard2;
    pair <string,int> drawnCard3;
    pair <string,int> drawnCard4;
    int games, wins, losses;
    games = 0;
    wins = 0;
    losses = 0;
    int balance = 0;
    while (games < NUMGAMES) {
        balance -= 1;
        drawnCards->erase();
        numberOfCardsDrawn = 0;
        drawnCard1 = getCard();
        drawnCard2 = getCard();
        drawnCard3 = getCard();
        drawnCard4 = getCard();
#ifdef DEBUG
        cout << "Cards were: " << (drawnCard1.first) << " & " << (drawnCard2.first) << " & " << (drawnCard3.first) << " & " << (drawnCard4.first) << "\n";
#endif
        if ( (drawnCard1.first.find("Ace") != std::string::npos ) && (drawnCard2.first.find("Ace") != std::string::npos) && (drawnCard3.first.find("Ace") != std::string::npos) && (drawnCard4.first.find("Ace") != std::string::npos)) /* instant win */
        {
#ifdef DEBUG
            printf("Winner!\n");
#endif
            wins++;
            balance += 240000;
        } else {
            losses++;
#ifdef DEBUG
            printf("Lost!\n");
#endif
        }

        games++;
#ifdef DEBUG
        printf("\n");
#endif
    }
    printf("\n");
    printf("George's Game\n");
    printf("Number of trials: %d\n", NUMGAMES);
    printf("Number of wins: %d\n", wins);
    printf("Number of losses: %d\n", losses);
    printf("Estimated probability of winning: %8.6f\n", 1.0 * wins / games);
    printf("Estimated balance: %d\n", balance);
}
void case5InfiniteDeck() {
    pair <string,int> drawnCard1;
    pair <string,int> drawnCard2;
    pair <string,int> drawnCard3;
    pair <string,int> drawnCard4;
    int games, wins, losses;
    games = 0;
    wins = 0;
    losses = 0;
    int balance = 0;
    while (games < NUMGAMES) {
        balance -= 1;
        drawnCard1 = drawCard();
        drawnCard2 = drawCard();
        drawnCard3 = drawCard();
        drawnCard4 = drawCard();
#ifdef DEBUG
        cout << "Cards were: " << (drawnCard1.first) << " & " << (drawnCard2.first) << " & " << (drawnCard3.first) << " & " << (drawnCard4.first) << "\n";
#endif
        if ( (drawnCard1.first.find("Ace") != std::string::npos ) && (drawnCard2.first.find("Ace") != std::string::npos) && (drawnCard3.first.find("Ace") != std::string::npos) && (drawnCard4.first.find("Ace") != std::string::npos)) /* instant win */
        {
#ifdef DEBUG
            printf("Winner!\n");
#endif
            wins++;
            balance += 240000;
        } else {
            losses++;
#ifdef DEBUG
            printf("Lost!\n");
#endif
        }

        games++;
#ifdef DEBUG
        printf("\n");
#endif
    }
    printf("\n");
    printf("George's Game Infinite Deck\n");
    printf("Number of trials: %d\n", NUMGAMES);
    printf("Number of wins: %d\n", wins);
    printf("Number of losses: %d\n", losses);
    printf("Estimated probability of winning: %8.6f\n", 1.0 * wins / games);
    printf("Estimated balance: %d\n", balance);
}
void case6() {
    pair <string,int> drawnCard1;
    pair <string,int> drawnCard2;
    pair <string,int> drawnCard3;
    pair <string,int> drawnCard4;
    pair <string,int> drawnCard5;
    int games, wins, losses;
    games = 0;
    wins = 0;
    losses = 0;
    int balance = 0;
    while (games < NUMGAMES) {
        balance -= 1;
        drawnCards->erase();
        numberOfCardsDrawn = 0;
        drawnCard1 = getCard();
        drawnCard2 = getCard();
        drawnCard3 = getCard();
        drawnCard4 = getCard();
        drawnCard5 = getCard();
#ifdef DEBUG
        cout << "Cards were: " << (drawnCard1.first) << " & " << (drawnCard2.first) << " & " << (drawnCard3.first) << " & " << (drawnCard4.first) << " & " << (drawnCard5.first) << "\n";
#endif
        vector <int> v;
        v.push_back(drawnCard1.second);
        v.push_back(drawnCard2.second);
        v.push_back(drawnCard3.second);
        v.push_back(drawnCard4.second);
        v.push_back(drawnCard5.second);
        sort(v.begin(),v.end());
        v.erase( unique( v.begin(), v.end() ), v.end() );
        if(v.size() == 5) {
            if (  ( v.at(0) + 1 == v.at(1) && v.at(1) + 1 == v.at(2) )   ||  (v.at(1) + 1 == v.at(2) && v.at(2) + 1 == v.at(3) )  ||  (v.at(2) + 1 == v.at(3) && v.at(3) + 1 == v.at(4)) )
            {
#ifdef DEBUG
                printf("Winner!\n");
#endif      cout<<v.size();
                wins++;
                balance += 5;
            } else {
                losses++;
#ifdef DEBUG
                printf("Lost!\n");
#endif
            }
        }
        if(v.size() == 4) {
            if (  ( v.at(0) + 1 == v.at(1) && v.at(1) + 1 == v.at(2) )   ||  (v.at(1) + 1 == v.at(2) && v.at(2) + 1 == v.at(3) ) )
            {
#ifdef DEBUG
                printf("Winner!\n");
#endif      cout<<v.size();
                wins++;
                balance += 5;
            } else {
                losses++;
#ifdef DEBUG
                printf("Lost!\n");
#endif
            }
        }
        if(v.size() == 3) {
            if ( ( v.at(0) + 1 == v.at(1) && v.at(1) + 1 == v.at(2) ))
            {
#ifdef DEBUG
                printf("Winner!\n");
#endif      cout<<v.size();
                wins++;
                balance += 5;
            } else {
                losses++;
#ifdef DEBUG
                printf("Lost!\n");
#endif
            }
        }


        games++;
#ifdef DEBUG
        printf("\n");
#endif
    }
    printf("\n");
    printf("New Game\n");
    printf("Number of trials: %d\n", NUMGAMES);
    printf("Number of wins: %d\n", wins);
    printf("Number of losses: %d\n", losses);
    printf("Estimated probability of winning: %8.6f\n", 1.0 * wins / games);
    printf("Estimated balance: %d\n", balance);
}
void case6InfiniteDeck() {
    pair <string,int> drawnCard1;
    pair <string,int> drawnCard2;
    pair <string,int> drawnCard3;
    pair <string,int> drawnCard4;
    pair <string,int> drawnCard5;
    int games, wins, losses;
    games = 0;
    wins = 0;
    losses = 0;
    int balance = 0;
    while (games < NUMGAMES) {
        balance -= 1;
        drawnCards->erase();
        numberOfCardsDrawn = 0;
        drawnCard1 = drawCard();
        drawnCard2 = drawCard();
        drawnCard3 = drawCard();
        drawnCard4 = drawCard();
        drawnCard5 = drawCard();
#ifdef DEBUG
        cout << "Cards were: " << (drawnCard1.first) << " & " << (drawnCard2.first) << " & " << (drawnCard3.first) << " & " << (drawnCard4.first) << " & " << (drawnCard5.first) << "\n";
#endif
        vector <int> v;
        v.push_back(drawnCard1.second);
        v.push_back(drawnCard2.second);
        v.push_back(drawnCard3.second);
        v.push_back(drawnCard4.second);
        v.push_back(drawnCard5.second);
        sort(v.begin(),v.end());
        v.erase( unique( v.begin(), v.end() ), v.end() );
        if(v.size() == 5) {
            if (  ( v.at(0) + 1 == v.at(1) && v.at(1) + 1 == v.at(2) )   ||  (v.at(1) + 1 == v.at(2) && v.at(2) + 1 == v.at(3) )  ||  (v.at(2) + 1 == v.at(3) && v.at(3) + 1 == v.at(4)) )
            {
#ifdef DEBUG
                printf("Winner!\n");
#endif      cout<<v.size();
                wins++;
                balance += 5;
            } else {
                losses++;
#ifdef DEBUG
                printf("Lost!\n");
#endif
            }
        }
        if(v.size() == 4) {
            if (  ( v.at(0) + 1 == v.at(1) && v.at(1) + 1 == v.at(2) )   ||  (v.at(1) + 1 == v.at(2) && v.at(2) + 1 == v.at(3) ) )
            {
#ifdef DEBUG
                printf("Winner!\n");
#endif      cout<<v.size();
                wins++;
                balance += 5;
            } else {
                losses++;
#ifdef DEBUG
                printf("Lost!\n");
#endif
            }
        }
        if(v.size() == 3) {
            if ( ( v.at(0) + 1 == v.at(1) && v.at(1) + 1 == v.at(2) ))
            {
#ifdef DEBUG
                printf("Winner!\n");
#endif      cout<<v.size();
                wins++;
                balance += 5;
            } else {
                losses++;
#ifdef DEBUG
                printf("Lost!\n");
#endif
            }
        }


        games++;
#ifdef DEBUG
        printf("\n");
#endif
    }
    printf("\n");
    printf("New Game\n");
    printf("Number of trials: %d\n", NUMGAMES);
    printf("Number of wins: %d\n", wins);
    printf("Number of losses: %d\n", losses);
    printf("Estimated probability of winning: %8.6f\n", 1.0 * wins / games);
    printf("Estimated balance: %d\n", balance);
}
void testCase() {
    pair <string,int> drawnCard1;
    pair <string,int> drawnCard2;
    pair <string,int> drawnCard3;
    pair <string,int> drawnCard4;
    pair <string,int> drawnCard5;
    int games, wins, losses;
    games = 0;
    wins = 0;
    losses = 0;
    int balance = 0;
    while (games < NUMGAMES) {
        balance -= 1;
        drawnCards->erase();
        numberOfCardsDrawn = 0;
        drawnCard1 = getCard();
        drawnCard2 = getCard();
        drawnCard3 = getCard();
//        drawnCard4 = getCard();
//        drawnCard5 = getCard();
#ifdef DEBUG
        cout << "Cards were: " << (drawnCard1.first) << " & " << (drawnCard2.first) << " & " << (drawnCard3.first) << "\n";
#endif
        vector <int> v;
        v.push_back(drawnCard1.second);
        v.push_back(drawnCard2.second);
        v.push_back(drawnCard3.second);
//        v.push_back(drawnCard4.second);
//        v.push_back(drawnCard5.second);
        sort(v.begin(),v.end());
        if (  ( v.at(0) + 1 == v.at(1) && v.at(1) + 1 == v.at(2) ) )
        {
#ifdef DEBUG
            printf("Winner!\n");
#endif
            wins++;
            balance += 5;
        } else {
            losses++;
#ifdef DEBUG
            printf("Lost!\n");
#endif
        }

        games++;
#ifdef DEBUG
        printf("\n");
#endif
    }
    printf("\n");
    printf("New Game\n");
    printf("Number of trials: %d\n", NUMGAMES);
    printf("Number of wins: %d\n", wins);
    printf("Number of losses: %d\n", losses);
    printf("Estimated probability of winning: %8.6f\n", 1.0 * wins / games);
    printf("Estimated balance: %d\n", balance);
}
int main()
{
    int userchoice=1;
    while(userchoice >= 1 && userchoice < 13) {
        srandom(1234567);
        gameModes();
        cin >> userchoice;
        switch (userchoice) {
            case 1: case1(); break;
            case 2: case2(); break;
            case 3: case3(); break;
            case 4: case4(); break;
            case 5: case5(); break;
            case 6: case1InfiniteDeck(); break;
            case 7: case2InfiniteDeck(); break;
            case 8: case3InfiniteDeck(); break;
            case 9: case4InfiniteDeck(); break;
            case 10: case5InfiniteDeck(); break;
            case 11: case6(); break;
            case 12: case6InfiniteDeck(); break;

        }
    }


}
