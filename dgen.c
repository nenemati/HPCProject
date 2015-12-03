#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char * argv []) {
        int count, dim, maxval;
        int i, j, r;
        const char * fname = "data.txt";

        if (argc != 4) {
                printf ("\nUsage:");
                printf ("$ ./dgen [# data points] [# dimensions] [maxium value]\n");
                return -1;
        }

        count = atoi (argv[1]);
        dim = atoi (argv[2]);
        maxval = atoi (argv[3]);

        srand(time(NULL));

        FILE * fd = fopen (fname, "w");

        fprintf (fd, "%d %d\n", count, dim);

        for (i = 0; i < count; i++) {
                for (j = 0; j < dim - 1; j++) {
                        r = rand () % maxval;
                        fprintf (fd, "%d ",  r);
                }
                r = rand () % maxval;
                fprintf (fd, "%d\n", r);
        }
        fclose (fd);
        return 0;
}
