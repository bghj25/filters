#ifndef FILTERS_H
#define FILTERS_H
#ifndef MAX_WIND_SIZE_FOR_MED
#define MAX_WIND_SIZE_FOR_MED 100 //ћаксимальный размер окна медианы
#endif // MAX_WIND_SIZE_FOR_MED
#ifndef MAX_WIND_SIZE_FOR_AVG
#define MAX_WIND_SIZE_FOR_AVG 100 //ћаксимальный размер окна скольз€щего среднего
#endif // MAX_WIND_SIZE_FOR_AVG
double medf (double newitem, int windsize);
double movavf(double newitem, int windsize);
#endif // FILTERS_H
