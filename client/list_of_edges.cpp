#include "list_of_edges.h"
#include "ui_list_of_edges.h"
#include <ctime>
#include <QTableWidget>
#include <QTableView>
#include <QtWidgets>
#include <QSize>
#include <QRegularExpression>
#include <singleclient.h>
#include <client.h>

const int matrixSize = 5;
QVector<QVector<int>> adjacencyMatrix(matrixSize, QVector<int>(matrixSize, 0));

QTableWidget *tableWidget;

list_of_edges::list_of_edges(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::list_of_edges)
{
    ui->setupUi(this);
    srand(time(0));
    tableWidget = new QTableWidget(matrixSize, matrixSize);
    ui->verticalLayout->addWidget(tableWidget);
    generateRandomMatrix();
    updateMatrixDisplay();
    tableWidget->resizeColumnsToContents();
    tableWidget->resizeRowsToContents();

    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(adjacencyMatrix[i][j]));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Запрещаем редактирование
            tableWidget->setItem(i, j, item);
        }
    }
}

void list_of_edges::generateRandomMatrix()
{
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = i + 1; j < matrixSize; ++j) {
            adjacencyMatrix[i][j] = (rand() % 2);
            adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
        }
    }
}

void list_of_edges::updateMatrixDisplay() {
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(adjacencyMatrix[i][j]));
            tableWidget->setItem(i, j, item);
        }
    }
}

void list_of_edges::checkAnswer() {
    QString answer = ui->answer->text();

    // Разбиваем строку на список рёбер, используя QRegularExpression
    QRegularExpression re("^(\\d{2},?\\s?)+$");
    if (re.match(answer).hasMatch()) {
        QStringList edges = answer.split(QRegularExpression(",\\s?|\\s"));
        QStringList expectedEdges; // Создаем ожидаемый список рёбер

        // Генерируем ожидаемый список рёбер на основе матрицы смежности
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = i + 1; j < matrixSize; ++j) {
                if (adjacencyMatrix[i][j] == 1) {
                    expectedEdges.append(QString("%1%2").arg(i + 1).arg(j + 1));
                }
            }
        }

        // Сортируем список рёбер в лексикографическом порядке
        edges.sort();
        expectedEdges.sort();

        // Сравниваем список рёбер с ожидаемым
        if (edges == expectedEdges) {
            // Выводим MessageBox с сообщением о правильном ответе
            QMessageBox::information(this, " ", "Ответ верный!");
            SingletonClient::getInstance()->sendToServer("answer " + Client::getInstance()->user_login + " " + Client::getInstance()->user_pass + " " + "1" + "\n");
        } else {
            // Выводим MessageBox с сообщением о неправильном ответе
            QMessageBox::warning(this, " ", "Ответ неверный.");
            SingletonClient::getInstance()->sendToServer("answer " + Client::getInstance()->user_login + " " + Client::getInstance()->user_pass + " " + "0" + "\n");
        }
    } else {
        // Выводим MessageBox с сообщением о неправильном формате ответа
        QMessageBox::warning(this, "Неправильный формат ответа", "Ответ не соответствует формату.");
    }
    generateRandomMatrix();
    updateMatrixDisplay();
}

list_of_edges::~list_of_edges()
{
    delete ui;
}

void list_of_edges::on_sendAnswer_clicked()
{
    checkAnswer();
}

