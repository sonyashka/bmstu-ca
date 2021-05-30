#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>

#define MEMERR -1
#define INPUTERR -2

struct Data
{
    int N;
    int *func;
    float x;
    int ind;
    float *h;
    float *aCoef;
    float *bCoef;
    float *cCoef;
    float *dCoef;
    float res;
};

int dataInput(struct Data *data);
int xInput(struct Data *data);
void resOut(struct Data data);

#endif // STRUCT_H
