#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sendflag = false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exitslot(){
    ::close(socketfd);
    exit(0);
}

void MainWindow::connectslot(){
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockaddr.sin_port = htons(3600);

    socklen = sizeof(sockaddr);

    if(::connect(socketfd, (struct sockaddr *)&sockaddr, socklen) == -1)
    {        perror("connect error");
    }

    // readfd set 0
    FD_ZERO(&readfds);
    // socketfd에 해당하는 readfds의 비트를 1로 한다.
    FD_SET(socketfd, &readfds);
    // 0번째 인자를 1로 set한다
    FD_SET(0, &readfds);

    maxfd = socketfd;
    oldfds = readfds;

    ui->chat->setText("success!");

}
void MainWindow::sendslot(){
    QString text = ui->Entry->toPlainText();
    char strc[MAXLINE] = {0,};
    qsnprintf(strc, sizeof(strc), "%s", text.toUtf8().constData());

    writen = write(socketfd, strc, MAXLINE);
    if(readn != writen)
    {
        return;
    }
    sendflag = true;
}

void MainWindow::readslot(){
        readfds = oldfds;
        fd_num = select(maxfd + 1, &readfds, NULL, NULL, NULL);

            //memset(buf, 0x00, MAXLINE);

            memset(buf, 0x00, MAXLINE);
            readn = recv (socketfd, buf, MAXLINE, 0);

            if(readn <= 0)
            {
                return;
            }
            sendflag = false;

            QString str = QString(buf);
            ui->chat->setText(str);
}

