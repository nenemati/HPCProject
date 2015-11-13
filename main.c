#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main (int argc, char * argv []) {

    // check if command-line argument matches.
    if (argc != 2) {
        printf ("\nUsage:\n");
        printf ("$ ./main [file path]\n\n");
        return -1;
    }

    printf ("Input file: %s\n", argv[1]);
    FILE * fd = fopen (argv[1], "r");

    // first line contains number of data and dimension
    int count, dim;
    int out = fscanf (fd, "%d %d\n", &count, &dim);

    printf ("Size=%d Dim=%d\n", count, dim);

    int * data = (int *) malloc (count * dim * sizeof (int));
    int i, j, k; // indice variables
    for (i = 0; i < count; i++) {
        for (j = 0; j < dim - 1; j++) {
            out = fscanf (fd, "%d ", &data[i * dim + j]);
        }
        j = dim - 1;
        out = fscanf (fd, "%d\n", &data[i * dim + j]);
    }


    fclose (fd);
    /*
    For validation use only

    for (i = 0; i < count; i++) {
        for (j = 0; j < dim - 1; j++) {
            printf ("%d ", data[i * dim + j]);
        }
        j = dim - 1;
        printf ("%d\n", data [i * dim + j]);
    }*/

    // dimmensional matrix, keeps the distance between every two points
    double * dimmat = (double *) malloc (count * count * sizeof(double));

    // calculate the distance between every two data points. takes n * n * m time
    for (i = 0; i < count; i++) {
        #pragma omp parallel for
        for (j = 0; j < count; j++) {
            double dist = 0.0;
            for (k = 0; k < dim; k++) {
                int d = data [i * dim + k] - data [j * dim + k];
                dist += d * d;
            }
            dist = sqrt (dist);
            dimmat [i * count + j] = dist;
        }
    }


    // For validation use only
    for (i = 0; i < count; i++) {
        for (j = 0; j < count; j++) {
            printf ("%f ", dimmat [i * count + j]);
        }
        printf ("\n");
    }

    free (data);
    free (dimmat);
    return 0;
}
