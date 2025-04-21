#ifndef LUXAPARTEMNTCALCFACTORY_H
#define LUXAPARTEMNTCALCFACTORY_H

#include "calcfactory.h"

class LuxApartemntCalcFactory : public CalcFactory
{
public:
    explicit LuxApartemntCalcFactory(QObject *parent = nullptr);
    bstractCalc* CalcFactoryMethod() override;
};

#endif // LUXAPARTEMNTCALCFACTORY_H
