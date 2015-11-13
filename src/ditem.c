#include <math.h>
#include <ditem.h>

double dist (Data a, Data b) {
    int size = a.size;
    int i = 0;
    double result = 0.0;

    for (i = 0; i < size; i++) {
        int ai = a.values[i];
        int bi = b.values[i];

        double dsqr = ai * ai + bi * bi + 0.0;
        result += sqrt (dsqr);
    }

    return result;
}
