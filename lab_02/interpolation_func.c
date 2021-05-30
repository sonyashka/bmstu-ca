#include <stdio.h>
#include <stdlib.h>
#include "in_out.h"
#include "interpolation_func.h"

void divided_difference_newton(struct polynomial *data, int column);
float find_polynom_newton(struct polynomial *data, int column);

void find_config(struct polynomial *data)
{
    data->ind_x = 0, data->ind_y = 0;
    for (int i = 0; i < COUNT; i++)
    {
        if (data->x >= i && data->x <= i + 1)
            data->ind_x = i;
        if (data->y >= i && data->y <= i + 1)
            data->ind_y = i;
    }

    int step_x = (data->nx + 1) / 2, step_y = (data->ny + 1) / 2;
    if ((data->nx + 1) % 2 == 0)
    {
        if (data->ind_x - step_x >= 0)
        {
            if (data->ind_x + step_x <= COUNT - 1)
                data->ind_x -= step_x - 1;
            else
                data->ind_x = COUNT - step_x * 2;
        }
        else
            data->ind_x = 0;
    }
    else
    {
        if (data->ind_x - step_x + 1 >= 0)
        {
            if (data->ind_x + step_x <= COUNT - 1)
                data->ind_x -= step_x;
            else
                data->ind_x = COUNT - 1 - step_x * 2;
        }
        else
            data->ind_x = 0;
    }
    if ((data->ny + 1) % 2 == 0)
    {
        if (data->ind_y - step_y >= 0)
        {
            if (data->ind_y + step_y <= COUNT - 1)
                data->ind_y -= step_y - 1;
            else
                data->ind_y = COUNT - step_y * 2;
        }
        else
            data->ind_y = 0;
    }
    else
    {
        if (data->ind_y - step_y + 1 >= 0)
        {
            if (data->ind_y + step_y <= COUNT - 1)
                data->ind_y -= step_y;
            else
                data->ind_y = COUNT - 1 - step_y * 2;
        }
        else
            data->ind_y = 0;
    }
    printf("Config x: %d - %d\n", data->ind_x, data->ind_x + data->nx);
    printf("Config y: %d - %d\n", data->ind_y, data->ind_y + data->ny);
}

void calculations(struct polynomial *data)
{
    float dif_x[data->nx + 1];
    for (int i = 0; i < data->nx + 1; i++)
    {
        divided_difference_newton(data, i + data->ind_x);
        dif_x[i] = find_polynom_newton(data, i + data->ind_x);
        printf("%.2f\n", dif_x[i]);
    }

    data->difference = malloc(sizeof(float) * (data->nx + 1) * (data->nx + 1));
    if (data->difference)
    {
        printf("DIVIDED COEFS\n");
        //вычисление разностей аргументов и первых разделенных разностей
        for (int i = 0; i < data->nx; i++)
        {
            data->difference[i * (data->nx + 1)] = data->x - (i + data->ind_x);
            data->difference[i * (data->nx + 1) + 1] = (dif_x[i] - dif_x[i + 1]) / (-1);
        }

        //вычисление оставшихся разделенных разностей
        for (int j = 2; j < data->nx + 1; j++)
            for (int i = 0; i < data->nx - j + 1; i++)
                data->difference[i * (data->nx + 1) + j] = (data->difference[i * (data->nx + 1) + j - 1] - data->difference[(i + 1) * (data->nx + 1) + j - 1]) / (-j);
        for (int i = 0; i < data->nx + 1; i++)
        {
            for (int j = 0; j < data->nx + 1; j++)
                printf("%.2f ", data->difference[i * (data->nx + 1) + j]);
            printf("\n");
        }

        data->result = dif_x[0];
        float buf_x = 1;
        for (int i = 1; i < data->nx + 1; i++)
        {
            buf_x *= data->difference[(i - 1) * (data->nx + 1)];
            data->result += buf_x * data->difference[i];
        }
        free(data->difference);
        printf("RES %f\n", data->result);
    }
    else
        printf("Memory allocate error!\n");
}

void divided_difference_newton(struct polynomial *data, int column)
{
    printf("DIVIDED COEFS\n");
    data->difference = malloc(sizeof(float) * (data->ny + 1) * (data->ny + 1));
    if (data->difference)
    {
        //вычисление разностей аргументов и первых разделенных разностей
        for (int i = 0; i < data->ny; i++)
        {
            data->difference[i * (data->ny + 1)] = data->y - (i + data->ind_y);
            data->difference[i * (data->ny + 1) + 1] = (data->data_f[(i + data->ind_y) * COUNT + column] - data->data_f[(i + data->ind_y + 1) * COUNT + column]) / (-1);
        }

        //вычисление оставшихся разделенных разностей
        for (int j = 2; j < data->ny + 1; j++)
            for (int i = 0; i < data->ny - j + 1; i++)
                data->difference[i * (data->ny + 1) + j] = (data->difference[i * (data->ny + 1) + j - 1] - data->difference[(i + 1) * (data->ny + 1) + j - 1]) / (-j);
        for (int i = 0; i < data->ny + 1; i++)
        {
            for (int j = 0; j < data->ny + 1; j++)
                printf("%.2f ", data->difference[i * (data->ny + 1) + j]);
            printf("\n");
        }
    }
    else
        printf("Memory allocate error!\n");
}

float find_polynom_newton(struct polynomial *data, int column)
{
    float res = data->data_f[data->ind_y * COUNT + column];
    float buf_x = 1;
    for (int i = 1; i < data->ny + 1; i++)
    {
        buf_x *= data->difference[(i - 1) * (data->ny + 1)];
        res += buf_x * data->difference[i];
    }
    free(data->difference);
    return res;
}
