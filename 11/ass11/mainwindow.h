#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slotAdd();
    void slotSub();
    void slotMul();
    void slotDiv();
    void slotResult();
    void changedTextState();

private:
    Ui::MainWindow *ui;
    QString data;
    int firstNum;
    int secondNum;
    int code;
};
#endif // MAINWINDOW_H
