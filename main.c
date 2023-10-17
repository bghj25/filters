#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
//#include <stdint.h>

#define NUM_POINTS 100
#define NUM_COMMANDS 11


#define AV4
//#define AV5
double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
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
    int i;
        srand(time(NULL));
    double xvals[NUM_POINTS];
    double yvals[NUM_POINTS];

    for (i=0; i < NUM_POINTS; i++)
    {
        xvals[i] = 4 * M_PI * i / NUM_POINTS;
        yvals[i] = sin(xvals[i]) + randfrom(-0.25, 0.25);
    }

    FILE * temp = fopen("data.temp", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");


    #ifdef AV4
    int windsize = 4;
    char * commandsForGnuplot[] = {"set terminal qt size 1920, 1080", "set tics font \"Helvetica,15\"", "set multiplot", "set size 0.5, 0.8","set origin 0.0, 0.1" ,"set title 'Сигнал с помехами' font \"Helvetica,15\"",
    "plot 'data.temp' u 1:2  title '' with lines", "set size 0.5, 0.8","set origin 0.5, 0.1", "set title 'Отфильтрованный сигнал ск ср 4' font \"Helvetica,15\"", "plot 'data.temp' u 1:3 title '' with lines"};

    for (i=0; i < NUM_POINTS - windsize; i++)
    {
    fprintf(temp, "%lf %lf %lf\n", xvals[i], yvals[i], movavf(&yvals[i], windsize)); //Write the data to a temporary file
    //fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]);
    }

    for (i=0; i < NUM_COMMANDS; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
    #endif // AV4


    #ifdef AV5
    int windsize = 5;
    char * commandsForGnuplot[] = {"set terminal qt size 1920, 1080", "set tics font \"Helvetica,15\"", "set multiplot", "set size 0.5, 0.8","set origin 0.0, 0.1" ,"set title 'Сигнал с помехами' font \"Helvetica,15\"",
    "plot 'data.temp' u 1:2  title '' with lines", "set size 0.5, 0.8","set origin 0.5, 0.1", "set title 'Отфильтрованный сигнал ск ср 4' font \"Helvetica,15\"", "plot 'data.temp' u 1:3 title '' with lines"};

    for (i=0; i < NUM_POINTS - windsize; i++)
    {
    fprintf(temp, "%lf %lf %lf\n", xvals[i], yvals[i], movavf(&yvals[i], windsize)); //Write the data to a temporary file
    //fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]);
    }

    for (i=0; i < NUM_COMMANDS; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
    #endif // AV5
    //return 0;

}
