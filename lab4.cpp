#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

const int N = 512;
char line[N];
char removeChars[N];
char toSearch[N];


void task1() {
    cout << "Выберите: Ручной ввод (0) или Ввод с файла (1)" << "\n";
    int choice;
    cin >> choice;
    cin.ignore();
    ifstream file("text.txt");
    switch (choice)
    {
    case 0:
        cout << "Введите строку" << "\n";
        cin.getline(line , N);
        break;
    case 1:
        cout << "Чтение файла text.txt" << endl;
        file.getline(line, N);
        if (!file.is_open()) {
            cout << "Не удалось открыть файл, завершаю выполнение.";
        }
        file.close();
        break;
    default:
        cout << "Некорректный ввод" << "\n";
        break;
    }
}

void task2() {
    int countDot = 0, i = 0, j = 0;
    i = 0, j = 0;
    char prevSymb;
    while (line[i] != '\0') {
        if (ispunct(line[i]) != 0) {
            if (line[i] == '.' && prevSymb == '.') {
                countDot++;
                if (countDot <= 2) {
                    line[j++] = line[i];
                }
            }
            else if (ispunct(prevSymb) != 0) {
                line[j++] = ' ';
                i++;
            }
            else
            {
                line[j++] = line[i];
            }
        }
        else {
            line[j++] = line[i];
            countDot = 0;
        }
        prevSymb = line[i];
        i++;
    }
    line[j] = '\0';

    bool isSpace = false;
    i = 0, j = 0;
    while (line[i] != '\0') {
        if (line[i] != ' ') {
            line[j++] = line[i];
            isSpace = false;
        }
        else if (isSpace == false) {
            line[j++] = ' ';
            isSpace = true;
        }
        i++;
    }
    line[j] = '\0';

    i = 0;
    prevSymb = ' ';
    while (line[i] != '\0') {
        if (isalpha(line[i]) && prevSymb != ' ') {
            line[i] = tolower(line[i]);
        }
        prevSymb = line[i];
        i++;
    }
}

bool findDup(char* word) {
    for (int i = 0; word[i] != '\0'; ++i) {
        for (int j = i + 1; word[j] != '\0'; ++j) {
            if (word[i] == word[j]) {
                return true;
            }
        }
    }
    return false;
}

void task3() {
    int i = 0, j = 0;
    char word[20] = {};
    while (line[i] != '\0') {
        if (line[i] == ' ' || ispunct(line[i]) != 0) {
            if (findDup(word) == true) {
                cout << word << " ";
                for (int k = 0; word[k] != '\0'; k++) {
                    word[k] = 0;
                }
                j = 0;
                i++;
            }
            else {
                for (int k = 0; word[k] != '\0'; k++) {
                    word[k] = 0;
                }
                j = 0;
                i++;
            }
        }
        word[j] = line[i];
        j++;
        i++;

    }
}

void task4() {
    cin.ignore();
    cout << "Введите символы для удаления: ";
    cin.getline(removeChars, N);
    int i = 0, j = 0;
    while (line[i] != '\0') {
        bool toRemove = false;
        for (int k = 0; removeChars[k] != '\0'; k++) {
            if (line[i] == removeChars[k]) {
                toRemove = true;
                break;
            }
        }
        if (toRemove == false) {
            line[j++] = line[i];
        }
        i++;
    }
    line[j] = '\0';
}

void linearSearch(char* line, char* pattern) {


    int lenLine = strlen(line);
    int lenPat = strlen(pattern);
    int count = 0;
    
    for (int i = 0; i <= lenLine - lenPat; ++i) {
        int j;
        for (j = 0; j < lenPat; ++j) {
            if (line[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == lenPat) {
            cout << "Индекс начала подстроки: " << i << endl;
            count++;
        }
    }
    if (count == 0) {
        cout << "Подстрока не найдена" << endl;
    }

   
}

vector<int> computeLps(string pattern) {
    int n = pattern.length();
    vector<int> lps(n, 0);
    int len = 0;
    int i = 1;

    while (i < n) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

vector<int> kmp(string text, string pattern) {
    vector<int> lps = computeLps(pattern);
    vector<int> occurrences;
    int n = text.length();
    int m = pattern.length();
    int i = 0;
    int j = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            occurrences.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }

    return occurrences;
}

void task5() {
    cin.ignore();
    cout << "Введите строку, которую хотите найти: ";
    cin.getline(toSearch, N);
    cout << "Выберите способ поиска: Линейный поиск(0) или Алгоритм КМП(1)";
    int choice;
    cin >> choice;
    vector<int> occurrences = kmp(line, toSearch);
    switch (choice)
    {
    case 0:
        linearSearch(line, toSearch);
        break;
    case 1:

        if (occurrences.empty()) {
            cout << "Подстрока не найдена." << endl;
        }
        else {
            cout << "Индекс начала подстроки: ";
            for (int i : occurrences) {
                cout << i << " ";
            }
            cout << endl;
        }
        break;
    default:
        cout << "Некорректный ввод" << "\n";
        break;
    }
}

int main()
{
    setlocale(0, "");
    int choosetask;
    do {
        cout << "Выберите задание: ";
        cin >> choosetask;
        switch (choosetask)
        {
        case 1:
            task1();
            cout << line << "\n" << endl;
            break;
        case 2:
            task2();
            cout << line << "\n" << endl;
            break;
        case 3:
            task3();
            cout << "\n" << endl;
            break;
        case 4:
            task4();
            cout << line << "\n" << endl;
            break;
        case 5:
            task5();
            break;
        default:
            cout << "Некорректный ввод" << "\n" << endl;
            break;
        }
    } while (choosetask != 0);
}
