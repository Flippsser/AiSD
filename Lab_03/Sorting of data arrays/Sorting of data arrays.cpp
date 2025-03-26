#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;
// Функция пузырьковой сортировки
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
// Функция сортировки вставками
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
// Функция сортировки выбором
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}
// Функция быстрой сортировки
void quickSort(int arr[], int left, int right) {
    if (left >= right) return;
    int pivot = arr[left + (right - left) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}
int main() {
    system("chcp 1251");
    int N;
    cout << "Введите число N: ";
    cin >> N;
    int* A = new int[N];
    srand(time(0));
    cout << "Исходный массив A: ";
    for (int i = 0; i < N; i++)
    {
        A[i] = rand() ;
        cout << A[i] << " "; 
    }
    cout << endl;
    int* B = new int[N];
    int* C = new int[N];
    int* D = new int[N];
    int* E = new int[N];
    for (int i = 0; i < N; i++) {
        B[i] = A[i];
        C[i] = A[i];
        D[i] = A[i];
        E[i] = A[i];
    }
    // Сортировка пузырьком
    auto start = high_resolution_clock::now();
    bubbleSort(B, N);
    auto end = high_resolution_clock::now();
    cout << "Массив B (пузырьковая сортировка): ";
    for (int i = 0; i < N; i++) cout << B[i] << " ";
    cout << endl;
    auto durationCircle = duration_cast<nanoseconds>(end - start);
    auto durationCircleMicro = duration_cast<microseconds>(end - start);
    auto durationCircleMilli = duration_cast<milliseconds>(end - start);
    auto durationCircleSec = duration_cast<seconds>(end - start);
    auto durationCircleMin = duration_cast<minutes>(end - start);
    // Сортировка вставками
    auto start2 = high_resolution_clock::now();
    insertionSort(C, N);
    auto end2 = high_resolution_clock::now();
    cout << "Массив C (сортировка вставками): ";
    for (int i = 0; i < N; i++) cout << C[i] << " ";
    cout << endl;
    auto durationCircle2 = duration_cast<nanoseconds>(end2 - start2);
    auto durationCircleMicro2 = duration_cast<microseconds>(end2 - start2);
    auto durationCircleMilli2 = duration_cast<milliseconds>(end2 - start2);
    auto durationCircleSec2 = duration_cast<seconds>(end2 - start2);
    auto durationCircleMin2 = duration_cast<minutes>(end2 - start2);
    // Сортировка выбором
    auto start3 = high_resolution_clock::now();
    selectionSort(D, N);
    auto end3 = high_resolution_clock::now();
    cout << "Массив D (сортировка выбором): ";
    for (int i = 0; i < N; i++) cout << D[i] << " ";
    cout << endl;
    auto durationCircle3 = duration_cast<nanoseconds>(end3 - start3);
    auto durationCircleMicro3 = duration_cast<microseconds>(end3 - start3);
    auto durationCircleMilli3 = duration_cast<milliseconds>(end3 - start3);
    auto durationCircleSec3 = duration_cast<seconds>(end3 - start3);
    auto durationCircleMin3 = duration_cast<minutes>(end3 - start3);
    // Быстрая сортировка
    auto start4 = high_resolution_clock::now();
    quickSort(E, 0, N - 1);
    auto end4 = high_resolution_clock::now();
    cout << "Массив E (быстрая сортировка): ";
    for (int i = 0; i < N; i++) cout << E[i] << " ";
    cout << endl;
    auto durationCircle4 = duration_cast<nanoseconds>(end4 - start4);
    auto durationCircleMicro4 = duration_cast<microseconds>(end4 - start4);
    auto durationCircleMilli4 = duration_cast<milliseconds>(end4 - start4);
    auto durationCircleSec4 = duration_cast<seconds>(end4 - start4);
    auto durationCircleMin4 = duration_cast<minutes>(end4 - start4);
    cout << "Время пузырьковой сортировки: " << durationCircleMin.count() << " минут " << durationCircleSec.count() % 60 << " секунд " << durationCircleMilli.count() % 1000 << " миллисекунд " << durationCircleMicro.count() % 1000 << " микросекунд " << durationCircle.count() % 1000 << " наносекунд." << endl;
    cout << "Время сортировки вставками: " << durationCircleMin2.count() << " минут " << durationCircleSec2.count() % 60 << " секунд " << durationCircleMilli2.count() % 1000 << " миллисекунд " << durationCircleMicro2.count() % 1000 << " микросекунд " << durationCircle2.count() % 1000 << " наносекунд." << endl;
    cout << "Время сортировкой выбора: " << durationCircleMin3.count() << " минут " << durationCircleSec3.count() % 60 << " секунд " << durationCircleMilli3.count() % 1000 << " миллисекунд " << durationCircleMicro3.count() % 1000 << " микросекунд " << durationCircle3.count() % 1000 << " наносекунд." << endl;
    cout << "Время быстрой сортировки: " << durationCircleMin4.count() << " минут " << durationCircleSec4.count() % 60 << " секунд " << durationCircleMilli4.count() % 1000 << " миллисекунд " << durationCircleMicro4.count() % 1000 << " микросекунд " << durationCircle4.count() % 1000 << " наносекунд." << endl;
    delete[] A;
    delete[] B;
    delete[] C;
    delete[] D;
    delete[] E;
    return 0;
}
