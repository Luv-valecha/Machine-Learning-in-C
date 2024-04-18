#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h> 

// to have the size of the data
void calculate_csv_shape(char filename[200], int *rows, int *cols)
{

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    // Initialize variables to count rows and columns

    int temp_cols = 0;

    char line[4048];

    // Read the file line by line
    while (fgets(line, sizeof(line), file) != NULL)
    {

        // Split the line by comma to count columns
        char *token = strtok(line, ",");
        temp_cols = 0;

        while (token != NULL)
        {
            temp_cols++;
            token = strtok(NULL, ",");
        }

        // If this is the first line, count the number of columns
        if (*rows == 0)
        {
            *cols = temp_cols;
        }

        // Increment the number of rows
        (*rows)++;
    }
    // printf("shape calulation end\n");
    fclose(file);
}

// csv file data loading
// csv file data loading
float **load_data(char filename[200], int *rows, int *cols)
{
    // first find the shape of the data
    calculate_csv_shape(filename, rows, cols);

    int n = *rows, m = *cols;

    FILE *df = fopen(filename, "r");

    if (df == NULL)
    {
        printf("Data can't loaded right now. better luck next time\n");
        return NULL;
    }

    // Allocate memory for the 2D array
    float **loaded_data = malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++)
    {
        loaded_data[i] = malloc(m * sizeof(float));
    }

    // Load the data from file to the 2D array
    char line[4096];
    for (int i = 0; i < n; i++)
    {
        if (fgets(line, sizeof(line), df) != NULL)
        {
            char *token = strtok(line, ",");
            for (int j = 0; j < m && token != NULL; j++)
            {
                loaded_data[i][j] = atof(token);
                token = strtok(NULL, ",");
            }
        }
        else
        {
            printf("Error reading data from file.\n");
            fclose(df);
            return NULL;
        }
    }

    // Close the file
    fclose(df);

    // Return the pointer to the loaded data
    return loaded_data;
}

// function to get the target names
float *get_targets(char filename[200])
{
    int n = 0, m = 0;

    float **data = load_data(filename, &n, &m);

    // memory allocation
    float *targets = (float *)malloc(n * sizeof(float));
    if (targets == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    for (int i = 0; i < n; i++)
    {

        targets[i] = data[i][m - 1];
    }
    free(data);

    return targets;
}

//function to print graph for linear regression
void graph(char filename[200]) {
    FILE *gp = popen("gnuplot -persist", "w");
    FILE *fptr = fopen(filename, "r");

    if (fptr == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    // Skip the first line (header)
    char header[100];
    fgets(header, sizeof(header), fptr);

    if (gp == NULL) {
        printf("Error: Could not open pipe to Gnuplot.\n");
        fclose(fptr);
        return;
    }

    fprintf(gp, "set xlabel 'X'\n");
    fprintf(gp, "set ylabel 'Y'\n");
    fprintf(gp, "plot %s skip 1 with points point type 7 pointsize 1 lc rgb 'red'\n",filename);

    fflush(gp);
    fprintf(gp, "exit\n");

    pclose(gp);
    fclose(fptr);
}