#include "clientsmenuform.h"
#include "ui_clientsmenuform.h"

ClientsMenuForm::ClientsMenuForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientsMenuForm)
{
    ui->setupUi(this);
}

ClientsMenuForm::~ClientsMenuForm()
{
    delete ui;
}
