#pragma once
#include "Classes.h"
#include "SimTable.h"
#include "SimOwningList.h"

// АВЛ-дерево узел
struct Tree
{
	Client* ClientInfo = nullptr;
	int h = 1;
	Tree* left = nullptr;
	Tree* right = nullptr;
};

void ShowTree(Tree*, int);

void ShowClients(Tree*);

void DeleteTree(Tree**);

void AddElem(Tree**, Client*);

bool DeleteElem(Tree**, string);

Client* FindClientByPassport(Tree**, string);

void PrintAllClientsByFIO(Tree*, string, int&);

void PrintAllClientsByAdress(Tree*, string, int&);

void ClearAllOfClient(Tree**, SimTable&, SimOwningList*);

void BalanceTree(Tree** Root);