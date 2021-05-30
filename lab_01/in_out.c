#include <stdio.h>
#include <stdlib.h>
#include "in_out.h"

int file_reading(FILE *f, struct polynom *data);

int input_data(FILE *f, struct polynom *data)
{
    int res = OK;
    if (f)
    {
        res = file_reading(f, data);
    }

    if (!res)
    {
        printf("File-data is correct.\n");
        printf("Input x: ");
        int rc = 0;
        rc = scanf("%f", &data->x);
        if (rc)
        {
            printf("Input polynomal degree n (in range 1-4): ");
            rc += scanf("%d", &data->n);
            if (data->n < 1 || data->n > 4)
                res = ERR;
        }
        if (rc != 2 && !res)
        {
            printf("Wrong data!\n");
            res = ERR;
        }
        else
            printf("Correct data.\n");
    }

    return res;
}

int file_reading(FILE *f, struct polynom *data)
{
    data->count = 0;
    int res = OK, rc = 3;
    float a, b, c;

    while (rc == 3 && !feof(f))
    {
        rc = fscanf(f, "%f%f%f\n", &a, &b, &c);
        data->count++;
    }

    if (rc != 3 && feof(f))
    {
        printf("Wrong data!\n");
        res = ERR;
    }
    else
    {
        rewind(f);
        data->data_x = malloc(sizeof(float) * data->count);
        data->data_y = malloc(sizeof(float) * data->count);
        data->data_y_p1 = malloc(sizeof(float) * data->count);
        if (data->data_x &&  data->data_y && data->data_y_p1)
            for (int i = 0; i < data->count; i++)
                fscanf(f, "%f%f%f\n", &(data->data_x[i]), &(data->data_y[i]), &(data->data_y_p1[i]));
        else
        {
            res = ERR;
            printf("Memory allocate error!\n");
        }
    }

    return res;
}

void out_res(struct polynom data, int mode)
{
    if (mode == 1)
    {
        printf("Polynoms for %d power.\nNewton: %.6f\nArmit: %.6f\n", data.n, data.y_newton, data.y_armit);
        free(data.difference1);
        free(data.difference2);
    }
    else
    {
        printf("Function root: %.6f\n", data.y_newton);
        free(data.difference1);
        free(data.data_x);
        free(data.data_y);
        free(data.data_y_p1);
    }
}
