#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QKeyEvent>
#include <QDebug>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_value(0)
    , m_waitingForOperand(true)
    , m_memory(0)
{
    ui->setupUi(this);

    // 设置窗口标题
    setWindowTitle("Calculator");

    // 设置样式表
    this->setStyleSheet(
        "MainWindow { "
        "   background-color: #2b2b2b; "
        "}"
        "QLineEdit { "
        "   background-color: #000000; "
        "   color: #ffffff; "
        "   border: 2px solid #555555; "
        "   border-radius: 10px; "
        "   padding: 15px; "
        "   font-size: 24px; "
        "   font-weight: bold; "
        "   selection-background-color: #333333; "
        "}"
        "QPushButton { "
        "   background-color: #4a4a4a; "
        "   color: #ffffff; "
        "   border: 2px solid #555555; "
        "   border-radius: 15px; "
        "   font-size: 18px; "
        "   font-weight: bold; "
        "   min-width: 60px; "
        "   min-height: 60px; "
        "}"
        "QPushButton:hover { "
        "   background-color: #5a5a5a; "
        "   border: 2px solid #666666; "
        "}"
        "QPushButton:pressed { "
        "   background-color: #3a3a3a; "
        "   border: 2px solid #444444; "
        "}"
        "QPushButton[text='+'], QPushButton[text='-'], "
        "QPushButton[text='×'], QPushButton[text='÷'], "
        "QPushButton[text='='] { "
        "   background-color: #ff9500; "
        "   color: #ffffff; "
        "}"
        "QPushButton[text='+']:hover, QPushButton[text='-']:hover, "
        "QPushButton[text='×']:hover, QPushButton[text='÷']:hover, "
        "QPushButton[text='=']:hover { "
        "   background-color: #ffaa33; "
        "}"
        "QPushButton[text='+']:pressed, QPushButton[text='-']:pressed, "
        "QPushButton[text='×']:pressed, QPushButton[text='÷']:pressed, "
        "QPushButton[text='=']:pressed { "
        "   background-color: #cc7700; "
        "}"
        "QPushButton[text='C'], QPushButton[text='⌫'], "
        "QPushButton[text='%'] { "
        "   background-color: #a6a6a6; "
        "   color: #000000; "
        "}"
        "QPushButton[text='C']:hover, QPushButton[text='⌫']:hover, "
        "QPushButton[text='%']:hover { "
        "   background-color: #b6b6b6; "
        "}"
        "QPushButton[text='C']:pressed, QPushButton[text='⌫']:pressed, "
        "QPushButton[text='%']:pressed { "
        "   background-color: #969696; "
        "}"
        "QPushButton[text='MC'], QPushButton[text='M+'], "
        "QPushButton[text='M-'], QPushButton[text='MR'] { "
        "   background-color: #6a6a6a; "
        "   color: #ffffff; "
        "   font-size: 14px; "
        "}"
        "QPushButton[text='MC']:hover, QPushButton[text='M+']:hover, "
        "QPushButton[text='M-']:hover, QPushButton[text='MR']:hover { "
        "   background-color: #7a7a7a; "
        "}"
        "QPushButton[text='MC']:pressed, QPushButton[text='M+']:pressed, "
        "QPushButton[text='M-']:pressed, QPushButton[text='MR']:pressed { "
        "   background-color: #5a5a5a; "
        "}"
        );

    // 连接数字按钮 (0-9)
    for (int i = 0; i <= 9; ++i) {
        QString buttonName = QString("pushButton_%1").arg(i);
        QPushButton *button = findChild<QPushButton*>(buttonName);
        if (button) {
            connect(button, &QPushButton::clicked, this, &MainWindow::digitClicked);
        }
    }

    // 连接操作符按钮
    connect(ui->pushButton_add, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->pushButton_subtract, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->pushButton_multiply, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->pushButton_divide, &QPushButton::clicked, this, &MainWindow::operatorClicked);

    // 连接功能按钮
    connect(ui->pushButton_clear, &QPushButton::clicked, this, &MainWindow::clearClicked);
    connect(ui->pushButton_backspace, &QPushButton::clicked, this, &MainWindow::backspaceClicked);
    connect(ui->pushButton_equal, &QPushButton::clicked, this, &MainWindow::equalClicked);
    connect(ui->pushButton_point, &QPushButton::clicked, this, &MainWindow::pointClicked);
    connect(ui->pushButton_percent, &QPushButton::clicked, this, &MainWindow::percentClicked);

    // 连接内存按钮
    connect(ui->pushButton_MC, &QPushButton::clicked, this, &MainWindow::memoryClear);
    connect(ui->pushButton_MR, &QPushButton::clicked, this, &MainWindow::memoryRecall);
    connect(ui->pushButton_Mplus, &QPushButton::clicked, this, &MainWindow::memoryAdd);
    connect(ui->pushButton_Mminus, &QPushButton::clicked, this, &MainWindow::memorySubtract);

    // 初始化显示
    ui->lineEdit_display->setText("0");
    ui->lineEdit_display->setAlignment(Qt::AlignRight);

    // 设置焦点策略，确保可以接收键盘事件
    setFocusPolicy(Qt::StrongFocus);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digitClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        int digitValue = clickedButton->text().toInt();
        digitButtonClicked(digitValue);
    }
}

void MainWindow::digitButtonClicked(int digit)
{
    if (ui->lineEdit_display->text() == "0" && digit == 0)
        return;

    if (m_waitingForOperand) {
        ui->lineEdit_display->clear();
        m_waitingForOperand = false;
    }

    ui->lineEdit_display->setText(ui->lineEdit_display->text() + QString::number(digit));
}

void MainWindow::pointClicked()
{
    if (m_waitingForOperand) {
        ui->lineEdit_display->setText("0");
        m_waitingForOperand = false;
    }

    if (!ui->lineEdit_display->text().contains('.')) {
        ui->lineEdit_display->setText(ui->lineEdit_display->text() + ".");
    }
}

void MainWindow::backspaceClicked()
{
    QString text = ui->lineEdit_display->text();
    if (text.length() > 0) {
        text.chop(1);
    }

    if (text.isEmpty() || text == "-") {
        text = "0";
        m_waitingForOperand = true;
    }

    ui->lineEdit_display->setText(text);
}

void MainWindow::clearClicked()
{
    ui->lineEdit_display->setText("0");
    m_value = 0;
    m_pendingOperation.clear();
    m_waitingForOperand = true;
}

void MainWindow::percentClicked()
{
    double value = ui->lineEdit_display->text().toDouble();
    value *= 0.01;
    ui->lineEdit_display->setText(QString::number(value));
    m_waitingForOperand = true;
}

void MainWindow::operatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    QString clickedOperator = clickedButton->text();
    double operand = ui->lineEdit_display->text().toDouble();

    if (!m_pendingOperation.isEmpty()) {
        // 执行之前的运算
        if (!calculate(operand, m_pendingOperation)) {
            return; // 计算出错，已在calculate中处理
        }
        ui->lineEdit_display->setText(QString::number(m_value));
    } else {
        m_value = operand;
    }

    m_pendingOperation = clickedOperator;
    m_waitingForOperand = true;
}

bool MainWindow::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == "+") {
        m_value += rightOperand;
    } else if (pendingOperator == "-") {
        m_value -= rightOperand;
    } else if (pendingOperator == "×") {
        m_value *= rightOperand;
    } else if (pendingOperator == "÷") {
        if (rightOperand == 0.0) {
            ui->lineEdit_display->setText("Error");
            clearClicked();
            return false;
        }
        m_value /= rightOperand;
    }
    return true;
}

void MainWindow::equalClicked()
{
    double operand = ui->lineEdit_display->text().toDouble();

    if (!m_pendingOperation.isEmpty()) {
        if (!calculate(operand, m_pendingOperation)) {
            return; // 计算出错，已在calculate中处理
        }
        m_pendingOperation.clear();
    } else {
        m_value = operand;
    }

    ui->lineEdit_display->setText(QString::number(m_value));
    m_waitingForOperand = true;
}

void MainWindow::memoryClear()
{
    m_memory = 0;
}

void MainWindow::memoryRecall()
{
    ui->lineEdit_display->setText(QString::number(m_memory));
    m_waitingForOperand = true;
}

void MainWindow::memoryAdd()
{
    double value = ui->lineEdit_display->text().toDouble();
    m_memory += value;
    m_waitingForOperand = true;
}

void MainWindow::memorySubtract()
{
    double value = ui->lineEdit_display->text().toDouble();
    m_memory -= value;
    m_waitingForOperand = true;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_0:
        digitButtonClicked(0);
        break;
    case Qt::Key_1:
        digitButtonClicked(1);
        break;
    case Qt::Key_2:
        digitButtonClicked(2);
        break;
    case Qt::Key_3:
        digitButtonClicked(3);
        break;
    case Qt::Key_4:
        digitButtonClicked(4);
        break;
    case Qt::Key_5:
        digitButtonClicked(5);
        break;
    case Qt::Key_6:
        digitButtonClicked(6);
        break;
    case Qt::Key_7:
        digitButtonClicked(7);
        break;
    case Qt::Key_8:
        digitButtonClicked(8);
        break;
    case Qt::Key_9:
        digitButtonClicked(9);
        break;
    case Qt::Key_Plus:
        ui->pushButton_add->click();
        break;
    case Qt::Key_Minus:
        ui->pushButton_subtract->click();
        break;
    case Qt::Key_Asterisk:
        ui->pushButton_multiply->click();
        break;
    case Qt::Key_Slash:
        ui->pushButton_divide->click();
        break;
    case Qt::Key_Equal:
    case Qt::Key_Enter:
    case Qt::Key_Return:
        equalClicked();
        break;
    case Qt::Key_Period:
    case Qt::Key_Comma:
        pointClicked();
        break;
    case Qt::Key_Backspace:
        backspaceClicked();
        break;
    case Qt::Key_Escape:
        clearClicked();
        break;
    case Qt::Key_Delete:
        clearClicked();
        break;
    case Qt::Key_Percent:
        percentClicked();
        break;
    default:
        QMainWindow::keyPressEvent(event);
        return;
    }

    event->accept();
}
