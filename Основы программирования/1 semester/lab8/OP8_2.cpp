#include <iostream>
#include <Windows.h>
#include <cstdio>

using namespace std;

void LineSeparation(FILE *Fbegin, FILE *Fansw)
{
	const int n = 1000;
	char line[n]= "";
	int num_len = 1;

	while (fgets(line, n, Fbegin)) {
		for (int i = 0; i < strlen(line); i++)
		{
			if (isdigit(line[i]) && isdigit(line[i + 1]))
			{
				num_len += 1;
			}
			if (line[i + 1] == ' ' || i == strlen(line) - 1)
			{
				if (num_len == 2)
				{
					fputs(line, Fansw);
					break;
				}
				num_len = 1;
			}
		}
		num_len = 1;
	}

}

int main() {
	setlocale(LC_ALL, "ru");
	const int n = 1000;
	char Fname[n], Foutput[n] = "otvet.txt";
	FILE *Fbegin;
	FILE *Fansw;

	cout << "Введите путь и название файла для открытия: ";
	cin >> Fname;

	errno_t erro = fopen_s(&Fbegin, Fname, "r");
	while (erro!=0)
	{
		cout << "Не удалось открыть файл " << Fname << endl;
		cout << "Введите путь и название повторно: ";
		cin >> Fname;
		errno_t erro = fopen_s(&Fbegin, Fname, "r");
	}

	erro = fopen_s(&Fansw, Foutput, "w");

	LineSeparation(Fbegin, Fansw);

	fclose(Fbegin);
	fclose(Fansw);
}

