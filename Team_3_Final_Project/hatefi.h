#include "aghli.h"


void printPlayBack() { //// havaset bashe tu new game failo pak koni
    FILE *plybk;
    plybk = fopen("PlayBack.txt", "at");
    fprintf(plybk, "%d %d\n", sizeMap, numAnimal);
    for (int i = 0; i < sizeMap; i++) { // col
        for (int j = 0; j < sizeMap; j++) { // row
            fprintf(plybk, "%c", map[i][j]);
        }
        fprintf(plybk, "\n");
    }
}


void watchAGame() {
    clear();
    for(int i = 1; i < 4; i++) {
        printf("\n\n\n\n\n\n\t------[ %d ]------\n\n\n\n", i);
        sleep(2);
        clear();
    }
    clear();
    FILE *plybk;
    plybk = fopen("PlayBack.txt", "rt");
    if(!plybk){
        printf("couldn't open the PlayBack file.\n");
        return;
    }
    char mapLine[SIZE];
    int lineCounter = 0, roundCounter = -1, watchSizeMap, watchNumAni;
    fscanf(plybk, "%d %d", &watchSizeMap, &watchNumAni);
    while(!feof(plybk)) {
        fscanf(plybk, "%s", mapLine);
        for (int i = 0; i < watchSizeMap; i++) { // col
            if (mapLine[i] == '.')
                printf("\033[1;%d;30m . \033[0m", 42);

            else if (mapLine[i] == '#')
                printf(" # ");

            else if (mapLine[i] == 'F')
                printf("\033[%d;42m F \033[0m", 33);

            else if (mapLine[i] == 'H')
                printf("\033[%d;36m H \033[0m", 43);
            
             else if (mapLine[i] == '%')
                printf("\033[31;42m %c \033[0m", '%');
                
            else
                printf("\033[%d;42m %c \033[0m", 30, mapLine[i]);            
        }
        lineCounter++;
        printf("\n");
        if(lineCounter == watchSizeMap) {
            printf("\n");
            lineCounter = 0;
            roundCounter++;
            if(roundCounter == watchNumAni) {
                printf("\n\n\t End of round\n");
                roundCounter = 0;
                sleep(3);
            }
            fscanf(plybk, "%d %d", &watchSizeMap, &watchNumAni);
            sleep(1);
            clear();
        }
    }
    printf("\nGame finished.\n");
    sleep(3);
}


void intro() {
    printf("\nHello! Welcome to this apocalypse, Here you must fight for your destiny.\n");
    sleep(introTIME);
    printf("The first specie arrive to heaven will survive. you can move, attack, eat, breed, and help your friends.\n");
    sleep(introTIME);
    printf("every decision you make, will affect the whole world, so be careful about your thoughts.\n");
    sleep(introTIME);
    printf("try not to be smarter than the others, because you can't!\n");
    sleep(introTIME);
    printf("continue your way and be the first one who has experienced the impeccable place. GOOD LUCK.\n");
    sleep(introTIME + 3);

}


int maximum(int a, int b) {
    if(a > b)
        return a;
    else
        return b;
}


int isOpen (int x, int y, int open[][3], int openNum) {
    for(int i = 0; i < openNum; i++) {
        if(open[i][0] == x && open[i][1] == y)
            return 1;
    }
    return 0;
}


int isClosed (int x, int y, int closed[][2], int closedNum) {
    if(x >= sizeMap || x < 0 || y >= sizeMap || y < 0)
        return 1;

    if(map[x][y] == '#')
        return 1;

    for(int i = 0; i < closedNum; i++) {
        if(closed[i][0] == x && closed[i][1] == y)
            return 1;
    }

    if(map[x][y] != 'H' && map[x][y] != 'F') {
        if(map[x][y] < 91 && map[x][y] > 64) 
            return 1;
    }

    return 0;
}


int theLowestCost(int open[][3], int openNum) {
    int minCost = 1000000, minIndex = 0;
    for(int i = 0; i < openNum; i++) {
        if(open[i][2] < minCost) {
            minCost = open[i][2];
            minIndex = i;
        }
    }
    return minIndex;
}


void deleteTheLowest(int open[][3], int openNum, int index) {
    for (int i = index; i < openNum - 1; i++) {
        open[i][0] = open[i + 1][0];
        open[i][1] = open[i + 1][1];
        open[i][2] = open[i + 1][2];
    }
}


void finisher(int animalIndex, int lastMove) {
    if(animals[animalIndex].goalName == animals[animalIndex].name) {
        animals[animalIndex].way[lastMove - 1] = BR;
    } else if (animals[animalIndex].goalName < 91 && animals[animalIndex].goalName > 64) {
        if (animals[animalIndex].goalName != 'H' && animals[animalIndex].goalName != 'F')
            animals[animalIndex].way[lastMove - 1] = AT;
    }
}


void decideByParent(int startX, int startY, int homeX, int homeY, int way[], int animalIndex) {

    int decide, wayCounter = 0, tempWay[SIZE];
    int nextX, nextY, curX, curY;
    curX = startX;
    curY = startY;
    nextX = AstarMap[startX][startY].parentx;
    nextY = AstarMap[startX][startY].parenty;
    while (curX != homeX || curY != homeY) {
        if(curX < nextX) {
            if(curY < nextY)
                decide = UL;
            else if(curY == nextY)
                decide = UP;
            else if (curY > nextY)
                decide = UR;
        } else if (curX == nextX) {
            if(curY < nextY)
                decide = LT;
            else if (curY > nextY)
                decide = RT;
        } else if (curX > nextX) {
            if(curY < nextY)
                decide = DL;
            else if(curY == nextY)
                decide = DN;
            else if (curY > nextY)
                decide = DR;
        }
        tempWay[wayCounter] = decide;
        wayCounter++;
        curX = nextX;
        curY = nextY;
        nextX = AstarMap[curX][curY].parentx;
        nextY = AstarMap[curX][curY].parenty;
    }

    //to reverse the way from dest to home
    for(int i = 0; i < wayCounter; i++) {
        way[i] = tempWay[wayCounter - 1 - i];
    }
    way[wayCounter] = -1;
    animals[animalIndex].goalCost = wayCounter - 1;
    finisher(animalIndex, wayCounter);
}


void initAiMap () {
    for(int i = 0; i < sizeMap; i++) {
        for(int j = 0; j < sizeMap; j++) {
            AstarMap[i][j].cost = 0;
        }
    }
}


void AStarAlg(int startX, int startY, int destX, int destY, int way[], int animalIndex) {

    initAiMap();
    int currentVx = startX, currentVy = startY;
    int open [SIZE * SIZE][3], closed[SIZE * SIZE][2];
    int opensCount = 0, closedCount = 0;
    int minOpen = 0;
    AstarMap[currentVx][currentVy].disFromStart = 0;
    AstarMap[currentVx][currentVy].disFromDest = maximum(abs(currentVx - destX), abs(currentVy - destY));
    AstarMap[currentVx][currentVy].cost = AstarMap[currentVx][currentVy].disFromDest + AstarMap[currentVx][currentVy].disFromStart;
    closed[closedCount][0] = currentVx;
    closed[closedCount][1] = currentVy;
    closedCount++;
    while (currentVx != destX || currentVy != destY) {
        for(int i = 1; i > -2; i--) {
            for(int j = -1; j < 2; j++) {
                if(i == 0 && j == 0)
                    continue;
                if(!isClosed(currentVx + i, currentVy + j, closed, closedCount) || (currentVx + i == destX) && (currentVy + j == destY)) {
                    if(!isOpen(currentVx + i, currentVy + j, open, opensCount)) {
                        AstarMap[currentVx + i][currentVy + j].disFromStart = AstarMap[currentVx][currentVy].disFromStart + 1;
                        AstarMap[currentVx + i][currentVy + j].disFromDest = maximum(abs((currentVx + i) - destX), abs((currentVy + j) - destY));
                        AstarMap[currentVx + i][currentVy + j].cost = AstarMap[currentVx + i][currentVy + j].disFromStart + AstarMap[currentVx + i][currentVy + j].disFromDest;
                        AstarMap[currentVx + i][currentVy + j].parentx = currentVx;
                        AstarMap[currentVx + i][currentVy + j].parenty = currentVy;
                        open[opensCount][0] = currentVx + i;
                        open[opensCount][1] = currentVy + j;
                        open[opensCount][2] = AstarMap[currentVx + i][currentVy + j].cost;
                        opensCount++;
                    }
                }
            }
        }
        closed[closedCount][0] = currentVx;
        closed[closedCount][1] = currentVy;
        closedCount++;
        minOpen = theLowestCost(open, opensCount);
        currentVx = open[minOpen][0];
        currentVy = open[minOpen][1];
        deleteTheLowest(open, opensCount, minOpen);
        opensCount--;
    }
    decideByParent(destX, destY, startX, startY, way, animalIndex);
}


int canAchive (int animalIndex) {
    if(animals[animalIndex].goalCost * animals[animalIndex].moveEnergy <= animals[animalIndex].energy)
        return 1;
    else
        return 0;
}


void goalFinder(int animalIndex, char goal) {
    int x = animals[animalIndex].x;
    int y = animals[animalIndex].y;
    int minCost = SIZE * SIZE;
    int goalIndex = 0;

    if(goal == 'H') {
        for(int i = 0; i < numHeaven; i++) {
            AStarAlg(x, y, heavens[i].x, heavens[i].y, animals[animalIndex].way, animalIndex);
            if(animals[animalIndex].goalCost < minCost) {
                minCost = animals[animalIndex].goalCost;
                goalIndex = i;
            }
        }
        animals[animalIndex].goalName = 'H';
        animals[animalIndex].goalX = heavens[goalIndex].x;
        animals[animalIndex].goalY = heavens[goalIndex].y;
        AStarAlg(x, y, heavens[goalIndex].x, heavens[goalIndex].y, animals[animalIndex].way, animalIndex);

    } else if(goal == 'F') {
        for(int i = 0; i < numFood; i++) {
            AStarAlg(x, y, foods[i].x, foods[i].y, animals[animalIndex].way, animalIndex);
            if(animals[animalIndex].goalCost < minCost) {
                minCost = animals[animalIndex].goalCost;
                goalIndex = i;
            }
        }
        animals[animalIndex].goalName = 'F';
        animals[animalIndex].goalX = foods[goalIndex].x;
        animals[animalIndex].goalY = foods[goalIndex].y;
        AStarAlg(x, y, foods[goalIndex].x, foods[goalIndex].y, animals[animalIndex].way, animalIndex);

    } else if(goal == 'A') {
        for(int i = 0; i < numAnimal; i++) {
            if(i == animalIndex || animals[i].name == animals[animalIndex].name || animals[i].attack > animals[animalIndex].attack)
                continue;
            AStarAlg(x, y, animals[i].x, animals[i].y, animals[animalIndex].way, animalIndex);
            if(animals[animalIndex].goalCost < minCost) {
                minCost = animals[animalIndex].goalCost;
                goalIndex = i;
            }
        }
        animals[animalIndex].goalName = animals[goalIndex].name;
        animals[animalIndex].goalX = animals[goalIndex].x;
        animals[animalIndex].goalY = animals[goalIndex].y;
        AStarAlg(x, y, animals[goalIndex].x, animals[goalIndex].y, animals[animalIndex].way, animalIndex);

    } else if(goal == 'B') {
        for(int i = 0; i < numAnimal; i++) {
            if(i == animalIndex || animals[i].name != animals[animalIndex].name)
                continue;
            AStarAlg(x, y, animals[i].x, animals[i].y, animals[animalIndex].way, animalIndex);
            if(animals[animalIndex].goalCost < minCost) {
                minCost = animals[animalIndex].goalCost;
                goalIndex = i;
            }
        }
        animals[animalIndex].goalName = animals[goalIndex].name;
        animals[animalIndex].goalX = animals[goalIndex].x;
        animals[animalIndex].goalY = animals[goalIndex].y;
        AStarAlg(x, y, animals[goalIndex].x, animals[goalIndex].y, animals[animalIndex].way, animalIndex);

    } else if(goal == 'N') {
        int maxEnergy = 0, niggaIndex;
        for(int i = 0; i < numAnimal; i++) {
            if(animals[i].name == animals[animalIndex].name && animalIndex != i) {
                if(animals[i].energy > maxEnergy) {
                    maxEnergy = animals[i].energy;
                    niggaIndex = i;
                }
            }
        }
        animals[animalIndex].goalName = animals[niggaIndex].name;
        animals[animalIndex].goalX = animals[niggaIndex].x;
        animals[animalIndex].goalY = animals[niggaIndex].y;
        animals[animalIndex].way[0] = HL;
        animals[animalIndex].waynum = 0;
    }
}


void wayFinder(int animalIndex) {
    if (animals[animalIndex].name == userAnimal)
        return;
    
    animals[animalIndex].waynum = 0;
    int p = 0, helpFlag = 1;
    int breedAnimal = 0, enemyAnimal = 0;

    //how many animals to breed :
    for(int i = 0; i < numAnimal; i++){
        if(animals[animalIndex].name == animals[i].name)
            breedAnimal++;
    }

    //how many animal to attack :
    enemyAnimal = numAnimal - breedAnimal;

    goalFinder(animalIndex, 'H');

    if(numFood) {
        if(!canAchive(animalIndex))
            goalFinder(animalIndex, 'F');
    }
    if(breedAnimal > 1) {
        if(!canAchive(animalIndex) && animals[animalIndex].energy > animals[animalIndex].breedEnergy)
            goalFinder(animalIndex, 'B');
    }
    if(breedAnimal > 1){
        if(!canAchive(animalIndex)) {
            goalFinder(animalIndex, 'N');
            int frndIndex;
            for(int i = 0; i < numAnimal; i++) {
                if(animals[i].x == animals[animalIndex].goalX) {
                    if(animals[i].y == animals[animalIndex].goalY) {
                        frndIndex = i;
                        break;
                    }
                }
            }
            if(!canAchive(frndIndex))
                helpFlag = 0;
        }
    }
    if(!helpFlag)
        goalFinder(animalIndex, 'H');
    
}


// braye tekrar kardan harekat system
int repeatcheck(int animalIndex, int decision) {
    int x = animals[animalIndex].x;
    int y = animals[animalIndex].y;

    switch (decision) {
        case DL:
            x += 1;
            y -= 1;
            break;

        case DN:
            x += 1;
            break;

        case DR:
            x += 1;
            y += 1;
            break;

        case LT:
            y -= 1;
            break;

        case RT:
            y += 1;
            break;

        case UL:
            x -= 1;
            y -= 1;
            break;

        case UP:
            x -= 1;
            break;

        case UR:
            x -= 1;
            y += 1;
            break;

        default:
            break;
        }
    if (x < 0 || x > sizeMap || y < 0 || y > sizeMap)
        return 0;
    else if(map[x][y] == 'H' || map[x][y] == 'F' || map[x][y] == '.')
        return 1;
    else 
        return 0;
    
}


void systemDecide(int moves[], int animalIndex) {
    int prevLog = animals[animalIndex].logNum;
    if(animals[animalIndex].way[0] == 0)
        wayFinder(animalIndex);
    if (moves[animals[animalIndex].way[animals[animalIndex].waynum]] && animals[animalIndex].goalName == map[animals[animalIndex].goalX][animals[animalIndex].goalY]) {
        if(animals[animalIndex].way[animals[animalIndex].waynum] <= 9 && animals[animalIndex].way[animals[animalIndex].waynum] != 5)
            humanLog(animalIndex, 'm', animals[animalIndex].x, animals[animalIndex].y);

        afterDecide(animals[animalIndex].way[animals[animalIndex].waynum], animalIndex);
        repeatAI++;

        while(animals[animalIndex].way[animals[animalIndex].waynum] == animals[animalIndex].way[animals[animalIndex].waynum + 1] && repeatAI <= animals[animalIndex].stepNum && repeatcheck(animalIndex, animals[animalIndex].way[animals[animalIndex].waynum + 1])) {
            afterDecide(animals[animalIndex].way[animals[animalIndex].waynum + 1], animalIndex);
            animals[animalIndex].waynum++;
            repeatAI++;
        }
        if(animals[animalIndex].way[animals[animalIndex].waynum] <= 9 && animals[animalIndex].way[animals[animalIndex].waynum] != 5 && animals[animalIndex].logNum == prevLog)
            humanLog(animalIndex, 'M', animals[animalIndex].x, animals[animalIndex].y);

        animals[animalIndex].waynum++;
        repeatAI = 1;
    } else {
        wayFinder(animalIndex);
        if(animals[animalIndex].way[animals[animalIndex].waynum] <= 9 && animals[animalIndex].way[animals[animalIndex].waynum] != 5)
            humanLog(animalIndex, 'm', animals[animalIndex].x, animals[animalIndex].y);

        afterDecide(animals[animalIndex].way[animals[animalIndex].waynum], animalIndex);
        repeatAI++;

        while(animals[animalIndex].way[animals[animalIndex].waynum] == animals[animalIndex].way[animals[animalIndex].waynum + 1] && repeatAI <= animals[animalIndex].stepNum && repeatcheck(animalIndex, animals[animalIndex].way[animals[animalIndex].waynum + 1])) {
            afterDecide(animals[animalIndex].way[animals[animalIndex].waynum + 1], animalIndex);
            animals[animalIndex].waynum++;
            repeatAI++;
        }
        if(animals[animalIndex].way[animals[animalIndex].waynum] <= 9 && animals[animalIndex].way[animals[animalIndex].waynum] != 5 && animals[animalIndex].logNum == prevLog)
            humanLog(animalIndex, 'M', animals[animalIndex].x, animals[animalIndex].y);

        animals[animalIndex].waynum++;
        repeatAI = 1;
    }
    repeatAI = 1;
}