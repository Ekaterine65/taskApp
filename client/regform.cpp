#include "regform.h"
#include "ui_regform.h"
#include "client.h"

regForm::regForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regForm)
{
    ui->setupUi(this);
    ui->teacher_login->setReadOnly(true);
    ui->teacher_login->setStyleSheet("QLineEdit { background-color: lightgray; color: darkgray; }");
}

regForm::~regForm()
{
    delete ui;
}

void regForm::on_typeBox_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->teacher_login->setText("");
        ui->teacher_login->setStyleSheet("QLineEdit { background-color: lightgray; color: darkgray; }");
        this->ui->teacher_login->setReadOnly(true);
    } else {
        ui->teacher_login->setStyleSheet("");
        this->ui->teacher_login->setReadOnly(false);
    }
}


void regForm::on_regButton_clicked()
{
    Client::getInstance()->reg(ui->loginEdit->text(), ui->passwordEdit->text(), ui->typeBox->currentIndex() ^ 1, ui->teacher_login->text());
}

