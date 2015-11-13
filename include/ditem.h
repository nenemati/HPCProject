#ifndef DITEM_H
#define DITEM_H

#define A_LARGER 1
#define A_SMALLER -1

typedef struct d_item {
  int size; // indicate the dimension of the data itemo
  int * values; // pointer to actual data, dynamically allocated in run time
} Data;

double dist (Data a, Data b); // get the distance between two data points

#endif
