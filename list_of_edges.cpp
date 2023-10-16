#include "list_of_edges.h"
#include "ui_list_of_edges.h"

list_of_edges::list_of_edges(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::list_of_edges)
{
    ui->setupUi(this);
}

list_of_edges::~list_of_edges()
{
    delete ui;
}
