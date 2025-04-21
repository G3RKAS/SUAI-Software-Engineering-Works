#include "SimOwningList.h"
#include "SubFunctions.h"
#include "AVLTree.h"

// ������� ������
void ClearList(SimOwningList** Root)
{
	if (not(*Root))
	{
		return;
	}

	SimOwningList* cur = nullptr;

	while ((*Root)->next)
	{
		cur = (*Root);
		*Root = (*Root)->next;
		delete cur->OwningInfo;
		delete cur;
	}
	delete *Root;
	*Root = nullptr;
}

// �������� ������� ����� �������� N
SimOwningList* MakeListOfN(int n)
{
	SimOwningList* OwningList = nullptr;

	for (int i{0}; i < n; i++)
	{
		GiveSim(&OwningList, nullptr);
	}

	return OwningList;
}

// ����� ������
void PrintList(SimOwningList* Root)
{
	if (not(Root))
	{
		cout << "���������� �� ������� � ��������� ������" << endl;
		return;
	}

	while (Root)
	{
		if (Root->OwningInfo)
		{
			cout << endl;
			cout << "����� SIM " << Root->OwningInfo->GetSimID() << endl;
			cout << "������� ������� " << Root->OwningInfo->GetPassport() << endl;
			cout << "���� ������: " << Root->OwningInfo->GetDateOfIssue() << endl;
			cout << "���� ��������� �����������: " << Root->OwningInfo->GetDateOfExpiration() << endl;
		}
		Root = Root->next;
	}
}

// ��������� ����� ������
int GetSize(SimOwningList* Root)
{
	int size = 0;
	while (Root)
	{
		size++;
		Root = Root->next;
	}
	return size;
}

// ���������� N �� ����� ������� �� ������
void SetElementInListOnIndex(SimOwningList* Root, int index, SimOwning* OwningInfo)
{
	int ListIndex = 0;
	while (ListIndex != index)
	{
		ListIndex++;
		Root = Root->next;
	}

	Root->OwningInfo = new SimOwning(OwningInfo->GetPassport(), OwningInfo->GetSimID(), OwningInfo->GetDateOfIssue(),
									 OwningInfo->GetDateOfExpiration());
}

// ���������� ������� �� �������(�������)
SimOwning* GetElementByIndex(SimOwningList* Root, int index)
{
	int ListIndex = 0;
	while (ListIndex != index)
	{
		ListIndex++;
		Root = Root->next;
	}

	return Root->OwningInfo;
}

// ��������� �������� ��� ���������� ���������
int GetKForSort(SimOwningList* Root, string SimID, int ListSize, int SourceIndex)
{
	int k = 0;
	for (int i{0}; i < ListSize; i++)
	{
		if (GetElementByIndex(Root, i)->GetSimID() < SimID)
		{
			k++;
		}
		else if (i < SourceIndex and GetElementByIndex(Root, i)->GetSimID() == SimID)
		{
			k++;
		}
		else if (i == SourceIndex)
		{
			continue;
		}
	}
	return k;
}

// ���������� ���������
void SortList(SimOwningList** Root)
{
	SimOwningList* NewOwningList = nullptr;
	int ListSize = GetSize(*Root);

	NewOwningList = MakeListOfN(ListSize);

	for (int i{0}; i < ListSize; i++)
	{
		SimOwning* OwningInfo = GetElementByIndex(*Root, i);

		int k = GetKForSort(*Root, OwningInfo->GetSimID(), ListSize, i);
		SetElementInListOnIndex(NewOwningList, k, OwningInfo);
	}

	ClearList(Root);
	*Root = NewOwningList;
}

// ������ �������� �������
void GiveSim(SimOwningList** Root, SimOwning* OwningInfo)
{
	SimOwningList* cur = *Root;
	SimOwningList* p = new SimOwningList;

	if (cur == nullptr)
	{
		p->next = nullptr;
		p->OwningInfo = OwningInfo;
		*Root = p;
	}
	else
	{
		while (cur->next)
		{
			cur = cur->next;
		}
		p->next = nullptr;
		p->OwningInfo = OwningInfo;
		cur->next = p;
	}
}

// ������� �������� �� �������
bool ReturnSim(SimOwningList* Root, string ClientPassport, string ClientSim)
{
	while (Root and (Root->OwningInfo->GetSimID() != ClientSim or Root->OwningInfo->GetPassport() != ClientPassport))
	{
		Root = Root->next;
	}

	if (Root)
	{
		Root->OwningInfo->SetDateOfExpiration(GetDateByTime(time(0)));
		return true;
	}

	return false;
}

// ������� �� ������ ���������
bool IsClientOwningSim(SimOwningList* Root, string ClientPassport, string ClientSim)
{
	while (Root and (Root->OwningInfo->GetSimID() != ClientSim or Root->OwningInfo->GetPassport() != ClientPassport))
	{
		Root = Root->next;
	}

	if (Root)
	{
		return true;
	}

	return false;
}

// �������� ���������� � �������� ���������
SimOwning* GetSimOwnningInfo(SimOwningList* Root, string ClientSim)
{
	while (Root and (Root->OwningInfo->GetSimID() != ClientSim or Root->OwningInfo->GetDateOfExpiration() != "-"))
	{
		Root = Root->next;
	}

	if (Root)
	{
		return Root->OwningInfo;
	}
	return nullptr;
}

// ��������� ������� ������� �������
vector<string> GetAllSimsOfClient(SimOwningList* Root, string ClientPassport)
{
	vector<string> ClientSims{};
	while (Root)
	{
		if (Root->OwningInfo->GetPassport() == ClientPassport and Root->OwningInfo->GetDateOfExpiration() == "-")
		{
			ClientSims.push_back((Root->OwningInfo->GetSimID()));
		}

		Root = Root->next;
	}

	return ClientSims;
}