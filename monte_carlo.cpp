#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Проверка, принадлежит ли точка окружности
bool isInsideCircle(double x, double y, double cx, double cy, double r) {
    return (x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r;
}

int main() {
    // Входные данные: координаты центров и радиусы
    double x1, y1, r1, x2, y2, r2, x3, y3, r3;
    cin >> x1 >> y1 >> r1;
    cin >> x2 >> y2 >> r2;
    cin >> x3 >> y3 >> r3;

    // Границы прямоугольной области
    double minX = min(x1 - r1, min(x2 - r2, x3 - r3));
    double maxX = max(x1 + r1, max(x2 + r2, x3 + r3));
    double minY = min(y1 - r1, min(y2 - r2, y3 - r3));
    double maxY = max(y1 + r1, max(y2 + r2, y3 + r3));

    // Число случайных точек
    const int N = 1000000;
    int count = 0;

    srand(time(0));

    // Генерация случайных точек и проверка попадания в пересечение кругов
    for (int i = 0; i < N; ++i) {
        double x = minX + (maxX - minX) * (rand() / (double)RAND_MAX);
        double y = minY + (maxY - minY) * (rand() / (double)RAND_MAX);

        if (isInsideCircle(x, y, x1, y1, r1) &&
            isInsideCircle(x, y, x2, y2, r2) &&
            isInsideCircle(x, y, x3, y3, r3)) {
            count++;
        }
    }

    // Вычисление площади пересечения
    double areaRect = (maxX - minX) * (maxY - minY);
    double areaIntersection = (count / (double)N) * areaRect;

    // Вывод результата
    cout << fixed << areaIntersection << endl;

    return 0;
}
