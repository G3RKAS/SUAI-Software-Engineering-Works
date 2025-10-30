#include "apartmentcalc.h"

ApartmentCalc::ApartmentCalc(QObject *parent)
    : QObject{parent}
{}


// Расчёт стоимости для обычной квартиры
int ApartmentCalc::getCost(Estate *value)
{
    float k = 1;
    int price_per_p = 75;
    int square_k = 60;
    int price_per_6m = 100;
    return k * (price_per_p * value->getResidents() + square_k * value->getArea() + price_per_6m * value->getMonths());
}
