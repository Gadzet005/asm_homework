#include <stdio.h>
#include <getopt.h>
#include "func.h"
#include "integral.h"
#include "root.h"

#define eps1 0.0001 // Точность вычисления точек пересечения
#define eps2 0.0001 // Точность вычисления интеграла

int main(int argc, char* argv[]) {
    const char* short_options = "hriR:I:";
    const struct option long_options[] = {
		{"help",            no_argument,        NULL, 'h'},
        {"root",            no_argument,        NULL, 'r'},
        {"iterations",      no_argument,        NULL, 'i'},
        {"test-root",       required_argument,  NULL, 'R'},
        {"test-integral",   required_argument,  NULL, 'I'},
		{0, 0, 0, 0}
	};

    int res = getopt_long(argc, argv, short_options, long_options, NULL);

    switch (res) {
    case -1: { // Без параметров
        double root12 = root(func1, func2, 1, 2, eps1);
        double root13 = root(func1, func3, -3, -2, eps1);
        double root23 = root(func2, func3, 0, 1, eps1);

        double s = integral(f1mf3, root13, root23, eps2) + 
                   integral(f1mf2, root23, root12, eps2);

        printf("Площадь фигуры, ограниченной функциями f1, f2 и f3, равна %lf\n", s);
        break;
    }

    case 'h': { // --help
        printf(
            "Доступные опции командной строки:\n"
            "-h, --help             Вывод информации о параметрах командной строки\n"
            "-r, --root             Печать абцисс точек пересечения кривых\n"
            "-i, --iterations       Печать числа итераций для вычисления точек пересечения\n"
            "-R, --test-root        Тестирование функции root\n"
            "-I, --test-integral    Тестирование функции integral\n"
        );
        break;
    }

    case 'r': { // --root
        double root12 = root(func1, func2, 1, 2, eps1);
        double root13 = root(func1, func3, -3, -2, eps1);
        double root23 = root(func2, func3, 0, 1, eps1);
        printf(
            "Абцисса точки пересечения функций:\n"
            "f1 и f2: %lf\n"
            "f1 и f3: %lf\n"
            "f2 и f3: %lf\n",
            root12, root13, root23
        );
        break;
    }

    case 'i': { // --iterations
        int cnt = 0;
        root(func1, func2, 1, 2, eps1);
        cnt += iterCounter;
        root(func1, func3, -3, -2, eps1);
        cnt += iterCounter;
        root(func2, func3, 0, 1, eps1);
        cnt += iterCounter;

        printf("Число итераций при вычислении точек пересечения функций: %d\n", cnt);
        break;
    }

    case 'R': { // --test-root
        int num1, num2;
        double a, b, eps, ans;
        int res = sscanf(optarg, "%d:%d:%lf:%lf:%lf:%lf", &num1, &num2, &a, &b, &eps, &ans);
        
        if (res != 6) {
            printf("Неверный формат параметра --test-root\n");
            return 1;
        }

        double r = root(
            getFuncByNumber(num1), getFuncByNumber(num2),
            a, b, eps
        );

        double diff = fabs(r - ans);
        double relDiff = fabs(diff / r);

        printf("%lf %lf %lf\n", r, diff, relDiff);

        break;
    }

    case 'I': { // --test-integral
        int num;
        double a, b, eps, ans;
        int res = sscanf(optarg, "%d:%lf:%lf:%lf:%lf", &num, &a, &b, &eps, &ans);

        if (res != 5) {
            printf("Неверный формат параметра --test-integral\n");
            return 1;
        }

        double r = integral(getFuncByNumber(num).d0, a, b, eps);

        double diff = fabs(r - ans);
        double relDiff = fabs(diff / r);

        printf("%lf %lf %lf\n", r, diff, relDiff);

        break;
    }

    }
    
    return 0;
}