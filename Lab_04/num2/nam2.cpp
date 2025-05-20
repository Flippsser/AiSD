#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Функция пузырьковой сортировки для сортировки вектора по убыванию
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] < arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    int N;
    cout << "Введите количество участников: ";
    cin >> N;

    vector<int> results(N);

    srand(static_cast<unsigned int>(time(0)));

    cout << "Результаты участников: ";
    for (int i = 0; i < N; ++i) {
        results[i] = rand() % 100 + 1;
        cout << results[i] << " ";
    }
    cout << endl;

    // результаты, чтобы найти три максимальных
    vector<int> temp_results = results;

    
    bubbleSort(temp_results);

    // Находим три максимальных значения
    int first = temp_results[0];
    int second = -1;
    int third = -1;

    for (int i = 1; i < N; ++i) {
        if (temp_results[i] < first && second == -1) {
            second = temp_results[i];
        }
        else if (temp_results[i] < second && third == -1) {
            third = temp_results[i];
            break;
        }
    }

    // Подсчитываем всех участников с этими значениями
    int count_prize_winners = 0;
    for (int result : results) {
        if (result == first || result == second || result == third) {
            count_prize_winners++;
        }
    }

    cout << "Количество призеров: " << count_prize_winners << endl;

    return 0;
}
