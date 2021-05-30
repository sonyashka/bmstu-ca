#include "spline.h"

int coefAlloc(struct Data *data);
int hCalc(struct Data *data);
void findACoef(struct Data *data);
void findBCoef(struct Data *data);
void findCCoef(struct Data *data);
void findDCoef(struct Data *data);
void funcCalc(struct Data *data);

int splineCalc(struct Data *data)
{
    int statusCode = EXIT_SUCCESS;
    statusCode = coefAlloc(data);
    if (!statusCode)
    {
        statusCode = hCalc(data);
        if (!statusCode)
        {
            findCCoef(data);
            findACoef(data);
            findBCoef(data);
            findDCoef(data);

            funcCalc(data);
        }
    }
    return statusCode;
}

int coefAlloc(struct Data *data)
{
    int statusCode = EXIT_SUCCESS;
    data->aCoef = malloc((data->N + 1) * sizeof(float));
    if (!data->aCoef)
        statusCode = MEMERR;
    else
    {
        data->bCoef = malloc((data->N + 1) * sizeof(float));
        if (!data->bCoef)
            statusCode = MEMERR;
        else
        {
            data->cCoef = malloc((data->N + 2) * sizeof(float));
            if (!data->cCoef)
                statusCode = MEMERR;
            else
            {
                data->dCoef = malloc((data->N + 1) * sizeof(float));
                if (!data->dCoef)
                    statusCode = MEMERR;
            }
        }
    }
    return statusCode;
}

int hCalc(struct Data *data)
{
    int statusCode = EXIT_SUCCESS;
    data->h = malloc((data->N + 1) * sizeof(float));
    if (!data->h)
        statusCode = MEMERR;
    else
    {
        for (int i = 0; i < data->N + 1; i++)
            data->h[i] = 1;
    }
    return statusCode;
}

void findCCoef(struct Data *data)
{
    float e[data->N + 2];
    float n[data->N + 2];
    float f[data->N + 1];

    for (int i = 2; i < data->N + 1; i++)
        f[i] = 3 * ((data->func[i] - data->func[i - 1]) / data->h[i] - (data->func[i - 1] - data->func[i - 2]) / data->h[i - 1]);

    e[2] = 0, n[2] = 0;
    for (int i = 3; i < data->N + 2; i++)
    {
        e[i] = data->h[i - 1] / (data->h[i - 2] * e[i - 1] + 2 * (data->h[i - 2] + data->h[i - 1]));
        n[i] = (f[i - 1] - data->h[i - 2] * n[i - 1]) / (data->h[i - 2] * e[i - 1] + 2 * (data->h[i - 2] + data->h[i - 1]));
    }

    data->cCoef[1] = 0;
    data->cCoef[data->N + 1] = 0;
    for (int i = data->N; i > 1; i--)
        data->cCoef[i] = e[i + 1] * data->cCoef[i + 1] + n[i + 1];
}

void findACoef(struct Data *data)
{
    for (int i = 1; i < data->N + 1; i++)
        data->aCoef[i] = data->func[i - 1];
}

void findBCoef(struct Data *data)
{
    for (int i = 1; i < data->N; i++)
        data->bCoef[i] = (data->func[i] - data->func[i - 1]) / data->h[i] - data->h[i] * (data->cCoef[i + 1] - 2 * data->cCoef[i]) / 3;
    data->bCoef[data->N] = (data->func[data->N] - data->func[data->N - 1]) / data->h[data->N] - data->h[data->N] * 2 * data->cCoef[data->N] / 3;
}

void findDCoef(struct Data *data)
{
    for (int i = 1; i < data->N; i++)
        data->dCoef[i] = (data->cCoef[i + 1] - data->cCoef[i]) / 3 / data->h[i];
    data->dCoef[data->N] = -data->cCoef[data->N] / 3 / data->h[data->N];
}

void funcCalc(struct Data *data)
{
    float dif = data->x - data->ind + 1;
    data->res = data->aCoef[data->ind] + data->bCoef[data->ind] * dif + data->cCoef[data->ind] * dif * dif + data->dCoef[data->ind] * dif * dif * dif;
}
