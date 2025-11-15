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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <codeeditor.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *action_O;
    QAction *action_S;
    QAction *action_A;
    QAction *action_X;
    QAction *action_Z;
    QAction *action_Shift_Z;
    QAction *action_X_2;
    QAction *action_C;
    QAction *action_V;
    QAction *action_F;
    QAction *action_R;
    QAction *action_A_2;
    QAction *action_W;
    QAction *action_L;
    QAction *action_F_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_L_2;
    QAction *action_7;
    QAction *action_A_3;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    CodeEditor *TextEdit;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_O;
    QMenu *menu_V;
    QMenu *menu_H;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1083, 620);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/invoice-text-plus-outline.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionNew->setIcon(icon);
        actionNew->setMenuRole(QAction::MenuRole::NoRole);
        action_O = new QAction(MainWindow);
        action_O->setObjectName("action_O");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/folder-open-outline.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_O->setIcon(icon1);
        action_O->setMenuRole(QAction::MenuRole::NoRole);
        action_S = new QAction(MainWindow);
        action_S->setObjectName("action_S");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/content-save-check-outline.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_S->setIcon(icon2);
        action_S->setMenuRole(QAction::MenuRole::NoRole);
        action_A = new QAction(MainWindow);
        action_A->setObjectName("action_A");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/content-save-move.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_A->setIcon(icon3);
        action_A->setMenuRole(QAction::MenuRole::NoRole);
        action_X = new QAction(MainWindow);
        action_X->setObjectName("action_X");
        action_X->setMenuRole(QAction::MenuRole::NoRole);
        action_Z = new QAction(MainWindow);
        action_Z->setObjectName("action_Z");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/reply-outline.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_Z->setIcon(icon4);
        action_Z->setMenuRole(QAction::MenuRole::NoRole);
        action_Shift_Z = new QAction(MainWindow);
        action_Shift_Z->setObjectName("action_Shift_Z");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/image/share-outline.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_Shift_Z->setIcon(icon5);
        action_Shift_Z->setMenuRole(QAction::MenuRole::NoRole);
        action_X_2 = new QAction(MainWindow);
        action_X_2->setObjectName("action_X_2");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/image/content-cut.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_X_2->setIcon(icon6);
        action_X_2->setMenuRole(QAction::MenuRole::NoRole);
        action_C = new QAction(MainWindow);
        action_C->setObjectName("action_C");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/image/content-copy.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_C->setIcon(icon7);
        action_C->setMenuRole(QAction::MenuRole::NoRole);
        action_V = new QAction(MainWindow);
        action_V->setObjectName("action_V");
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/image/content-paste.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_V->setIcon(icon8);
        action_V->setMenuRole(QAction::MenuRole::NoRole);
        action_F = new QAction(MainWindow);
        action_F->setObjectName("action_F");
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/image/file-find-outline.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_F->setIcon(icon9);
        action_F->setMenuRole(QAction::MenuRole::NoRole);
        action_R = new QAction(MainWindow);
        action_R->setObjectName("action_R");
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/image/replace.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_R->setIcon(icon10);
        action_R->setMenuRole(QAction::MenuRole::NoRole);
        action_A_2 = new QAction(MainWindow);
        action_A_2->setObjectName("action_A_2");
        action_A_2->setMenuRole(QAction::MenuRole::NoRole);
        action_W = new QAction(MainWindow);
        action_W->setObjectName("action_W");
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/image/keyboard-return.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_W->setIcon(icon11);
        action_W->setMenuRole(QAction::MenuRole::NoRole);
        action_L = new QAction(MainWindow);
        action_L->setObjectName("action_L");
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/image/format-list-numbered.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_L->setIcon(icon12);
        action_L->setMenuRole(QAction::MenuRole::NoRole);
        action_F_2 = new QAction(MainWindow);
        action_F_2->setObjectName("action_F_2");
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/image/format-size.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_F_2->setIcon(icon13);
        action_F_2->setMenuRole(QAction::MenuRole::NoRole);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName("action_3");
        action_3->setMenuRole(QAction::MenuRole::NoRole);
        action_4 = new QAction(MainWindow);
        action_4->setObjectName("action_4");
        action_4->setMenuRole(QAction::MenuRole::NoRole);
        action_5 = new QAction(MainWindow);
        action_5->setObjectName("action_5");
        action_5->setMenuRole(QAction::MenuRole::NoRole);
        action_L_2 = new QAction(MainWindow);
        action_L_2->setObjectName("action_L_2");
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/image/tools.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_L_2->setIcon(icon14);
        action_L_2->setMenuRole(QAction::MenuRole::NoRole);
        action_7 = new QAction(MainWindow);
        action_7->setObjectName("action_7");
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/image/list-status.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_7->setIcon(icon15);
        action_7->setMenuRole(QAction::MenuRole::NoRole);
        action_A_3 = new QAction(MainWindow);
        action_A_3->setObjectName("action_A_3");
        action_A_3->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        TextEdit = new CodeEditor(centralwidget);
        TextEdit->setObjectName("TextEdit");

        horizontalLayout->addWidget(TextEdit);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1083, 25));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_O = new QMenu(menubar);
        menu_O->setObjectName("menu_O");
        menu_V = new QMenu(menubar);
        menu_V->setObjectName("menu_V");
        menu_H = new QMenu(menubar);
        menu_H->setObjectName("menu_H");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_O->menuAction());
        menubar->addAction(menu_V->menuAction());
        menubar->addAction(menu_H->menuAction());
        menu->addAction(actionNew);
        menu->addAction(action_O);
        menu->addAction(action_S);
        menu->addAction(action_A);
        menu->addSeparator();
        menu->addAction(action_X);
        menu_2->addAction(action_Z);
        menu_2->addAction(action_Shift_Z);
        menu_2->addAction(action_X_2);
        menu_2->addAction(action_C);
        menu_2->addAction(action_V);
        menu_2->addAction(action_F);
        menu_2->addAction(action_R);
        menu_2->addSeparator();
        menu_2->addAction(action_A_2);
        menu_O->addAction(action_W);
        menu_O->addAction(action_L);
        menu_O->addAction(action_F_2);
        menu_O->addAction(action_3);
        menu_O->addSeparator();
        menu_O->addAction(action_4);
        menu_O->addAction(action_5);
        menu_V->addAction(action_L_2);
        menu_V->addAction(action_7);
        menu_H->addAction(action_A_3);
        toolBar->addAction(action_O);
        toolBar->addAction(actionNew);
        toolBar->addAction(action_S);
        toolBar->addAction(action_A);
        toolBar->addSeparator();
        toolBar->addAction(action_Z);
        toolBar->addAction(action_Shift_Z);
        toolBar->addAction(action_X_2);
        toolBar->addAction(action_C);
        toolBar->addAction(action_V);
        toolBar->addAction(action_F);
        toolBar->addAction(action_R);
        toolBar->addSeparator();
        toolBar->addAction(action_W);
        toolBar->addAction(action_F_2);
        toolBar->addSeparator();
        toolBar->addAction(action_L);
        toolBar->addAction(action_L_2);
        toolBar->addAction(action_7);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272(&N\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        action_O->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200(&O\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        action_O->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_O->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        action_S->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230(&S\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        action_S->setToolTip(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_S->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        action_A->setText(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272(A\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        action_A->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", nullptr));
#endif // QT_CONFIG(tooltip)
        action_X->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272(E)", nullptr));
#if QT_CONFIG(tooltip)
        action_X->setToolTip(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_X->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Z->setText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200(U)", nullptr));
#if QT_CONFIG(tooltip)
        action_Z->setToolTip(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_Z->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Shift_Z->setText(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215(\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        action_Shift_Z->setToolTip(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_Shift_Z->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        action_X_2->setText(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207(T\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        action_X_2->setToolTip(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_X_2->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        action_C->setText(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266(C\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        action_C->setToolTip(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_C->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        action_V->setText(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264(P)", nullptr));
#if QT_CONFIG(tooltip)
        action_V->setToolTip(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_V->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        action_F->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276(F\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        action_F->setToolTip(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_F->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        action_R->setText(QCoreApplication::translate("MainWindow", "\346\233\277\346\215\242(R)", nullptr));
#if QT_CONFIG(tooltip)
        action_R->setToolTip(QCoreApplication::translate("MainWindow", "\346\233\277\346\215\242", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_R->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        action_A_2->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211(&A\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        action_A_2->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_A_2->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        action_W->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\346\215\242\350\241\214(W\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        action_W->setToolTip(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\346\215\242\350\241\214", nullptr));
#endif // QT_CONFIG(tooltip)
        action_L->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\350\241\214\345\217\267(L)", nullptr));
#if QT_CONFIG(shortcut)
        action_L->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        action_F_2->setText(QCoreApplication::translate("MainWindow", "\345\255\227\344\275\223(F\357\274\211", nullptr));
        action_3->setText(QCoreApplication::translate("MainWindow", "\345\255\227\344\275\223\351\242\234\350\211\262", nullptr));
#if QT_CONFIG(tooltip)
        action_3->setToolTip(QCoreApplication::translate("MainWindow", "\345\255\227\344\275\223\351\242\234\350\211\262", nullptr));
#endif // QT_CONFIG(tooltip)
        action_4->setText(QCoreApplication::translate("MainWindow", "\345\255\227\344\275\223\350\203\214\346\231\257\350\211\262", nullptr));
#if QT_CONFIG(tooltip)
        action_4->setToolTip(QCoreApplication::translate("MainWindow", "\345\255\227\344\275\223\350\203\214\346\231\257\350\211\262", nullptr));
#endif // QT_CONFIG(tooltip)
        action_5->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\345\231\250\350\203\214\346\231\257\350\211\262", nullptr));
#if QT_CONFIG(tooltip)
        action_5->setToolTip(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\345\231\250\350\203\214\346\231\257\350\211\262", nullptr));
#endif // QT_CONFIG(tooltip)
        action_L_2->setText(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267\346\240\217(L\357\274\211", nullptr));
        action_7->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\346\240\217", nullptr));
#if QT_CONFIG(tooltip)
        action_7->setToolTip(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\346\240\217", nullptr));
#endif // QT_CONFIG(tooltip)
        action_A_3->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216(A\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        action_A_3->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216(A\357\274\211", nullptr));
#endif // QT_CONFIG(tooltip)
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266(&F\357\274\211", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221(&E)", nullptr));
        menu_O->setTitle(QCoreApplication::translate("MainWindow", "\346\240\274\345\274\217(&O\357\274\211", nullptr));
        menu_V->setTitle(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213(&V\357\274\211", nullptr));
        menu_H->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
