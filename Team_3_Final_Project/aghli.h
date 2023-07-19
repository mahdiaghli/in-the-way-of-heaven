#include "data.h"


void humanLog(int animalIndex,char event, int x, int y) {
    FILE *logFile;
    logFile = fopen("HumanLog.txt", "at");
    switch (event) {
    case 'S' : //start
        fprintf(logFile, "A new game.\n");
        fprintf(logFile, "Basic information :\n");
        fprintf(logFile, "Heavens -> ");
        for(int i = 0; i < numHeaven; i++) {
            fprintf(logFile, " (%d,%d)", heavens[i].x, heavens[i].y);
        }
        fprintf(logFile, "\nFoods -> ");
        for(int i = 0; i < numFood; i++) {
            fprintf(logFile, " (%d,%d,E:[%d])", foods[i].x, foods[i].y, foods[i].energy);
        }
        fprintf(logFile, "\nBlocks -> ");
        for(int i = 0; i < numBlock; i++) {
            fprintf(logFile, " (%d,%d)", blocks[i].x, blocks[i].y);
        }
        fprintf(logFile, "\nAnimals :\n");
        for(int i = 0; i < numAnimal; i++) {
            fprintf(logFile, "%c.%d -> (%d,%d) : [ Energy : %d | Move energy : %d | Breed energy : %d | Attack : %d | Defence : %d ]\n", animals[i].name, animals[i].logNum, animals[i].x, animals[i].y, animals[i].energy, animals[i].moveEnergy, animals[i].breedEnergy, animals[i].attack, animals[i].defence);
        }
        fprintf(logFile, "---------[ Game Started. ]--------\n");
        break;
    
    case 'm' : //starts moving
        fprintf(logFile, "%c.%d Moved (%d,%d) -> ", animals[animalIndex].name, animals[animalIndex].logNum, x, y);
        break;
    
    case 'M' : // moving ends
        fprintf(logFile, "(%d,%d) dastur\n", x, y);
        break;

    case 'F' : // eat food
        fprintf(logFile, "%c.%d ate food in (%d,%d)\n", animals[animalIndex].name, animals[animalIndex].logNum, x, y);
        break;

    case 'B' : // breed
        fprintf(logFile, "%c.%d breeded with animal in (%d,%d)\n", animals[animalIndex].name, animals[animalIndex].logNum, x, y);
        break;
    
    case 'N' : // new animal
        fprintf(logFile, "An animals was born, %c.%d -> (%d,%d) : [ Energy : %d | Move energy : %d | Breed energy : %d | Attack : %d | Defence : %d ]\n", animals[animalIndex].name, animals[animalIndex].logNum, animals[animalIndex].x, animals[animalIndex].y, animals[animalIndex].energy, animals[animalIndex].breedEnergy, animals[animalIndex].moveEnergy, animals[animalIndex].attack, animals[animalIndex].defence);
        break;

    case 'A' :
        fprintf(logFile, "%c.%d attacked to (%d,%d)\n", animals[animalIndex].name, animals[animalIndex].logNum, x, y);
        break;

    case 'D' : // animal died
        fprintf(logFile, "%c.%d died out.\n", animals[animalIndex].name, animals[animalIndex].logNum);
        break;
    
    case 'H' : // help to another animal
        fprintf(logFile, "%c.%d helped it's friend in (%d,%d)\n", animals[animalIndex].name, animals[animalIndex].logNum, x, y);
        break;

    default:
        break;
    }
}


void clear() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}


void initmap() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = '.';
        }
    }
}


int getInput() {
    FILE* infile;
    infile = fopen("map_phase4.txt", "rt");
    if (!infile) {
        printf("can't open file!");
        return 0;
    }
    fscanf(infile, "%d", &sizeMap);
    char name[5], input[SIZE * SIZE];
    int number;
    name[0] = ' ';
    while (1) {  // heaven and block input
        fscanf(infile, "%s", name);
        if (name[0] == '=') break;
        fscanf(infile, "%d", &number);
        if (number == 0)
            continue;
        fscanf(infile, "%s", input);
        for (int i = 1, j = 0, k = 0; input[i - 1]; i += 5, j++) {
            if (name[0] == '#') {
                numBlock = number;
                blocks[j].x = input[i] - 48;
                if (input[i + 1] <= 58 && input[i + 1] >= 48) {
                    blocks[j].x *= 10;
                    blocks[j].x += input[i + 1] - 48;
                    i++;
                }

                blocks[j].y = input[i + 2] - 48;
                if (input[i + 3] <= 58 && input[i + 3] >= 48) {
                    blocks[j].y *= 10;
                    blocks[j].y += input[i + 3] - 48;
                    i++;
                }

                map[blocks[j].x][blocks[j].y] = name[0];

            } else if (name[0] == 'H') {
                if (k == number) break;
                numHeaven = number;
                heavens[k].x = input[i] - 48;
                if (input[i + 1] <= 58 && input[i + 1] >= 48) {
                    heavens[k].x *= 10;
                    heavens[k].x += input[i + 1] - 48;
                    i++;
                }

                heavens[k].y = input[i + 2] - 48;
                if (input[i + 3] <= 58 && input[i + 3] >= 48) {
                    heavens[k].y *= 10;
                    heavens[k].y += input[i + 3] - 48;
                    i++;
                }
                map[heavens[k].x][heavens[k].y] = name[0];
                k++;
            }

        }
    }

    int energy;
    int j = 0;
    while (1) { //foods

        fscanf(infile, "%s", name);
        if (name[0] == '=') break;
        fscanf(infile, "%d %s", &energy, input);
        foods[j].energy = energy;
        for (int i = 1; input[i]; i += 4) {
            foods[j].x = input[i] - 48;
            if (input[i + 1] <= 58 && input[i + 1] >= 48) {
                foods[j].x *= 10;
                foods[j].x += input[i + 1] - 48;
                i++;
            }

            foods[j].y = input[i + 2] - 48;
            if (input[i + 3] <= 58 && input[i + 3] >= 48) {
                foods[j].y *= 10;
                foods[j].y += input[i + 3] - 48;
                i++;
            }
        }
        map[foods[j].x][foods[j].y] = name[0];
        numFood++;
        j++;
    }

    j = 0;

    while (1) { //animals
        fscanf(infile, "%s", name);
        if (name[0] == '=') break;
        fscanf(infile, "%d %s", &number, input);
        numAnimal += number;
        for (int i = 1; input[i - 1]; i += 5, j++) {
            animals[j].name = name[0];
            animals[j].x = input[i] - 48;
            if (input[i + 1] <= 58 && input[i + 1] >= 48) {
                animals[j].x *= 10;
                animals[j].x += input[i + 1] - 48;
                i++;
            }
            animals[j].y = input[i + 2] - 48;
            if (input[i + 3] <= 58 && input[i + 3] >= 48) {
                animals[j].y *= 10;
                animals[j].y += input[i + 3] - 48;
                i++;
            }
            map[animals[j].x][animals[j].y] = name[0];
        }
    }
    fscanf(infile, " %c", &userAnimal);
    fscanf(infile, "%s", input);
    //moteqaier hay jen
    int moveEnergy, stepNum, breedEnergy, attack, defence;
    while (!feof(infile)) {
        fscanf(infile, "%s %d", name, &energy);
        fscanf(infile, "%d$%d$%d$%d$%d", &moveEnergy, &stepNum, &breedEnergy, &attack, &defence);
        for (int i = 0; i < numAnimal; i++) {
            if (animals[i].name == name[0]) {
                animals[i].energy = energy;
                animals[i].childEnergy = energy;
                animals[i].moveEnergy = moveEnergy;
                animals[i].stepNum = stepNum;
                animals[i].breedEnergy = breedEnergy;
                animals[i].attack = attack;
                animals[i].defence = defence;
                animals[i].logNum = i;
            }
        }
    }
    fclose(infile);
    return 1;
}


void PrintMap(int animalIndex) {
    int AnimalColor = 34;
    clear();
    printf("   ");
    for (int i = 0; i < sizeMap; i++) {
        printf(" %d ", i % 10);
    }
    printf("\n");
    for (int i = 0; i < sizeMap; i++) { // col
        printf(" %d ", i % 10);
        for (int j = 0; j < sizeMap; j++) { // row

            if (map[i][j] == '.')
                printf("\033[1;%d;30m . \033[0m", 42);

            else if (map[i][j] == '#')
                printf(" # ");

            else if (map[i][j] == 'F')
                printf("\033[%d;42m F \033[0m", 33);

            else if (map[i][j] == 'H')
                printf("\033[%d;36m H \033[0m", 43);

            else if (map[i][j] == userAnimal) {
                if (animals[animalIndex].x == i && animals[animalIndex].y == j) printf("\033[31;42m[\033[0m");
                else printf("\033[31;42m \033[0m");
                printf("\033[%d;42m%c\033[0m", AnimalColor, map[i][j]);
                if (animals[animalIndex].x == i && animals[animalIndex].y == j) printf("\033[31;42m]\033[0m");
                else printf("\033[31;42m \033[0m");
            
            } else if (map[i][j] == '%')
                printf("\033[31;42m %c \033[0m", '%');
            
            else
                printf("\033[%d;42m %c \033[0m", 30, map[i][j]);
        }
        printf(" %d \n", i % 10);
    }
    printf("   ");
    for (int i = 0; i < sizeMap; i++) {
        printf(" %d ", i % 10);
    }
    printf("\n");
}


int isDead(int animalIndex) {
    if (animals[animalIndex].energy < animals[animalIndex].moveEnergy) {
        if (animals[animalIndex].energy > 0) {
            map[animals[animalIndex].x][animals[animalIndex].y] = 'F';
            foods[numFood].x = animals[animalIndex].x;
            foods[numFood].y = animals[animalIndex].y;
            foods[numFood].energy = animals[animalIndex].energy;
            numFood++;
        } else {
            map[animals[animalIndex].x][animals[animalIndex].y] = '%';
        }
        if(animals[animalIndex].name == userAnimal)
            humanLog(animalIndex, 'D', 0, 0);
        else {
            humanLog(animalIndex, 'M', animals[animalIndex].x, animals[animalIndex].y);
            humanLog(animalIndex, 'D', 0, 0);
        }
        for (int i = animalIndex; i < numAnimal - 1; i++) {
            animals[i] = animals[i + 1];
        }
        numAnimal--;
        if(curAnim > animalIndex)
            curAnim--;
        return 1;
    } else {
        map[animals[animalIndex].x][animals[animalIndex].y] = animals[animalIndex].name;
        return 0;
    }
}


void eatFood(int animalIndex, int x, int y) {
    int eaten;
    for (int i = 0; i < numFood; i++) {
        if (foods[i].x == x && foods[i].y == y) {
            animals[animalIndex].energy += foods[i].energy;
            eaten = i;
            break;
        }
    }
    humanLog(animalIndex, 'F', x, y);
    for (int i = eaten; i < numFood - 1; i++) {
        foods[i] = foods[i + 1];
    }
    numFood--;
}


int random(int max, int min) {
    if (max == min)
        return min;
    srand(time(0));
    return (rand() % (max - min + 1)) + min;
}


void randomPlace(int x, int y, int animalIndex, int fatherIndex) {
    int places[14][2], placeCounter = 0, ran;
    for (int i = 1; i > -2; i--) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0)
                continue;
            else if (x + i < 0 || x + i >= sizeMap || y + j < 0 || y + j >= sizeMap)
                continue;
            else if (map[x + i][y + j] == '.' && (x + i != animals[fatherIndex].x || y + j != animals[fatherIndex].y)) {
                places[placeCounter][0] = x + i;
                places[placeCounter][1] = y + j;
                placeCounter++;
            } else if (map[animals[fatherIndex].x + i][animals[fatherIndex].y + j] == '.') {
                places[placeCounter][0] = animals[fatherIndex].x + i;
                places[placeCounter][1] = animals[fatherIndex].y + j;
                placeCounter++;
            }
        }
    }
    ran = random(placeCounter - 1, 0);
    animals[animalIndex].x = places[ran][0];
    animals[animalIndex].y = places[ran][1];
}


void breed(int animalIndex) {
    int wifeX, wifeY, wifeIndex;
    for (int i = 1; i > -2; i--) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0)
                continue;
            if (map[animals[animalIndex].x + i][animals[animalIndex].y + j] == animals[animalIndex].name) {
                wifeX = animals[animalIndex].x + i;
                wifeY = animals[animalIndex].y + j;
                break;
            }
        }
    }
    animals[numAnimal].name = animals[animalIndex].name;
    animals[numAnimal].moveEnergy = random(200, 20);
    animals[numAnimal].stepNum = random(3, 1);
    animals[numAnimal].breedEnergy = random(600, 60);
    animals[numAnimal].attack = random(500, 20);
    animals[numAnimal].defence = 500 - random(500, 20) + 20;
    animals[numAnimal].energy = animals[animalIndex].childEnergy;
    animals[numAnimal].childEnergy = animals[animalIndex].childEnergy;
    animals[numAnimal].logNum = lastLog;
    randomPlace(wifeX, wifeY, numAnimal, animalIndex);
    map[animals[numAnimal].x][animals[numAnimal].y] = animals[numAnimal].name;
    animals[animalIndex].energy -= (animals[animalIndex].breedEnergy / 2);
    for (int i = 0; i < numAnimal; i++) {
        if (animals[i].x == wifeX) {
            if (animals[i].y == wifeY) {
                wifeIndex = i;
                break;
            }
        }
    }
    humanLog(animalIndex, 'B', animals[wifeIndex].x, animals[wifeIndex].y);
    humanLog(numAnimal, 'N', animals[numAnimal].x, animals[numAnimal].y);
    animals[wifeIndex].energy -= animals[wifeIndex].breedEnergy / 2;
    numAnimal++;
    lastLog++;
}


void attackAction(int animalIndex) {
    int enemyX, enemyY, enemyIndex;
    for (int i = 1; i > -2; i--) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0)
                continue;
            if (map[animals[animalIndex].x + i][animals[animalIndex].y + j] < 91 && map[animals[animalIndex].x + i][animals[animalIndex].y + j] > 64) {
                if (map[animals[animalIndex].x + i][animals[animalIndex].y + j] != 'H' && map[animals[animalIndex].x + i][animals[animalIndex].y + j] != 'F') {
                    if (map[animals[animalIndex].x + i][animals[animalIndex].y + j] != animals[animalIndex].name) {
                        enemyX = animals[animalIndex].x + i;
                        enemyY = animals[animalIndex].y + j;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < numAnimal; i++) {
        if (animals[i].x == enemyX) {
            if (animals[i].y == enemyY) {
                enemyIndex = i;
                break;
            }
        }
    }
    animals[animalIndex].energy -= animals[animalIndex].moveEnergy * 3;
    if (animals[animalIndex].attack > animals[enemyIndex].defence) {
        animals[animalIndex].energy += animals[enemyIndex].energy;
        animals[enemyIndex].energy = 0;
        isDead(enemyIndex);
        map[enemyX][enemyY] = '%';
    } else {
        animals[enemyIndex].energy += animals[animalIndex].energy;
        animals[animalIndex].energy = 0;
    }
    humanLog(animalIndex, 'A', enemyX, enemyY);
}


void helpToFriend(int animalIndex) {
    char input[SIZE];
    int frndX, frndY, frndIndex;
    if (animals[animalIndex].name == userAnimal) {
        while (1) {
            while (1) {
                printf("\nEnter the row of your friend :\n>> ");
                scanf("%s", input);
                frndX = atoi(input);
                if (frndX > sizeMap || frndX < 0)
                    printf("Out of world! blind.");
                else
                    break;
            }

            while (1) {
                printf("\nEnter the column of your friend :\n>> ");
                scanf("%s", input);
                frndY = atoi(input);
                if (frndY > sizeMap || frndY < 0)
                    printf("Out of world! blind.");
                else
                    break;
            }

            if (map[frndX][frndY] != animals[animalIndex].name)
                printf("It is not coordinates of your friend, try again.\n");
            else
                break;
        }
    } else {
        frndX = animals[animalIndex].goalX;
        frndY = animals[animalIndex].goalY;
    }
    humanLog(animalIndex, 'H', frndX, frndY);
    for (int i = 0; i < numAnimal; i++) {
        if (animals[i].x == frndX) {
            if (animals[i].y == frndY) {
                frndIndex = i;
                break;
            }
        }
    }
    animals[frndIndex].energy += animals[animalIndex].moveEnergy;
}


void afterDecide(int decision, int animalIndex) {
    if(decision <= 9 && decision != 5 && animals[animalIndex].name == userAnimal)
        humanLog(animalIndex, 'm', animals[animalIndex].x, animals[animalIndex].y);
    map[animals[animalIndex].x][animals[animalIndex].y] = '.';
    for (int i = repeatDecide; i > 0; i--) {
        switch (decision) {
        case DL:
            animals[animalIndex].x += 1;
            animals[animalIndex].y -= 1;
            break;

        case DN:
            animals[animalIndex].x += 1;
            break;

        case DR:
            animals[animalIndex].x += 1;
            animals[animalIndex].y += 1;
            break;

        case LT:
            animals[animalIndex].y -= 1;
            break;

        case RT:
            animals[animalIndex].y += 1;
            break;

        case UL:
            animals[animalIndex].x -= 1;
            animals[animalIndex].y -= 1;
            break;

        case UP:
            animals[animalIndex].x -= 1;
            break;

        case UR:
            animals[animalIndex].x -= 1;
            animals[animalIndex].y += 1;
            break;

        case BR:
            if(repeatAI == 1)
                breed(animalIndex);
            break;

        case AT:
            if(repeatAI == 1)
                attackAction(animalIndex);
            break;

        case HL:
            if(i == 1)
                helpToFriend(animalIndex);
            break;

        default:
            break;
        }
        if(i == 1 && animals[animalIndex].name == userAnimal && decision <= 9 && decision != 5) {
            humanLog(animalIndex, 'M', animals[animalIndex].x, animals[animalIndex].y);
        }
        if (map[animals[animalIndex].x][animals[animalIndex].y] == 'H') {
            WIN = 1;
            break;
        }
        if (map[animals[animalIndex].x][animals[animalIndex].y] == 'F') {
            eatFood(animalIndex, animals[animalIndex].x, animals[animalIndex].y);
            map[animals[animalIndex].x][animals[animalIndex].y] = '.';
        }
        if (decision != BR || decision != AT)
            animals[animalIndex].energy -= animals[animalIndex].moveEnergy;
    }
    
    if (!isDead(animalIndex))
        map[animals[animalIndex].x][animals[animalIndex].y] = animals[animalIndex].name;

}


void help() {
    printf("\ntype 1 : down left\n");
    printf("type 2 : down\n");
    printf("type 3 : down right\n");
    printf("type 4 : left\n");
    printf("type 5 : help your friend\n");
    printf("type 6 : right\n");
    printf("type 7 : up left\n");
    printf("type 8 : up\n");
    printf("type 9 : up right\n");
    printf("type 10 : Attack to the adjacent\n");
    printf("type 11 : Breed with the adjacent\n");
    printf("call 118 : information based on coordinates\n");
    printf("call 125 : Save the game\n");
    printf("call 911 : Help\n\n");
    printf("\n      7  8  9\n");
    printf("       \\ | /\n");
    printf("    4 <- U -> 6\n");
    printf("       / | \\\n");
    printf("      1  2  3\n\n");
}

struct heivanat {
    char name;
    int energy;
    int stepNum;
    int moveEnergy;
    int breed;
    int attack;
    int defence;
    int numberSpicie;
};
void accidentalMap () {
    srand(time(0));
    FILE* voroodi;
    voroodi = fopen("map_phase30.txt", "wt");
    int size;
    heivanat heivan[30];
    size = random(50 , 10);
    fprintf(voroodi, "%d\n", size);
    fprintf(voroodi, "#");
    int numberMane = random(20 , 5);
    //int numberMane = 3;

    fprintf(voroodi, " %d ", numberMane);
    int x , y; 
    char newMap[SIZE][SIZE];
    char blackList[SIZE][SIZE];
    int i,j,k;
    for (i = 0 ; i < size ; i++) {
        for (j = 0 ; j < size ; j++) {
            newMap[i][j] = '.';
        }
    }


    for (i = 0 ; i < size ; i++) {
        for (j = 0 ; j < size ; j++) {
            blackList[i][j] = '.';
        }
    }



    // walls
    for (k=0 ; k < numberMane ; k++) {
        x = random(size , 0);
        y = random(size , 0);
        if (newMap[x][y] != '.') {
            k--;
            continue;
        }
        newMap[x][y] = '#';
        fprintf(voroodi, "(%d,%d)", x , y);
    }



    //heavens
    fprintf(voroodi, "\n%c ", 'H');
    int numberHeaven = random(8 , 2);
    //int numberHeaven = 2;
    fprintf(voroodi, "%d ", numberHeaven);
    for (k=0 ; k < numberHeaven ; k++) {
        x = random(size , 0);
        y = random(size , 0);
        if (newMap[x][y] != '.') {
            k--;
            continue;
        }
        newMap[x][y] = 'H';

        fprintf(voroodi, "(%d,%d)", x , y);
    }




    int allAnimal = 0;
    int numberAnimal = random(5 , 2);
    for (i = 0 ; i < numberAnimal ; i++) {
        heivan[i].numberSpicie = random(5 , 2);
        allAnimal += heivan[i].numberSpicie;
    }
    for (i = 0 , j = 0 ; i < numberAnimal && j < 1000 ; i++ , j++) {
        heivan[i].stepNum = random(3, 1);
        heivan[i].breed = random(600, 60);
        heivan[i].attack = random(500, 20);
        heivan[i].defence = random(500, 20);
        heivan[i].energy = random(1500 , 500);
        heivan[i].moveEnergy = random(200 , 50);
        if (heivan[i].numberSpicie == j) {
            j = 0;
            i++;
        }
        i--;
    }


    // maxMoveEnergy
    int maxMoveEnergy;
    for (i = 1 ; i < numberAnimal ; i++) {
        if (heivan[i].moveEnergy >= heivan[i - 1].moveEnergy) {
            maxMoveEnergy = heivan[i].moveEnergy;
        }
    }



    //foods
    int disX , disY , cost;
    fprintf(voroodi, "\n%s\n", "===");
    int numberFood = random(10 , 5);
    //int numberFood = 2;
    int hvnCount;
    int a = numberFood;
    
    for (k=0 ; k < numberFood ; k++) {
        int foodEnergy = random(1000 , 500);
        for (i = 0 ; i < size ; i++) {
            for (j = 0 ; j < size ; j++) {
                if (newMap[i][j] == 'H' && blackList[i][j] != 'H') {
                    cost = foodEnergy / maxMoveEnergy;
                    // disX = random(cost , -cost);
                    // disY = random(cost , -cost);
                    disX = random(cost , -cost);
                    disY = random(cost , -cost);
                    if (disX + i > size || disX + i < 0 || disY + j > size || disY + j < 0) {
                        j--;
                        continue;
                    }
                    x = disX + i;
                    y = disY + j;
                    blackList[i][j] = 'H';
                    hvnCount = a % numberHeaven ;
                    if (hvnCount == 0) {
                        for (int c = 0 ; c < size ; c++) {
                            for (int d = 0 ; d < size ; d++) {
                                blackList[c][d] = '.';
                            }
                        }
                    }
                    if (a == 0) {
                        i = size;
                        j = size;

                    }
                    a--;
                }
            }
        }
        if (newMap[x][y] != '.') {
            k--;
            continue;
        }
        fprintf(voroodi, "%c ", 'F');  
        fprintf(voroodi, "%d ", foodEnergy);
        newMap[x][y] = 'F';
        fprintf(voroodi, "(%d,%d)\n", x , y);
    }



    for (i = 0 ; i < size ; i++) {
        for (j = 0 ; j < size ; j++) {
            blackList[i][j] = '.';
        }
    }


    //heivans
    fprintf(voroodi, "===\n");
    a = allAnimal;
    char name;
    int n; // name
    for (n = 0 ; n < numberAnimal ; n++) {
        name = n + 65;
        fprintf(voroodi, "%c ", name);
        fprintf(voroodi, "%d ", heivan[n].numberSpicie);
        for (k=0 ; k < heivan[n].numberSpicie ; k++) {
            for (i = 0 ; i < size ; i++) {
                for (j = 0 ; j < size ; j++) {
                    if (newMap[i][j] == 'F' || newMap[i][j] == 'H') {
                        if (blackList[i][j] != 'H') {
                            cost = heivan[n].energy / maxMoveEnergy;
                            // disX = random(cost , -cost);
                            // disY = random(cost , -cost);disX = cost;
                            disX = random(cost , -cost);
                            disY = random(cost , -cost);
                            if (disX + i > size || disX + i < 0 || disY + j > size || disY + j < 0) {
                                j--;
                                continue;
                            }
                            x = disX + i;
                            y = disY + j;
                            blackList[i][j] = 'H';
                            hvnCount = a % numberHeaven ;
                            if (hvnCount == 0) {
                                for (int c = 0 ; c < size ; c++) {
                                    for (int d = 0 ; d < size ; d++) {
                                        blackList[c][d] = '.';
                                    }
                                }
                            }
                            if (a == 0) {
                                i = size;
                                j = size;
                        }
                        a--;
                        }
                    }
                }
            }
            if (newMap[x][y] != '.') {
                k--;
                continue;
            }
        newMap[x][y] = name;
        fprintf(voroodi, "(%d,%d)", x , y);
        }
         fprintf(voroodi,"\n");
    }
    


    fprintf(voroodi, "%s\n", "===");
    fprintf(voroodi, "%c", name);
    fprintf(voroodi, "\n%s\n", "===");
    for (i = 0 ; i < numberAnimal ; i++) {
        name = i + 65;
        fprintf(voroodi, "%c ", name);
        fprintf(voroodi, "%d ", heivan[i].energy);
        fprintf(voroodi, "%d$%d$%d$%d$%d\n",heivan[i].moveEnergy, heivan[i].stepNum, heivan[i].breed, heivan[i].attack, heivan[i].defence);
    }


    for (i = 0 ; i < size ; i++) {
        for (j = 0 ; j < size ; j++) {
            printf("%c " , newMap[i][j]);
        }
        printf("\n");
    }

}