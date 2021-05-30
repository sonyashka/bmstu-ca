#include <stdio.h>
#include <stdlib.h>
#include "in_out.h"

int file_reading(FILE *f, struct polynomial *data);

int input_data(FILE *f, struct polynomial *data)
{
    int res = OK;
    if (f)
    {
        res = file_reading(f, data);
    }

    if (!res)
    {
        printf("File-data is correct.\n");
        printf("Input nx and ny (integer): ");
        int rc = 0;
        rc = scanf("%d %d", &data->nx, &data->ny);
        if (rc == 2 && data->nx > 0 && data->nx < 4 && data->ny > 0 && data->ny < 4)
        {
            printf("Input polynomal degree x and y: ");
            rc = scanf("%f %f", &data->x, &data->y);
        }
        else
            res = ERR;

        if (rc != 2 || res)
        {
            printf("Wrong data!\n");
            res = ERR;
        }
        else
            printf("Correct data.\n");
    }

    return res;
}

int file_reading(FILE *f, struct polynomial *data)
{
    int res = OK, rc = 1;

    for (int i = 0; i < COUNT && rc; i++)
        for (int j = 0; j < COUNT && rc; j++)
            rc = fscanf(f, "%f", &(data->data_f[i * COUNT + j]));

    if (rc != 1 && feof(f))
    {
        printf("Wrong data!\n");
        res = ERR;
    }

    return res;
}

void out_res(struct polynomial data)
{
    printf("Interpolation equal %f.", data.result);
}
