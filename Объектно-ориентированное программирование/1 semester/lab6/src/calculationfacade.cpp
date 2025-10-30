#include "calculationfacade.h"

CalculationFacade::CalculationFacade(QObject *parent) : QObject(parent)
{
}


// Фасад для расчёта стоимости
int CalculationFacade::getCost(Estate *value)
{
    int cost;
    switch (value->getType()) {
    case Estate::EstateType::ECONOM: // Обычная квартира
        cost = ApartmentCalc::getCost(value);
        break;
    case Estate::EstateType::LUXURIOUS: // Люкс квартира
        cost = LuxuriousApartmentCalc::getCost(value);
        break;
    case Estate::EstateType::TOWN_HOUSE: // ТаунХаус
        cost = TownhouseCalc::getCost(value);
        break;
    case Estate::EstateType::COTTAGE: // Коттедж
        cost = CottageCalc::getCost(value);
        break;
    default:
        cost = -1;
        break;
    }
    return cost;
}
