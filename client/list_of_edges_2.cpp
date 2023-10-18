#include "list_of_edges_2.h"
#include "ui_list_of_edges_2.h"
#include <ctime>
#include <QTableWidget>
#include <QTableView>
#include <QtWidgets>
#include <QSize>
#include <algorithm>
#include <QRegularExpression>
#include <singleclient.h>
#include <client.h>

const int numVertices = 5;
const int numEdges = 5;

QVector<QVector<int>> incidenceMatrix(numVertices, QVector<int>(numEdges, 0));

QTableWidget *tableWidget2;

list_of_edges_2::list_of_edges_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::list_of_edges_2)
{
    ui->setupUi(this);
    srand(time(0));
    tableWidget2 = new QTableWidget(numVertices, numEdges);
    ui->verticalLayout->addWidget(tableWidget2);
    generateRandomMatrix();
    updateMatrixDisplay();
    tableWidget2->resizeColumnsToContents();
    tableWidget2->resizeRowsToContents();

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numEdges; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(incidenceMatrix[i][j]));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Запрещаем редактирование
            tableWidget2->setItem(i, j, item);
        }
    }
}

void list_of_edges_2::generateRandomMatrix()
{
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numEdges; ++j) {
            incidenceMatrix[i][j] = 0;
        }
    }

    QList<QPair<int, int>> usedEdges; // Список, чтобы отслеживать уже использованные рёбра

    for (int j = 0; j < numEdges; ++j) {
        int outVertex = -1;
        int inVertex = -1;

        // Генерация случайных вершин, не инцидентных другому ребру
        do {
            outVertex = rand() % numVertices;
            inVertex = rand() % numVertices;
        } while (outVertex == inVertex || usedEdges.contains(qMakePair(outVertex, inVertex)) || usedEdges.contains(qMakePair(inVertex, outVertex)));

        incidenceMatrix[outVertex][j] = 1;
        incidenceMatrix[inVertex][j] = -1;

        usedEdges.append(qMakePair(outVertex, inVertex));
    }
}


void list_of_edges_2::updateMatrixDisplay() {
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numEdges; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(incidenceMatrix[i][j]));
            tableWidget2->setItem(i, j, item);
        }
    }
}

void list_of_edges_2::checkAnswer() {
    QString answer = ui->answer->text();

    QRegularExpression re("^(\\d{2}(\\s*\\d{2})+)$");
    if (re.match(answer).hasMatch()) {
        QStringList edges = answer.split(" ");
        QSet<QPair<int, int>> answeredEdges;

        for (const QString& edge : edges) {
            QStringList vertices {edge[0], edge[1]};
            if (vertices.size() == 2) {
                int vertex1 = vertices[0].toInt();
                int vertex2 = vertices[1].toInt();
                answeredEdges.insert(QPair<int, int>(qMin(vertex1, vertex2), qMax(vertex1, vertex2)));
            }
        }

        QSet<QPair<int, int>> expectedEdges;

        for (int j = 0; j < numEdges; ++j) {
            int outVertex = -1;
            int inVertex = -1;

            for (int i = 0; i < numVertices; ++i) {
                if (incidenceMatrix[i][j] == 1) {
                    outVertex = i+1;
                } else if (incidenceMatrix[i][j] == -1) {
                    inVertex = i+1;
                }
            }

            expectedEdges.insert(QPair<int, int>(qMin(outVertex, inVertex), qMax(outVertex, inVertex)));
        }

        qDebug() << "Ответ пользователя: " << answeredEdges;
        qDebug() << "Ожидаемый ответ: " << expectedEdges;

        if (answeredEdges == expectedEdges) {
            QMessageBox::information(this, " ", "Ответ верный!");
            SingletonClient::getInstance()->sendToServer("answer " + Client::getInstance()->user_login + " " + Client::getInstance()->user_pass + " " + "1" + "\n");
        } else {
            QMessageBox::warning(this, " ", "Ответ неверный.");
            SingletonClient::getInstance()->sendToServer("answer " + Client::getInstance()->user_login + " " + Client::getInstance()->user_pass + " " + "0" + "\n");
        }
    } else {
        QMessageBox::warning(this, "Неправильный формат ответа", "Ответ не соответствует формату.");
    }
    generateRandomMatrix();
    updateMatrixDisplay();
}



list_of_edges_2::~list_of_edges_2()
{
    delete ui;
}

void list_of_edges_2::on_sendAnswer_clicked()
{
    checkAnswer();
}

