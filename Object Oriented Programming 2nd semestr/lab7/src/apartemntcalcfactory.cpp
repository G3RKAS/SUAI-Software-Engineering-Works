#include "apartemntcalcfactory.h"
#include "apartmentcalc.h"

ApartemntCalcFactory::ApartemntCalcFactory(QObject *parent)
    : CalcFactory{parent}
{}

bstractCalc* ApartemntCalcFactory::CalcFactoryMethod()
{
    return new ApartmentCalc;
}
