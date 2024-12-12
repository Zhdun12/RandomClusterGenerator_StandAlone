/*********************************************************
* REMEMBER TO SET WORKING DIRECTORY TO PROJECT DIRECTORY!*
* Mines will be printed to the file "cords.txt" in the   *
* working directory                                      *
*********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define UPPER 9 // Max. coordinate value
#define TW_UPPER 7 // Max. TW value

typedef struct
{
    unsigned int x; // x-coordinate of mine
    unsigned int y; // y-coordinate of mine
    double tw; // Terrain-weight (coefficient) at mine location
} mine_s;

void GenerateRandomCluster (char* filename);


int main(void){
    char filename[30] = "cords.txt";
    GenerateRandomCluster(filename);

    return EXIT_SUCCESS;
}

void GenerateRandomCluster (char* filename) {

    // Adds a path specifier "src/" to filename
    // The name of the file can be no longer than the "length" in filepath[length]
    char filepath[20];
    sprintf(filepath, "%s", filename);

    // Variable for the number of mines in a cluster
    char mode;
    int NumberOfMines;

    // Input a value for number of mines in a cluster
    printf("Enter the number of mines in your cluster:\n");
    scanf("%d", &NumberOfMines);


    // Prompts user whether TW's is to be included in the output.
    do
    {
        printf("\nInclude TW's (TerrainWeights), (Y/N)?\n");
        scanf(" %c", &mode);
    } while ((mode != 'Y') && (mode != 'N'));


    // Variable for struct of mines based on the variable NumberOfMines
    mine_s mines[NumberOfMines];

    // Generate random numbers
    srand(time(NULL));

    // Assign random values for the x- and y-coordinates in the struct
    for (int i = 0; i < NumberOfMines; ++i) {
        mines[i].x = rand() % (UPPER + 1);
        mines[i].y = rand() % (UPPER + 1);
        do
        {
            mines[i].tw = ((double)rand()/(double)(RAND_MAX)) * TW_UPPER; // Generating random floating point numbers between 0-7
        } while (mines[i].tw < 1); // TW's has to be greater than or equal to 1.0
    }

    // Open a file in write mode,
    // that should write x- and y-coordinates for a cluster of mines
    FILE *fp = fopen(filepath, "w");
    // Checks if the file is open
    if (fp == NULL) {
        printf("Error: Could not open file\n");
        exit(EXIT_FAILURE);
    }

    // Prints the assigned values from the struct into the file that fp is pointing to
    // Which in this case is the one filepath points to which is filename
    if (mode == 'Y')
    {
        for (int i = 0; i < NumberOfMines; ++i) {
            fprintf(fp, "%u %u %.1lf\n", mines[i].x, mines[i].y, mines[i].tw);
        }
    } else if (mode == 'N')
    {
        for (int i = 0; i < NumberOfMines; ++i) {
            if (i == NumberOfMines-1) fprintf(fp, "%u %u", mines[i].x, mines[i].y);
            else fprintf(fp, "%u %u\n", mines[i].x, mines[i].y);
        }
    }

    fclose(fp);
}