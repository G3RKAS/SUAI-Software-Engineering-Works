// Вариант 10
#include <iostream>

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

unsigned int get_u_int()
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

void full_array(int* array, unsigned int n)
{
    for (unsigned int i = 0; i < n; i++) // Заполнение массива
    {
        array[i] = get_num_int();
    }
}

void show_array(int* array, unsigned int n)
{
    for (unsigned int i = 0; i < n; i++) 
    {
        cout << array[i] << "\t";
    }
    cout << endl;
}

int find_elem(int* array, unsigned int n, int find)
{
    for (unsigned int i = 0; i < n; i++)
    {
        if (array[i] == find)
        {
            return i;
        }
    }
    return -1;
}

void delete_elem(int*& array, unsigned int &n, int find)
{
    int* arr = new int[n - 1];

    for (unsigned int i = 0; i < n; i++) 
    {
        if (i >= find)
            arr[i] = array[i+1];
        else
            arr[i] = array[i];
        
    }
    delete[] array;
    array = arr;
    n--;
}

int ar_min(int* array, unsigned int n)
{
    int mins = pow(10, 5);
    for (unsigned int i = 0; i < n; i++)
    {
        if (array[i] < mins)
        {
            mins = array[i];
        }
    }
    return mins;
}

int ar_max(int* array, unsigned int n)
{
    int maxs = pow(-10, 5);
    for (unsigned int i = 0; i < n; i++)
    {
        if (array[i] > maxs)
        {
            maxs = array[i];
        }
    }
    return maxs;
}

int count_sort(int*& array, unsigned int n) // Counting sort
{
    int ar_mins = ar_min(array, n);
    int ar_maxs = ar_max(array, n);

    int* arr = new int[ar_maxs - ar_mins + 1];
    int* arrs = new int[n];

    for (unsigned int x = 0; x < (ar_maxs - ar_mins + 1); x++)
    {
        arr[x] = 0;
    }
    for (unsigned int y = 0; y < n; y++)
    {
        arr[array[y] - ar_mins] += 1;
    }

    unsigned int j;
    unsigned int smeh = 0;
    for (unsigned int i = 0; i < (ar_maxs - ar_mins + 1); i++)
    {
        
        int ind = arr[i];
        for (j = 0; j < (ind); j++)
        {
            arrs[smeh] = i + ar_mins;
            smeh++;
        }
    }

    int unic = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        if (arr[i] == 1)
            unic += 1;
    }
    
    delete[] arr;
    delete[] array;
    array = arrs;

    return unic;
}

void add_elem(int*& array, unsigned int& n, int find)
{
    int* arr = new int[n + 1];

    for (unsigned int i = 0; i < n; i++)
    {
        arr[i] = array[i];
    }
    arr[n] = find;
    delete[] array;
    array = arr;
    n++;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int choice;

    cout << "Добро пожаловать в программу сортировки." << endl;
    cout << "Введите длину массива: " << endl;
    unsigned int n = get_u_int();
    int* array = new int[n];
    bool full = false;

    while (true)
    {
        cout << "Выберите дальнейшее действие" << endl;
        cout << "1. Задать массив" << endl;
        if (full)
        {
            cout << "2. Вывести массив" << endl;
            cout << "3. Добавить элемент" << endl;
            cout << "4. Удалить элемент" << endl;
            cout << "5. Найти элемент" << endl;
            cout << "6. Отсортировать массив" << endl;
        }
        cout << "7. Выход" << endl;
        choice = get_u_int();

        if (choice == 1)
        {
            system("cls");
            cout << "Заполните массив: " << endl;
            full_array(array, n);
            full = true;
        }
        else if (choice == 2)
        {
            system("cls");
            cout << "Ваш массив: " << endl;
            show_array(array, n);
        }
        else if (choice == 3)
        {
            system("cls");
            cout << "Введите элемент для добавления: " << endl;
            int choc;
            choc = get_num_int();
            add_elem(array, n, choc);
            count_sort(array, n);
        }
        else if (choice == 4)
        {
            system("cls");
            cout << "Введите элемент для удаления: " << endl;
            int choc;
            choc = get_num_int();
            int i = find_elem(array, n, choc);
            if (i >= 0)
            {
                if (n == 1)
                {
                    delete[] array;
                    full = false;
                    cout << "Массив удалён" << endl;
                }
                else
                {
                    delete_elem(array, n, i);
                    cout << "Удалён элемент " << choc << " на позиции " << i << endl;
                }
            }
            else
            {
                cout << "Не найдено." << endl;
            }
        }
        else if (choice == 5)
        {
            choice:
            system("cls");
            cout << "Выберите дальнейшее действие" << endl;
            cout << "1. Поиск по позиции" << endl;
            cout << "2. Поиск по содержимому" << endl;
            cout << "3. Назад" << endl;
            int choc;
            choice = get_u_int();
            if (choice == 1)
            {
                system("cls");
                cout << "Введите позицию элемента для вывода: " << endl;
                choc = get_num_int();
                if ((choc > n) || (choc < 0))
                {
                    cout << "Выход за границы массива." << endl;
                }
                else 
                {
                    cout << "Найденный элемент: " << array[choc] << endl;
                }
                    
            }
            else if (choice == 2)
            {
                system("cls");
                cout << "Введите cодержимое для поиска: " << endl;
                choc = get_num_int();
                int i = find_elem(array, n, choc);
                if (i >= 0)
                {
                    cout << "Элемент " << choc << " на позиции " << i << endl;
                }
                else
                {
                    cout << "Не найдено." << endl;
                }

            }
            else if (choice == 3)
            {
                system("cls");
            }
            else
            {
                goto choice;
            }
        }
        else if (choice == 6)
        {
            system("cls");
            int unic = count_sort(array, n);
            cout << "Массив отсортирован." << endl;
            cout << "Количество уникальных элементов: " << unic << endl;
        }
        else if (choice == 7)
        {
            cout << "Заверщение работы..." << endl;
            break;
        }
        else
        {
            system("cls");
        }
    }

    delete[] array;
}

