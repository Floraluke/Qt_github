#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
// 【新增】引入文件操作相关头文件
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 自动生成的槽函数声明（如果UI里右键转到槽了，这里会自动有，没有就手动加上）
    void on_btnCheckIn_clicked();
    void on_btnCheckOut_clicked();

    // 【新增】筛选和搜索的槽
    void on_comboType_currentTextChanged(const QString &arg1);
    void on_btnSearch_clicked();
    void on_btnShowAll_clicked();
    void on_btnExport_clicked(); // 【新增】导出按钮槽函数

    void on_btnStats_clicked();

    void on_btnLogout_clicked();

    void on_btnLogout_2_clicked();

private:
    Ui::MainWindow *ui;

    QSqlTableModel *model;        // 房态模型
    QSqlTableModel *historyModel; // 【新增】历史记录模型

    void initModel(); // 初始化函数
};
#endif // MAINWINDOW_H
