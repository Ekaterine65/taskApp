#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "singleton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Singleton <MainWindow>
{
    Q_OBJECT

public:
    friend Singleton <MainWindow>;
    Ui::MainWindow *ui;

private slots:
    void on_openRegForm_clicked();

    void on_authButton_clicked();

    void is_auth_suc(bool key);

private:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
