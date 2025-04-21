#include "ctime"
#include <iostream>
#include <string>

using namespace std;

// ������� ������� � ������� ������
string GetDateByTime(time_t arg1)
{
	tm date_struct;
	char s[40];
	localtime_s(&date_struct, &arg1);
	strftime(s, 40, "%d.%m.%Y", &date_struct);

	return s;
}

// ������� ��������� ������
bool IsPassportValid(string ID)
{
	if (ID.length() != 11)
	{
		return false;
	}

	for (int i{0}; i < ID.length(); i++)
	{
		if (i == 4)
		{
			if (ID[4] == '-')
				continue;
			else
				return false;
		}
		else if (isdigit(ID[i]))
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool IsSimValid(string ID)
{
	if (ID.length() != 11)
	{
		return false;
	}

	for (int i{0}; i < ID.length(); i++)
	{
		if (i == 3)
		{
			if (ID[3] == '-')
				continue;
			else
				return false;
		}
		else if (isdigit(ID[i]))
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool IsYearValid(int year)
{
	if (to_string(year).length() != 4)
	{
		return false;
	}
	return true;
}

// ������� ������� ���������� ������

string GetPassportNo()
{
	string x;

	getline(cin, x);

	while (not(IsPassportValid(x)))
	{
		cout << "���������� ������: NNNN-NNNNNN" << endl;
		cout << "��������� ����: ";
		getline(cin, x);
	}

	return x;
}

string GetSimNo()
{
	string x;

	getline(cin, x);

	while (not(IsSimValid(x)))
	{
		cout << "���������� ������: NNN-NNNNNNN" << endl;
		cout << "��������� ����: ";
		getline(cin, x);
	}

	return x;
}

int GetInt(int a = 0, int b = 0)
{
	bool bInRange = true;
	if (a == b)
	{
		bInRange = false;
	}

	int x;

	cin >> x;

	while (cin.fail() or (cin.peek() != '\n') or (bInRange and not((x >= a and x <= b))))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "��������� ����: ";
		cin >> x;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return x;
}

int GetValidYear()
{
	int x;

	cin >> x;

	while (cin.fail() or (cin.peek() != '\n') or not(IsYearValid(x)))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "��������� ����: ";
		cin >> x;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return x;
}
