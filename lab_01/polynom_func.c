#include <stdio.h>
#include <stdlib.h>
#include "in_out.h"
#include "polynom_func.h"

void shift(struct polynom *data, int ind, int pos);
void swap(struct polynom *data, int i, int j);

void sort_data(struct polynom *data)
{
    for (int i = 1; i < data->count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (data->data_x[i] < data->data_x[j])
                shift(data, j, i);
        }
    }
}

void shift(struct polynom *data, int ind, int pos)
{
    for (int k = ind; k < pos; k++)
    {
        swap(data, k, pos);
    }
}

void swap(struct polynom *data, int i, int j)
{
    float a = data->data_x[i], b = data->data_y[i], c = data->data_y_p1[i];
    data->data_x[i] = data->data_x[j], data->data_y[i] = data->data_y[j], data->data_y_p1[i] = data->data_y_p1[j];
    data->data_x[j] = a, data->data_y[j] = b, data->data_y_p1[j] = c;
}

void find_config(struct polynom *data)
{
    data->ind1 = 0, data->ind2 = 0;
    for (int i = 0; i < data->count - 1; i++)
    {
        if (data->x >= data->data_x[i] && data->x <= data->data_x[i + 1])
            data->ind1 = i;
    }

    int step = (data->n + 1) / 2;
    if (data->count < data->n + 1)
    {
        printf("Need more data.\n");
    }
    else if ((data->n + 1) % 2 == 0)
    {
        if (data->ind1 - step >= 0)
        {
            if (data->ind1 + step <= data->count - 1)
            {
                data->ind2 = data->ind1 + step;
                data->ind1 -= step - 1;
            }
            else
            {
                data->ind2 = data->count - 1;
                data->ind1 = data->count - step * 2;
            }
        }
        else
        {
            data->ind1 = 0;
            data->ind2 = step * 2 - 1;
        }
    }
    else
    {
        if (data->ind1 - step + 1 >= 0)
        {
            if (data->ind1 + step <= data->count - 1)
            {
                data->ind2 = data->ind1 + step;
                data->ind1 -= step;
            }
            else
            {
                data->ind2 = data->count - 1;
                data->ind1 = data->count - 1 - step * 2;
            }
        }
        else
        {
            data->ind1 = 0;
            data->ind2 = step * 2;
        }
    }
    printf("Config: %f - %f\n", data->data_x[data->ind1], data->data_x[data->ind2]);
}

void divided_difference_newton(struct polynom *data)
{
    data->difference1 = malloc(sizeof(float) * (data->n + 1) * (data->n + 1));
    if (data->difference1)
    {
        //вычисление разностей аргументов и первых разделенных разностей
        for (int i = 0; i < data->n; i++)
        {
            data->difference1[i * (data->n + 1)] = data->x - data->data_x[i + data->ind1];
            data->difference1[i * (data->n + 1) + 1] = (data->data_y[i + data->ind1] - data->data_y[i + 1 + data->ind1]) / (data->data_x[i + data->ind1] - data->data_x[i + 1 + data->ind1]);
        }

        //вычисление оставшихся разделенных разностей
        for (int j = 2; j < data->n + 1; j++)
            for (int i = 0; i < data->n - j + 1; i++)
                data->difference1[i * (data->n + 1) + j] = (data->difference1[i * (data->n + 1) + j - 1] - data->difference1[(i + 1) * (data->n + 1) + j - 1]) / (data->data_x[i + data->ind1] - data->data_x[i + j + data->ind1]);
    }
    else
        printf("Memory allocate error!\n");

    for (int i = 1; i < data->n + 1; i++)
        printf(" %f", data->difference1[i]);
    printf("\n");
}

void divided_difference_armit(struct polynom *data)
{
    data->difference2 = malloc(sizeof(float) * 2 * (data->n + 1) * 2 * (data->n + 1));
    if (data->difference2)
    {
        //вычисление разностей аргументов
        for (int i = 0; i < data->n + 1; i++)
            data->difference2[i * 2 * (data->n + 1)] = data->x - data->data_x[i + data->ind1];

        //вычисление первых разделенных разностей
        for (int i = 0; i < 2 * data->n + 1; i++)
            if (i % 2 == 0)
                data->difference2[i * 2 * (data->n + 1) + 1] = data->data_y_p1[i / 2 + data->ind1];
            else
                data->difference2[i * 2 * (data->n + 1) + 1] = (data->data_y[i / 2 + data->ind1] - data->data_y[(i + 1) / 2 + data->ind1]) / (data->data_x[i / 2 + data->ind1] - data->data_x[(i + 1) / 2 + data->ind1]);

        //вычисление оставшихся разделенных разностей
        for (int j = 2; j < 2 * (data->n + 1); j++)
            for (int i = 0; i < 2 * (data->n + 1) - j; i++)
                if (i % 2 == 0)
                    data->difference2[i * 2 * (data->n + 1) + j] = (data->difference2[i * 2 * (data->n + 1) + j - 1] - data->difference2[(i + 1) * 2 * (data->n + 1) + j - 1]) / (data->data_x[i / 2 + data->ind1] - data->data_x[i / 2 + j / 2 + data->ind1]);
                else
                    data->difference2[i * 2 * (data->n + 1) + j] = (data->difference2[i * 2 * (data->n + 1) + j - 1] - data->difference2[(i + 1) * 2 * (data->n + 1) + j - 1]) / (data->data_x[i / 2 + data->ind1] - data->data_x[i / 2 + j / 2 + j % 2 + data->ind1]);
    }
    else
        printf("Memory allocate error!\n");

    /*for (int i = 1; i < 2 * (data->n + 1); i++)
        printf("%f ", data->difference2[i]);
    printf("\n");*/
}

void find_polynom_newton(struct polynom *data)
{
    data->y_newton = data->data_y[data->ind1];
    float buf_x = 1;
    for (int i = 1; i < data->n + 1; i++)
    {
        buf_x *= data->difference1[(i - 1) * (data->n + 1)];
        data->y_newton += buf_x * data->difference1[i];
    }
}

void find_polynom_armit(struct polynom *data)
{
    data->y_armit = data->data_y[data->ind1];
    float buf_x = 1;
    for (int i = 1; i < 2 * (data->n + 1); i++)
    {
        buf_x *= data->difference2[(i - 1) / 2 * 2 * (data->n + 1)];
        data->y_armit += buf_x * data->difference2[i];
    }
}

int check_monotony(struct polynom data)
{
    int res = 0;
    if (data.data_y[0] < 0)
        res = -1;
    else
        res = 1;
    for (int i = 0; i < data.count - 1; i++)
        if (res > 0 && data.data_y[i] <= 0)
            res = 2;
        else if (res < 0 && data.data_y[i] >= 0)
            res = -2;
    if (res % 2 != 0)
        res = 0;
    return res;
}

void swap_columns(struct polynom *data)
{
    float buf = 0;
    for (int i = 0; i < data->count; i++)
    {
        buf = data->data_x[i];
        data->data_x[i] = data->data_y[i];
        data->data_y[i] = buf;
    }
}
