#include "threadtest.h"

ThreadTest::ThreadTest(QObject *parent):
    QThread(parent)
{
}

void ThreadTest::run()
{

    emit ReadServer();
}

void ThreadTest::ReadServer(){

}
