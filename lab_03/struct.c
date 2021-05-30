#include "struct.h"

int dataInput(struct Data *data)
{
    int statusCode = EXIT_SUCCESS;
    data->N = 10;
    data->func = malloc(sizeof(int) * (data->N + 1));
    if (!data->func)
        statusCode = MEMERR;
    else
    {
        for (int i = 0; i < data->N + 1; i++)
                data->func[i] = i * i;
    }
    return statusCode;
}

int xInput(struct Data *data)
{
    int statusCode = EXIT_SUCCESS;
    printf("Input x: ");
    int rc = scanf("%f", &data->x);
    if (!rc)
        statusCode = INPUTERR;
    else
    {
        if ((data->x < 0) || (data->x > data->N))
            statusCode = INPUTERR;
        else
            for (int i = 0; i < data->N; i++)
                if (data->x > i && data->x < i + 1)
                    data->ind = i + 1;
    }
    return statusCode;
}

void resOut(struct Data data)
{
    printf("Spline-interpolation equal %.4f\n", data.res);
    printf("Exact value equal %.4f\n", data.x * data.x);
    printf("Innacuracy is %.2f%%\n", (data.res / (data.x * data.x) - 1) * 100);
}
