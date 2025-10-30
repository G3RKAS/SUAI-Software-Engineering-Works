#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
using namespace std;

void LineSeparation(ifstream& Fbegin, ofstream& Fansw)
{
	string line;
	int num_len = 1;

	while (getline(Fbegin, line)) {
		for (int i = 0; i < line.length(); i++)
		{
			if ( isdigit(line[i]) && isdigit(line[i + 1])) 
			{
				num_len += 1;
			}
			if (line[i+1] == ' ' || i == line.length()-1)
			{
				if (num_len == 2)
				{
					Fansw << line << endl;
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
	string Fname, Foutput = "otvet.txt";
	ifstream Fbegin;
	ofstream Fansw;

	cout << "Введите путь и название файла для открытия: ";
	cin >> Fname;

	Fbegin.open(Fname);
	while (!Fbegin.is_open())
	{
		cout << "Не удалось открыть файл " << Fname << endl;
		cout << "Введите путь и название повторно: ";
		cin >> Fname;
		Fbegin.open(Fname);
	}

	Fansw.open(Foutput);

	LineSeparation(Fbegin, Fansw);

	Fbegin.close();
	Fansw.close();
}

