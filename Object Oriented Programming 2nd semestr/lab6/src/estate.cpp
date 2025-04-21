#include "estate.h"


// Конструктор класса
Estate::Estate(QObject *parent, int age, int area, int residents, int months, EstateType type, QString owner)
    : QObject{parent}
{
    this->age = age;
    this->area = area;
    this->residents = residents;
    this->months = months;
    this->type = type;
    this->owner = owner;
}


// Функции получения атрибутов
Estate::EstateType Estate::getType() const
{
    return type;
}

int Estate::getAge() const
{
    return age;
}

int Estate::getArea() const
{
    return area;
}

int Estate::getResidents() const
{
    return residents;
}

int Estate::getMonths() const
{
    return months;
}

QString Estate::getOwner() const
{
    return owner;
}
