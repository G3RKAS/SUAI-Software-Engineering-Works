#include "cottagecalc.h"

CottageCalc::CottageCalc(QObject *parent)
    : bstractCalc{parent}
{}

// Расчёт стоимости для коттеджа
int CottageCalc::getCost(Estate *value)
{
    float k = 1.65;
    int price_per_p = 165;
    int square_k = 185;
    int price_per_6m = 400;
    return k * (price_per_p * value->getResidents() + square_k * value->getArea() + price_per_6m * value->getMonths());
}
