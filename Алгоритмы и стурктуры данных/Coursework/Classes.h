#pragma once
#include <iostream>
using namespace std;

// Класс Клиент
class Client
{
private:
	string Passport;	 // Номер паспорта
	string PassportInfo; // Кто выдал паспорт
	string FIO;			 // ФИО
	int YearOfBirth;	 // год рождения
	string Adress;		 // Адрес проживания

public:
	Client(string, string, string, int, string);
	string GetPassport() const;
	string GetPassportInfo() const;
	string GetFIO() const;
	int GetYearBirth() const;
	string GetAdress() const;
};

// Класс симкарты
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
	string SIM_ID;	   // Номер Симкарты
	Tarrif TarrifInfo; // Тарриф симкарты
	int YearRelease;   // Год выпуска
	bool Available;	   // Доступность

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

// Класс о владении симкартов клиентом
class SimOwning
{
private:
	string Passport;		 // Номер паспорта
	string SimID;			 // Номер симкарты
	string DateOfIssue;		 // Дата выдачи
	string DateOfExpiration; // Дата возврата

public:
	SimOwning(string, string);
	SimOwning(string, string, string, string);
	string GetPassport() const;
	string GetSimID() const;
	string GetDateOfIssue() const;
	string GetDateOfExpiration() const;
	void SetDateOfExpiration(string);
};