// 665
// Обслуживание клиентов оператора сотовой связи
// Закрытое хеширование с линейным опробованием
// Сортировка подсчётом
// Список Линейный однонаправленный
// Метод обхода прямой
// Алгоритм поиска слова в тексте прямой
#include "AVLTree.h"
#include "Classes.h"
#include "SimOwningList.h"
#include "SimTable.h"
#include "SubFunctions.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Tree* Root = nullptr;
	SimTable SimInfos;
	SimOwningList* OwningList = nullptr;

	cout << "Добро пожаловать в систему 'Обслуживание клиентов оператора сотовой связи'" << endl;
	cout << endl;

	int x;

	string Passport;
	string PassportInfo;
	string FIO;
	int YearOfBirth;
	string Adress;

	string SIM;
	int TarrifName;
	int YearOfRelease;

	int count;

	Client* ClientInfo;
	Sim* SimInfo;
	vector<string> ClientSims;

	// Изначальная информация
	// Клиенты
	AddElem(&Root, new Client("1419-049233", "ГУ МВД России по Красноярскому краю 09.03.2020", "Филатов Марк Юрьевич",
							  1980, "г.Санкт-Петербург, ул. Макарова, дом 23"));
	AddElem(&Root, new Client("1419-049234", "ГУ МВД России по Краснодарскому краю 03.04.2020",
							  "Савельев Богдан Наумович", 2000, "г. Красноярск, пр. Революции, дом 45"));
	AddElem(&Root, new Client("4425-093423", "ГУ МВД России по г. Санкт-Петербургу и Ленинградской области 09.12.2013",
							  "Власов Георгий Пётрович", 1973, "г. Красноярск, ул. Софийская, дом 3"));
	AddElem(&Root, new Client("3246-052234", "ОП№84 по Приморскому району г. Санкт-Петербурга 04.01.2007",
							  "Пономарёв Геннадий Созонович", 1987, "г. Благовещенск, ул. Советская, дом 6"));
	AddElem(&Root, new Client("3246-052235", "ОП№84 по Приморскому району г. Санкт-Петербурга 04.01.2007",
							  "Пономарёв Геннадий Созонович", 1987, "г. Благовещенск, ул. Советская, дом 6"));
	// SIM
	AddSim(SimInfos, new Sim("434-4561284", Sim::Tarrif::Base, 2024));
	AddSim(SimInfos, new Sim("334-4561284", Sim::Tarrif::Super, 2025));
	AddSim(SimInfos, new Sim("494-4589284", Sim::Tarrif::Medium, 2021));
	AddSim(SimInfos, new Sim("434-4599984", Sim::Tarrif::Base, 2024));
	AddSim(SimInfos, new Sim("434-4568284", Sim::Tarrif::Ultra, 2024));
	AddSim(SimInfos, new Sim("474-4561284", Sim::Tarrif::Base, 2024));

	bool bRunMenu = true;
	bool bRunClient;
	bool bRunSim;
	bool bRunGiveReturn;

	while (bRunMenu)
	{
		cout << "1. Работа с клиентами" << endl;
		cout << "2. Работа с SIM" << endl;
		cout << "3. Выдача и возврат" << endl;
		cout << "4. Выход" << endl;

		cout << "Выберите пункт меню: ";
		x = GetInt();

		switch (x)
		{
		case 1:
			bRunClient = true;

			while (bRunClient)
			{
				system("cls");
				cout << "1. Зарегистрировать нового клиента" << endl;
				cout << "2. Снять клиента с обслуживания" << endl;
				cout << "3. Список зарегистрированных клиентов" << endl;
				cout << "4. Очистить данные о клиентах" << endl;
				cout << "5. Найти клиента по паспорту" << endl;
				cout << "6. Найти клиентов по ФИО" << endl;
				cout << "7. Найти клиентов по адресу" << endl;
				cout << "8. Назад" << endl;

				cout << "Выберите пункт меню: ";
				x = GetInt();
				switch (x)
				{
				case 1:
					// Добавление клиента

					cout << "Введите номер паспорта: ";
					Passport = GetPassportNo();
					// Проверка на существование
					if (FindClientByPassport(&Root, Passport))
					{
						cout << "Данный клиент уже существует!" << endl;
						break;
					}

					cout << "Введите место и дату выдачи паспорта: ";
					getline(cin, PassportInfo);
					cout << "Введите ФИО: ";
					getline(cin, FIO);
					cout << "Введите год рождения: ";
					// Ввод корректного года
					YearOfBirth = GetValidYear();
					cout << "Введите адрес проживания: ";
					getline(cin, Adress);

					// Добавление
					AddElem(&Root, new Client(Passport, PassportInfo, FIO, YearOfBirth, Adress));
					cout << "Добавлен!" << endl;

					break;
				case 2:
					// Удаление по паспорту
					cout << "Введите номер паспорта: ";
					Passport = GetPassportNo();
					ClientInfo = FindClientByPassport(&Root, Passport);
					// Проверка на существование
					if (ClientInfo)
					{
						ClientSims = GetAllSimsOfClient(OwningList, Passport);
						// Проверка на существование привязанных симок
						if (not(ClientSims.empty()))
						{
							auto first = ClientSims.begin();
							auto last = ClientSims.end();
							for (; first != last; ++first)
							{
								// Нахождение симок по коду и удаление
								SimInfo = FindSim(SimInfos, *first);
								ReturnSim(OwningList, ClientInfo->GetPassport(), SimInfo->GetID());
								SimInfo->SetAvailable(true);

								cout << "SIM " << SimInfo->GetID() << " освобождена" << endl;
							}
						}
						// Удаление клиента
						DeleteElem(&Root, Passport);
						BalanceTree(&Root);
						cout << "Клиент удалён!" << endl;
					}
					else
					{
						cout << "Клиент не найден!" << endl;
					}

					break;
				case 3:
					// Список клиентов
					if (Root)
					{
						ShowClients(Root);
					}
					else
					{
						cout << "Информация по клиентам пустая" << endl;
					}

					break;
				case 4:
					// Удалить всех клиентов
					ClearAllOfClient(&Root, SimInfos, OwningList);

					break;
				case 5:
					// Найти клиента по паспорту

					cout << "Введите номер паспорта: ";
					Passport = GetPassportNo();
					ClientInfo = FindClientByPassport(&Root, Passport);

					if (ClientInfo)
					{
						cout << "Найденный клиент: " << endl << endl;
						cout << "Клиент " << ClientInfo->GetFIO() << endl;
						cout << "Паспорт " << ClientInfo->GetPassport() << endl;
						cout << "Выдан: " << ClientInfo->GetPassportInfo() << endl;
						cout << "Год рождения: " << ClientInfo->GetYearBirth() << endl;
						cout << "Адрес проживания: " << ClientInfo->GetAdress() << endl;

						// В случае существования привязанных симок - вывести
						ClientSims = GetAllSimsOfClient(OwningList, Passport);
						if (not(ClientSims.empty()))
						{
							cout << "SIM клиента:" << endl;
							auto first = ClientSims.begin();
							auto last = ClientSims.end();
							for (; first != last; ++first)
							{
								cout << *first << endl;
							}
						}
					}
					else
					{
						cout << "Клиент не найден!" << endl;
					}
					break;
				case 6:
					// Поиск клиента по ФИО
					count = 0;

					cout << "Введите ФИО: ";
					getline(cin, FIO);

					PrintAllClientsByFIO(Root, FIO, count);

					if (count == 0)
					{
						cout << "Информации по данному атрибуту не найдено." << endl;
					}

					break;
				case 7:
					// Поиск клиента по адрессу
					count = 0;

					cout << "Введите адрес: ";
					getline(cin, Adress);

					PrintAllClientsByAdress(Root, Adress, count);

					if (count == 0)
					{
						cout << "Информации по данному атрибуту не найдено." << endl;
					}

					break;
				case 8:
					bRunClient = false;
					break;
				default:
					break;
				}
				cout << endl;
				system("pause");
			}
			break;

		case 2:
			bRunSim = true;
			while (bRunSim)
			{
				system("cls");
				cout << "1. Добавить новую SIM-карту" << endl;
				cout << "2. Удалить SIM-карту" << endl;
				cout << "3. Список всех SIM-карт" << endl;
				cout << "4. Очистить данные о SIM-картах" << endl;
				cout << "5. Найти SIM-карту по номеру" << endl;
				cout << "6. Найти SIM-карты по тарифу" << endl;
				cout << "7. Назад" << endl;

				cout << "Выберите пункт меню: ";
				x = GetInt();

				switch (x)
				{
				case 1:
					// Добавление симки
					cout << "Введите номер SIM: ";
					// Валидация на существование
					SIM = GetSimNo();
					if (FindSim(SimInfos, SIM))
					{
						cout << "Данная SIM уже существует!" << endl;
						break;
					}
					cout << "Выберите тип тарифа: " << endl;
					cout << "1. Базовый" << endl;
					cout << "2. Базовый+" << endl;
					cout << "3. Супер" << endl;
					cout << "4. Ультра" << endl;
					TarrifName = GetInt(1, 4);

					cout << "Введите год выпуска: ";
					// Валидация года
					YearOfRelease = GetValidYear();
					// Добавление
					AddSim(SimInfos, new Sim(SIM, Sim::Tarrif(TarrifName), YearOfRelease));
					cout << "SIM добавлена!" << endl;
					break;
				case 2:
					// Удаление по коду
					cout << "Введите номер SIM: ";
					SIM = GetSimNo();
					SimInfo = FindSim(SimInfos, SIM);
					if (SimInfo)
					{
						// Проверка на существование владельцев
						SimOwning* OwningInfo = GetSimOwnningInfo(OwningList, SimInfo->GetID());
						if (OwningInfo)
						{
							// Если есть владелец, записать возврат сим карты
							ReturnSim(OwningList, OwningInfo->GetPassport(), OwningInfo->GetSimID());
							cout << "Клиент " << OwningInfo->GetPassport() << " освобождён от SIM!" << endl;
						}
						// Удалить сим карту
						DeleteSim(SimInfos, SIM);
						cout << "SIM удалена!" << endl;
					}
					else
					{
						cout << "SIM не найдена!" << endl;
					}
					break;
				case 3:
					// Список симок
					if (not(IsEmpty(SimInfos)))
					{
						PrintAllOfSims(SimInfos);
					}
					else
					{
						cout << "Информация по SIM картам пустая" << endl;
					}
					break;
				case 4:
					// Очистить все симкарты
					ClearAllSims(SimInfos, OwningList);
					break;
				case 5:
					// Найти симкарту по коду
					cout << "Введите номер SIM: ";
					SIM = GetSimNo();
					SimInfo = FindSim(SimInfos, SIM);
					if (SimInfo)
					{
						cout << "Найденная SIM:" << endl << endl;
						cout << "Номер SIM " << SimInfo->GetID() << endl;
						cout << "Тариф: " << SimInfo->TariffToString() << endl;
						cout << "Год выпуска: " << SimInfo->GetYearRelease() << endl;
						cout << "Наличие: " << SimInfo->IsAvailable() << endl;

						// Проверка на владельца
						SimOwning* OwningInfo = GetSimOwnningInfo(OwningList, SimInfo->GetID());
						if (OwningInfo)
						{
							Client* ClientInfo = FindClientByPassport(&Root, OwningInfo->GetPassport());
							// Вывод владельца при его существовании
							if (ClientInfo)
							{
								cout << "Владелец " << ClientInfo->GetFIO() << " " << ClientInfo->GetPassport() << endl;
							}
						}
					}
					else
					{
						cout << "SIM не найдена!" << endl;
					}

					break;
				case 6:
					// Найти симкарты по тарифу
					count = 0;

					cout << "Выберите тип тарифа: " << endl;
					cout << "1. Базовый" << endl;
					cout << "2. Базовый+" << endl;
					cout << "3. Супер" << endl;
					cout << "4. Ультра" << endl;
					TarrifName = GetInt(1, 4);

					PrintAllOfSimsByTarrif(SimInfos, Sim::Tarrif(TarrifName), count);

					if (count == 0)
					{
						cout << "Информации по данному атрибуту не найдено." << endl;
					}

					break;
				case 7:
					bRunSim = false;
					break;
				default:
					break;
				}
				cout << endl;
				system("pause");
			}
			break;
		case 3:
			bRunGiveReturn = true;
			while (bRunGiveReturn)
			{
				system("cls");
				cout << "1. Выдать SIM-карту клиенту" << endl;
				cout << "2. Вернуть SIM-карту от клиента" << endl;
				cout << "3. История выдачей и возвратов" << endl;
				cout << "4. Назад" << endl;

				cout << "Выберите пункт меню: ";
				x = GetInt();
				switch (x)
				{

				case 1:
					// Выдача симкарты
					cout << "Введите номер паспорта: ";
					Passport = GetPassportNo();
					ClientInfo = FindClientByPassport(&Root, Passport);
					if (not(ClientInfo))
					{
						cout << "Данного клиента не существует!" << endl;
						break;
					}
					cout << "Введите номер SIM: ";
					SIM = GetSimNo();
					SimInfo = FindSim(SimInfos, SIM);
					if (not(SimInfo))
					{
						cout << "Данной SIM не существует!" << endl;
						break;
					}
					else if (not(SimInfo->GetAvailable()))
					{
						cout << "Данная SIM уже выдана!" << endl;
						break;
					}
					GiveSim(&OwningList, new SimOwning(ClientInfo->GetPassport(), SimInfo->GetID()));
					SimInfo->SetAvailable(false);
					SortList(&OwningList);
					cout << "SIM выдана!" << endl;
					break;
				case 2:
					// Возврат симкарты
					cout << "Введите номер паспорта: ";
					Passport = GetPassportNo();
					ClientInfo = FindClientByPassport(&Root, Passport);
					if (not(ClientInfo))
					{
						cout << "Данного клиента не существует!" << endl;
						break;
					}
					cout << "Введите номер SIM: ";
					SIM = GetSimNo();
					SimInfo = FindSim(SimInfos, SIM);
					if (not(SimInfo))
					{
						cout << "Данной SIM не существует!" << endl;
						break;
					}
					else if (SimInfo->GetAvailable())
					{
						cout << "Данная SIM никому не выдана!" << endl;
						break;
					}
					else if (not(IsClientOwningSim(OwningList, ClientInfo->GetPassport(), SimInfo->GetID())))
					{
						cout << "Данная SIM не выдана данному клиенту!" << endl;
						break;
					}

					ReturnSim(OwningList, ClientInfo->GetPassport(), SimInfo->GetID());
					SimInfo->SetAvailable(true);
					cout << "SIM возвращена!" << endl;
					break;
				case 3:
					// Список выдач и возвратов
					PrintList(OwningList);
					break;
				case 4:
					bRunGiveReturn = false;
					break;
				default:
					break;
				}
				cout << endl;
				system("pause");
			}
			break;
		case 4:
			bRunMenu = false;
			goto exitMenu;
		default:
			break;
		}
		system("cls");
	}

exitMenu:
	// Очистка динамической памяти
	DeleteTree(&Root);
	ClearAllSim(SimInfos);
	ClearList(&OwningList);
}
