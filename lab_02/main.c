#include <stdio.h>
#include <stdlib.h>
#include "in_out.h"
#include "interpolation_func.h"

int main()
{
    int res = OK;
    FILE *f = fopen("in.txt", "r");
    struct polynomial data;
    res = input_data(f, &data);
    fclose(f);

    if (!res)
    {
        find_config(&data);
        calculations(&data);
    }

    return res;
}
