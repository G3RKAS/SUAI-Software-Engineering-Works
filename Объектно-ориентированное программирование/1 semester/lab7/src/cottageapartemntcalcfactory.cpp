#include "cottageapartemntcalcfactory.h"
#include "cottagecalc.h"

CottageApartemntCalcFactory::CottageApartemntCalcFactory(QObject *parent)
    : CalcFactory{parent}
{}

bstractCalc* CottageApartemntCalcFactory::CalcFactoryMethod()
{
    return new CottageCalc;
}
