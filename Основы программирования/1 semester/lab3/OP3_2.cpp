#include <iostream>

using namespace std;

unsigned short int request_data() // Запрос 16го числа 
{
	unsigned short int x;

	cin.unsetf(ios::dec); // Настройка ввода на 16е числа
	cin.setf(ios::hex);

	cout << "Введите состояние канала(16-е число)"  << endl;

	cin >> x;

	while (cin.fail() || (cin.peek() != '\n') ) // Проверка корректности
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Неверное 16-е число!" << endl;
		cin >> x;
	}

	return x;
}

int main()
{
	setlocale(LC_ALL, "rus");

	unsigned short int x;
	unsigned short int n, e, c, p;

	x = request_data(); // Запрос 16го числа

	n = x >> 12; // Составляющая n
	e = x >> 11 & 1; // Составляющая e
	c = x >> 2 & 0x1ff; // Составляющая c
	p = x & 1; // Составляющая p

	cout << "Составная N: " << dec << n << endl; // Вывод каждой составляющей
	cout << "Составная E: " << dec << e << endl;
	cout << "Составная C: " << dec << c << endl;
	cout << "Составная P: " << dec << p << endl;
}