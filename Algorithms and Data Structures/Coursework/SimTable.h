#pragma once
#include "Classes.h"
#include "SimOwningList.h"

// Хэш-таблица
struct SimTable
{
	const static int TableSize = 5000;
	static Sim DeleteSign;
	Sim** SimInfo;
	SimTable();
	~SimTable();
};

int GetHash(string);

bool AddSim(SimTable&, Sim*);

bool DeleteSim(SimTable&, string);

Sim* FindSim(SimTable&, string);

void ClearAllSim(SimTable&);

string GetRandomSimID();

bool IsEmpty(SimTable&);

void PrintAllOfSims(SimTable&);

void PrintAllOfSimsByTarrif(SimTable&, Sim::Tarrif, int&);

void ClearAllSims(SimTable&, SimOwningList*);