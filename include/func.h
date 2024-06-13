#pragma once
#include <math.h>

typedef double (*fptr)(double);

typedef struct {
    fptr d0;        // Сама функция
    fptr d1;        // 1 производная
    fptr d2;        // 2 производная
} func;

// Функции из ассемблера (из варианта)
double f1(double x);
double df1(double x);
double d2f1(double x);

double f2(double x);
double df2(double x);
double d2f2(double x);

double f3(double x);
double df3(double x);
double d2f3(double x);

// Функции для тестирования
double f4(double x);
double df4(double x);
double d2f4(double x);

double f5(double x);
double df5(double x);
double d2f5(double x);

double f6(double x);
double df6(double x);
double d2f6(double x);


double f1mf2(double x);
double f1mf3(double x);

extern func func1, func2, func3, func4, func5, func6;

func getFuncByNumber(int num);