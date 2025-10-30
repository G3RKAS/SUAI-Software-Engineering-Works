#include "Classes.h"
#include "SubFunctions.h"
using namespace std;

SimOwning::SimOwning(string Passport, string SimID)
{
	this->Passport = Passport;
	this->SimID = SimID;
	this->DateOfIssue = GetDateByTime(time(0));
	this->DateOfExpiration = "-";
}

SimOwning::SimOwning(string Passport, string SimID, string DateOfIssue, string DateOfExpiration)
{
	this->Passport = Passport;
	this->SimID = SimID;
	this->DateOfIssue = DateOfIssue;
	this->DateOfExpiration = DateOfExpiration;
}

string SimOwning::GetPassport() const
{
	return this->Passport;
}

string SimOwning::GetSimID() const
{
	return this->SimID;
}

string SimOwning::GetDateOfIssue() const
{
	return this->DateOfIssue;
}

string SimOwning::GetDateOfExpiration() const
{
	return this->DateOfExpiration;
}

void SimOwning::SetDateOfExpiration(string DateOfExpiration)
{
	this->DateOfExpiration = DateOfExpiration;
}