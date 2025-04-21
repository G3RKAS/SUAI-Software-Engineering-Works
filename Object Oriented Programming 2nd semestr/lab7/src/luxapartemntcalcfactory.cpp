#include "luxapartemntcalcfactory.h"
#include "luxuriousapartmentcalc.h"

LuxApartemntCalcFactory::LuxApartemntCalcFactory(QObject *parent)
    : CalcFactory{parent}
{}

bstractCalc* LuxApartemntCalcFactory::CalcFactoryMethod()
{
    return new LuxuriousApartmentCalc;
}
