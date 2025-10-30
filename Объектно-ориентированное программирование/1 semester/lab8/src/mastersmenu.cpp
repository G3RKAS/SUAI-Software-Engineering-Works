#include "mastersmenu.h"
#include "ordermanipulate.h"
#include "ui_mastersmenu.h"

MastersMenu::MastersMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MastersMenu)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);

    model = new QStandardItemModel(0, 4);
    SetModelHeader();

    this->NumOfMasters = 0;
    auto MasterTable = ui->MastersTable;
    MasterTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    MasterTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    MasterTable->setModel(model);
    ui->RegEdit->setInputMask(">AA-9000;_");

    AddNewMasterToModel(new Worker(nullptr, "АА еее ВВ", "Junior"));
    AddNewMasterToModel(new Worker(nullptr, "УУ вва даку", "Junior"));
    AddNewMasterToModel(new Worker(nullptr, "павп кукпп п", "Senior"));
    AddNewMasterToModel(new Worker(nullptr, "аупау пук", "Middle"));

    connect(ui->AddMaster, &QPushButton::clicked, this, &MastersMenu::RequestToAddMaster);
    connect(ui->RemoveMaster, &QPushButton::clicked, this, [this] {emit RequestToRemoveMaster(ui->RegEdit->text());});
    connect(ui->PositionCombo, &QComboBox::currentTextChanged, this, &MastersMenu::InfoChanged);
    connect(ui->FIOEdit, &QLineEdit::textChanged, this, &MastersMenu::InfoChanged);
    connect(ui->RegEdit, &QLineEdit::textChanged, this, &MastersMenu::RegNumberChanged);
}

MastersMenu::~MastersMenu()
{
    auto ListBegin = MasterList.begin();
    auto ListEnd = MasterList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        delete *ListBegin;

    }
    model->clear();
    delete model;
    delete ui;
}

void MastersMenu::SetMasterBusyStatusByRegCode(QString RegCode, int OrderNumber)
{
    auto ListBegin = MasterList.begin();
    auto ListEnd = MasterList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetRegCode() == RegCode)
        {
            break;
        }
    }

    (*ListBegin)->SetOrder(OrderNumber);
    model->setItem(ListBegin-MasterList.begin(), 3, new QStandardItem((*ListBegin)->GetOrderStatus()));
}

void MastersMenu::SetModelHeader()
{
    model->setHeaderData(0, Qt::Horizontal, "Регистрационный номер");
    model->setHeaderData(1, Qt::Horizontal, "ФИО");
    model->setHeaderData(2, Qt::Horizontal, "Должность");
    model->setHeaderData(3, Qt::Horizontal, "Заказ");
}

void MastersMenu::ClearInputs()
{
    ui->AddMaster->setDisabled(true);
    ui->RemoveMaster->setDisabled(true);

    ui->FIOEdit->clear();
    ui->PositionCombo->setCurrentIndex(0);
    ui->RegEdit->clear();
}

void MastersMenu::AddNewMasterToModel(Worker* MasterInfo)
{
    int IndexForAdd = ++this->NumOfMasters-1;
    model->setItem(IndexForAdd, 0, new QStandardItem(MasterInfo->GetRegCode()));
    model->setItem(IndexForAdd, 1, new QStandardItem(MasterInfo->GetFIO()));
    model->setItem(IndexForAdd, 2, new QStandardItem(MasterInfo->GetPosition()));
    model->setItem(IndexForAdd, 3, new QStandardItem(MasterInfo->GetOrderStatus()));
    MasterList.append(MasterInfo);
}

void MastersMenu::RemoveMasterFromModel(QString RegCode)
{
    auto ListBegin = MasterList.begin();
    auto ListEnd = MasterList.end();
    QList<Worker*>::iterator finded = ListEnd;
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetRegCode() == RegCode)
        {
            finded = ListBegin;
            break;
        }
    }
    int IndexOfFinded = finded-MasterList.begin();
    if (finded != ListEnd)
    {
        MasterList.erase(finded);
        model->removeRow(IndexOfFinded);
        this->NumOfMasters--;
    }
}

bool MastersMenu::IsMasterInList(QString RegCode)
{
    auto ListBegin = MasterList.begin();
    auto ListEnd = MasterList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetRegCode() == RegCode)
        {
            return true;
        }
    }
    return false;
}

Worker* MastersMenu::GetMasterByRegCode(QString RegCode)
{
    auto ListBegin = MasterList.begin();
    auto ListEnd = MasterList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetRegCode() == RegCode)
        {
            return *ListBegin;
        }
    }
    return nullptr;
}

void MastersMenu::RequestToAddMaster()
{
    QString FIO = ui->FIOEdit->text();
    QString Position = ui->PositionCombo->currentText();
    QString RegCode = Worker::FIOnPosToRegCode(FIO, Position);
    if (not(IsMasterInList(RegCode)))
    {
        AddNewMasterToModel(new Worker(nullptr, FIO, Position));
    }
    else
    {
        OrderManipulate::SendErrorMessage("Такой мастер уже существует.");
        return;
    }
    ClearInputs();
}

void MastersMenu::InfoChanged()
{
    if (not(ui->PositionCombo->currentText().isEmpty()) && not(ui->FIOEdit->text().isEmpty()) &&
        not(ui->FIOEdit->text().size() > 31))
    {
        ui->AddMaster->setDisabled(false);
    }
    else
    {
        ui->AddMaster->setDisabled(true);
    }
}

void MastersMenu::RegNumberChanged()
{
    if (ui->RegEdit->hasAcceptableInput() && NumOfMasters>0)
    {
        ui->RemoveMaster->setDisabled(false);
    }
    else
    {
        ui->RemoveMaster->setDisabled(true);
    }
}
