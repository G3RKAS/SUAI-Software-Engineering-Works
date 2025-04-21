#ifndef COTTAGEAPARTEMNTCALCFACTORY_H
#define COTTAGEAPARTEMNTCALCFACTORY_H

#include "calcfactory.h"

class CottageApartemntCalcFactory : public CalcFactory
{
public:
    explicit CottageApartemntCalcFactory(QObject *parent = nullptr);
    bstractCalc* CalcFactoryMethod() override;
};

#endif // COTTAGEAPARTEMNTCALCFACTORY_H
