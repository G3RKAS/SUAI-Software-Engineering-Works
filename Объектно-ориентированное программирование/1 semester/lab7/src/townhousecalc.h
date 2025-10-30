#ifndef TOWNHOUSECALC_H
#define TOWNHOUSECALC_H

#include "bstractcalc.h"
#include <QObject>

class TownhouseCalc : public bstractCalc
{
    Q_OBJECT
public:
    explicit TownhouseCalc(QObject *parent = nullptr);
    virtual int getCost(Estate *value) override;

signals:
};

#endif // TOWNHOUSECALC_H
