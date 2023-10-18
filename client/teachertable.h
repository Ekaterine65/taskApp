#ifndef TEACHERTABLE_H
#define TEACHERTABLE_H

#include <QWidget>
#include <QtWidgets>
#include <singleton.h>

namespace Ui {
class teacherTable;
}

class teacherTable : public QWidget, public Singleton<teacherTable>
{
    Q_OBJECT

public:
    QTableWidget *tableWidget;
    friend Singleton<teacherTable>;
    explicit teacherTable(QWidget *parent = nullptr);
    ~teacherTable();

private:
    Ui::teacherTable *ui;
};

#endif // TEACHERTABLE_H
