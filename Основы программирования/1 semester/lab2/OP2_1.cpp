#include<iostream>
#include <limits>
#include <math.h>

using namespace std;

double get_num() // Запрос и проверка числа на корректность
{
    double x;

    cin >> x;
    while (cin.fail() || (cin.peek() != '\n')) // Проверка на корректность
    {
        cin.clear(); // Очищение флага ошибки
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера запроса
        cout << "Повторите ввод: ";
        cin >> x;
    }

    return x;
}

double request(double &y) // Функция запроса координаты x
{
    double x;

    cout << "Введите координаты точек" << endl;
    cout << "x = ";
    x = get_num();
    cout << "y = ";
    y = get_num();


    return x;
}

bool check_right(const double x, const double y) // Функция проверки вхождения в 1 четверть
{

    if ((x >= 0 && x <= 1) && (y >= -1 && y <= 1))
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool check_left(const double x, const double y) // Функция проверки вхождения во 2 четверть
{

    if ((x >= -1 && x <= 0) && (y >= -1 && y <= 1) && (sqrt(pow(x, 2) + pow(y, 2)) <= 1))
    {
        return true;
    }
    else
    {
        return false;
    }

}

int main()
{
    setlocale(LC_ALL, "rus");

    double x, y;

    cout << "Привет! Введи координаты точки!" << endl;

    x = request(y);// Запрос координат

    if (check_right(x, y) || check_left(x, y)) // Проверки на каждую четверть
    {
        cout << "Точка входит в область" << endl;
        return 1;
    }

    cout << "Точка не входит в область" << endl;

}