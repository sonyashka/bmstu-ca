#include <stdio.h>

#ifndef _IN_OUT_H_
#define _IN_OUT_H_

#define OK 0
#define ERR -1
#define COUNT 5

struct polynomial
{
    float data_f[COUNT * COUNT];
    int nx;
    int ny;
    float x;
    float y;
    int ind_x;
    int ind_y;
    float *difference;
    float result;
};

int input_data(FILE *f, struct polynomial *data);
void out_res(struct polynomial data);

#endif
