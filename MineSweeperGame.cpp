#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLUMNS 11
#define ROWS 11
#define BOMBS_TOTAL 15

int map[COLUMNS][ROWS];        // Map containing all the bomb spots
char shown_map[COLUMNS][ROWS]; // Map shown to the player, containing uncovered squares and surrounding bomb numbers

int bombs_surrounding(int x, int y) {
    int bombs_around = 0;

    // Check all surrounding cells
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) {
                // Skip the current cell itself
                continue;
            }

            int nx = x + dx;
            int ny = y + dy;

            // Check if the neighboring coordinates are within the bounds of the grid
            if (nx >= 0 && nx < COLUMNS && ny >= 0 && ny < ROWS) {
                // Increment the bomb count if a bomb is present
                if (map[nx][ny] == 0) {
                    bombs_around++;
                }
            }
        }
    }

    return bombs_around;
}

void generate_map() {
    // Set all spots to safe (1)
    for (int i = 0; i < COLUMNS; i++) {
        for (int j = 0; j < ROWS; j++) {
            map[i][j] = 1;
        }
    }

    srand(time(NULL));    // Seed RNG
    int bombs_placed = 0; // Places the bombs (0)
    while (bombs_placed < BOMBS_TOTAL) {
        int i = rand() % COLUMNS;
        int j = rand() % ROWS;
        if (map[i][j] != 0) { // Only place a bomb if the spot is currently safe (1)
            map[i][j] = 0;
            bombs_placed++;
        }
    }

    // Initialize the shown map with '*' representing unexplored spots
    for (int i = 0; i < COLUMNS; i++) {
        for (int j = 0; j < ROWS; j++) {
            shown_map[i][j] = '*';
        }
    }
}

void display_map(void) {
    printf("  ");
    for (int i = 0; i < COLUMNS; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%c ", shown_map[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    generate_map();
    int x = 0; // column (i in for)
    int y = 0; // row (j in for)
    int bombs_remaining = BOMBS_TOTAL; // Initializing with the maximum amount of bombs remaining
    int bombs_discovered = 0;          // No bombs have been uncovered so far
    int attempts = 0;                  // Begin with no attempts

    while (bombs_remaining > 0) {
        display_map();
        printf("\nInsert the column number: ");
        scanf("%d", &x);
        printf("Insert the row number: ");
        scanf("%d", &y);
        x--; // Decrement the coordinates as the matrix begins with 0
        y--;

        attempts++;
        if (x < 0 || x >= COLUMNS || y < 0 || y >= ROWS) {
            printf("Invalid coordinates. Try again.\n");
            continue;
        }

        if (map[x][y] == 0) { //bomb 
            shown_map[x][y] = '#'; // Explosion symbol
            display_map();
            printf("\nGame over. The square contains a bomb.\n");
            break; // Ends the game
        } else {
            int surrounding_bombs = bombs_surrounding(x, y);
            shown_map[x][y] = '0' + surrounding_bombs;
            if (surrounding_bombs == 0) {
                shown_map[x][y] = '0 ';
            }
            bombs_remaining--; // Decrement the bombs remaining only if a safe spot is uncovered
        }
    }

    return 0;
}