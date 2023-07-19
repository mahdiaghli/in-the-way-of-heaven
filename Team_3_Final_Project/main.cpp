#include "zocker.h"

int main() {
    char input[SIZE];
    int userChoice;
    printf("\n\033[35m-----[\033[0m\033[103;35m IN THE WAY OF HEAVEN \033[0m\033[35m]-----\033[0m\n");
    printf("\n\t\033[35m1.\033[0m\033[33m New game\033[0m\t\033[35m|\033[0m\n");
    printf("\n\t\033[35m2.\033[0m\033[33m Load game\033[0m\t\033[35m|\033[0m\n");
    printf("\n\t\033[35m3.\033[0m\033[33m Watch a game\033[0m\t\033[35m|\033[0m\n");
    printf("\n\033[35mChoose one of the above :\033[0m\n");
    while (1) {
        printf(">> ");
        scanf("%s", input);
        userChoice = atoi(input);
        if (userChoice < 1 || userChoice > 3)
            printf("\nWrong number!\n");
        else
            break;
    }
    switch (userChoice) {
        case 1 :
            fopen("PlayBack.txt", "wt");
            startGame(1);
            break;
        
        case 2:
            startGame(2);
            break;

        case 3 :
            watchAGame();
            break;

        default:
            printf("not available now.");
            break;
    }

    return 0;
}