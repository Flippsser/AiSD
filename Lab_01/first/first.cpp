#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

 long long fibonacciCircle(int n) {
    if (n <= 1) return n;
     long long first = 0, second = 1;
    for (int i = 2; i <= n; ++i) {
         long long temp = second;
        second += first;
        first = temp;
    }
    return second;
}

 long long fibonacciRecursive(int n) {
    if (n <= 1) return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    setlocale(LC_ALL, "RU");
    int n;
    cout << "Введите число N: ";
    cin >> n;
    
    auto startCircle = high_resolution_clock::now();
    long long fibCircle = fibonacciCircle(n);
    auto endCircle = high_resolution_clock::now();
    auto durationCircle = duration_cast<nanoseconds>(endCircle - startCircle);
    auto durationCircleMicro = duration_cast<microseconds>(endCircle - startCircle);
    auto durationCircleMilli = duration_cast<milliseconds>(endCircle - startCircle);
    auto durationCircleSec = duration_cast<seconds>(endCircle - startCircle);
    auto durationCircleMin = duration_cast<minutes>(endCircle - startCircle);

 cout << "N-ое число Фибоначчи (циклом): " << fibCircle << endl;
    cout << "Расчетное время циклом: " << durationCircleMin.count() << " минут " << durationCircleSec.count() % 60 << " секунд " << durationCircleMilli.count() % 1000 << " миллисекунд " << durationCircleMicro.count() % 1000 << " микросекунд " << durationCircle.count() % 1000 << " наносекунд." << endl;

    auto startRecursive = high_resolution_clock::now();
    long long fibRecursive = fibonacciRecursive(n);
    auto endRecursive = high_resolution_clock::now();
    auto durationRecursive = duration_cast<nanoseconds>(endRecursive - startRecursive);
    auto durationRecursiveMicro = duration_cast<microseconds>(endRecursive - startRecursive);
    auto durationRecursiveMilli = duration_cast<milliseconds>(endRecursive - startRecursive);
    auto durationRecursiveSec = duration_cast<seconds>(endRecursive - startRecursive);
    auto durationRecursiveMin = duration_cast<minutes>(endRecursive - startRecursive);

   
    cout << "N-ое число Фибоначчи (рекурсивно): " << fibRecursive << endl;
    cout << "Расчетное время рекурсией: " << durationRecursiveMin.count() << " минут " << durationRecursiveSec.count() % 60 << " секунд " << durationRecursiveMilli.count() % 1000 << " миллисекунд " << durationRecursiveMicro.count() % 1000 << " микросекунд " << durationRecursive.count() % 1000 << " наносекунд." << endl;

    return 0;
}
