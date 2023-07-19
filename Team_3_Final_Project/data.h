#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SIZE 50

#define DL 1
#define DN 2
#define DR 3

#define LT 4
#define HL 5
#define RT 6

#define UL 7
#define UP 8
#define UR 9

#define AT 10
#define BR 11

#define introTIME 2
#define endOfRoundTIME 2
char starter[SIZE];

char map[SIZE][SIZE];

int sizeMap;

struct heaven {
    int x,y;
} heavens[20];
int numHeaven = 0;

struct block {
    int x,y;
} blocks[50];
int numBlock = 0;

struct food {
    int x,y,energy;
} foods[100];
int numFood = 0;

struct animal { 
    char name;
    int x,y;
    int energy;
    int moveEnergy, stepNum, breedEnergy, attack, defence;
    int way[SIZE], waynum;
    int goalX, goalY, goalCost;
    char goalName;
    int childEnergy, logNum;
} animals[50];
int numAnimal = 0;
char userAnimal;
int lastLog = 0;

int repeatDecide;
int repeatAI = 1;

struct AiMap {
    int cost, disFromStart, disFromDest;
    int parentx, parenty;
} AstarMap[SIZE][SIZE];


char prefrences[10] = "HFABH";

int WIN = 0;

int curAnim;