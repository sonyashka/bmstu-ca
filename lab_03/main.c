#include "spline.h"

int main()
{
    int res = EXIT_SUCCESS;
    struct Data data;
    res = dataInput(&data);
    if (!res)
    {
        for (int i = 0; i < 2 && !res; i++)
        {
            res = xInput(&data);
            if (!res)
            {
                res = splineCalc(&data);
                if (!res)
                    resOut(data);
            }
        }
    }
    return res;
}
