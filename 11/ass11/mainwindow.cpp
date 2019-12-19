#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotAdd(){
    data = ui->textEdit->toPlainText();
    ui->textEdit->setText(data+"+");
    code = 1;
}

void MainWindow::slotSub(){
    data = ui->textEdit->toPlainText();
    ui->textEdit->setText(data+"-");
    code = 2;
}

void MainWindow::slotMul(){
    data = ui->textEdit->toPlainText();
    ui->textEdit->setText(data+"*");
    code = 3;
}

void MainWindow::slotDiv(){
    data = ui->textEdit->toPlainText();
    ui->textEdit->setText(data+"/");
    code = 4;
}

void MainWindow::slotResult(){
    data = ui->textEdit->toPlainText();
    QStringList list;
    int result;
    switch (code) {
    case 1:
        list = data.split("+");
        firstNum = list.value(0).toInt();
        secondNum = list.value(1).toInt();
        result = firstNum + secondNum;
        ui->textEdit_2->setText(QString::number(result));
        break;
    case 2:
        list = data.split("-");
        firstNum = list.value(0).toInt();
        secondNum = list.value(1).toInt();
        result = firstNum - secondNum;
        ui->textEdit_2->setText(QString::number(result));
        break;
    case 3:
        list = data.split("*");
        firstNum = list.value(0).toInt();
        secondNum = list.value(1).toInt();
        result = firstNum * secondNum;
        ui->textEdit_2->setText(QString::number(result));
        break;
    case 4:
        list = data.split("/");
        firstNum = list.value(0).toInt();
        secondNum = list.value(1).toInt();
        if(secondNum!=0)
            result = (float)firstNum / secondNum;
        else
            result=0;
        ui->textEdit_2->setText(QString::number(result));
        break;
    default:
        break;
    }
}

void MainWindow::changedTextState(){
}

