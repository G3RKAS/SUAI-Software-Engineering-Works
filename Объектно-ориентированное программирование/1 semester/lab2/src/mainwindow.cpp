#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "main_functions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->motherBoard,SIGNAL(checkStateChanged(Qt::CheckState)),SLOT(on_motherBoard_checkStateChanged));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_motherBoard_checkStateChanged(const Qt::CheckState &arg1)
{
    ui->motherBoard->setProperty("Checked", isChecked(arg1));
    updateOutput(ui->compList,ui->resultName);
}


void MainWindow::on_videocard_checkStateChanged(const Qt::CheckState &arg1)
{
    ui->videocard->setProperty("Checked", isChecked(arg1));
    updateOutput(ui->compList,ui->resultName);
}


void MainWindow::on_processor_checkStateChanged(const Qt::CheckState &arg1)
{
    ui->processor->setProperty("Checked", isChecked(arg1));
    updateOutput(ui->compList,ui->resultName);
}


void MainWindow::on_ram_checkStateChanged(const Qt::CheckState &arg1)
{
    ui->ram->setProperty("Checked", isChecked(arg1));
    updateOutput(ui->compList,ui->resultName);
}


void MainWindow::on_cooler_checkStateChanged(const Qt::CheckState &arg1)
{
    ui->cooler->setProperty("Checked", isChecked(arg1));
    updateOutput(ui->compList,ui->resultName);
}

