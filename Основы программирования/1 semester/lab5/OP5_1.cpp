// Для обнаружения утечек памяти 
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif

#include<iostream>;

using namespace std;

int get_num_int() // Запрос и проверка числа на корректность
{
    int x;

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

unsigned int request_len()
{
	int n;

    cout << "Введи размерность массива целым неотрицательным числом (!=0)!" << endl;
    cout << "n = ";

	n = get_num_int();
	
    while (n <= 0) // Проверка на корректный ввод
    {
        cout << "Повторите ввод: ";
        n = get_num_int();
    }

    return n;
}

void requst_arr(int* numbers, const unsigned int n) // Заполнение массива
{
    unsigned int i = 0;

    cout << "Начинай вводить значения массива" << endl;

    while (i < n) // Заполнение массива
    {
        numbers[i] = get_num_int();
        i++;
    }
    cout << "Массив введён" << endl;
}

int task1(int *numbers, const unsigned int n) // Решение первого задания (Произведение элементов на чётных позициях)
{
    cout << "Начинаем считать произведение элементов чётных позиций..." << endl;

    int S = 1;

    for (unsigned int i{ 0 }; i < n; i++) // Перебор каждого индекса
    {
        if ((i % 2) == 0) // Проверка индекса на чётность
        {
            S = S * numbers[i]; // Произведение
        }
    }

    return S;
}

int task2(int *numbers, const unsigned int n, int &flag) // Решение второго задания (Сумма элементов между крайними нулями)
{
    cout << "Начинаем считать сумму элементов между первым и последним нулём..." << endl;

    int S = 0;
    unsigned int k_right = -1, k_left = -1;
    flag = 0;

    for (unsigned int i{ 0 }; i < n; i++)// Перебор элементов и нахождение двух крайних нулей и присвоение их индексов переменным
    {
        if (numbers[i] == 0)
        {
            if (k_left == -1)
            {
                k_left = i;
            }
            k_right = i;      
        }
    }

    if ((k_right == -1) && (k_left == -1)) // Вывод на каждый из случаев
    {
        flag = 1;
    }
    else if (k_right == k_left)
    {
        flag = 2;
    }
    else if ((k_left + 1) == k_right)
    {
        flag = 3;
    }
    else
    {
        for (unsigned int i{ k_left + 1 }; i < k_right; i++)// Перебор элементов между нулями и сложение
        {
            S += numbers[i];
        }
    }

    return S;
}

void task3(int *numbers_copy, int *numbers, const unsigned int n) // Cортировка массива по убыванию методом bubblesort
{
    cout << "Начинаем пересобирать массив..." << endl;

    int n1 = n;

    for (unsigned int i = 0; i < n; i++)
    {
        numbers_copy[i] = numbers[i];
    }

    while (n1--)
    {
        bool swapped = false;

        for (int i = 0; i < n1; i++)
        {
            if (numbers_copy[i] < numbers_copy[i + 1])
            {
                swap(numbers_copy[i], numbers_copy[i + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    unsigned int n = request_len();
    int S;
    int *numbers = new int[n];
    int *numbers_copy = new int[n];
    int f;

    requst_arr(numbers, n);

    cout << "Произведение элементов на чётных позициях: " << task1(numbers, n) << endl;

    S = task2(numbers, n, f);

    if (f == 0)
    {
        cout << "Сумма элементов перед первым и последним нулём: " << S << endl;
    }
    else if (f == 1)
    {
        cout << "В массиве нет нулей" << endl;
    }
    else if (f == 2)
    {
        cout << "В массиве один нуль" << endl;
    }
    else
    {
        cout << "Нет элементов между нулями" << endl;
    }

    task3(numbers_copy, numbers, n);

    for (unsigned int i{ 0 }; i < n; i++)
    {
        cout << numbers_copy[i] << '\t';
    }

    delete[] numbers;
    delete[] numbers_copy;

    // Для обнаружения утечек памяти 
    _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE ); 
    _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT ); 
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE ); 
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT ); 
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE ); 
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT ); 
    _CrtDumpMemoryLeaks();

}

