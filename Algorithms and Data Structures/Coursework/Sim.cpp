#include "Classes.h"
using namespace std;

Sim::Sim()
{
	this->SIM_ID = "-----------"; 
	this->TarrifInfo = Tarrif::Base;
	this->YearRelease = 0;
	this->Available = false;
}

Sim::Sim(string SIM_ID, Sim::Tarrif Tarrif, int YearRelease)
{
	this->SIM_ID = SIM_ID;
	this->TarrifInfo = Tarrif;
	this->YearRelease = YearRelease;
	this->Available = true;
}

string Sim::GetID() const
{
	return this->SIM_ID;
}

Sim::Tarrif Sim::GetTariff() const
{
	return this->TarrifInfo;
}

int Sim::GetYearRelease() const
{
	return this->YearRelease;
}

bool Sim::GetAvailable() const
{
	return Available;
}

void Sim::SetAvailable(bool Available)
{
	this->Available = Available;
}

string Sim::IsAvailable() const
{
	switch (Available)
	{
	case (true):
		return "��";
	case (false):
		return "���";
	}
	return "-";
}

string Sim::TariffToString() const
{
	switch (TarrifInfo)
	{
	case (Tarrif::Base):
		return "�������";
	case (Tarrif::Medium):
		return "�������+";
	case (Tarrif::Super):
		return "�����";
	case (Tarrif::Ultra):
		return "������";
	}
	return "";
}