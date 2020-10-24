#include <iostream>
#include <cmath>

double func_1(double x) {
    return ((1 - x) * (1 - x) + exp(x));
}
double func_2(double x) {
    return func_1(x) * sin(5 * x);
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
double probability(double delta_f, double T) { //вычисляем вероятность перехода
    return (exp(-delta_f / T));
}
bool chance(double P) {
    double ch = fRand(0, 1);
    if (ch > P) {
        return false;
    }
    else {
        return true;
    }
}
bool check_delta(double delta) {
    if (delta <= 0) {
        return true;
    }
    else {
        return false;
    }
}
double downgrade_T(double T) {
    return 0.95 * T;
}

void SA(double func(double x)) {
    //for func_1
    double left = -2;
    double right = 4;
    double T0 = 0.1;
    double T1 = 10000;
    double x1 = fRand(left, right); //случайно выбираем значение х на отрезке
    double f = func(x1);
    double Ti = T1;
    double x2, delta_f;
    std::cout << "N  T      x      f(x)\n";
    int N = 1;
    std::cout << N << " " << Ti << " " << x1 << " " << func(x1) << "\n";
    while (Ti > T0) { //непосредственно сам алгоритм отжига
        x2 = fRand(left, right);
        delta_f = func(x2) - func(x1);
        if (check_delta(delta_f)) {
            x1 = x2;
        }
        else {
            if (chance(probability(delta_f, Ti))) {
                x1 = x2;
            }
        }
        Ti = downgrade_T(Ti);
        std::cout << N << " " << Ti << " " << x1 << " " << func(x1) << "\n";
        N++;
    }
    std::cout << "\n";
}

int main() {
    SA(func_1);
    SA(func_2);
    return 0;
}