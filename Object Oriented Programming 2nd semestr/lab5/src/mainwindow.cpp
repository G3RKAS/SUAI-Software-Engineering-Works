#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QDir>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->elemIndexEdit, &QLineEdit::textEdited, this, &MainWindow::indexChanged);
    connect(ui->elemVarEdit, &QLineEdit::textEdited, this, &MainWindow::elemChanged);

    connect(ui->saveCollectionToFileButton, &QPushButton::pressed, this, &MainWindow::loadToFile);
    connect(ui->collectionFromFileButton, &QPushButton::pressed, this, &MainWindow::loadFromFile);
    connect(ui->clearCollectionButton, &QPushButton::pressed, this, &MainWindow::clearCollection);
    connect(ui->elemByIndexButton, &QPushButton::pressed, this, &MainWindow::getElemByIndex);
    connect(ui->removeElemByIndexButton, &QPushButton::pressed, this, &MainWindow::removeElemByIndex);
    connect(ui->removeElemByVarButton, &QPushButton::pressed, this, &MainWindow::removeElemByVar);
    connect(ui->addElemButton, &QPushButton::pressed, this, &MainWindow::addElemToEdited);
    connect(ui->sumOfElemButton, &QPushButton::pressed, this, &MainWindow::summElem);
    connect(ui->sumOfEvenButton, &QPushButton::pressed, this, &MainWindow::summEvenElem);
    connect(ui->sumOfPositiveButton, &QPushButton::pressed, this, &MainWindow::summPositiveElem);
    connect(ui->sortButton, &QPushButton::pressed, this, &MainWindow::sortElem);

    connect(ui->fileChooser, &QComboBox::currentTextChanged, this, &MainWindow::fileChanged);

    connect(ui->editedCollectionEdit, &QTextEdit::textChanged, this, &MainWindow::editedCollectionChanged);

    fileLoad();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MyList::updateSize(int arg1)
{
    this->listSize += arg1;
}

void MyList::insert(float arg1)
{
    List.append(arg1);
    updateSize(1);
}

int MyList::size()
{
    return this->listSize;
}

float MyList::at(int arg1)
{
    return List.at(arg1);
}

void MyList::clear()
{
    List.clear();
    this->listSize = 0;
}

bool MyList::isEmpty()
{
    return List.isEmpty();
}

void MyList::takeAt(int arg1)
{
    List.takeAt(arg1);
    updateSize(-1);
}

int MyList::indexOf(float arg1)
{
    return List.indexOf(arg1);
}

void MyList::copy(MyList arg1)
{
    this->clear();

    QList<float>::iterator it = arg1.begin();
    for (; it != arg1.end(); ++it) {
        this->insert(*it);
    }
}


QList<float>::iterator MyList::begin()
{
    return List.begin();
}

QList<float>::iterator MyList::end()
{
    return List.end();
}



void MainWindow::fileLoad()
{
    QDir directory;
    QStringList files = directory.entryList(QStringList() << "list-*.txt",QDir::Files);
    ui->fileChooser->addItems(files);
}

void MainWindow::indexChanged(QString arg1)
{
    if ((arg1.toInt() < 0) or (arg1.toInt() >= EditedList.size()))
    {
        if (arg1.toInt() >= EditedList.size())
        {
            if (EditedList.size() == 0)
            {
                ui->elemIndexEdit->clear();
            }
            else
            {
                ui->elemIndexEdit->setText(QString::number(EditedList.size()-1));
            }

        }
        else
        {
            ui->elemIndexEdit->clear();
        }

    }

    if (ui->elemIndexEdit->text().isEmpty() or EditedList.isEmpty())
    {
        ui->elemByIndexButton ->setDisabled(true);
        ui->removeElemByIndexButton->setDisabled(true);
    }
    else
    {
        ui->elemByIndexButton ->setDisabled(false);
        ui->removeElemByIndexButton->setDisabled(false);
    }
}

void MainWindow::elemChanged()
{
    if (ui->elemVarEdit->text().isEmpty() or EditedList.isEmpty())
    {
        ui->removeElemByVarButton->setDisabled(true);
        ui->addElemButton->setDisabled(ui->elemVarEdit->text().isEmpty());
    }
    else
    {
        ui->removeElemByVarButton->setDisabled(false);
        ui->addElemButton->setDisabled(false);
    }
}

void MainWindow::updateSource()
{
    QString str;
    QList<float>::iterator it = SourceList.begin();
    for (; it != SourceList.end(); ++it) {
        str += QString::number(*it) + '\n';
    }
    ui->sourceCollectionEdit->setText(str);
}

void MainWindow::updateEdited()
{
    QString str;
    QList<float>::iterator it = EditedList.begin();
    for (; it != EditedList.end(); ++it) {
        str += QString::number(*it) + '\n';
    }
    ui->editedCollectionEdit->setText(str);
}


void MainWindow::loadToFile()
{
    QFile myfile(ui->fileChooser->currentText());
    if (!myfile.open(QIODevice::WriteOnly))
    {
        qInfo() << "Что-то пошло не так!";
        return;
    }

    QTextStream stream(&myfile);
    for (int i{0};i<EditedList.size();i++)
    {
        stream << QString::number(EditedList.at(i)) << "\n";
    }

    myfile.close();
}

void MainWindow::loadFromFile()
{
    SourceList.clear();
    EditedList.clear();
    QFile myfile(ui->fileChooser->currentText());
    if (!myfile.open(QIODevice::ReadOnly))
    {
        qInfo() << "Что-то пошло не так!";
        return;
    }

    QTextStream stream(&myfile);
    while (!stream.atEnd())
    {
        QString element = stream.readLine();
        SourceList.insert(element.toFloat());
        EditedList.insert(element.toFloat());
    }

    updateSource();
    updateEdited();

    if (not(EditedList.isEmpty()))
        ui->clearCollectionButton->setDisabled(false);
    indexChanged(ui->elemIndexEdit->text());
    elemChanged();

}

void MainWindow::ClearEdit()
{
    ui->elemIndexEdit->clear();
    ui->elemVarEdit->clear();
    ui->sumEdit->clear();
    ui->sumPositiveEdit->clear();
}

void MainWindow::fileChanged()
{
    SourceList.clear();
    ui->sourceCollectionEdit->clear();
}

void MainWindow::clearCollection()
{
    EditedList.clear();
    ui->editedCollectionEdit->clear();
    ui->clearCollectionButton->setDisabled(true);
}

void MainWindow::editedCollectionChanged()
{
    ClearEdit();
    indexChanged(ui->elemIndexEdit->text());
    elemChanged();
}

void MainWindow::getElemByIndex()
{
    ui->elemVarEdit->setText(QString::number(EditedList.at(ui->elemIndexEdit->text().toInt())));
}

void MainWindow::removeElemByIndex()
{
    EditedList.takeAt(ui->elemIndexEdit->text().toInt());
    updateEdited();
}

void MainWindow::removeElemByVar()
{
    int index = EditedList.indexOf(ui->elemVarEdit->text().toFloat());
    if (index != -1)
    {
        EditedList.takeAt(index);
    }
    updateEdited();
}

void MainWindow::addElemToEdited()
{
    EditedList.insert(ui->elemVarEdit->text().toFloat());
    updateEdited();
}

void MainWindow::summElem()
{
    float sum{0};

    QList<float>::iterator it = EditedList.begin();
    for (; it != EditedList.end(); ++it) {
        sum += *it;
    }

    ui->sumEdit->setText(QString::number(sum));
}

void MainWindow::summEvenElem()
{
    float sum{0};

    QList<float>::iterator it = EditedList.begin();
    for (; it != EditedList.end(); ++it) {
        if ((int)*it % 2 == 0)
            sum += *it;
    }

    ui->sumEdit->setText(QString::number(sum));
}

void MainWindow::summPositiveElem()
{


    QList<float>::iterator it = EditedList.begin();
    QList<float>::iterator endforsum;

    for (; it != EditedList.end(); ++it) {
        if ((*it)>0)
            endforsum = it;
    }
    endforsum++;
    float sum{0};
    it = EditedList.begin();

    for (; it != endforsum; ++it) {
        sum += *it;
    }

    ui->sumPositiveEdit->setText(QString::number(sum));
}

void MainWindow::sortElem()
{
    MyList TempList;

    QList<float>::iterator it = EditedList.begin();
    for (; it != EditedList.end(); ++it) {
        if (abs(*it)<1)
            TempList.insert(*it);
    }
    it = EditedList.begin();
    for (; it != EditedList.end(); ++it) {
        if (abs(*it)>=1)
            TempList.insert(*it);
    }

    EditedList.copy(TempList);

    updateEdited();
}
