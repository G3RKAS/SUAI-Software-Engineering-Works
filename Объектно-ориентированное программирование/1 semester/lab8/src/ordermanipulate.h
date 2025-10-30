#ifndef ORDERMANIPULATE_H
#define ORDERMANIPULATE_H

#include "mainwindow.h"
#include "order.h"
#include <QWidget>

class OrderManipulate : public QWidget
{
    Q_OBJECT
public:
    explicit OrderManipulate(QWidget *parent = nullptr);
    static void SendErrorMessage(QString);
    static void AddOrder(Order*, MainWindow*);
    static void ExecuteOrder(int, MainWindow*);
    static void RemoveOrder(int, MainWindow*);
    static void RemoveClient(int, MainWindow*);
    static void RemoveMaster(QString, MainWindow*);

signals:
};

#endif // ORDERMANIPULATE_H
