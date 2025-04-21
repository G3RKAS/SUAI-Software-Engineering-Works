#ifndef CLIENTSMENU_H
#define CLIENTSMENU_H

#include "client.h"
#include "qstandarditemmodel.h"
#include <QWidget>

namespace Ui {
class ClientsMenu;
}

class ClientsMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ClientsMenu(QWidget *parent = nullptr);
    ~ClientsMenu();
    bool IsClientInList(int);
    void ClearInputs();
    void RemoveClientFromModel(int);

signals:
    void RequestToRemoveClient(int);

private:
    Ui::ClientsMenu* ui;
    int NumOfClients;
    QList<Client*> ClientsList;
    QStandardItemModel* model;

    void SetModelHeader();
    void AddNewClientToModel(Client*);


private slots:
    void RequestToAddClient();
    void InfoChanged();
    void RegChanged();
};

#endif // CLIENTSMENU_H
