#include <iostream>
 
using namespace std;

struct CODE // Структура из 4 переменныъ
{
	unsigned short int n;
	unsigned short int e;
	unsigned short int c;
	unsigned short int p;
};

CODE request_data() // Функция запроса данных
{
	unsigned short int n, e, c, p;
	
	CODE code;

	cout << "Введите признак завершения программы P: ";
	cin >> p;
	if (cin.fail() || (cin.peek() != '\n') || !((p==0) || (p==1))) // Проверка на корректность и ограничения 
	{
		cout << "Составляющая P неверна!";
		exit(0); // Прекращение программы
	}
	code.p = p; // Добавление p в структуру

	cout << "Введите код причины прерывания(C): ";
	cin >> c;
	if (cin.fail() || (cin.peek() != '\n') || !((c >= 0) && (c <= 511))) // Проверка на корректность и ограничения 
	{
		cout << "Составляющая C неверна!";
		exit(0); // Прекращение программы
	}
	code.c = c; // Добавление с в структуру

	cout <<  "Введите признак ошибки(E): ";
	cin >> e;
	if (cin.fail() || (cin.peek() != '\n') || !((e == 0) || (e == 1))) // Проверка на корректность и ограничения 
	{
		cout << "Составляющая E неверна!";
		exit(0); // Прекращение программы
	}
	code.e = e; // Добавление е в структуру

	cout << "Введите номер канал(N): ";
	cin >> n;
	if (cin.fail() || (cin.peek() != '\n') || !((n >= 0) && (n <= 15))) // Проверка на корректность и ограничения 
	{
		cout << "Составляющая N неверна!";
		exit(0); // Прекращение программы
	}
	code.n = n; // Добавление n в структуру

	return code;
}

int main()
{ 
	setlocale(LC_ALL, "rus");
	
	unsigned short int x = 0;

	CODE code = request_data(); // Получение стукрутры 

	x = code.p;  // Добавление составляющей p
	x = 0 << 1 | x; // Добавление 0 в структуру
	x = code.c << 2 | x; // Добавление составляющей с
	x = code.e << 11 | x; // Добавление составляющей е
	x = code.n << 12 | x; // Добавление составляющей n

	cout << "Состояние канала: " << hex << x << endl;
}