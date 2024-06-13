#include <root.h>

int iterCounter; // Счетчик числа итераций при вызове функции root

// Нахождение корня уравнения f(x) - g(x) = 0 методом касательных
double root(func f, func g, double a, double b, double eps) {
    #define F(x) (f.d0(x) - g.d0(x))
    #define dF(x) (f.d1(x) - g.d1(x))
    #define d2F(x) (f.d2(x) - g.d2(x))

    double p; // Точка приближения
    if (F(a) * d2F(a) > 0) {
        p = a; // Приближение слева
    } else {
        p = b; // Приближение справа
        eps = -eps;
    }
    
    iterCounter = 0;
    while (F(p) * F(p + eps) > 0) {
        p -= F(p) / dF(p);
        iterCounter++;
    }

    #undef F
    #undef dF
    #undef d2F

    return p;
}