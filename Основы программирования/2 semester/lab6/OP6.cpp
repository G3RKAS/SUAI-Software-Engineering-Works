// Вариант 5

#include <iostream>
#include <math.h>
using namespace std;


// Класс обработки исключений
class array_error: public std::exception
{
private:
    string message;
public:
    array_error(const string& mes);
    const char* what() const override;
};

array_error::array_error(const string& message)
{
    this->message = message;
};

const char* array_error::what() const
{
    return message.c_str();
};

// Класс массив
class new_array
{ 
private:
    static const int len = 12;
    float arr[len];
public:
    new_array(float arr[], int len);
    float sum_odd_elements();
    float sum_between_negative();
    void compress_array();
    void print_array();
};

new_array::new_array(float arr[], int len)
{
    if (this->len != len)
        throw array_error("Размеры массива и предполагаемый размер разные");
    for (int i{ 0 }; i < this->len; i++)
    {
        this->arr[i] = arr[i];
    };
};

float new_array::sum_odd_elements()
{
    float sum = 0;

    for (int i{ 0 }; i < this->len; i++)
    {
        if (i % 2 == 1)
            sum += arr[i];
    };

    return sum;
}

float new_array::sum_between_negative()
{
    int left_negative_pos = -1;
    int right_negative_pos = -1;
    float sum = 0;

    for (int i{ 0 }; i < this->len; i++)
    {
        if (arr[i] < 0)
        {
            if (left_negative_pos == -1)
                left_negative_pos = i;
            right_negative_pos = i;
        }

    };

    if ((left_negative_pos == -1) || (right_negative_pos == -1))
        throw array_error("Отрицательные элементы отсутсвуют");
    else if (left_negative_pos + 1 == right_negative_pos)
        throw array_error("Между отрицательными числами нет элементов");
    else if (left_negative_pos == right_negative_pos)
        throw array_error("Пары отрицательных нет в массиве");

    for (int i = left_negative_pos+1; i < right_negative_pos; i++)
    {
        sum += arr[i];
    };

    return sum;
}

void new_array::compress_array()
{
    float nums[this->len];
    int pos = 0;

    for (int i{ 0 }; i < this->len; i++)
    {
        if (abs(this->arr[i]) <= 1)
            continue;
        else
        {
            nums[pos] = this->arr[i];
            pos++;
        }
    };

    for (pos; pos < this->len; pos++)
    {
        nums[pos] = 0;
    };

    for (int i{ 0 }; i < this->len; i++)
    {
        this->arr[i] = nums[i];
    };
}

void new_array::print_array()
{
    for (int i{ 0 }; i < this->len; i++)
    {
        cout << arr[i] << '\t';
    };
    cout << endl;
};

int main()
{
    setlocale(LC_ALL, "RUS");

    try
    {
        float nums[] = { 4, 5, 8, -34, 2, 4, 0, 0.5, 0.25, -3, -0.75, 23};
        int n = sizeof(nums) / sizeof(nums[0]);
        new_array arr(nums, n);

        cout << "Ваш массив: " << endl; arr.print_array();

        cout << "Сумма элементов на нечётных позициях: " << endl << arr.sum_odd_elements() << endl;

        cout << "Сумма элементов между отрицательными элементами: " << endl << arr.sum_between_negative() << endl;

        cout << "Сжатый массив с элементами превосходящими единицу: " << endl; arr.compress_array(); arr.print_array();
    }
    catch (const array_error& error) 
    {
        cout << "В процессе выполнения обработана ошибка: " << error.what() << endl;
    }
    catch (const exception& error)
    {
        cout << error.what() << endl;
    }
};
