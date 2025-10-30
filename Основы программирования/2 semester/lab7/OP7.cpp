// Вариант 5

#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;


template <typename T>
class IsNegative
{
public:
    bool operator()(T element)
    {
        return (element < 0);
    }
};

template <typename T>
bool Greater(T x, T y)
{
    return x > y;
}

template <typename T>
class my_array {
private:
    static const int len = 10;
    T arr[len];
    int count_elem(T);
public: 
    my_array(T, T);
    void replace_zeros();
    void delete_repeats();
    void print();
    template <typename K>
    T max_elem(K fun);
};

template <typename T>
int my_array<T>::count_elem(T elem)
{
    int count = 0;
    for (int i{ 0 }; i < len; i++)
    {
        if (arr[i] == elem)
            count++;
    }
    return count;
}

template <typename T>
my_array<T>::my_array(T m_1, T m_2)
{
    srand(unsigned(time(0)));
    
    for (int i{ 0 }; i < len; i++)
    {
        arr[i] = m_1 + (m_2 - m_1) * rand() / RAND_MAX;
    }

};

template <typename T>
template <typename K>
T my_array<T>::max_elem(K fun)
{
    T max_elem = 0;
    for (int i{ 0 }; i < len; i++)
    {
        if (fun(abs(arr[i]), abs(max_elem)))
        {
            max_elem = arr[i];
        }
    }
    return max_elem;
};

template <typename T>
void my_array<T>::replace_zeros()
{
    IsNegative<T> IsNegative; // Объект-функция
    for (int i{ 0 }; i < len; i++)
    {
        if (IsNegative(arr[i]))
        {
            arr[i] = 0;
        }
    }
};

template <typename T>
void my_array<T>::delete_repeats()
{
    T nums[this->len];
    int pos = 0;


    for (int i{ 0 }; i < this->len; i++)
    {
        if ((count_elem(arr[i]) > 1) && (i != 0))
            continue;
        else
        {
            nums[pos] = this->arr[i];
            pos++;
        }
    };

    for (pos; pos < this->len; pos++)
    {
        nums[pos] = -999;
    };


    for (int i{ 0 }; i < this->len; i++)
    {
        this->arr[i] = nums[i];
    };

};

template <typename T>
void my_array<T>::print()
{
    for (int i{ 0 }; i < len; i++)
    {
        cout << arr[i] << setw(10);
    }
    cout << endl;
};

int main()
{
    setlocale(LC_ALL, "RUS");

    my_array<double> arr{-8.5, 6};


    cout << "1. \nВаш массив: ";
    arr.print();

    cout << "Максимальный элемент по абсолютному значению: " << arr.max_elem(Greater<double>);
    cout << endl;

    cout << "Заменяем отрицательные числа на 0" << endl;
    arr.replace_zeros();
    cout << "Ваш новый массив: ";
    arr.print();

    cout << "Удаляем повторения.." << endl;
    arr.delete_repeats();
    cout << "Ваш новый массив: ";
    arr.print();

    cout << endl;

    my_array<int> arr_2{ -10, 10 };


    cout << "2. \nВаш массив: ";
    arr_2.print();

    cout << "Максимальный элемент по абсолютному значению: " << arr_2.max_elem(Greater<int>);
    cout << endl;

    cout << "Заменяем отрицательные числа на 0" << endl;
    arr_2.replace_zeros();
    cout << "Ваш новый массив: ";
    arr_2.print();

    cout << "Удаляем повторения.." << endl;
    arr_2.delete_repeats();
    cout << "Ваш новый массив: ";
    arr_2.print();

};

