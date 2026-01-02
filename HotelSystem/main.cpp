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

    w.setWindowTitle("酒店智能管理系统 v1.0"); // 加上标题

    // ==================== 豪华版 QSS 样式表Start ====================
    QString qss = R"(
    QDialog {
    background-color: #ffffff; /* 纯白背景 */
    }

    /* 弹窗里的输入框变高、变大 */
    QDialog QLineEdit {
    border: 1px solid #ccc;
    border-radius: 4px;
    padding: 8px;      /* 内边距加大 */
    font-size: 14px;   /* 字号加大 */
    min-height: 25px;  /* 最小高度限制 */
    }
    QDialog QLineEdit:focus {
    border: 2px solid #409eff; /* 聚焦变蓝 */
    }

    /* 弹窗里的标签 */
    QDialog QLabel {
    font-size: 14px;
    color: #333;
    font-weight: bold; /* 加粗看起来更清晰 */
    }

        /* 1. 全局背景色：柔和的灰白色，不刺眼 */
        QMainWindow {
            background-color: #f5f6fa;
        }

        /* 2. Tab 选项卡美化：去掉老土的边框，改成现代导航栏风格 */
        QTabWidget::pane {
            border: none;
            background: white;
            border-radius: 8px; /* 圆角卡片 */
            margin-top: 10px;
        }
        QTabBar::tab {
            background: transparent;
            color: #636e72;
            padding: 10px 20px;
            font-weight: bold;
            font-size: 14px;
            border-bottom: 3px solid transparent; /* 默认底部无条 */
        }
        QTabBar::tab:selected {
            color: #0984e3; /* 选中变蓝 */
            border-bottom: 3px solid #0984e3; /* 选中底部亮条 */
            background-color: #dfe6e9;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
        }

        /* 3. 表格 (TableView) 美化：斑马纹、去虚线 */
        QTableView {
            background-color: white;
            border: 1px solid #dfe6e9;
            border-radius: 4px;
            gridline-color: #ecf0f1; /* 极淡的网格线 */
            selection-background-color: #74b9ff; /* 选中行的颜色 */
            selection-color: white;
            alternate-background-color: #f9fbfd; /* 隔行变色 */
        }
        QHeaderView::section {
            background-color: #f1f2f6; /* 表头背景 */
            border: none;
            border-bottom: 1px solid #dcdde1;
            padding: 8px;
            font-weight: bold;
            color: #2d3436;
        }

        /* 4. 按钮通用样式：扁平、圆角、阴影 */
        QPushButton {
            background-color: #0984e3; /* 科技蓝 */
            color: white;
            border-radius: 5px;
            padding: 8px 16px;
            font-size: 13px;
            border: none;
        }
        QPushButton:hover {
            background-color: #74b9ff; /* 悬停变亮 */
        }
        QPushButton:pressed {
            background-color: #0652DD; /* 按下变深 */
        }

        /* 5. 特殊按钮颜色定制 */
        /* 退房按钮：红色警示 */
        QPushButton#btnCheckOut {
            background-color: #d63031;
        }
        QPushButton#btnCheckOut:hover {
            background-color: #ff7675;
        }

        /* 统计/显示全部：绿色/橙色 */
        QPushButton#btnShowAll {
            background-color: #00b894;
        }
        QPushButton#btnStats {
            background-color: #fdcb6e;
            color: #2d3436;
        }

        /* 6. 输入框美化 */
        QLineEdit, QComboBox, QDateEdit {
            border: 1px solid #b2bec3;
            border-radius: 4px;
            padding: 5px;
            background: white;
            selection-background-color: #0984e3;
        }
        QLineEdit:focus, QComboBox:focus, QDateEdit:focus {
            border: 1px solid #0984e3; /* 聚焦时边框变蓝 */
        }

        /* 7. 标签文字 */
        QLabel {
            color: #2d3436;
            font-size: 13px;
        }
    )";
    // ==================== 豪华版 QSS 样式表 End ====================
    a.setStyleSheet(qss);

    w.show();
    return a.exec();
}
