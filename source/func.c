#include <func.h>

// Для подсчета площади фигуры
double f1mf2(double x) { return f1(x) - f2(x); }
double f1mf3(double x) { return f1(x) - f3(x); }

double f4(double x) {
    return exp(-x) + 3;
}

double df4(double x) {
    return -exp(-x);
}

double d2f4(double x) {
    return exp(-x);
}

double f5(double x) {
    return 2*x - 2;
}

double df5(double x) {
    return 2;
}

double d2f5(double x) {
    return 0;
}

double f6(double x) {
    return 1 / x;
}

double df6(double x) {
    return -1 / (x * x);
}

double d2f6(double x) {
    return 2 / (x * x * x);
}

func func1 = {f1, df1, d2f1};
func func2 = {f2, df2, d2f2};
func func3 = {f3, df3, d2f3};
func func4 = {f4, df4, d2f4};
func func5 = {f5, df5, d2f5};
func func6 = {f6, df6, d2f6};

func getFuncByNumber(int num) {
    switch (num) {
        case 1:
            return func1;
        case 2:
            return func2;
        case 3:
            return func3;
        case 4:
            return func4;
        case 5:
            return func5;
        case 6:
            return func6;
    }
    return func1;
}