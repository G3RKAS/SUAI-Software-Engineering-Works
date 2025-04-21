#include "SimTable.h"
#include "SimOwningList.h"

Sim SimTable::DeleteSign = Sim();

// Конструктор хэш-таблицы
SimTable::SimTable()
{
	SimInfo = new Sim*[TableSize];
	for (int i{0}; i < TableSize; i++)
	{
		SimInfo[i] = nullptr;
	}
}

// Деструктор таблицы
SimTable::~SimTable()
{
	for (int i{0}; i < TableSize; i++)
	{
		if (SimInfo[i] == &SimTable::DeleteSign)
		{
			continue;
		}
		delete SimInfo[i];
	}
	delete SimInfo;
	SimInfo = nullptr;
}

// Хэш-функция
int GetHash(string SIMID)
{
	int hash = 0;
	for (int i{0}; i < SIMID.length(); i++)
	{
		int CharOfID = SIMID[i];
		hash += (int)pow((CharOfID * (i + 1)), 2);
	}
	hash = hash % SimTable::TableSize;

	return hash;
}

// Добавление элемента в таблицу
bool AddSim(SimTable& SimInfos, Sim* SimData)
{
	int SimKey = GetHash(SimData->GetID());

	int i = 0;
	while (SimInfos.SimInfo[SimKey] and SimInfos.SimInfo[SimKey] != &SimTable::DeleteSign)
	{
		i++;
		if (i >= SimTable::TableSize)
		{
			return false;
		}
		SimKey = (SimKey + 1) % SimTable::TableSize;
	}

	SimInfos.SimInfo[SimKey] = SimData;
	return true;
}

// Удаление элемента
bool DeleteSim(SimTable& SimInfos, string SimID)
{
	int SimKey = GetHash(SimID);

	int i = 0;
	while (SimInfos.SimInfo[SimKey])
	{
		if (SimInfos.SimInfo[SimKey]->GetID() == SimID)
		{
			delete SimInfos.SimInfo[SimKey];
			SimInfos.SimInfo[SimKey] = nullptr;
			SimInfos.SimInfo[SimKey] = &SimTable::DeleteSign;
			return true;
		}
		else
		{
			i++;
			if (i >= SimTable::TableSize)
			{
				return false;
			}
			SimKey = (SimKey + 1) % SimTable::TableSize;
		}
	}

	return false;
}

// Поиск элемента
Sim* FindSim(SimTable& SimInfos, string SimID)
{
	int SimKey = GetHash(SimID);

	int i = 0;
	while (SimInfos.SimInfo[SimKey])
	{
		if (SimInfos.SimInfo[SimKey]->GetID() == SimID)
		{
			return SimInfos.SimInfo[SimKey];
		}
		else
		{
			i++;
			if (i >= SimTable::TableSize)
			{
				return nullptr;
			}
			SimKey = (SimKey + 1) % SimTable::TableSize;
		}

	}

	return nullptr;
}

// Очистка памяти
void ClearAllSim(SimTable& SimInfos)
{
	for (int i{0}; i < SimTable::TableSize; i++)
	{
		if (SimInfos.SimInfo[i] == &SimTable::DeleteSign)
		{
			continue;
		}
		delete SimInfos.SimInfo[i];
		SimInfos.SimInfo[i] = nullptr;
	}
}

// Получение случайного номера симкарты
string GetRandomSimID()
{
	string SIMID = "";

	for (int i{0}; i < 11; i++)
	{
		if (i == 3)
		{
			SIMID += "-";
		}
		else
		{
			SIMID += '0' + rand() % (('9') - ('0'));
		}
	}

	return SIMID;
}

// Проверка на пустоту таблицу
bool IsEmpty(SimTable& SimInfos)
{
	for (int i{0}; i < SimTable::TableSize; i++)
	{
		Sim* Sim = SimInfos.SimInfo[i];
		if ((Sim) and (Sim != &SimTable::DeleteSign))
		{
			return false;
		}
	}
	return true;
}

// Вывод всех симкарт
void PrintAllOfSims(SimTable& SimInfos)
{
	for (int i{0}; i < SimTable::TableSize; i++)
	{
		Sim* Sim = SimInfos.SimInfo[i];
		if ((Sim) and (Sim != &SimTable::DeleteSign))
		{
			cout << endl;
			cout << "Номер SIM " << Sim->GetID() << endl;
			cout << "Тариф: " << Sim->TariffToString() << endl;
			cout << "Год выпуска: " << Sim->GetYearRelease() << endl;
			cout << "Наличие: " << Sim->IsAvailable() << endl;
		}
	}
}

// Вывод всех симкарт по тарифу
void PrintAllOfSimsByTarrif(SimTable& SimInfos, Sim::Tarrif TarrifInfo, int& count)
{
	for (int i{0}; i < SimTable::TableSize; i++)
	{
		Sim* Sim = SimInfos.SimInfo[i];
		if ((Sim) and (Sim != &SimTable::DeleteSign) and (Sim->GetTariff() == TarrifInfo))
		{
			count++;
			cout << endl;
			cout << "Номер SIM " << Sim->GetID() << endl;
			cout << "Тариф: " << Sim->TariffToString() << endl;
			cout << "Год выпуска: " << Sim->GetYearRelease() << endl;
		}
	}
}

// Удаление всех симкарт и корректировка других структур
void ClearAllSims(SimTable& SimInfos, SimOwningList* OwningList)
{
	for (int i{0}; i < SimTable::TableSize; i++)
	{
		Sim* SimInfo = SimInfos.SimInfo[i];
		if (not(SimInfo) or (SimInfo == &SimTable::DeleteSign))
		{
			continue;
		}

		SimOwning* OwningInfo = GetSimOwnningInfo(OwningList, SimInfo->GetID());
		if (OwningInfo)
		{
			ReturnSim(OwningList, OwningInfo->GetPassport(), OwningInfo->GetSimID());
		}
		
		delete SimInfos.SimInfo[i];
		SimInfos.SimInfo[i] = &SimTable::DeleteSign;
		cout << "SIM удалена!" << endl;
	}
}