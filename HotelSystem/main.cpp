#include "mainwindow.h"
#include <QApplication>

// 1. 引入头文件
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 2. 在创建窗口之前，先连接数据库
    if (!createConnection()) {
        return -1; // 如果连接失败，直接退出程序
    }

    MainWindow w;
    w.show();
    return a.exec();
}
