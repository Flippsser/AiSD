#include <iostream>
using namespace std;

void fillArray(int array[], int n) {
	for (int i = 0;i != n;++i) {
		array[i] = rand() % 100 + 1;
	}
}

void sorting(int array[], int n) {
	int temp = 0;
	for (int i = 0; i != n;++i) {
		for (int j = 1;j != n;++j) {
			if (array[j] < array[j - 1]) {
				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	int price[10000];
	int n;
	cout << "¬ведите N:";
	cin >> n;

	fillArray(price, n);

	cout << "÷ены товаров:" << endl;
	for (int i = 0;i != n;++i) {
		cout << price[i] << " ";
	}

	sorting(price, n);

	int lowPrice[5000], highPrice[5000];
	int mid = n / 2;
	for (int i = 0; i != mid;++i) {
		lowPrice[i] = price[i];
	}

	for (int i = n - 1, j = 0; i >= mid;--i, ++j) {
		highPrice[j] = price[i];
	}

	int check[10000];
	int highIndex = 0;
	int lowIndex = 0;
	int sum = 0;
	for (int i = 0;i != n;++i) {
		if (i % 2 != 0) {
			check[i] = lowPrice[lowIndex];
			++lowIndex;
		}
		else {
			check[i] = highPrice[highIndex];
			++highIndex;
			sum += check[i];
		}
	}

	cout << endl << endl << "»тоговый чек:" << endl;
	for (int i = 0;i != n;++i) {
		cout << check[i] << " ";
	}

	cout << endl << "—умма к оплате: " << sum;
}