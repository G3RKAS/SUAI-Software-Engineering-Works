#define _USE_MATH_DEFINES

#include<iostream>
#include<cmath>
#include <limits>

using namespace std;

double degree2radian(const double angle) // Функция перевода градусов в радианы
{
    return angle * M_PI / 180; 
}

double floor_2(const double number) // Округление числа до двух знаков после запятой
{
    return floor(number * 100) / 100;
}

double equation1(const double angle) // Функция подсчёта первого выражения
{
    double a; // Инциализация переменных
    double b;

    a = floor_2(sin(2 * angle) + sin(5 * angle) - sin(3 * angle)); // Присвоение значение числителя
    b = floor_2(cos(angle) + 1 - 2 * pow(sin(2 * angle), 2)); // Присвоение значения знаменателя

    if (b == 0)
    {
        return 0; // Если знаметатель ноль, вернёт ноль
    }
    else
    {
        return a / b; // Иначе посчитает выражение
    }
}

double request() // Функция запроса угла
{
    double a;

    cout << "Привет! Введи угол в градусах!" << endl;
    cout << "a = ";

    cin >> a;

    while (cin.fail() || (cin.peek() != '\n')) // Проверка на корректный ввод
    {
        cin.clear(); // Очищение флага ошибки
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера запроса
        cout << "Неверное значение! Введи заново" << endl;
        cout << "a = ";
        cin >> a;
    }

    return a;
}

int main()
{
    setlocale(LC_ALL, "rus");

    double a;

    a = request(); // Запрос данного

    a = degree2radian(a); // Перевод в радианы

    cout << "Уравнение 1 при " << a << " радиан: " << equation1(a) << endl; // Вывод значений выражений
    cout << "2*Синус при " << a << " радиан: " << 2 * sin(a);
}