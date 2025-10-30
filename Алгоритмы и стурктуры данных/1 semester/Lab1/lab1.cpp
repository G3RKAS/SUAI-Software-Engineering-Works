// Вариант 16
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif

#include <iostream>
#include <iomanip>

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

    n = get_num_int();

    while (n <= 0) // Проверка на корректный ввод
    {
        cout << "Повторите ввод: ";
        n = get_num_int();
    }

    return n;
}

void fill_arr(int* numbers, const unsigned int n) 
{
    srand(time(NULL));
    int min = -1 * ((n / 2) - 1);
    int max = (n / 2);

    for (unsigned int i = 0; i < n; i++) // Заполнение массива
    {
        numbers[i] = (min) + rand() % (max - min + 1);
    }
}

void reduce_even(int* numbers, const unsigned int n)
{
    for (unsigned int i = 0; i < n; i++) // Поиск чётных и уменьшение на 2
    {
        if (numbers[i] % 2 == 0)
        {
            numbers[i] /= 2;
        }
    }
}

void print_zero(int counts)
{
    cout << "Количество нулевых элементов: " << counts;
}

void print_arr(int* numbers, const unsigned int n)
{
    for (unsigned int i = 0; i < n; i++) // Вывод массива
    {
        cout << numbers[i] << setw(5);
    }
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "rus");

    cout << "Введи размерность массива целым неотрицательным числом (!=0)!" << endl;
    cout << "n = ";

    unsigned int n = request_len();

    int* numbers = new int[n];
    int counts = 0;
    int choose;

    fill_arr(numbers, n);

    cout << "Ваш массив заполненный случайными числами: " << endl;
    print_arr(numbers, n);

    while (true)
    {
        cout << "Выберите дальнейшее действие: " << endl;
        cout << "1. Уменьшить все чётные значения в два раза" << endl;
        cout << "2. Подсчитать количество нулевых элементов" << endl;
        cin >> choose;

        if (choose == 1)
        {
            reduce_even(numbers, n);
            cout << "Ваш массив преобразован: " << endl;
            print_arr(numbers, n);
            break;
        }
        else if (choose == 2)
        {
            for (unsigned int i = 0; i < n; i++) 
            {
                if (numbers[i] == 0)
                {
                    counts += 1;
                }
            }

            print_zero(counts);
            break;
        }
    }

    delete[] numbers;

    // Для обнаружения утечек памяти 
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtDumpMemoryLeaks();

}
