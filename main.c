#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#include "my_timer.h"

// structure for storing data point and distance together
typedef struct {
        int p;
        double dist;
} Distance;

// generate Distance array for data point at idx
Distance * ptrdist (double * dist, int count, int idx) {
        Distance * d = (Distance *) malloc (sizeof(Distance) * count);
        int i = 0;
        #pragma omp parallel for
        for (i = 0; i < count; i++) {
                d[i].p = i;
                d[i].dist = dist[count * idx + i];
        }
        return d;
}

// comparison function for qsort use
int comparator (const void * v1, const void * v2) {
        const Distance * d1 = (Distance *) v1;
        const Distance * d2 = (Distance *) v2;
        if (d1->dist > d2->dist) {
                return 1;
        } else if (d1->dist < d2->dist) {
                return -1;
        } else {
                return 0;
        }
}

int main (int argc, char * argv []) {


        // check if command-line argument matches.
        if (argc != 3) {
                printf ("\nUsage:\n");
                printf ("$ ./main [file path] [k]\n\n");
                return -1;
        }

        // verify input file
        printf ("Input file: %s\n", argv[1]);
        FILE * fd = fopen (argv[1], "r");
        int K = atoi (argv[2]);

        int count, dim;  // first line contains number of data and dimension
        int i, j, k; // indice variables
        int out = fscanf (fd, "%d %d\n", &count, &dim);

        // check if file reading has problem
        if (out == EOF) {
                fputs ("File reading error. Process terminates.", stderr);
                return -1;
        }

        printf ("Size=%d Dim=%d\n", count, dim); // verify dimension and count

        int * data = (int *) malloc (count * dim * sizeof (int)); // allocate memory

        // read data file into array
        for (i = 0; i < count; i++) {
                for (j = 0; j < dim - 1; j++) {
                        out = fscanf (fd, "%d ", &data[i * dim + j]);
                }
                j = dim - 1;
                out = fscanf (fd, "%d\n", &data[i * dim + j]);
        }


        fclose (fd);
        printf ("File reading complete.\n");

        /*
        // print out data, For validation use only
        puts ("\n[Data]");
        for (i = 0; i < count; i++) {
                for (j = 0; j < dim - 1; j++) {
                        printf ("%d ", data[i * dim + j]);
                }
                j = dim - 1;
                printf ("%d\n", data [i * dim + j]);
        }
        */

        // distance matrix, keeps the distance between every two points
        double * dismat = (double *) malloc (count * count * sizeof(double));

        // calculate the distance between every two data points. takes n * n * m time
        // this is the most time consuming part. need to be improved.
        /*#pragma omp parallel for
        for (i = 0; i < count; i++) {

                printf ("Calculating distances around point [%d]\n", i);
                double dist = 0.0;
                int d = 0;
                #pragma omp parallel for
                for (j = 0; j < count; j++) {
                        dist = 0.0;

                        #pragma omp parallel for
                        for (k = 0; k < dim; k++) {
                                d = data [i * dim + k] - data [j * dim + k];

                                #pragma omp critical
                                {
                                        dist += d * d;
                                }
                        }
                        dist = sqrt (dist);
                        dismat [i * count + j] = dist;
                }
        }*/

        double calc_time = 0.0;
        double copy_time = 0.0;
        myTimer_t t = getTimeStamp ();
        #pragma omp parallel for
        for (i = 0; i < count - 1; i++) {

                //printf ("Calculating distances around point [%d]\n", i);
                double dist = 0.0;
                int d = 0;

                //#pragma omp parallel for
                for (j = i + 1; j < count; j++) {
                        dist = 0.0;

                        //#pragma omp parallel for
                        for (k = 0; k < dim; k++) {
                                d = data [i * dim + k] - data [j * dim + k];

                                //#pragma omp critical
                                {
                                        dist += d * d;
                                }
                        }
                        dist = sqrt (dist);
                        dismat [i * count + j] = dist;
                }
        }
        calc_time = getElapsedTime (t, getTimeStamp());

        t = getTimeStamp ();
        //#pragma omp parallel for
	for (i = 1; i < count; i++) {
                for (j = 0; j < i; j++) {
                        dismat [i * count + j] = dismat [j * count + i];
                }
	}
        copy_time = getElapsedTime (t, getTimeStamp());

        printf ("Distance Matrix Calc Time: %f\n", calc_time);
        printf ("Distance Matrix Copy Time: %f\n", copy_time);
        printf ("Distance matrix complete.\n");

        double seek_time = 0.0;
        t = getTimeStamp ();
        // for each points, find the nearest points
        //#pragma omp parallel for
        for (i = 0; i < count; i++) {
                Distance * d = ptrdist (dismat, count, i);
                qsort (d, count, sizeof(Distance), comparator);
                //for (j = 1; j < K + 1; j++) {
                        //printf ("Point [%d] Neighbor [%d] Distance [%f]\n",i, d[j].p, d[j].dist);
                //}
                free (d);
                //printf ("\n");
        }

        seek_time = getElapsedTime(t, getTimeStamp()) / (count * 1.0);
        printf ("Average Seeking Time: %f\n", seek_time);

        /*
        //print distance matrix, for validation use only
        for (i = 0; i < count; i++) {
                for (j = 0; j < count; j++) {
                        printf ("%f ", dismat [i * count + j]);
                }
                printf ("\n");
        }*/


        free (data);
        free (dismat);
        return 0;
}
