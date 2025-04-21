#ifndef CALCFACTORY_H
#define CALCFACTORY_H

#include "bstractcalc.h"
#include <QObject>

class CalcFactory : public QObject
{
    Q_OBJECT
public:
    explicit CalcFactory(QObject *parent = nullptr);
    virtual bstractCalc* CalcFactoryMethod() = 0;

signals:
};

#endif // CALCFACTORY_H
