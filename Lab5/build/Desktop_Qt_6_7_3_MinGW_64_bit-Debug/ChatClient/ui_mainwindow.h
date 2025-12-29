/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *chatPage;
    QVBoxLayout *verticalLayout_3;
    QLabel *titleLabel2;
    QHBoxLayout *horizontalLayout;
    QTextEdit *roomTextEdit;
    QListWidget *userListWidget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *sayLineEdit;
    QPushButton *sayButton;
    QPushButton *logoutButton;
    QWidget *loginPage;
    QGridLayout *gridLayout_2;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QFrame *loginFrame;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_8;
    QLabel *label_17;
    QLabel *label_16;
    QLineEdit *serverEdit;
    QLineEdit *usernameEdit;
    QSpacerItem *verticalSpacer_7;
    QPushButton *loginButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("/* \345\237\272\344\272\216\345\216\237\346\234\211\346\240\267\345\274\217\344\277\256\346\224\271\357\274\232\350\203\214\346\231\257\346\265\205\350\223\235 + \345\255\227\344\275\223\347\231\275\350\211\262 + \345\215\217\350\260\203\350\276\271\346\241\206 */\n"
"#titleLabel {\n"
"    background: #5DADEC; /* \346\237\224\345\222\214\346\265\205\350\223\235\350\211\262\350\203\214\346\231\257\357\274\210\345\260\217\346\270\205\346\226\260\344\270\273\350\211\262\350\260\203\357\274\211 */\n"
"    color: white; /* \347\231\275\350\211\262\345\255\227\344\275\223\357\274\214\345\222\214\346\265\205\350\223\235\350\203\214\346\231\257\345\257\271\346\257\224\346\270\205\346\231\260 */\n"
"    font-size: 20px; /* \344\277\235\347\225\231\345\216\237\346\234\211\345\255\227\345\217\267 */\n"
"    border: none; /* \344\277\235\347\225\231\346\227\240\350\276\271\346\241\206 */\n"
"    border-bottom: 1px solid #4A90E2; /* \347\250\215\346\267\261\347\232\204\350\223\235\350\211\262\350\276\271\346\241\206\357\274"
                        "\214\345\222\214\350\203\214\346\231\257\345\221\274\345\272\224\346\233\264\345\215\217\350\260\203 */\n"
"    padding: 5px; /* \344\277\235\347\225\231\345\216\237\346\234\211\345\206\205\350\276\271\350\267\235 */\n"
"    \n"
"}\n"
"#titleLabel2\n"
"{\n"
"    background: #5DADEC; /* \346\237\224\345\222\214\346\265\205\350\223\235\350\211\262\350\203\214\346\231\257\357\274\210\345\260\217\346\270\205\346\226\260\344\270\273\350\211\262\350\260\203\357\274\211 */\n"
"    color: white; /* \347\231\275\350\211\262\345\255\227\344\275\223\357\274\214\345\222\214\346\265\205\350\223\235\350\203\214\346\231\257\345\257\271\346\257\224\346\270\205\346\231\260 */\n"
"    font-size: 20px; /* \344\277\235\347\225\231\345\216\237\346\234\211\345\255\227\345\217\267 */\n"
"    border: none; /* \344\277\235\347\225\231\346\227\240\350\276\271\346\241\206 */\n"
"    border-bottom: 1px solid #4A90E2; /* \347\250\215\346\267\261\347\232\204\350\223\235\350\211\262\350\276\271\346\241\206\357\274\214\345\222\214\350\203\214"
                        "\346\231\257\345\221\274\345\272\224\346\233\264\345\215\217\350\260\203 */\n"
"    padding: 5px; /* \344\277\235\347\225\231\345\216\237\346\234\211\345\206\205\350\276\271\350\267\235 */\n"
"    \n"
"}\n"
"/* mainFrame\357\274\232\344\277\235\347\225\231\347\272\257\347\231\275\346\227\240\350\276\271\346\241\206\357\274\214\345\217\257\345\217\257\351\200\211\345\212\240\350\275\273\345\276\256\351\230\264\345\275\261\346\217\220\345\215\207\345\261\202\346\254\241\346\204\237 */\n"
"#mainFrame {\n"
"    border: none;\n"
"    background: white;\n"
"\n"
"}\n"
"\n"
"\n"
"#loginFrame {\n"
"   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d6d6d6 stop:1 #a8a8a8);\n"
"    border: 1px solid gray;\n"
"    padding-top: 20px;\n"
"    border-radius: 25px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setStyleSheet(QString::fromUtf8("#title_label {\n"
"    color: blue;\n"
"    font-size: 20px;\n"
"    border: none;\n"
"    border-bottom: 1px solid black;\n"
"    padding-top: 5px;\n"
"}\n"
"\n"
"#smallFrame {\n"
"    border: none;\n"
"    background: white;\n"
"}\n"
"\n"
"#loginFrame {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d6d6d6 stop:1 #a8a8a8);\n"
"    border: 1px solid gray;\n"
"    padding-top: 20px;\n"
"    border-radius: 25px;\n"
"}"));
        chatPage = new QWidget();
        chatPage->setObjectName("chatPage");
        verticalLayout_3 = new QVBoxLayout(chatPage);
        verticalLayout_3->setObjectName("verticalLayout_3");
        titleLabel2 = new QLabel(chatPage);
        titleLabel2->setObjectName("titleLabel2");

        verticalLayout_3->addWidget(titleLabel2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        roomTextEdit = new QTextEdit(chatPage);
        roomTextEdit->setObjectName("roomTextEdit");

        horizontalLayout->addWidget(roomTextEdit);

        userListWidget = new QListWidget(chatPage);
        userListWidget->setObjectName("userListWidget");
        userListWidget->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(userListWidget);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        sayLineEdit = new QLineEdit(chatPage);
        sayLineEdit->setObjectName("sayLineEdit");

        horizontalLayout_2->addWidget(sayLineEdit);

        sayButton = new QPushButton(chatPage);
        sayButton->setObjectName("sayButton");

        horizontalLayout_2->addWidget(sayButton);

        logoutButton = new QPushButton(chatPage);
        logoutButton->setObjectName("logoutButton");

        horizontalLayout_2->addWidget(logoutButton);


        verticalLayout_3->addLayout(horizontalLayout_2);

        stackedWidget->addWidget(chatPage);
        loginPage = new QWidget();
        loginPage->setObjectName("loginPage");
        gridLayout_2 = new QGridLayout(loginPage);
        gridLayout_2->setObjectName("gridLayout_2");
        titleLabel = new QLabel(loginPage);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_2->addWidget(titleLabel, 0, 0, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 3, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 4, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 3, 0, 1, 1);

        loginFrame = new QFrame(loginPage);
        loginFrame->setObjectName("loginFrame");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loginFrame->sizePolicy().hasHeightForWidth());
        loginFrame->setSizePolicy(sizePolicy);
        loginFrame->setMinimumSize(QSize(250, 0));
        loginFrame->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        loginFrame->setStyleSheet(QString::fromUtf8("/* 1. \346\240\207\351\242\230Label\357\274\210titleLabel\357\274\211\357\274\232\350\226\204\350\215\267\347\273\277\346\226\207\345\255\227 */\n"
"#titleLabel {\n"
"    font-family: \"\345\276\256\350\275\257\351\233\205\351\273\221\", \"\346\200\235\346\272\220\351\273\221\344\275\223\";\n"
"    font-size: 18px;\n"
"    color: #67C23A; /* \346\267\241\350\226\204\350\215\267\347\273\277\346\226\207\345\255\227 */\n"
"    qproperty-alignment: 'AlignCenter';\n"
"    padding: 10px 0;\n"
"}\n"
"\n"
"/* 2. \344\270\273\346\241\206\346\236\266\357\274\210mainFrame\357\274\211\357\274\232\346\236\201\346\265\205\347\273\277\350\203\214\346\231\257 */\n"
"#mainFrame {\n"
"    background-color: #F0F9F0; /* \346\267\241\347\273\277\345\272\225\357\274\214\346\216\245\350\277\221\347\231\275\350\211\262\346\233\264\346\270\205\347\210\275 */\n"
"    border-radius: 5px;\n"
"    border: 1px solid #E1F3E1; /* \346\265\205\347\273\277\350\276\271\346\241\206 */\n"
"}\n"
"\n"
"\n"
"#loginFrame {\n"
"    background: qlinear"
                        "gradient(x1:0, y1:0, x2:0, y2:1, stop:0 #F5F9FF, stop:1 #E4EDFC);\n"
"    border: 1px solid #D1E0FC; /* \346\233\277\346\215\242\346\267\261\347\201\260\350\276\271\346\241\206\344\270\272\346\267\241\350\223\235\347\201\260\357\274\214\345\222\214\346\270\220\345\217\230\345\221\274\345\272\224 */\n"
"    padding-top: 20px;\n"
"    border-radius: 25px; /* \344\277\235\347\225\231\345\216\237\346\234\211\345\244\247\345\234\206\350\247\222\357\274\214\346\233\264\346\230\276\346\237\224\345\222\214 */\n"
"    \n"
"}\n"
""));
        loginFrame->setFrameShape(QFrame::Shape::StyledPanel);
        loginFrame->setFrameShadow(QFrame::Shadow::Plain);
        verticalLayout = new QVBoxLayout(loginFrame);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName("gridLayout_8");
        label_17 = new QLabel(loginFrame);
        label_17->setObjectName("label_17");

        gridLayout_8->addWidget(label_17, 0, 0, 1, 1);

        label_16 = new QLabel(loginFrame);
        label_16->setObjectName("label_16");

        gridLayout_8->addWidget(label_16, 1, 0, 1, 1);

        serverEdit = new QLineEdit(loginFrame);
        serverEdit->setObjectName("serverEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(serverEdit->sizePolicy().hasHeightForWidth());
        serverEdit->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(serverEdit, 0, 1, 1, 1);

        usernameEdit = new QLineEdit(loginFrame);
        usernameEdit->setObjectName("usernameEdit");
        sizePolicy1.setHeightForWidth(usernameEdit->sizePolicy().hasHeightForWidth());
        usernameEdit->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(usernameEdit, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_8);

        verticalSpacer_7 = new QSpacerItem(20, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_7);

        loginButton = new QPushButton(loginFrame);
        loginButton->setObjectName("loginButton");

        verticalLayout->addWidget(loginButton);


        gridLayout_2->addWidget(loginFrame, 2, 1, 2, 1);

        stackedWidget->addWidget(loginPage);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\201\212\345\244\251\345\256\244\345\256\242\346\210\267\347\253\257", nullptr));
        titleLabel2->setText(QCoreApplication::translate("MainWindow", "\351\231\206\346\263\263\345\200\251\347\232\204\350\201\212\345\244\251\345\256\244", nullptr));
        sayButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "\351\231\206\346\263\263\345\200\251\347\232\204\350\201\212\345\244\251\345\256\244", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\346\230\265\347\247\260", nullptr));
        serverEdit->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        usernameEdit->setText(QCoreApplication::translate("MainWindow", "lyq", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225\350\201\212\345\244\251\345\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
