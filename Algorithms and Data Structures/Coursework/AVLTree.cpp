#include "AVLTree.h"
#include "SimOwningList.h"
#include "SimTable.h"
#include "math.h"
#include <algorithm>

// ����� ������(������� ��������)
void ShowTree(Tree* Root, int level)
{
	if (Root != nullptr)
	{
		ShowTree(Root->right, level + 1);
		for (int i = 1; i <= level; i++)
			cout << "           ";
		cout << Root->ClientInfo->GetPassport() << " " << Root->h << endl;
		ShowTree(Root->left, level + 1);
	}
}

// ����� ��������(������ �����)
void ShowClients(Tree* Root)
{
	if (Root == nullptr)
	{
		return;
	}

	cout << endl;
	cout << "������ " << Root->ClientInfo->GetFIO() << endl;
	cout << "������� " << Root->ClientInfo->GetPassport() << endl;
	cout << "�����: " << Root->ClientInfo->GetPassportInfo() << endl;
	cout << "��� ��������: " << Root->ClientInfo->GetYearBirth() << endl;
	cout << "����� ����������: " << Root->ClientInfo->GetAdress() << endl;

	ShowClients(Root->left);
	ShowClients(Root->right);
}

// ������� ������ �� ������
void DeleteTree(Tree** Root)
{
	if (*Root == nullptr)
	{
		return;
	}

	DeleteTree(&(*Root)->left);
	DeleteTree(&(*Root)->right);
	delete (*Root)->ClientInfo;
	delete (*Root);
	*Root = nullptr;
}

// ��������� ������ ���������
int GetHeight(Tree* Root)
{
	if (Root == nullptr)
	{
		return 0;
	}
	else
	{
		return Root->h;
	}
}

// ����������� ����� ����������� ����� ��������
void FixHeight(Tree** Root)
{
	(*Root)->h = max(GetHeight((*Root)->left), GetHeight((*Root)->right)) + 1;
}

// ������� ����� �����������
int GetHeightDiff(Tree* Root)
{
	return GetHeight(Root->right) - GetHeight(Root->left);
}

// ����� ������ �������
void RotateRight(Tree** Root)
{
	Tree* left = (*Root)->left;
	(*Root)->left = left->right;
	left->right = (*Root);
	FixHeight(Root);
	FixHeight(&left);
	*Root = left;
}

// ����� ����� �������
void RotateLeft(Tree** Root)
{
	Tree* right = (*Root)->right;
	(*Root)->right = right->left;
	right->left = (*Root);
	FixHeight(Root);
	FixHeight(&right);
	*Root = right;
}

// ������������ ����������
void BalanceTree(Tree** Root)
{
	FixHeight(Root);

	if (GetHeightDiff(*Root) == 2)
	{
		if (GetHeightDiff((*Root)->right) < 0)
		{
			RotateRight(&(*Root)->right);
		}
		RotateLeft(Root);
	}
	else if (GetHeightDiff(*Root) == -2)
	{
		if (GetHeightDiff((*Root)->left) > 0)
		{
			RotateLeft(&(*Root)->left);
		}
		RotateRight(Root);
	}
}

// ���������� �������� � ������
void AddElem(Tree** Root, Client* ClientToAdd)
{
	if (*Root == nullptr)
	{
		Tree* R = new Tree;
		R->ClientInfo = ClientToAdd;
		R->left = nullptr;
		R->right = nullptr;
		*Root = R;
		return;
	}
	if (ClientToAdd->GetPassport() < (*Root)->ClientInfo->GetPassport())
	{
		AddElem(&((*Root)->left), ClientToAdd);
	}
	else if (ClientToAdd->GetPassport() > (*Root)->ClientInfo->GetPassport())
	{
		AddElem(&((*Root)->right), ClientToAdd);
	}

	BalanceTree(Root);
}

// ����� ������������ �������� � ������
Tree* FindMin(Tree* Root)
{
	if (Root->left)
	{
		FindMin(Root->left);
	}
	else
	{
		return Root;
	}
}

// �������� ������������ � ������
void RemoveMin(Tree** Root)
{
	if ((*Root)->left == 0)
	{
		(*Root) = (*Root)->right;
		return;
	}
	RemoveMin(&((*Root)->left));
	BalanceTree(Root);
}

// �������� �������� � ������
bool DeleteElem(Tree** Root, string Passport)
{
	if (*Root == nullptr)
	{
		return false;
	}

	if (Passport < (*Root)->ClientInfo->GetPassport())
	{
		return DeleteElem(&((*Root)->left), Passport);
	}
	else if (Passport > (*Root)->ClientInfo->GetPassport())
	{
		return DeleteElem(&((*Root)->right), Passport);
	}
	else
	{
		Tree* Left = (*Root)->left;
		Tree* Right = (*Root)->right;
		delete (*Root)->ClientInfo;
		delete (*Root);
		*Root = nullptr;
		if (!Right)
		{
			(*Root) = Left;
		}
		else
		{
			Tree* Min = FindMin(Right);
			RemoveMin(&Right);
			Min->right = Right;
			Min->left = Left;
			(*Root) = Min;
			BalanceTree(Root);
		}
		return true;
	}
}

// ����� ������� �� �������� � ������
Client* FindClientByPassport(Tree** Root, string Passport)
{
	if (*Root == nullptr)
	{
		return nullptr;
	}
	if (Passport < (*Root)->ClientInfo->GetPassport())
	{
		return FindClientByPassport(&((*Root)->left), Passport);
	}
	else if (Passport > (*Root)->ClientInfo->GetPassport())
	{
		return FindClientByPassport(&((*Root)->right), Passport);
	}
	else
	{
		return (*Root)->ClientInfo;
	}

	return nullptr;
}

// ����� ������ ������
bool FindSubTextInText(string NodeInfo, string ClientInfo)
{
	int all;
	std::transform(NodeInfo.begin(), NodeInfo.end(), NodeInfo.begin(), [](unsigned char c) { return std::tolower(c); });
	std::transform(ClientInfo.begin(), ClientInfo.end(), ClientInfo.begin(),
				   [](unsigned char c) { return std::tolower(c); });

	for (int i{0}; i < NodeInfo.length() - ClientInfo.length() + 1; i++)
	{
		all = 0;
		for (int j{0}; j < ClientInfo.length(); j++)
		{
			if (NodeInfo[i + j] == ClientInfo[j])
			{
				all += 1;
			}
			else
			{
				break;
			}
		}
		if (all == ClientInfo.length())
		{
			return true;
		}
	}
	return false;
}

// ����� �������� �� ���(������ �����)
void PrintAllClientsByFIO(Tree* Root, string FIO, int& count)
{
	if (Root == nullptr)
	{
		return;
	}

	if (FindSubTextInText(Root->ClientInfo->GetFIO(), FIO))
	{
		count++;
		cout << endl;
		cout << "������ " << Root->ClientInfo->GetFIO() << endl;
		cout << "������� " << Root->ClientInfo->GetPassport() << endl;
		cout << "�����: " << Root->ClientInfo->GetPassportInfo() << endl;
		cout << "��� ��������: " << Root->ClientInfo->GetYearBirth() << endl;
		cout << "����� ����������: " << Root->ClientInfo->GetAdress() << endl;
	}

	PrintAllClientsByFIO(Root->left, FIO, count);
	PrintAllClientsByFIO(Root->right, FIO, count);
}

// ����� �������� �� ������(������ �����)
void PrintAllClientsByAdress(Tree* Root, string Adress, int& count)
{
	if (Root == nullptr)
	{
		return;
	}

	if (FindSubTextInText(Root->ClientInfo->GetAdress(), Adress))
	{
		count++;
		cout << endl;
		cout << "������ " << Root->ClientInfo->GetFIO() << endl;
		cout << "������� " << Root->ClientInfo->GetPassport() << endl;
		cout << "����� ����������: " << Root->ClientInfo->GetAdress() << endl;
	}

	PrintAllClientsByAdress(Root->left, Adress, count);
	PrintAllClientsByAdress(Root->right, Adress, count);
}

// ������� ���� �������� � ������������� ���������� � ��������� ����������(�������� �����)
void ClearAllOfClient(Tree** Root, SimTable& SimInfos, SimOwningList* OwningRoot)
{
	if (*Root == nullptr)
	{
		return;
	}

	ClearAllOfClient(&(*Root)->left, SimInfos, OwningRoot);
	ClearAllOfClient(&(*Root)->right, SimInfos, OwningRoot);

	Client* ClientInfo = (*Root)->ClientInfo;

	vector<string> ClientSims = GetAllSimsOfClient(OwningRoot, ClientInfo->GetPassport());
	if (not(ClientSims.empty()))
	{
		auto first = ClientSims.begin();
		auto last = ClientSims.end();
		for (; first != last; ++first)
		{
			Sim* SimInfo = FindSim(SimInfos, *first);
			ReturnSim(OwningRoot, ClientInfo->GetPassport(), SimInfo->GetID());
			SimInfo->SetAvailable(true);
			cout << "SIM " << SimInfo->GetID() << " �����������" << endl;
		}
	}

	cout << "������ " << ClientInfo->GetPassport() << " �����!" << endl;

	delete (*Root)->ClientInfo;
	delete (*Root);
	*Root = nullptr;
}
