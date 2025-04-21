#ifndef APARTEMNTCALCFACTORY_H
#define APARTEMNTCALCFACTORY_H

#include "calcfactory.h"

class ApartemntCalcFactory : public CalcFactory
{
public:
    explicit ApartemntCalcFactory(QObject *parent = nullptr);
    bstractCalc* CalcFactoryMethod() override;
};

#endif // APARTEMNTCALCFACTORY_H
