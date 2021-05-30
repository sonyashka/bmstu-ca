#include <stdio.h>
#include <stdlib.h>
#include "in_out.h"
#include "polynom_func.h"

int main()
{
    int res = OK;
    FILE *f = fopen("in.txt", "r");
    struct polynom data;
    res = input_data(f, &data);
    fclose(f);

    if (!res)
    {
        sort_data(&data);
        find_config(&data);
        divided_difference_newton(&data);
        divided_difference_armit(&data);
        if (data.difference1 && data.difference2)
        {
            find_polynom_newton(&data);
            find_polynom_armit(&data);
            out_res(data, 1);
        }

        if (check_monotony(data))
        {
            swap_columns(&data);
            data.x = 0;
            sort_data(&data);
            find_config(&data);
            divided_difference_newton(&data);
            if (data.difference1)
            {
                find_polynom_newton(&data);
                out_res(data, 2);
            }
        }
        else
            printf("Function is not monotonous.\n");
    }

    return res;
}
