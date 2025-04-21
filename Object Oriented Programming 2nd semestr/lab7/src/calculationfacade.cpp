#include "calculationfacade.h"
#include "calcfactory.h"
#include "apartemntcalcfactory.h"
#include "cottageapartemntcalcfactory.h"
#include "luxapartemntcalcfactory.h"
#include "townhouseapartemntcalcfactory.h"


CalculationFacade::CalculationFacade(QObject *parent) : QObject(parent)
{
}

// Фасад для расчёта стоимости
int CalculationFacade::getCost(Estate *value)
{
    CalcFactory* Factory;
    switch (value->getType()) { // Выбор фабрики класса расчёта
    case Estate::EstateType::ECONOM:
        Factory = new ApartemntCalcFactory;
        break;
    case Estate::EstateType::LUXURIOUS:
        Factory = new LuxApartemntCalcFactory;
        break;
    case Estate::EstateType::TOWN_HOUSE:
        Factory = new TownHouseApartemntCalcFactory;
        break;
    case Estate::EstateType::COTTAGE:
        Factory = new CottageApartemntCalcFactory;
        break;
    default:
        break;
    }
    // Запуск фабрики
    bstractCalc *Type = Factory->CalcFactoryMethod();
    // Получение цены
    int price = Type->getCost(value);
    delete Factory;
    delete Type;
    return price;
}
