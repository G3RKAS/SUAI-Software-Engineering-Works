#ifndef TOWNHOUSEAPARTEMNTCALCFACTORY_H
#define TOWNHOUSEAPARTEMNTCALCFACTORY_H

#include "calcfactory.h"

class TownHouseApartemntCalcFactory : public CalcFactory
{
public:
    explicit TownHouseApartemntCalcFactory(QObject *parent = nullptr);
    bstractCalc* CalcFactoryMethod() override;
};

#endif // TOWNHOUSEAPARTEMNTCALCFACTORY_H
