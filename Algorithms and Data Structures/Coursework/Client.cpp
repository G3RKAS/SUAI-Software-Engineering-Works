#include "Classes.h"
using namespace std;

// Функции класса клиент

Client::Client(string passport, string passport_info, string FIO, int year_bith, string adress)
{
	this->Passport = passport;
	this->PassportInfo = passport_info;
	this->FIO = FIO;
	this->YearOfBirth = year_bith;
	this->Adress = adress;
}

string Client::GetPassport() const
{
	return this->Passport;
}

string Client::GetPassportInfo() const
{
	return this->PassportInfo;
}

string Client::GetFIO() const
{
	return this->FIO;
}

int Client::GetYearBirth() const
{
	return this->YearOfBirth;
}

string Client::GetAdress() const
{
	return this->Adress;
}