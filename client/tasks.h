#ifndef TASKS_H
#define TASKS_H

#include <QWidget>
#include "singleton.h"

namespace Ui {
class tasks;
}

class tasks : public QWidget, public Singleton<tasks>
{
    Q_OBJECT

public:
    friend Singleton<tasks>;
    Ui::tasks *ui;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    explicit tasks(QWidget *parent = nullptr);
    ~tasks();
};

#endif // TASKS_H
