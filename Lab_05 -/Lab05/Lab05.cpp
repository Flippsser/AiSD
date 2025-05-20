#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool areBracketsBalanced(const string& str) {
    stack<char> s;

    for (char c : str) {
        // Если символ - открывающая скобка, кладем в стек
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        }
        // Если символ - закрывающая скобка
        else if (c == ')' || c == ']' || c == '}') {

            if (s.empty()) {
                return false; // Если стек пуст, значит скобка не имеет пары
            }
            char top = s.top();
            s.pop();
            if ((c == ')' && top != '(') || (c == ']' && top != '[') || (c == '}' && top != '{')) {
                return false;
            }
        }
    }

    return s.empty();
}

int main() {
    setlocale(LC_ALL, "ru");
    string str;
    cout << "Введите строку: ";
    getline(cin, str);

    if (areBracketsBalanced(str)) {
        cout << "скобки расставлены верно" << endl;
    }
    else {
        cout << "скобки расставлены не верно" << endl;
    }

    return 0;
}
