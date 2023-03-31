 #include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAP_Y_SIZE 25
#define MAP_X_SIZE 80

char **alloc_matrix(char **);
char **dealloc_matrix(char **);
int file_open(char **);
void output(char **);
void game_logic(char **, char **);

int main() {
    int check = 0;
    char **map = NULL;
    char **secondMap = NULL;
    int game_speed = 20000;
    char user_input;

    map = alloc_matrix(map);
    secondMap = alloc_matrix(secondMap);
    if (map != NULL && secondMap != NULL) {
        if (file_open(map) != 1) {
            printf("File opening error");
            check = 1;
        } else {
            initscr();
            noecho();
            nodelay(stdscr, true);
        
            while ((user_input = getch()) != 113) {
                if (user_input == 45) game_speed *= 1.5;
                if (user_input == 43) game_speed *= 0.5;
                clear();
                output(map);
                game_logic(map, secondMap);
                usleep(game_speed);
            }
        
            endwin();
        
            dealloc_matrix(map);
            dealloc_matrix(secondMap);
        }
    } else printf("n/a");
    return check;
}

char **alloc_matrix(char **map) {
    map = malloc(MAP_Y_SIZE * sizeof(char *));
    for (int i = 0; i < MAP_Y_SIZE; i++) {
        map[i] = malloc(MAP_X_SIZE * sizeof(char));
    }

    return map;
}

char **dealloc_matrix(char **map) {
    for (int i = 0; i < MAP_Y_SIZE; i++) {
        free(map[i]);
    }

    free(map);
    return 0;
}

int file_open(char **map) {
    int bufferLength = MAP_X_SIZE + 2;
    char buf[bufferLength];
    int check = 0;

    int i = 0;
    while (fgets(buf, bufferLength, stdin) && i < MAP_Y_SIZE) {
        for (int j = 0; j < MAP_X_SIZE; j++) {
            map[i][j] = buf[j];
        }
        i++;
    }

    if (i == MAP_Y_SIZE) {
        check = 1;
    }

    FILE *fl = freopen("/dev/tty", "r", stdin);
    if (fl == NULL) {
        printf("Hello Staff!");
        check = 1;
    }
    return check;
}

void output(char **map) {
    for (int i = 0; i < MAP_Y_SIZE; i++) {
        int j;
        for (j = 0; j < MAP_X_SIZE - 1; j++) {
            addch(map[i][j]);
        }
        addstr("\n");
    }
    refresh();
}

void game_logic(char **map, char **secondMap) {
    int count;
    int firstOperation, secondOperation, thirdOperation, fourthOperation;
    for (int i = 0; i < MAP_Y_SIZE; i++) {
        for (int j = 0; j < MAP_X_SIZE; j++) {
            count = 0;

            firstOperation = (i - 1 >= 0) ? (i - 1) : (MAP_Y_SIZE - 1);
            secondOperation = ((i + 1) <= (MAP_Y_SIZE - 1)) ? (i + 1) : 0;
            thirdOperation = (j - 1 >= 0) ? (j - 1) : (MAP_X_SIZE - 1);
            fourthOperation = ((j + 1) <= (MAP_X_SIZE - 1)) ? (j + 1) : 0;

            if (map[firstOperation][j] == '*') count++;                 // Верхний
            if (map[firstOperation][thirdOperation] == '*') count++;    // Верхний левый
            if (map[firstOperation][fourthOperation] == '*') count++;   // Верхний правый
            if (map[i][thirdOperation] == '*') count++;                 // Левый
            if (map[i][fourthOperation] == '*') count++;                // Правый
            if (map[secondOperation][j] == '*') count++;                // Нижний
            if (map[secondOperation][thirdOperation] == '*') count++;   // Нижний левый
            if (map[secondOperation][fourthOperation] == '*') count++;  // Нижний правый

            if (map[i][j] == '*' && count < 2)
                secondMap[i][j] = ' ';
            else if (map[i][j] == '*' && (count == 2 || count == 3))
                secondMap[i][j] = '*';
            else if (map[i][j] == '*' && count > 3)
                secondMap[i][j] = ' ';
            else if (map[i][j] == ' ' && count == 3)
                secondMap[i][j] = '*';
            else {
                secondMap[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < MAP_Y_SIZE; i++) {
        for (int j = 0; j < MAP_X_SIZE; j++) {
            map[i][j] = secondMap[i][j];
        }
    }
}
