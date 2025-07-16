#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 9

/**
 * @brief Reads a Latin square from a file.
 * 
 * @param fp File pointer to the input file.
 * @param n Size of the Latin square.
 * @param square 2D array to store the Latin square.
 * @return int Returns 0 if successful, 1 if there is an error.
 */
int readLatinSquare(FILE *fp, short n, short square[n][n]) {
    short num;
    int count = 0;
    if (N < n) {
        perror("N number cannot be above 9\n");
        exit(-1);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(fp, "%hd", &num) != 1) {
                perror("Error reading number\n");
                return 1;
            }if (abs(num) > n) {
                perror("File contains invalid values!\n");
                return 1;
            }
            square[i][j] = num;
            count++;
        }
    }
    
    // Check if there are extra numbers in the file
    short extra;
    if (fscanf(fp, "%hd", &extra) == 1) {
        perror("File contains more data than expected!\n");
        return 1;
    }
    
    fclose(fp);
    return 0;
}

/**
 * @brief Writes the Latin square to a file with "out-" prefixed to the filename.
 * 
 * @param n Size of the Latin square.
 * @param arr 2D array containing the Latin square.
 * @param filename Original filename to which "out-" will be prefixed.
 */
void writeLatinSquare(int n, short arr[n][n], const char *filename) {
    // Write the Latin square to the file
    FILE *fp;
    char newFilename[256];
    snprintf(newFilename, sizeof(newFilename), "out-%s", filename);
    fp = fopen(newFilename, "w");
    if (fp == NULL) {
        perror("Error opening file\n");
        exit(-1);
    }
    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(fp, "%d ", arr[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("Saving to out-lsq1.txt...\n");
    printf("Done\n");
}

/**
 * @brief Displays the Latin square puzzle.
 * 
 * @param n Size of the Latin square.
 * @param puzzle 2D array containing the Latin square.
 */
void displayLatinSquare(short n, short puzzle[n][n]) {
    int i, j;
    for (i = 0; i < n; i++) {
        printf("+");
        for (j = 0; j < n; j++) {
            printf("-----+");
        }
        printf("\n");

        for (j = 0; j < n; j++) {
            printf("|");
            if (puzzle[i][j] == 0) {
                printf("  0  ");
            } else if (puzzle[i][j] < 0) {
                printf("(%2d )", abs(puzzle[i][j]));
            } else {
                printf(" %2d  ", puzzle[i][j]);
            }
        }
        printf("|\n");
    }
    printf("+");
    for (j = 0; j < n; j++) {
        printf("-----+");
    }
    printf("\n");
}

/**
 * @brief Prints instructions for entering commands.
 * 
 * @param n Size of the Latin square.
 */
void printInstructions(int n) {
    printf("Enter your command in the following format:\n");
    printf("+ i,j=val: for entering val at position (i,j)\n");
    printf("+ i,j=0 : for clearing cell (i,j)\n");
    printf("Notice: i,j,val numbering is from [1..%d]\n", n);
}

/**
 * @brief Checks if the Latin square is valid.
 * 
 * @param n Size of the Latin square.
 * @param arr 2D array containing the Latin square.
 * @return int Returns 1 if the Latin square is valid, 0 otherwise.
 */
int check(int n, short arr[n][n]) {
    int counter, number;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == 0) {
                return 0;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            counter = 0;
            number = abs(arr[i][j]);
            if (number != 0) {
                for (int k = 0; k < n; k++) {
                    if (abs(arr[i][k]) == number) {
                        counter++;
                    }
                }
            }
            if (counter > 1) {
                return 0; // Return 1 if duplicates are found
            }
        }
    }
    number = 0;
    counter = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            counter = 0;
            number = abs(arr[i][j]);
            if (number != 0) {
                for (int k = 0; k < n; k++) {
                    if (abs(arr[k][j]) == number) {
                        counter++;
                    }
                }
            }
            if (counter > 1) {
                return 0; // Return 1 if duplicates are found
            }
        }
    }
    return 1;
}

/**
 * @brief Plays the Latin square puzzle game.
 * 
 * @param n Size of the Latin square.
 * @param arr 2D array containing the Latin square.
 * @param filename Original filename to which "out-" will be prefixed.
 */
void play(int n, short arr[n][n], const char *filename) {
    int i, j, val;
    displayLatinSquare(n, arr);
    do {
        printInstructions(n);
        if (scanf("%d,%d=%d", &i, &j, &val) != 3) {
            while (getchar() != '\n') {};
            printf("Error: wrong format of command!\n");
            displayLatinSquare(n, arr);
        }
            else if (i == 0 && j == 0 && val == 0) {
                writeLatinSquare(n, arr, filename);
                exit(-1);
        } else if (i < 1 || i > n || j < 1 || j > n) {
            printf("Error: i,j or val are outside the allowed range [1..4]!\n");
            displayLatinSquare(n, arr);
        } else if (val < 0 || val > n) {
            printf("Illegal value insertion!\n");
            displayLatinSquare(n, arr);
        } else if (arr[i - 1][j - 1] < 0) {
            printf("Error: illegal to clear cell!\n");
            displayLatinSquare(n, arr);
        } else if (arr[i - 1][j - 1] > 0 && arr[i - 1][j - 1] < n && val != 0) {
            printf("Error: cell is already occupied!\n");
            displayLatinSquare(n, arr);
        } else {
            arr[i - 1][j - 1] = val;
            printf("Value inserted!\n");
            displayLatinSquare(n, arr);
        }
    } while (check(n, arr) == 0);
    writeLatinSquare(n, arr, filename);
    printf("Game completed!!!\n");
    displayLatinSquare(n, arr);
}

/**
 * @brief Main function to read the Latin square from a file and start the game.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Returns 0 if successful, 1 if there is an error.
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Missing arguments\n");
        fprintf(stderr, "Usage: %s <game-file>\n", argv[0]);
        return 1;
    }
    FILE *fp;
    int num, sum = 0;
    int n = 0;
    char *filename = argv[1];
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("unable to open file");
        exit(-1);
    }
    fscanf(fp, "%d", &n);
    short array[n][n];
    if (fp == NULL) {
        perror("unable to open file");
        exit(-1);
    }
    int ep = readLatinSquare(fp, n, array);
    if (ep == 1) {
        exit(-1);
    }
    play(n, array, filename);
}
