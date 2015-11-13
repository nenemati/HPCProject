#include <stdio.h>
#include <stdlib.h>

#include <ditem.h>


int main (int argc, char * argv []) {
    if (argc != 2) {
        printf ("\nUsage:\n");
        printf ("$ ./main [file path]\n\n");
        return -1;
    }

    printf ("Input file: %s\n", argv[1]);
    FILE * fd = fopen (argv[1], "r");

    int count, dim;
    fscanf (fd, "%d %d\n", &count, &dim);

    printf ("Size=%d Dim=%d\n", count, dim);

    int * data = (int *) malloc (count * dim * sizeof (int));
    int i, j;
    for (i = 0; i < count; i++) {
        for (j = 0; j < dim - 1; j++) {
            fscanf (fd, "%d ", &data[i * dim + j]);
        }
        j++;
        fscanf (fd, "%d\n", &data[i * dim + j]);
    }
    free (data);

    for (i = 0; i < count; i++) {
        for (j = 0; j < dim - 1; j++) {
            printf ("%d ", data[i * dim + j]);
        }
        j++;
        printf ("%d\n", data [i * dim + j]);
    }

    fclose (fd);
    return 0;
}
