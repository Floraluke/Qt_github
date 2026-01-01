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

    // 设置全局样式表
    QString qss = R"(
    QMainWindow {
        background-color: #f0f2f5;
    }
    QTableView {
        border: 1px solid #dcdfe6;
        background-color: white;
        selection-background-color: #409eff;
        gridline-color: #e4e7ed;
    }
    QHeaderView::section {
        background-color: #f5f7fa;
        padding: 5px;
        border: none;
        border-bottom: 1px solid #dcdfe6;
        font-weight: bold;
    }
    QPushButton {
        background-color: #409eff;
        color: white;
        border-radius: 4px;
        padding: 6px 16px;
        font-size: 14px;
    }
    QPushButton:hover {
        background-color: #66b1ff;
    }
    QPushButton:pressed {
        background-color: #3a8ee6;
    }
    /* 针对退房按钮做个红色警示 */
    QPushButton#btnCheckOut {
        background-color: #f56c6c;
    }
    QPushButton#btnCheckOut:hover {
        background-color: #f78989;
    }
)";
    a.setStyleSheet(qss);

    w.show();
    return a.exec();
}
