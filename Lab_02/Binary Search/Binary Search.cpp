#include <iostream>
#include <cmath>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int N;
    cout << "Введите число N: ";
    cin >> N;

    double low = 0;
    double high = N;
    int result;
    int ugadal;
    const int MAX_STEPS = 100;
    int steps[MAX_STEPS];
    int stepCount = 0;

    cout << "Загадайте число от 1 до " << N << " и запомните его." << endl;

    while (true) {
        result = ceil((low + high) / 2);
        steps[stepCount++] = result;
        cout << "Ваше число " << result << "? (введите:мало - 1, много -2 или угадал - 3): ";
        cin >> ugadal;

        if (ugadal == 3) {
            cout << "Угадал!" << endl;
            break;
        }
        else if (ugadal == 1) {
            low = result ;
        }
        else if (ugadal == 2) {
            high = (result );
        }
        else {
            cout << "Некорректный ввод. Попробуйте ещё раз." << endl;
        }
    }


    int maxSteps = ceil(log2(N));

    cout << "Максимальное количество шагов = " << maxSteps << endl;
    cout << "Шаги бинарного поиска: " << endl;
    for (int i = 0; i < stepCount; ++i) {
        cout << steps[i] << endl;
    }

    return 0;
}
