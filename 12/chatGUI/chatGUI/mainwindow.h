#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#define MAXLINE 1024

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int socketfd;
    struct sockaddr_in sockaddr;
    int socklen;
    fd_set readfds, oldfds;
    int maxfd;
    int fd_num;
    char buf[MAXLINE];
    int readn, writen;
    bool sendflag;
    pthread_t tid;

public slots:
    void exitslot();
    void connectslot();
    void sendslot();
    void readslot();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
