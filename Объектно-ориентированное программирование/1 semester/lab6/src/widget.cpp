#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    info(this)
{
    ui->setupUi(this);
    ui->lastInput->setEnabled(false);

    // регистрация слушателя
    connect(&info, SIGNAL(notifyObservers()), this, SLOT(update()));

    // регистрация остальных слотов и сигналов
    connect(ui->calculate, SIGNAL(pressed()), this, SLOT(btnCalcPressed()));
    connect(ui->lastInput, SIGNAL(pressed()), this, SLOT(btnUndoPressed()));

    connect(ui->name, SIGNAL(textChanged(QString)), this, SLOT(updateCost()));
    connect(ui->age, SIGNAL(textChanged(QString)), this, SLOT(updateCost()));
    connect(ui->area, SIGNAL(textChanged(QString)), this, SLOT(updateCost()));
    connect(ui->living, SIGNAL(textChanged(QString)), this, SLOT(updateCost()));

    connect(ui->house, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCost()));
    connect(ui->insurPeriod, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCost()));
}

Widget::~Widget()
{
    delete ui;
}

// Функция при получении сообщения
void Widget::update()
{
    // Получение последнего элемента в списке и заполнение формы
    auto value = info.getActualData();
    if(value != nullptr){
        fillForm(value);
    }
    // Включение-выключение кнопки на основе заполненности списка
    ui->lastInput->setEnabled(info.hasStates());

    value = nullptr;
}

// Нажатие кнопки расчёта
void Widget::btnCalcPressed()
{
    // Заполнение формы
    auto value = processForm();
    showCost(value);
    info.add(value);
    // Включение кнопки последнего запроса
    ui->lastInput->setEnabled(true);

    value = nullptr;
}

// Нажатие кнопки последнего запроса
void Widget::btnUndoPressed()
{
    info.undo();
}

// Заполнение данными объект Estate
Estate *Widget::processForm()
{
    int houseIndex = ui->house->currentIndex();
    Estate::EstateType type = Estate::EstateType(houseIndex);

    return new Estate(nullptr, ui->age->text().toInt(), ui->area->text().toInt(), ui->living->text().toInt(), (ui->insurPeriod->currentIndex()+1)*6, type, ui->name->text());
}


// Заполнение формы
void Widget::fillForm(Estate *value)
{
    ui->name->setText(value->getOwner());
    ui->age->setText(QString::number(value->getAge()));
    ui->living->setText(QString::number(value->getResidents()));
    ui->area->setText(QString::number(value->getArea()));
    ui->insurPeriod->setCurrentIndex(value->getMonths()/6 - 1);
    ui->house->setCurrentIndex((int)value->getType());
    showCost(value);
}

// Показ стоимости
void Widget::showCost(Estate *value)
{
    ui->insurPrice->setText( QString::number( CalculationFacade::getCost(value) ) );
}

// Обновление цены при изменении данных
void Widget::updateCost()
{
    ui->insurPrice->setText("0");
}
