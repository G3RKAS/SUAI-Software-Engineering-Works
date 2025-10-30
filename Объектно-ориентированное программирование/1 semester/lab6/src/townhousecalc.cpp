#include "townhousecalc.h"

TownhouseCalc::TownhouseCalc(QObject *parent)
    : QObject{parent}
{}

// Расчёт стоимости для таун хауса
int TownhouseCalc::getCost(Estate *value)
{
    float k = 1.4;
    int price_per_p = 135;
    int square_k = 115;
    int price_per_6m = 300;
    return k * (price_per_p * value->getResidents() + square_k * value->getArea() + price_per_6m * value->getMonths());
}
