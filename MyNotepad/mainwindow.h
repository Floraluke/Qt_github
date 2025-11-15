#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // 计算器状态变量
    double m_value;              // 存储当前值或运算结果
    QString m_pendingOperation;  // 待处理的操作符
    bool m_waitingForOperand;    // 是否等待输入操作数
    double m_memory;             // 内存存储值

private slots:
    // 数字按钮处理
    void digitClicked();
    void digitButtonClicked(int digit);

    // 操作符处理
    void operatorClicked();

    // 等号处理
    void equalClicked();

    // 清除处理
    void clearClicked();

    // 退格处理
    void backspaceClicked();

    // 小数点处理
    void pointClicked();

    // 百分比处理
    void percentClicked();

    // 内存功能
    void memoryClear();
    void memoryRecall();
    void memoryAdd();
    void memorySubtract();

    // 计算函数
    bool calculate(double rightOperand, const QString &pendingOperator);

protected:
    // 键盘事件处理
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
