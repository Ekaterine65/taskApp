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

private:
    Ui::tasks *ui;
    explicit tasks(QWidget *parent = nullptr);
    ~tasks();
};

#endif // TASKS_H