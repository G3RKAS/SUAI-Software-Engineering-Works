#include "ordermanipulate.h"
#include "qmessagebox.h"

OrderManipulate::OrderManipulate(QWidget *parent)
    : QWidget{parent}
{}

void OrderManipulate::SendErrorMessage(QString ErrorMessage)
{
    QMessageBox msgBox;
    msgBox.setText(ErrorMessage);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
}

void OrderManipulate::AddOrder(Order* OrderInfo, MainWindow* MainInfo)
{
    QString MasterRegCode = OrderInfo->GetMasterRegCode();
    if (not(MainInfo->GetClientsMenu()->IsClientInList(OrderInfo->GetClientRegNumber())))
    {
        OrderManipulate::SendErrorMessage("Такого клиента не существует.");

        delete OrderInfo;
        return;
    }
    if (not(MainInfo->GetMastersMenu()->IsMasterInList(MasterRegCode)))
    {
        OrderManipulate::SendErrorMessage("Такого мастера не существует.");

        delete OrderInfo;
        return;
    }
    if (MainInfo->GetMastersMenu()->GetMasterByRegCode(MasterRegCode)->IsBusy())
    {
        OrderManipulate::SendErrorMessage("Мастер уже занят.");

        delete OrderInfo;
        return;
    }
    MainInfo->GetOrdersMenu()->AddNewOrderToModel(OrderInfo);
    MainInfo->GetMastersMenu()->SetMasterBusyStatusByRegCode(MasterRegCode,
                                                             MainInfo->GetOrdersMenu()->GetSizeOfList());
    MainInfo->GetOrdersMenu()->ClearInputs();
}

void OrderManipulate::ExecuteOrder(int OrderNumber, MainWindow* MainInfo)
{

    if (OrderNumber > MainInfo->GetOrdersMenu()->GetSizeOfList())
    {
        OrderManipulate::SendErrorMessage("Такого заказа не существует.");

        return;
    }
    if (MainInfo->GetOrdersMenu()->GetModelOfMenu()->item(OrderNumber-1, 3)->text() == "Выполнен")
    {
        OrderManipulate::SendErrorMessage("Данный заказ уже выполнен.");

        return;
    }

    MainInfo->GetMastersMenu()->SetMasterBusyStatusByRegCode(MainInfo->GetOrdersMenu()->GetMasterRegCodeByValue(OrderNumber), -1);
    MainInfo->GetOrdersMenu()->SetOrderAsCompleted(OrderNumber);
    MainInfo->GetOrdersMenu()->ClearInputs();
}

void OrderManipulate::RemoveOrder(int OrderNumber, MainWindow* MainInfo)
{
    if (OrderNumber > MainInfo->GetOrdersMenu()->GetSizeOfList())
    {
        OrderManipulate::SendErrorMessage("Такого заказа не существует.");

        return;
    }
    if (MainInfo->GetOrdersMenu()->GetModelOfMenu()->item(OrderNumber-1, 3)->text() == "В процессе")
    {
        OrderManipulate::SendErrorMessage("Выполните заказ перед удалением.");

        return;
    }
    MainInfo->GetOrdersMenu()->RemoveOrder(OrderNumber);
    MainInfo->GetOrdersMenu()->ClearInputs();
}

void OrderManipulate::RemoveClient(int RegNumber, MainWindow* MainInfo)
{
    if (not(MainInfo->GetClientsMenu()->IsClientInList(RegNumber)))
    {
        OrderManipulate::SendErrorMessage("Такого клиента не существует.");

        return;
    }

    if (MainInfo->GetOrdersMenu()->HasSomeoneNotcompletedOrder(RegNumber))
    {
        OrderManipulate::SendErrorMessage("У клиента есть не выполненный заказ.");

        return;
    }

    MainInfo->GetClientsMenu()->RemoveClientFromModel(RegNumber);
    MainInfo->GetClientsMenu()->ClearInputs();
}

void OrderManipulate::RemoveMaster(QString RegCode, MainWindow* MainInfo)
{
    if (not(MainInfo->GetMastersMenu()->IsMasterInList(RegCode)))
    {
        OrderManipulate::SendErrorMessage("Такого мастера не существует.");

        return;
    }
    if (MainInfo->GetOrdersMenu()->HasSomeoneNotcompletedOrder(RegCode))
    {
        OrderManipulate::SendErrorMessage("У мастера есть не выполненный заказ.");

        return;
    }
    MainInfo->GetMastersMenu()->RemoveMasterFromModel(RegCode);
    MainInfo->GetMastersMenu()->ClearInputs();
}
