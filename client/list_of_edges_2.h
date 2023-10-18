#ifndef LIST_OF_EDGES_2_H
#define LIST_OF_EDGES_2_H

#include <QWidget>
#include "singleton.h"

namespace Ui {
class list_of_edges_2;
}

class list_of_edges_2 : public QWidget, public Singleton <list_of_edges_2>
{
    Q_OBJECT

public:
    friend Singleton <list_of_edges_2>;

    void generateRandomMatrix();

    void updateMatrixDisplay();

    void checkAnswer();

private slots:
    void on_sendAnswer_clicked();

private:
    Ui::list_of_edges_2 *ui;
    explicit list_of_edges_2(QWidget *parent = nullptr);
    ~list_of_edges_2();
};

#endif // LIST_OF_EDGES_2_H
