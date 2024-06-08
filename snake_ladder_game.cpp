#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h> // for usleep()

int colm = 30, row = 30; // global variables to use globally
int x, y, food_X, food_Y, game_over, score; // for snake, food, and score
int flag; // used in key_check() to check condition
int tailX[100], tailY[100];
int CountTail = 0; // used to increase snake length when it eats food

void set_up() { // to set the location of every element
    game_over = 0; // when the game is over or draw, the value becomes 1
    x = row / 2;
    y = colm / 2; // set the snake in the middle of the boundaries
    score = 0;
    flag = 0;
    CountTail = 0;
    // Initialize random seed
    srand(time(0));
    // For X:
    food_X = rand() % (row - 2) + 1;
    // For Y:
    food_Y = rand() % (colm - 2) + 1;
}

void boundary() { // to make outerline
    int i, j;
    system("cls"); // to clear the previous screen
    for (i = 0; i < row; i++) { // outer loop for row i.e. width
        for (j = 0; j < colm; j++) { // inner loop for column i.e. height
            if (i == 0 || i == row - 1 || j == 0 || j == colm - 1) { // here we take height-1 and row-1 because i start from 0
                printf("*"); // printing star
            } else {
                if (i == x && j == y) { // checking the position of the snake
                    printf("O");
                } else if (i == food_X && j == food_Y) { // checking the location of food_XY for generating the food
                    printf("F");
                } else {
                    int ch = 0;
                    for (int k = 0; k < CountTail; k++) {
                        if (i == tailX[k] && j == tailY[k]) {
                            printf("o"); // adding the segment according to condition
                            ch = 1;
                        }
                    }
                    if (ch == 0) { // if ch is 0 then print gap
                        printf(" "); // printing gap after 1st line and before last line
                    }
                }
            }
        }
        printf("\n"); // for next line
    }
}

void input_key_check() { // to check which key is pressed
    if (kbhit()) { // when we press any key it becomes true and gets into the if condition
        switch (getch()) { // we use getch() to get the char. which we press and check it
            case 'a': // a for left
                flag = 1;
                break;
            case 'd': // d for right
                flag = 2; // use switch cases to check which key is pressed by the user
                break;
            case 'w': // w for up
                flag = 3;
                break;
            case 's': // s for down
                flag = 4;
                break;
            case 'x': // to exit the game
                game_over = 1;
                break;
        }
    }
}

void game_logic() { // main logic for the game
    int i;
    int preX = tailX[0]; // storing the segment
    int preY = tailY[0];
    int pre2X, pre2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (i = 1; i < CountTail; i++) {
        pre2X = tailX[i];
        pre2Y = tailY[i]; // changing the location
        tailX[i] = preX;
        tailY[i] = preY;
        preX = pre2X;
        preY = pre2Y;
    }

    switch (flag) {
        case 1:
            y--; // to move left
            break;
        case 2:
            y++; // to move right
            break;
        case 3:
            x--; // to move up
            break;
        case 4:
            x++; // to move down
            break;
        default:
            break;
    }

    if (x <= 0 || x >= row - 1 || y <= 0 || y >= colm - 1) { // when the snake touches the outer boundary
        game_over = 1;
    }

    for (i = 0; i < CountTail; i++) {
        if (x == tailX[i] && y == tailY[i]) {
            game_over = 1;
        }
    }

    if (x == food_X && y == food_Y) { // to generate food again
        score += 10;
        CountTail++; // increasing the length
        food_X = rand() % (row - 2) + 1;
        food_Y = rand() % (colm - 2) + 1;
    }
}

int main() {
    char c;
    do {
        set_up();
        while (!game_over) { // to run the below functions according to the 1/0 i.e. T/F if(game_over is == 1) then exit
            boundary();
            input_key_check();
            game_logic();

            // to maintain the speed of the snake
            usleep(150000); // 150000 microseconds = 150 milliseconds
        }
        printf("--- GAME OVER ---\n");
        printf("SCORE = %d\n", score);
        printf("Press Y to continue again: ");
        fflush(stdin); // Clear the input buffer
        c = getchar();
    } while (c == 'Y' || c == 'y');
    return 0;
}
