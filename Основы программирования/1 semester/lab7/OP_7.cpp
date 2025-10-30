#include<iostream>
#include <Windows.h>

using namespace std;

int find_word(char* a, char* b) // Выделяет первое слово из строки
{
    int j = 0;
    int f = 0;

    int min_space = -1;
    int max_space = 1;

    for (int i = 0; a[i]; i++)
    {
        if ((a[i] == ' ') && ((a[i+1] != '\0') && (a[i + 1] != ' ')))
        {
            min_space = i;
        }
        else if (((a[i] != ' ') && (a[i] != '\n')) && ((a[i + 1] == '\0') || (a[i + 1] == ' ')))
        {
            max_space = i;
            break;
        }
    }

    for (int i = min_space+1; i != max_space+1; i++)
    {
        if (min_space+2 == max_space)
        {
            f = 1;
        }
        else if (j > 0)
        {
            f = 0;
        }
        b[j++] = a[i];
    }
    b[j] = '\0';
    return f;
}

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251);

    const int n = 256;
    char a[n];
    char b[n];
    int f;

    cout << "Внимание! Размер сообщения " << n-1 << " символa(ов)" << endl;
    cout << "Введи сообщение: " << endl;
    
    cin.getline(a, n);

    f = find_word(a, b);

    if (f == 0)
    {
        cout << "Твоё сообщение: " << a << endl;
        cout << "Найденое слово: " << b << endl;
    }
    else if (f == 1)
    {
        cout << "Сообщение пустое!" << endl;
    }
}