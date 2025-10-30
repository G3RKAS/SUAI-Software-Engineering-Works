#include<iostream>
#include<cmath>

using namespace std;

struct VARS // Структура для промежутка/коэффициентов
{
	double a;
	double b;
	double c;
};

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

VARS request_data() // Функция запроса промежутка
{
	VARS x_int;

	double x;

	cout << "Введите левую границу: " << endl;
	cout << "Xmin = ";
	x = get_num();

	x_int.a = x; // Добавление Xmin в структуру

	cout << "Введите правую границу: " << endl;
	cout << "Xmax = ";
	x = get_num();
	while (x <= x_int.a) // Проверка на ограничения(больше левой границы)
	{
		x = get_num();
	}
	x_int.b = x; // Добавление Xmax в структуру

	cout << "Введите шаг интервала: " << endl;
	cout << "dx = ";
	x = get_num();
	while ((x <= 0) || (x>(x_int.b-x_int.a))) // Проверка на корректность и ограничения 
	{
		x = get_num();
	}
	x_int.c = x; // Добавление dx в структуру

	return x_int;
}

VARS request_data_2() // Функция запроса коэффициентов 
{
	VARS a_b_c;

	double x;

	cout << "Введите коэффициент а: " << endl;
	cout << "a = ";

	x = get_num();
	a_b_c.a = x; // Добавление а в структуру

	cout << "Введите коэффициент b: " << endl;
	cout << "b = ";

	x = get_num();
	a_b_c.b = x; // Добавление b в структуру

	cout << "Введите коэффициент c: " << endl;
	cout << "c = ";

	x = get_num();
	a_b_c.c = x; // Добавление c в структуру

	return a_b_c;
}

double calc(const double x, VARS a_b_c, bool & flag) // Рассчёт функции
{
	flag = false;
	double y = 0;

	double a = a_b_c.a;
	double b = a_b_c.b;
	double c = a_b_c.c;

	if ((a < 0) && (c != 0)) // Проверка трёх случаев по заданию
	{
		y = a * pow(x, 2) + b * x + c;
	}
	else if ((a > 0) && (c == 0))
	{
		y = (-a) / (x - c);
		if ((x - c) == 0)
		{
			flag = true;
		}
	}
	else 
	{
		y = a * (x + c);
	}

	return y;
}

void print_table(VARS x_int, VARS a_b_c) // Функция принта таблицы вычислений на промежутке
{
	double n = (x_int.b - x_int.a) / x_int.c;
	double x = x_int.a;
	bool f;
	double y;

	printf("/-------------------------------\\\n");
	printf("|      x        |      y        |\n");

	for (x; x <= n; x+= x_int.c)
	{
		y = calc(x, a_b_c, f);
		if (f) // Печать строк таблицы для каждого x 
		{
			printf("|%15.2f|%15s|\n", x, "Деление на нуль"); // Печать строки при делении на нуль
		}
		else
		{
			printf("|%15.2f|%15.2f|\n", x, y); // Обычная печать
		}
	}

	printf("\\-------------------------------/\n");
}

int main()
{
	setlocale(LC_ALL, "rus");

	VARS x_int = request_data(); // Запрос промежутка
	VARS a_b_c = request_data_2(); // Запрос коэффициентов 

	print_table(x_int, a_b_c); // Принт таблицы вычислений
}

