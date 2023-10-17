#ifndef REGFORM_H
#define REGFORM_H

#include <QWidget>
#include "singleton.h"

namespace Ui {
class regForm;
}

class regForm : public QWidget, public Singleton<regForm>
{
    Q_OBJECT

public:
    friend Singleton<regForm>;

private slots:
    void on_typeBox_currentIndexChanged(int index);

    void on_regButton_clicked();

private:
    Ui::regForm *ui;
    explicit regForm(QWidget *parent = nullptr);
    ~regForm();
};

#endif // REGFORM_H
