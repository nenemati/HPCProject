#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char * argv []) {
        int count, dim, maxval;
        int i, j, r;
        const char * fname = "data.txt";

        if (argc != 4) {
                printf ("\nUsage:\n");
                printf ("$ ./dgen [# data points] [# dimensions] [maxium value]\n\n");
                return -1;
        }

        count = atoi (argv[1]);
        dim = atoi (argv[2]);
        maxval = atoi (argv[3]);

        srand(time(NULL));

        //myTimer_t t1 = getTimeStamp ();
        //myTimer_t t2 = getTimeStamp ();

        FILE * fd = fopen (fname, "w");

        // write down amount of data points and dimensions first
        fprintf (fd, "%d %d\n", count, dim);

        // for each data point, generate data by using random number
        for (i = 0; i < count; i++) {
                for (j = 0; j < dim - 1; j++) {
                        r = rand () % maxval;
                        fprintf (fd, "%d ",  r);
                }
                r = rand () % maxval;
                fprintf (fd, "%d\n", r);
        }
        fclose (fd);



        //double start = getElapsedTime (t1, getTimeStamp());
        //double end = getElapsedTime (t2, getTimeStamp());
        //printf ("Start = %f\nEnd = %f\n", start, end);


        return 0;
}
