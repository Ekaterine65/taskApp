#ifndef LIST_OF_EDGES_H
#define LIST_OF_EDGES_H

#include <QWidget>
#include "singleton.h"

namespace Ui {
class list_of_edges;
}

class list_of_edges : public QWidget, public Singleton <list_of_edges>
{
    Q_OBJECT

public:
    friend Singleton <list_of_edges>;

    void generateRandomMatrix();

    void updateMatrixDisplay();

    void checkAnswer();

private slots:
    void on_sendAnswer_clicked();

private:
    Ui::list_of_edges *ui;
    explicit list_of_edges(QWidget *parent = nullptr);
    ~list_of_edges();
};

#endif // LIST_OF_EDGES_H
