#ifndef CLIENTSMENUFORM_H
#define CLIENTSMENUFORM_H

#include <QWidget>

namespace Ui {
class ClientsMenuForm;
}

class ClientsMenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientsMenuForm(QWidget *parent = nullptr);
    ~ClientsMenuForm();

private:
    Ui::ClientsMenuForm *ui;
};

#endif // CLIENTSMENUFORM_H
