#include "matrixfunc.h"

long sum_all(const int *matptr, int strok, int stolb)
{
    long sum = 0;
    int i, j;

    for (i = 0; i < strok; i++)
        for (j = 0; j < stolb; j++)
            sum += *(matptr + i * stolb + j);

    return sum;
}

long sum_in_range(const int *matptr, int strok, int stolb, int k, int m)
{
    long sum = 0;
    int tmp;
    int i, j;

    if (k > m) {
        tmp = k;
        k = m;
        m = tmp;
    }

    for (i = 0; i < strok; i++)
        for (j = 0; j < stolb; j++)
            if (*(matptr + i * stolb + j) >= k && *(matptr + i * stolb + j) <= m)
                sum += *(matptr + i * stolb + j);

    return sum;
}

int sum_secondary_diag(const int *matptr, int strok, int stolb, long *result)
{
    long sum = 0;
    int i;

    if (strok != stolb)
        return -1;

    for (i = 0; i < strok; i++)
        sum += *(matptr + i * stolb + (stolb - 1 - i));

    *result = sum;
    return 0;
}