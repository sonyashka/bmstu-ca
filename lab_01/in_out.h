#include <stdio.h>

#ifndef _IN_OUT_H_
#define _IN_OUT_H_

#define OK 0
#define ERR -1

struct polynom
{
    int count;
    float *data_x;
    float *data_y;
    float *data_y_p1;
    float x;
    int n;
    int ind1;
    int ind2;
    float *difference1;
    float *difference2;
    float y_newton;
    float y_armit;
};

int input_data(FILE *f, struct polynom *data);
void out_res(struct polynom data, int mode);

#endif
