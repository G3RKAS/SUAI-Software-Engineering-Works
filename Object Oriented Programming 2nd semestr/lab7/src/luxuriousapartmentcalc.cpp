#include "luxuriousapartmentcalc.h"

LuxuriousApartmentCalc::LuxuriousApartmentCalc(QObject *parent)
    : bstractCalc{parent}
{}

// Расчёт стоимости для люкс квартиры
int LuxuriousApartmentCalc::getCost(Estate *value)
{
    float k = 1.2;
    int price_per_p = 100;
    int square_k = 95;
    int price_per_6m = 200;
    return k * (price_per_p * value->getResidents() + square_k * value->getArea() + price_per_6m * value->getMonths());
}
