#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "filters.h"


#define NUM_POINTS 100
#define NUM_COMMANDS 9


double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int main()
{
    #if 0
    double test[5] = {-1.5, 7.5, 9.0, 14.3, 1};
    medf(&test, 5);
    #endif
    FILE * temp1 = fopen("data1.temp", "w");
    FILE * temp2 = fopen("data2.temp", "w");
    FILE * temp3 = fopen("data3.temp", "w");
    FILE * temp4 = fopen("data4.temp", "w");
    FILE * temp5 = fopen("data5.temp", "w");
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    char* commandsForGnuplot[] = {
        "set terminal qt size 1920, 1080",
        "set tics font \"Helvetica,8\"",
        "set multiplot",
        "set size 1.1, 0.8",
        "set origin -0.1, 0.1",
        "set yrange [-1.5:1.5]",
        "set key box outside top vertical width 0.5 height 1 maxcols 1 spacing 1",
        "plot 'data1.temp' u 1:2 title 'Исходный сигнал' with lines linecolor rgb \"blue\", 'data2.temp' u 1:2 title 'Среднее 4' with lines linecolor rgb \"red\", 'data3.temp' u 1:2 title 'Среднее 5' with lines linecolor rgb \"green\", 'data4.temp' u 1:2 title 'Медиана 3' with lines linecolor rgb \"orange\", 'data5.temp' u 1:2 title 'Медиана 8' with lines linecolor rgb \"yellow\""};


    int i;
    srand(time(NULL));
    double xvals[NUM_POINTS];
    double yvals[NUM_POINTS];

    for (i=0; i < NUM_POINTS; i++)
    {
        xvals[i] = 2 * M_PI * i / NUM_POINTS;
        yvals[i] = sin(xvals[i]) + randfrom(-0.2, 0.2);
    }

    for (i=0; i < NUM_POINTS; i++)
    {
        fprintf(temp1, "%lf %lf\n", xvals[i], yvals[i]);
        fprintf(temp2, "%lf %lf\n", xvals[i], movavf(yvals[i], 4));
    }
    for (i=0; i < NUM_POINTS; i++)
    {
        fprintf(temp3, "%lf %lf\n", xvals[i], movavf(yvals[i], 5)); //Write the data to a temporary file
    }
    for (i=0; i < NUM_POINTS; i++)
    {
        fprintf(temp4, "%lf %lf\n", xvals[i], medf(yvals[i], 3)); //Write the data to a temporary file
    }
    for (i=0; i < NUM_POINTS; i++)
    {
        fprintf(temp5, "%lf %lf\n", xvals[i], medf(yvals[i], 8)); //Write the data to a temporary file
    }

    for (i=0; i <  sizeof(commandsForGnuplot)/sizeof(commandsForGnuplot[0]); i++)
    {
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }

    //return 0;

}
