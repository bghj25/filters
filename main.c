#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
//#include <stdint.h>

#define NUM_POINTS 100
#define NUM_COMMANDS 9


#define AV4
//#define AV5
double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

double medf (double *wind, int windsize)
{
    int i, j;
    double* bufwind = calloc(windsize, sizeof(double));
    for(int i = 0; i < windsize; i++)
    {
        bufwind[i] = *(wind + i);
    }
    double buf = bufwind[0];
    for(i = 0; i < windsize - 1; i++)
    {
        for(j = i + 1; j < windsize; j++)
        {
            if(bufwind[j] < bufwind[i])
            {
                buf = bufwind[i];
                bufwind[i] = bufwind[j];
                bufwind[j] = buf;
            }
        }
    }
    for(i = 0; i < windsize; i++)
    {
        printf("%f\n",bufwind[i]);
    }
    if(windsize % 2 == 0)
        return bufwind[windsize / 2] / bufwind[windsize / 2 - 1];
    else
        return bufwind[windsize / 2];
}

double movavf(double *wind, int windsize)
{
    int i;
    double sum = 0;
    for(i = 0; i < windsize; i++)
    {
        //printf("%f\n", *wind);
        sum += *wind;
        wind++;
    }
    return sum/windsize;
}

int main()
{
    double test[5] = {-1.5, 7.5, 9.0, 14.3, 1};
    medf(&test, 5);
    FILE * temp = fopen("data.temp", "w");
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    char* commandsForGnuplot[] = {
        "set terminal qt size 1920, 1080",
        "set tics font \"Helvetica,15\"",
        "set multiplot",
        "set size 1.1, 0.8",
        "set origin -0.1, 0.1",
        "plot 'data.temp' u 1:2 title '' with lines linecolor rgb \"blue\"",// 'data.temp' u 1:3 title '' with lines",
        "plot 'data.temp' u 1:3 title '' with lines linecolor rgb \"red\"",
        "plot 'data.temp' u 1:4 title '' with lines linecolor rgb \"green\"",
        "plot 'data.temp' u 1:5 title '' with lines linecolor rgb \"orange\""};

    int i;
    srand(time(NULL));
    double xvals[NUM_POINTS];
    double yvals[NUM_POINTS];

    for (i=0; i < NUM_POINTS; i++)
    {
        xvals[i] = 4 * M_PI * i / NUM_POINTS;
        yvals[i] = sin(xvals[i]) + randfrom(-0.25, 0.25);
    }

    for (i=0; i < NUM_POINTS - 8; i++)
    {
    fprintf(temp, "%lf %lf %lf %lf %lf\n", xvals[i], yvals[i], movavf(&yvals[i], 4), movavf(&yvals[i], 5), medf(&yvals[i], 8)); //Write the data to a temporary file
    //fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]);
    }


    for (i=0; i <  sizeof(commandsForGnuplot)/sizeof(commandsForGnuplot[0]); i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }

    //return 0;

}
