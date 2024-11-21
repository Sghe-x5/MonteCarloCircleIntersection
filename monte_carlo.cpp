#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

// Проверка, принадлежит ли точка окружности
bool isInsideCircle(double x, double y, double cx, double cy, double r) {
    return (x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r;
}

// Функция для выполнения Монте-Карло с указанным N
double monteCarloArea(int N, double x1, double y1, double r1,
                      double x2, double y2, double r2,
                      double x3, double y3, double r3) {
    double minX = min(x1 - r1, min(x2 - r2, x3 - r3));
    double maxX = max(x1 + r1, max(x2 + r2, x3 + r3));
    double minY = min(y1 - r1, min(y2 - r2, y3 - r3));
    double maxY = max(y1 + r1, max(y2 + r2, y3 + r3));

    int count = 0;
    for (int i = 0; i < N; ++i) {
        double x = minX + (maxX - minX) * (rand() / (double)RAND_MAX);
        double y = minY + (maxY - minY) * (rand() / (double)RAND_MAX);

        if (isInsideCircle(x, y, x1, y1, r1) &&
            isInsideCircle(x, y, x2, y2, r2) &&
            isInsideCircle(x, y, x3, y3, r3)) {
            count++;
        }
    }

    double areaRect = (maxX - minX) * (maxY - minY);
    return (count / (double)N) * areaRect;
}

int main() {
    // Параметры кругов
    double x1 = 1, y1 = 1, r1 = 1;
    double x2 = 1.5, y2 = 2, r2 = sqrt(5) / 2;
    double x3 = 2, y3 = 1.5, r3 = sqrt(5) / 2;

    // Точное значение площади
    double exactArea = 0.25 * M_PI + 1.25 * asin(0.8) - 1;

    // Результаты
    vector<int> points;
    vector<double> areas;
    vector<double> errors;

    ofstream results("/Users/alexandraovsyannikova/Desktop/results.csv");
    results << "N,EstimatedArea,RelativeError\n";

    for (int N = 100; N <= 100000; N += 500) {
        double estimatedArea = monteCarloArea(N, x1, y1, r1, x2, y2, r2, x3, y3, r3);
        double relativeError = fabs(estimatedArea - exactArea) / exactArea;

        points.push_back(N);
        areas.push_back(estimatedArea);
        errors.push_back(relativeError);

        results << N << "," << estimatedArea << "," << relativeError << "\n";
    }

    results.close();
    cout << "Experiment data saved to results.csv\n";
    return 0;
}
