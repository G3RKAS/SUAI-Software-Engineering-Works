#pragma once
#include "Classes.h"
#include <vector>

// Узел списка
struct SimOwningList
{
	SimOwning* OwningInfo;
	SimOwningList* next;
};

void ClearList(SimOwningList**);

SimOwningList* MakeListOfN(int);

void PrintList(SimOwningList*);

void GiveSim(SimOwningList**, SimOwning*);

bool ReturnSim(SimOwningList*, string, string);

void SortList(SimOwningList**);

bool IsClientOwningSim(SimOwningList*, string, string);

SimOwning* GetSimOwnningInfo(SimOwningList*, string);

vector<string> GetAllSimsOfClient(SimOwningList*, string);