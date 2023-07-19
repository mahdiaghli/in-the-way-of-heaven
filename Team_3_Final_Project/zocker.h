#include "hatefi.h"

void saveGame();
int loadGame();

void printUserInfo(int animalIndex) {
    printf("\nYour\nEnergy =\t[ %d\t]\t      7  8  9\n", animals[animalIndex].energy);
    printf("Move energy =\t[ %d\t]\t       \\ | /\n", animals[animalIndex].moveEnergy);
    printf("Breed energy =\t[ %d\t]\t    4 <- U -> 6\n", animals[animalIndex].breedEnergy);
    printf("Attack power =\t[ %d\t]\t       / | \\\n", animals[animalIndex].attack);
    printf("Defence power =\t[ %d\t]\t      1  2  3\n\n", animals[animalIndex].defence);
}


void infoByCoordinates() {
    int x, y;
    char target, input[SIZE];
    printf("\nEnter the Coordinates you want information about.\nFirst enter row number or -1 to finish :\n");
    while (1) {
        printf(">> ");
        scanf("%s", input);
        x = atoi(input);
        if (x < 0)
            return;
        else if (x >= sizeMap)
            printf("\nOut of world!\n");
        else
            break;
    }
    printf("\nEnter column number :\n");
    while (1) {
        printf(">> ");
        scanf("%s", input);
        y = atoi(input);
        if (y < 0)
            return;
        else if (y >= sizeMap)
            printf("\nOut of world!\n");
        else
            break;
    }
    while (1) {
        target = map[x][y];
        switch (target) {
        case '.':
            printf("\nHere's \033[1;42;30mgrass\033[0m and maybe some insects.\n");
            break;

        case 'H':
            printf("\nHere is the \033[43;36mfabulous heaven!\033[0m.\n");
            break;

        case 'F':
            int foodIndex;
            for (int i = 0; i < numFood; i++) {
                if (foods[i].x == x) {
                    if (foods[i].y == y) {
                        foodIndex = i;
                        break;
                    }
                }
            }
            printf("\nSome \033[33;42mdelicious food\033[0m with ( %d ) energy.\n", foods[foodIndex].energy);
            break;

        case '#':
            printf("\nAn Impenetrable wall made of stone is here.\n");
            break;

        case '%':
            printf("\nThere is a \033[41;37mCorpse\033[0m here.\n");
            break;

        default:
            int animalIndex;
            for (int i = 0; i < numAnimal; i++) {
                if (animals[i].x == x) {
                    if (animals[i].y == y) {
                        animalIndex = i;
                        break;
                    }
                }
            }
            printf("\nan animal.\nSpecie : %c\n", animals[animalIndex].name);
            printf("Energy =\t[ %d\t]\n", animals[animalIndex].energy);
            printf("Move energy =\t[ %d\t]\n", animals[animalIndex].moveEnergy);
            printf("Breed energy =\t[ %d\t]\n", animals[animalIndex].breedEnergy);
            printf("Attack power =\t[ %d\t]\n", animals[animalIndex].attack);
            printf("Defence power =\t[ %d\t]\n\n", animals[animalIndex].defence);
            break;
        }
        printf("\nEnter next row number or -1 to finish :\n");
        while (1) {
            printf(">> ");
            scanf("%s", input);
            x = atoi(input);
            if (x < 0)
                return;
            else if (x >= sizeMap)
                printf("\nWrong number!\n");
            else
                break;
        }
        printf("\nEnter next column number :\n");
        while (1) {
            printf(">> ");
            scanf("%s", input);
            y = atoi(input);
            if (y < 0)
                return;
            else if (y >= sizeMap)
                printf("\nWrong number!\n");
            else
                break;
        }
    }
}


void stepCounter(int animalIndex) {
    if (animals[animalIndex].energy < animals[animalIndex].moveEnergy) {
        repeatDecide = 1;
        return;
    }
    printUserInfo(animalIndex);
    int step = animals[animalIndex].stepNum;
    char input[SIZE];
    int possibleSteps = 0;
    printf("\n\tpossible steps :");
    for (; step > 0; step--) {
        if (animals[animalIndex].moveEnergy * step <= animals[animalIndex].energy) {
            possibleSteps++;
            printf(" %d ", step);
        }
    }
    printf("\n\t--------! Call 911 for HELP !--------\n");
    printf("\t-----! Call 118 for information !----\n");
    printf("\t----! Call 125 to save the game. !---\n");
    if (possibleSteps == 0)
        return;
    printf("\n");
    while (1) {
        printf(">> ");
        scanf("%s", input);
        repeatDecide = atoi(input);
        if (repeatDecide == 118) {
            infoByCoordinates();
            printf("Enter you're step number :\n");
        } else if (repeatDecide == 125) {
            saveGame();
            printf("Saved!.\n");
        } else if (repeatDecide == 911)
            help();
        else if (repeatDecide > possibleSteps || repeatDecide < 1) {
            printf("you're jene is not that good!\n");
        } else
            break;
    }
}


void getUserMove(int moves[], int animalIndex) {
    PrintMap(animalIndex);
    printUserInfo(animalIndex);
    int move, possibles = 0;
    char input[SIZE];
    int possibleFlag = 1;
    if (animals[animalIndex].moveEnergy * repeatDecide > animals[animalIndex].energy) {
        for (int i = 0; i < 10; i++) {
            moves[i] = 0;
        }
        possibleFlag = 0;
    }
    if (animals[animalIndex].energy < animals[animalIndex].breedEnergy) {
        moves[11] = 0;
    }

    if (possibleFlag || moves[11])
        printf("\n\tPossible moves:  ");
    for (int i = 0; i < 15; i++) {
        if (moves[i]) {
            printf("  %d  ", i);
            possibles++;
        }
    }
    if (!possibles) {
        printf("\n\nSorry, you silly can not move now, wait till the next round!\n\n");
        sleep(4);
        return;
    }
    printf("\n\t--------! Call 911 for HELP !--------\n");
    printf("\t-----! Call 118 for information !----\n");
    printf("\t------! Call 125 to save game. !-----\n");
    while (1) {
        printf(">> ");
        scanf("%s", input);
        move = atoi(input);
        if (move == 911) {
            help();
            continue;
        } else if (move == 118) {
            infoByCoordinates();
            printf("\nEnter your move :\n");
            continue;
        } else if (move == 125) {
            saveGame();
            printf("Saved!\n");
        } else if (move > 11 || move < 0) {
            printf("Impossible move!! stupid.\n");
        } else if (!moves[move]) {
            printf("Impossible move!! idiot.\n");
        } else break;
    }

    afterDecide(move, animalIndex);
}


void beforeMove(int animalIndex) {
    if (isDead(animalIndex))
        return;
    int moves[15] = { 0 };
    int curPos = 1, moveNum;
    int x = animals[animalIndex].x;
    int y = animals[animalIndex].y;
    int j_iPlus = 1, startI = 1, startJ = -1;
    repeatDecide = 1;
    if (animals[animalIndex].name == userAnimal) {
        PrintMap(animalIndex);
        stepCounter(animalIndex);
        for (int i = repeatDecide; i > 0; i--) {
            curPos = 1;
            for (int i = startI; i > -(j_iPlus + 1); i -= j_iPlus) { // y
                for (int j = startJ; j < j_iPlus + 1; j += j_iPlus) { // x

                    if (curPos == 5) {
                        curPos++;
                        continue;
                    }

                    moveNum = 1;
                    if (moves[curPos] && j_iPlus != 1) {
                        moves[BR] = 0;
                        moves[AT] = 0;
                        if (x + i < 0 || x + i >= sizeMap || y + j < 0 || y + j >= sizeMap) { // az bazi kharej mishe
                            moveNum = 0;
                        } else if (map[i + x][y + j] == '#') { // mane
                            moveNum = 0;
                        } else if (map[i + x][y + j] == animals[animalIndex].name) { // heyvoon hamno
                            moveNum = 0;
                        } else if (map[i + x][y + j] > 64 && map[i + x][y + j] < 91 && map[i + x][y + j] != 'H' && map[i + x][y + j] != 'F') { // heyvoon ghyr hamno
                            moveNum = 0;
                        }
                        if (map[i + x][y + j] == 'H' || map[i + x][y + j] == 'F') {
                            moveNum = 1;
                        }
                    } else if (j_iPlus == 1) {
                        if (x + i < 0 || x + i >= sizeMap || y + j < 0 || y + j >= sizeMap) { // az bazi kharej mishe
                            moveNum = 0;
                        } else if (map[i + x][y + j] == '#') { // mane
                            moveNum = 0;
                        } else if (map[i + x][y + j] == animals[animalIndex].name) { // heyvoon hamno
                            moveNum = 0;
                            if (animals[animalIndex].energy > animals[animalIndex].breedEnergy)
                                moves[BR] = 1;
                        } else if (map[i + x][y + j] > 64 && map[i + x][y + j] < 91 && map[i + x][y + j] != 'H' && map[i + x][y + j] != 'F') { // heyvoon ghyr hamno
                            moveNum = 0;
                            moves[AT] = 1;
                        }
                        if (map[i + x][y + j] == 'H' || map[i + x][y + j] == 'F') {
                            moveNum = 1;
                        }
                    } else
                        moveNum = 0;

                    moves[curPos] = moveNum;
                    curPos++;
                }
            }
            startJ--;
            startI++;
            j_iPlus++;
        }

    } else {
        // Az khone adad 1 (chap payin) shoro be barasi mikone
        for (int i = startI; i > -2; i -= j_iPlus) { // y
            for (int j = startJ; j < 2; j += j_iPlus) { // x

                if (curPos == 5) {
                    curPos++;
                    continue;
                }

                moveNum = 1;

                if (x + i < 0 || x + i >= sizeMap || y + j < 0 || y + j >= sizeMap) { // az bazi kharej mishe
                    moveNum = 0;
                } else if (map[i + x][y + j] == '#') { // mane
                    moveNum = 0;
                } else if (map[i + x][y + j] == animals[animalIndex].name) { // heyvoon hamno
                    moveNum = 0;
                    moves[BR] = 1;
                } else if (map[i + x][y + j] > 64 && map[i + x][y + j] < 91 && map[i + x][y + j] != 'H' && map[i + x][y + j] != 'F') { // heyvoon ghyr hamno
                    moveNum = 0;
                    moves[AT] = 1;
                }

                if (map[i + x][y + j] == 'H' || map[i + x][y + j] == 'F') {
                    moveNum = 1;
                }

                moves[curPos] = moveNum;
                curPos++;
            }
        }
    }
    //braye komak kardan
    int sameSpecie = 0;
    for (int i = 0; i < numAnimal; i++) {
        if (animals[i].name == animals[animalIndex].name) {
            sameSpecie++;
        }
    }
    if (sameSpecie > 1)
        moves[HL] = 1;

    if (animals[animalIndex].name == userAnimal) {
        getUserMove(moves, animalIndex);
    } else {
        systemDecide(moves, animalIndex);
    }
}


void startGame(int c) {
    int roundCounter = 1;
    if(c != 2)
        intro();
    initmap();
    if (c == 1) {
        if (getInput() == 0)
            return;
    } else if (c == 2) {
        if (loadGame() == 0)
            if (getInput() == 0)
                return;
    }
    fopen("HumanLog.txt", "wt");
    humanLog(0,'S', 0, 0);
    lastLog = numAnimal;
    for (int i = 0; i < numAnimal; i++) {
        wayFinder(i);
    }

    PrintMap(0);
    printPlayBack();
    help();
    printf("\nsay something if you're ready...\n");
    scanf("%s", starter);

    for (curAnim = 0; ; curAnim++) {
        if (numAnimal == 0) {
            PrintMap(0);
            printf("\nseriously? You all died stupids? shame on you.\nGoodBye.\n\n");
            break;
        }
        beforeMove(curAnim);
        if (WIN) {
            PrintMap(0);
            printPlayBack();
            if (animals[curAnim].name == userAnimal) {
                printf("\nYOU were lucky, you arrived to heaven and made your specie Immortal!\n\n");
            } else {
                printf("\nAnimal %c arrived to heaven and made it's specie Immortal!\n\n", animals[curAnim].name);
            }
            break;
        }
        PrintMap(curAnim);
        printPlayBack();
        if ((curAnim) == numAnimal - 1) {
            printf("\n\tend of round %d.\n", roundCounter);
            roundCounter++;
            sleep(endOfRoundTIME);
        }
        if (curAnim == numAnimal - 1)
            curAnim = -1;
    }
    return;
}


void saveGame() {
    FILE* outputFile;
    outputFile = fopen("save.txt", "w");

    // Print Map Size
    fprintf(outputFile, "%d\n", sizeMap);

    // Print Block & Heaven
    fprintf(outputFile, "# %d ", numBlock);
    for (int i = 0; i < numBlock; i++) {
        fprintf(outputFile, "(%d,%d)", blocks[i].x, blocks[i].y);
    }
    fprintf(outputFile, "\n");

    fprintf(outputFile, "H %d ", numHeaven);
    for (int i = 0; i < numHeaven; i++) {
        fprintf(outputFile, "(%d,%d)", heavens[i].x, heavens[i].y);
    }
    fprintf(outputFile, "\n");
    fprintf(outputFile, "===\n");

    // Print Foods
    for (int i = 0; i < numFood; i++) {
        fprintf(outputFile, "F %d (%d,%d)\n", foods[i].energy, foods[i].x, foods[i].y);
    }
    fprintf(outputFile, "===\n");

    // Print Animals
    for (int i = 0; i < numAnimal; i++) {
        fprintf(outputFile, "%c (%d,%d) %d %d$%d$%d$%d$%d\n", animals[i].name, animals[i].x, animals[i].y, animals[i].energy, animals[i].moveEnergy, animals[i].stepNum, animals[i].breedEnergy, animals[i].attack, animals[i].defence);
    }

    fprintf(outputFile, "===\n");

    // Print User Animal
    fprintf(outputFile, "%c\n", userAnimal);

    fclose(outputFile);
}


int loadGame() {

    FILE* infile;
    infile = fopen("save.txt", "r");
    if (!infile) {
        printf("no saved game found!");
        sleep(2);
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
    int moveEnergy, stepNum, breedEnergy, attack, defence;

    while (1) { //animals
        fscanf(infile, "%s", name);
        if (name[0] == '=') break;
        fscanf(infile, "%s %d %d$%d$%d$%d$%d", input, &energy, &moveEnergy, &stepNum, &breedEnergy, &attack, &defence);
        for (int i = 1; input[i - 1]; i += 5) {
            animals[numAnimal].x = input[i] - 48;
            if (input[i + 1] <= 58 && input[i + 1] >= 48) {
                animals[numAnimal].x *= 10;
                animals[numAnimal].x += input[i + 1] - 48;
                i++;
            }
            animals[numAnimal].y = input[i + 2] - 48;
            if (input[i + 3] <= 58 && input[i + 3] >= 48) {
                animals[numAnimal].y *= 10;
                animals[numAnimal].y += input[i + 3] - 48;
                i++;
            }
            map[animals[numAnimal].x][animals[numAnimal].y] = name[0];
        }

        animals[numAnimal].name = name[0];
        animals[numAnimal].energy = energy;
        animals[numAnimal].childEnergy = energy;
        animals[numAnimal].moveEnergy = moveEnergy;
        animals[numAnimal].stepNum = stepNum;
        animals[numAnimal].breedEnergy = breedEnergy;
        animals[numAnimal].attack = attack;
        animals[numAnimal].defence = defence;

        numAnimal++;
    }

    fscanf(infile, " %c", &userAnimal);

    fclose(infile);
    return 1;
}