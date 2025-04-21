#include "townhouseapartemntcalcfactory.h"
#include "townhousecalc.h"

TownHouseApartemntCalcFactory::TownHouseApartemntCalcFactory(QObject *parent)
    : CalcFactory{parent}
{}

bstractCalc* TownHouseApartemntCalcFactory::CalcFactoryMethod()
{
    return new TownhouseCalc;
}
