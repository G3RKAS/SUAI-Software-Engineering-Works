#pragma once
#include <iostream>
using namespace std;

// ����� ������
class Client
{
private:
	string Passport;	 // ����� ��������
	string PassportInfo; // ��� ����� �������
	string FIO;			 // ���
	int YearOfBirth;	 // ��� ��������
	string Adress;		 // ����� ����������

public:
	Client(string, string, string, int, string);
	string GetPassport() const;
	string GetPassportInfo() const;
	string GetFIO() const;
	int GetYearBirth() const;
	string GetAdress() const;
};

// ����� ��������
class Sim
{
public:
	enum class Tarrif
	{
		Base = 1,
		Medium = 2,
		Super = 3,
		Ultra = 4
	};

private:
	string SIM_ID;	   // ����� ��������
	Tarrif TarrifInfo; // ������ ��������
	int YearRelease;   // ��� �������
	bool Available;	   // �����������

public:
	Sim();
	Sim(string, Tarrif, int);
	string GetID() const;
	Tarrif GetTariff() const;
	int GetYearRelease() const;
	bool GetAvailable() const;
	string IsAvailable() const;
	string TariffToString() const;
	void SetAvailable(bool);
};

// ����� � �������� ��������� ��������
class SimOwning
{
private:
	string Passport;		 // ����� ��������
	string SimID;			 // ����� ��������
	string DateOfIssue;		 // ���� ������
	string DateOfExpiration; // ���� ��������

public:
	SimOwning(string, string);
	SimOwning(string, string, string, string);
	string GetPassport() const;
	string GetSimID() const;
	string GetDateOfIssue() const;
	string GetDateOfExpiration() const;
	void SetDateOfExpiration(string);
};