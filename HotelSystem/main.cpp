#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include "connection.h"

// 定义一个我们约定的暗号，防止魔法数字
const int RESTART_CODE = 773;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1. 设置全局字体
    QFont font("Microsoft YaHei", 10);
    a.setFont(font);

    // 2. 连接数据库 (只连一次即可)
    if (!createConnection()) {
        return -1;
    }

    // 3. 设置样式表 (Styles)
    QString qss = R"(
        /* 0. 弹窗 (Dialog) 专属样式 */
        QDialog {
            background-color: #ffffff; /* 纯白背景 */
        }
        QDialog QLineEdit {
            border: 1px solid #ccc;
            border-radius: 4px;
            padding: 8px;
            font-size: 14px;
            min-height: 25px;
        }
        QDialog QLineEdit:focus {
            border: 2px solid #409eff; /* 聚焦变蓝 */
        }
        QDialog QLabel {
            font-size: 14px;
            color: #333;
            font-weight: bold;
        }

        /* 1. 主窗口全局背景色 */
        QMainWindow {
            background-color: #f5f6fa;
        }

        /* 2. Tab 选项卡美化 */
        QTabWidget::pane {
            border: none;
            background: white;
            border-radius: 8px;
            margin-top: 10px;
        }
        QTabBar::tab {
            background: transparent;
            color: #636e72;
            padding: 10px 20px;
            font-weight: bold;
            font-size: 14px;
            border-bottom: 3px solid transparent;
        }
        QTabBar::tab:selected {
            color: #0984e3;
            border-bottom: 3px solid #0984e3;
            background-color: #dfe6e9;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
        }

        /* 3. 表格 (TableView) 美化 */
        QTableView {
            background-color: white;
            border: 1px solid #dfe6e9;
            border-radius: 4px;
            gridline-color: #ecf0f1;
            selection-background-color: #74b9ff;
            selection-color: white;
            alternate-background-color: #f9fbfd;
        }
        QHeaderView::section {
            background-color: #f1f2f6;
            border: none;
            border-bottom: 1px solid #dcdde1;
            padding: 8px;
            font-weight: bold;
            color: #2d3436;
        }

        /* 4. 按钮通用样式 */
        QPushButton {
            background-color: #0984e3;
            color: white;
            border-radius: 5px;
            padding: 8px 16px;
            font-size: 13px;
            border: none;
        }
        QPushButton:hover {
            background-color: #74b9ff;
        }
        QPushButton:pressed {
            background-color: #0652DD;
        }

        /* 5. 特殊按钮颜色定制 */
        QPushButton#btnCheckOut {
            background-color: #d63031;
        }
        QPushButton#btnCheckOut:hover {
            background-color: #ff7675;
        }
        QPushButton#btnShowAll {
            background-color: #00b894;
        }
        QPushButton#btnStats {
            background-color: #fdcb6e;
            color: #2d3436;
        }
        QPushButton#btnExport {
            background-color: #6c5ce7; /* 导出按钮紫色 */
        }



        /* 6. 输入框美化 (通用) */
        QLineEdit, QComboBox, QDateEdit {
            border: 1px solid #b2bec3;
            border-radius: 4px;
            padding: 5px;
            background: white;
            selection-background-color: #0984e3;
        }
        QLineEdit:focus, QComboBox:focus, QDateEdit:focus {
            border: 1px solid #0984e3;
        }

        /* 7. 标签文字 */
        QLabel {
            color: #2d3436;
            font-size: 13px;
        }
    )";
    a.setStyleSheet(qss); // 应用样式表

    // ==================== 4. 核心循环逻辑 ====================
    int currentExitCode = 0;

    do {
        // --- A. 弹出登录框 ---
        LoginDialog login;
        if (login.exec() != QDialog::Accepted) {
            // 如果用户在登录界面点了“退出”或右上角的叉，直接结束程序
            return 0;
        }

        // --- B. 登录成功，进入主界面 ---
        MainWindow w;
        w.setWindowTitle("酒店智能管理系统 v1.0");
        w.show();

        // --- C. 进入主循环，等待窗口关闭 ---
        // a.exec() 会阻塞在这里，直到 MainWindow 关闭
        // 当我们在 MainWindow 里调用 qApp->exit(773) 时，a.exec() 就会返回 773
        currentExitCode = a.exec();

    } while (currentExitCode == RESTART_CODE); // 如果返回的是 773，就循环，再次弹出登录框

    return currentExitCode;
}
