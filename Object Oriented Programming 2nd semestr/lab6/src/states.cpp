#include "states.h"

States::States(QObject *parent) : QObject(parent)
{
    actualData = nullptr;
}

// Деструктор(удаление данных в списке)
States::~States()
{
    // delete: actualData
    if (actualData)
    {
        delete actualData;
        actualData = nullptr;
    }
    // delete and clear: array
    qDeleteAll(array);
    array.clear();
}

// Метод получения информации, есть ли в списке что-либо
bool States::hasStates()
{
    return array.size() != 0;
}

// Метлод добавления в список нового элемента
void States::add(Estate *value)
{
    array.append(value);
    actualData = value;
}

// Метод получения последнего элемента
Estate* States::getActualData()
{
    return actualData;
}

// Метод удаления последнего элемента
void States::undo()
{
    if (not(hasStates()))
    {
        actualData = nullptr;
    }
    else
    {
        actualData = array.takeLast();
    }
    emit notifyObservers();
}
