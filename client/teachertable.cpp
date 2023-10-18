#include "teachertable.h"
#include "ui_teachertable.h"
#include <QtWidgets>

teacherTable::teacherTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacherTable)
{
    ui->setupUi(this);
    this->setWindowTitle("Таблица преподавателя");

    // Создаем таблицу с 4 столбцами
    tableWidget = new QTableWidget();
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels({"Логин студента", "Верные попытки", "Неверные попытки", "Результативность"});

    tableWidget->resizeColumnsToContents();
    tableWidget->resizeRowsToContents();

    // Создаем вертикальный макет
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tableWidget);

    // Создаем кнопки для сортировки по каждому столбцу и добавляем их в макет
    QPushButton *sortLoginButton = new QPushButton("Сортировка по логину");
    layout->addWidget(sortLoginButton);

    QPushButton *sortCorrectButton = new QPushButton("Сортировка по верным попыткам");
    layout->addWidget(sortCorrectButton);

    QPushButton *sortIncorrectButton = new QPushButton("Сортировка по неверным попыткам");
    layout->addWidget(sortIncorrectButton);

    QPushButton *sortResultButton = new QPushButton("Сортировка по результативности");
    layout->addWidget(sortResultButton);

    // Подключаем сигналы и слоты для сортировки по столбцам
    QObject::connect(sortLoginButton, &QPushButton::clicked, [=]() {
        tableWidget->sortItems(0);
    });

    QObject::connect(sortCorrectButton, &QPushButton::clicked, [=]() {
        tableWidget->sortItems(1);
    });

    QObject::connect(sortIncorrectButton, &QPushButton::clicked, [=]() {
        tableWidget->sortItems(2);
    });

    QObject::connect(sortResultButton, &QPushButton::clicked, [=]() {
        tableWidget->sortItems(3);
    });


    this->setLayout(layout);
}

teacherTable::~teacherTable()
{
    delete ui;
}
