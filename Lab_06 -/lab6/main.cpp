#include <iostream>
#include <string>
#include <climits>
#include <windows.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cctype>
#include <regex>

using namespace std;
using namespace std::chrono;

const int MAX_PHONE = 32767;
const int MAX_NAME_LENGTH = 100;
const regex NAME_REGEX("^[А-Яа-яЁёA-Za-z\\-\\s']+$");

struct PhoneRecord {
    int phoneNumber;
    string ownerName;
    PhoneRecord* next;
};

struct HashTable {
    PhoneRecord** table;
    int size;
    int collisionCount = 0;
};


bool isValidName(const string& name) {
    if (name.empty() || name.length() > MAX_NAME_LENGTH) {
        return false;
    }

    if (!regex_match(name, NAME_REGEX)) {
        return false;
    }

    if (name.find(' ') == string::npos) {
        return false;
    }

    if (name.find("  ") != string::npos || name.find("--") != string::npos || name.find("''") != string::npos) {
        return false;
    }

    return true;
}

void initHashTable(HashTable* ht, int tableSize) {
    ht->size = tableSize;
    ht->table = new PhoneRecord * [tableSize];
    for (int i = 0; i < tableSize; i++) {
        ht->table[i] = nullptr;
    }
    ht->collisionCount = 0;
}

void clearHashTable(HashTable* ht) {
    for (int i = 0; i < ht->size; ++i) {
        PhoneRecord* current = ht->table[i];
        while (current != nullptr) {
            PhoneRecord* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] ht->table;
}

int hashFunction(int key, int tableSize) {
    return key % tableSize;
}

void insertRecord(HashTable* ht, int phone, const string& name) {
    int index = hashFunction(phone, ht->size);
    if (ht->table[index] != nullptr) {
        ht->collisionCount++;
    }
    PhoneRecord* newRecord = new PhoneRecord;
    newRecord->phoneNumber = phone;
    newRecord->ownerName = name;
    newRecord->next = ht->table[index];
    ht->table[index] = newRecord;
}

PhoneRecord* findRecord(HashTable* ht, int phone) {
    int index = hashFunction(phone, ht->size);
    PhoneRecord* current = ht->table[index];

    while (current != nullptr) {
        if (current->phoneNumber == phone) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool deleteRecord(HashTable* ht, int phone) {
    int index = hashFunction(phone, ht->size);
    PhoneRecord* current = ht->table[index];
    PhoneRecord* prev = nullptr;

    while (current != nullptr) {
        if (current->phoneNumber == phone) {
            if (prev == nullptr) {
                ht->table[index] = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

void printTable(HashTable* ht) {
    cout << "\nТекущее состояние хеш-таблицы:\n";
    for (int i = 0; i < ht->size; ++i) {
        cout << "[" << i << "]: ";
        PhoneRecord* current = ht->table[i];
        while (current != nullptr) {
            cout << current->phoneNumber << " (" << current->ownerName << ")";
            if (current->next != nullptr) cout << " -> ";
            current = current->next;
        }
        cout << endl;
    }
    cout << endl;
}

int inputPhoneNumber() {
    int phone;
    while (true) {
        cout << "Введите номер телефона (" << MAX_PHONE << "): ";
        cin >> phone;

        if (cin.fail() || phone < 0 || phone > MAX_PHONE) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка! Номер должен быть от 0 до " << MAX_PHONE << endl;
        }
        else {
            cin.ignore();
            return phone;
        }
    }
}

string inputOwnerName() {
    string name;
    while (true) {
        cout << "Введите ФИО владельца: ";
        getline(cin, name);


        size_t start = name.find_first_not_of(" \t");
        if (start != string::npos) {
            name = name.substr(start);
            size_t end = name.find_last_not_of(" \t");
            name = name.substr(0, end + 1);
        }

        if (isValidName(name)) {
            return name;
        }

        cout << "Ошибка! Некорректное ФИО. Используйте только буквы, дефисы, апострофы и пробелы.\n";
        cout << "Пример правильного ввода: Иванов Иван Иванович или O'Connor John\n";
    }
}

void showMenu() {
    cout << "\nМеню управления телефонной книгой:\n";
    cout << "1. Добавить новую запись\n";
    cout << "2. Найти запись по номеру\n";
    cout << "3. Удалить запись\n";
    cout << "4. Показать всю таблицу\n";
    cout << "5. Исследовать хэш-таблицы\n";
    cout << "6. Выход\n";
    cout << "Выберите действие: ";
}

void testSearchTime(HashTable* ht, const vector<int>& phoneNumbers) {
    if (phoneNumbers.empty()) return;

    double totalTime = 0;
    for (int phone : phoneNumbers) {
        auto start = high_resolution_clock::now();
        findRecord(ht, phone);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        totalTime += duration.count();
    }

    double averageTime = totalTime / phoneNumbers.size();
    cout << "Среднее время поиска: " << averageTime << " микросекунд\n";
    cout << "Количество коллизий: " << ht->collisionCount << "\n";
    cout << "Коэффициент заполнения: ~" << (phoneNumbers.size() * 100 / ht->size) << "%\n\n";
}

void researchHashTables() {
    vector<int> sizes;
    int size, recordsCount;

    cout << "\n--- Исследование хэш-таблиц ---\n";
    cout << "Введите размеры таблиц через пробел (например, 16 32 64): ";
    cin.ignore();
    string sizesInput;
    getline(cin, sizesInput);

    size_t pos = 0;
    while ((pos = sizesInput.find(' ')) != string::npos) {
        size = stoi(sizesInput.substr(0, pos));
        sizes.push_back(size);
        sizesInput.erase(0, pos + 1);
    }
    if (!sizesInput.empty()) {
        sizes.push_back(stoi(sizesInput));
    }

    cout << "Введите количество записей для тестирования: ";
    cin >> recordsCount;

    vector<int> testPhones;
    vector<string> testNames;
    cout << "Введите " << recordsCount << " номеров телефонов:\n";
    for (int i = 0; i < recordsCount; ++i) {
        int phone = inputPhoneNumber();
        testPhones.push_back(phone);
        testNames.push_back("Test User " + to_string(i));
    }

    for (int size : sizes) {
        cout << "\n--- Таблица размером " << size << " ---\n";
        HashTable ht;
        initHashTable(&ht, size);

        for (int i = 0; i < recordsCount; ++i) {
            insertRecord(&ht, testPhones[i], testNames[i]);
        }

        testSearchTime(&ht, testPhones);
        clearHashTable(&ht);
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "RU");

    HashTable phoneBook;
    const int TABLE_SIZE = 12;
    initHashTable(&phoneBook, TABLE_SIZE);

    int choice;
    bool running = true;

    while (running) {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            int phone = inputPhoneNumber();
            string name = inputOwnerName();
            insertRecord(&phoneBook, phone, name);
            cout << "Запись добавлена успешно!\n";
            break;
        }
        case 2: {
            int phone = inputPhoneNumber();
            PhoneRecord* record = findRecord(&phoneBook, phone);
            if (record != nullptr) {
                cout << "Найдена запись: " << record->phoneNumber
                    << " - " << record->ownerName << endl;
            }
            else {
                cout << "Запись не найдена!\n";
            }
            break;
        }
        case 3: {
            int phone = inputPhoneNumber();
            if (deleteRecord(&phoneBook, phone)) {
                cout << "Запись удалена успешно!\n";
            }
            else {
                cout << "Запись не найдена!\n";
            }
            break;
        }
        case 4:
            printTable(&phoneBook);
            break;
        case 5:
            researchHashTables();
            break;
        case 6:
            running = false;
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова.\n";
        }
    }

    clearHashTable(&phoneBook);
    cout << "Программа завершена. До свидания!\n";
    return 0;
    int x1;
    int* pt = &x1;
    int** ptt = &pt;

    int* pw;

    *ptt = pw;
    *ptt = pw;
}