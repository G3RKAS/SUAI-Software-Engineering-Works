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

int get_num() // Запрос и проверка числа int на корректность
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


unsigned request_len() // Запрос размера массива
{
    int n;

    cout << "Введи размерность массива целым неотрицательным числом (!=0)!" << endl;
    cout << "n = ";

    n = get_num();

    while (n <= 0) // Проверка на корректный ввод
    {
        n = get_num();
    }

    return n;
}

void fill_matrix(int** matrix, int n) // Заполнение переданного массива с клавиатуры
{
    cout << "Матрица принимает только целые значения" << endl;
    for (int i = 0; i < n; i++)   // строки
    {
        cout << "Ввод " << i + 1 << " строки.." << endl; 
        for (int j = 0; j < n; j++)   //столбцы массива
        {
            cout << "Ввод " << j + 1 << " элемента: ";
            matrix[i][j] = get_num();                //запоминаем введенное значение
        }
    }
}

unsigned task1(int** matrix, int n, bool &flag) // 1 Задание - Найти кол-во столбов с хотя бы одним нулём
{
    unsigned s_count = 0;
    flag = true;

    cout << "Начинаем считать количество столбов с нулями..." << endl;
    for (int i = 0; i < n; i++) // столбцы
    {
        for (int j = 0; j < n; j++)   // строки
        {
            if (matrix[j][i] == 0)
            {
                s_count += 1;
                break;
            }
        }
    }

    if (s_count == 0)
    {
        flag = false;
    }

    return s_count;
}

int task2(int** matrix, int n, bool& flag) // 2 Задание - Найти номер строки в которой наибольшая серия одинаковых элементов
{
    int s_number = -1, pattern = -1, sum_l = -1;
    int sum = 1;

    flag = true;

    cout << "Начинаем искать строку с наибольшей серией одинаковых элементов..." << endl;
    for (int i = 0; i < n; i++) // строки
    {
        pattern = -1;

        for (int j = 0; j < n; j++)   // столбцы
        {
            if (matrix[i][j] == pattern)
            {
                sum += 1;
            }
            pattern = matrix[i][j];
        }

        if ((sum > sum_l) && (sum != 1))
        {
            s_number = i;
        }

        if (sum == n)
        {
            break;
        }
           

        sum_l = sum;
        sum = 1;

    }

    if (s_number == -1)
    {
        flag = false;
    }

    return s_number;
}

int main()
{
    setlocale(LC_ALL, "rus");

    unsigned n = request_len();
    unsigned s_count;
    int s_number;
    bool f;

    int** matrix; // Создание матрицы nxn c целочисленными данными
    matrix = new int* [n];
    for (unsigned i = 0; i < n; i++)
        matrix[i] = new int[n];

    fill_matrix(matrix, n);

    cout << "Ваша матрица:" << endl;
    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < n; j++)
        {
            cout << matrix[i][j] << '\t';
        }
        cout << endl;
    }
   
    s_count = task1(matrix, n, f);
    if (!f)
    {
        cout << "В матрице нет столбцов с нулевыми элементами" << endl;
    }
    else
    {
        cout << "Количество столбцов: " << s_count << endl;
    }
    

    s_number = task2(matrix, n, f);
    if (!f)
    {
        cout << "В матрице нет строк с серией одинаковых элементов" << endl;
    }
    else
    {
        cout << "Номер строки: " << s_number + 1 << endl;
    }


    for (unsigned i = 0; i < n; i++) // Освобождение памяти
        delete matrix[i];
    delete[] matrix;

    // Для обнаружения утечек памяти 
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtDumpMemoryLeaks();
}