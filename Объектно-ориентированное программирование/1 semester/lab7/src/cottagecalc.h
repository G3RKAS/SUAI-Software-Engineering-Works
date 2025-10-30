#ifndef COTTAGECALC_H
#define COTTAGECALC_H

#include "bstractcalc.h"
#include <QObject>

class CottageCalc : public bstractCalc
{
    Q_OBJECT
public:
    explicit CottageCalc(QObject *parent = nullptr);
    virtual int getCost(Estate *value) override;

signals:
};

#endif // COTTAGECALC_H
