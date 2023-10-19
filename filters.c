#include "filters.h"

double medf (double newitem, int windsize)
{
    static double window_sorted[MAX_WIND_SIZE_FOR_MED] = {0.0};
    static double window[MAX_WIND_SIZE_FOR_MED] = {0.0};
    static int count = 0;
    int i,j;


    i = 0;

    if(++count >= windsize)
    {
        count = 0;
    }
    for(i = 0; i < windsize; i++)
    {
        if(window_sorted[i] == window[count])
        {
            break;
        }
    }
    for(;i<windsize-1; i++)
    {
        window_sorted[i] = window_sorted[i+1];
    }
    window_sorted[windsize - 1] = 0;



    window[count] = newitem;
    i = 0;
    while(i < windsize - 1)
    {
        if(window_sorted[i] <= newitem)
        {
            i++;
        }
        else
        {
            break;
        }
    }
    for(j = windsize - 1;j>i; j--)
    {
        window_sorted[j] = window_sorted[j-1];
    }
    window_sorted[i] = newitem;
#if 0
    for(i = 0; i < MAX_WIND_SIZE_FOR_MED; i++)
        printf("%f ", window_sorted[i]);
    printf("\n");
#endif
       if(windsize % 2 == 0)
        return (window_sorted[windsize / 2] + window_sorted[windsize / 2 - 1])/2;
    else
        return window_sorted[windsize / 2];

}


double movavf(double newitem, int windsize)
{
    static double window_avg[MAX_WIND_SIZE_FOR_AVG] = {0.0};
    static int count = 0;
    static double sum = 0;
    sum -= window_avg[count];
    window_avg[count] = newitem;
    sum += newitem;
    if(++count >= windsize)
    {
        count = 0;
    }
    return sum/windsize;
}
