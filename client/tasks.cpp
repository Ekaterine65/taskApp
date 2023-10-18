#include "tasks.h"
#include "ui_tasks.h"
#include "list_of_edges.h"
#include "list_of_edges_2.h"


tasks::tasks(QWidget *parent) : QWidget(parent), ui(new Ui::tasks)
{
    ui->setupUi(this);
}

tasks::~tasks()
{
    delete ui;
}

void tasks::on_pushButton_clicked()
{
    list_of_edges::getInstance()->show();
    this->hide();
}


void tasks::on_pushButton_2_clicked()
{
    list_of_edges_2::getInstance()->show();
    this->hide();
}

