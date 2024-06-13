#include <integral.h>

#define n0 10 // стартовое разбиение отрезка при интегрировании

inline double fabs(double x) {
    return x < 0 ? -x : x;
}

// Вспомогательная фукнция для подсчета интеграла
double integralPart(fptr f, double a, double b, int n) {
    double h = (b - a) / n;
    double sum =    n == n0 ? (f(a) + f(b)) / 2 : 0;
    int step =      n == n0 ? 1                 : 2;

    for (int i = 1; i < n; i += step) {
        sum += f(a + i * h);
    }

    return sum * h;
}

// Подсчет интеграла формулой трапеции
double integral(fptr f, double a, double b, double eps) {
    double i1 = integralPart(f, a, b, n0);
    double i2 = i1 / 2 + integralPart(f, a, b, n0 << 1);

    int n = n0 << 1;
    while (fabs(i1 - i2) >= eps) {
        n <<= 1;
        i1 = i2;
        i2 = i2 / 2 + integralPart(f, a, b, n);
    }

    return i2;
}