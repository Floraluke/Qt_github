#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTabWidget>
#include <QStatusBar>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QCloseEvent>
#include <QTextStream>
#include <QFileInfo>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextBlock>
#include <QTimer>
#include <QPainter>
#include <QTextOption>
#include <QMap>
#include <QTextEdit>
#include "codeeditor.h"  // 包含独立的CodeEditor类

namespace Ui {
class MainWindow;
}

// 查找对话框
class FindDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FindDialog(QWidget *parent = nullptr);
    QString getFindText() const;
    bool caseSensitive() const;
    bool searchUp() const;

private:
    QLineEdit *findEdit;
    QCheckBox *caseCheckBox;
    QRadioButton *upRadio;
    QRadioButton *downRadio;
};

// 替换对话框
class ReplaceDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ReplaceDialog(QWidget *parent = nullptr);
    QString getFindText() const;
    QString getReplaceText() const;
    bool caseSensitive() const;
    bool searchUp() const;

private:
    QLineEdit *findEdit;
    QLineEdit *replaceEdit;
    QCheckBox *caseCheckBox;
    QRadioButton *upRadio;
    QRadioButton *downRadio;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 文件操作
    void on_actionNew_triggered();
    void on_action_O_triggered();
    void on_action_S_triggered();
    void on_action_A_triggered();
    void on_action_X_triggered();

    // 编辑操作
    void on_action_Z_triggered();
    void on_action_Shift_Z_triggered();
    void on_action_X_2_triggered();
    void on_action_C_triggered();
    void on_action_V_triggered();
    void on_action_F_triggered();
    void on_action_R_triggered();
    void on_action_A_2_triggered();

    // 格式操作
    void on_action_W_triggered();
    void on_action_L_triggered();
    void on_action_F_2_triggered();
    void on_action_3_triggered();
    void on_action_4_triggered();
    void on_action_5_triggered();

    // 查看操作
    void on_action_L_2_triggered();
    void on_action_7_triggered();

    // 帮助
    void on_action_A_3_triggered();

    // 标签页管理
    void closeTab(int index);
    void currentTabChanged(int index);

    // 文档修改状态
    void documentWasModified();

    // 更新状态栏
    void updateStatusBar();

    // 更新编辑动作状态
    void updateEditActions();

    // 自动保存
    void autoSave();

private:
    void setupUI();
    void setupConnections();
    void createAboutDialog();
    void createFindDialog();
    void createReplaceDialog();
    void setupToolBarVisibility();
    void setupStatusBarVisibility();

    CodeEditor* currentEditor() const;
    QString currentFileName() const;
    void setCurrentFileName(const QString &fileName);
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);

    Ui::MainWindow *ui;

    QTabWidget *tabWidget;
    QStatusBar *statusBar;

    // 对话框
    FindDialog *findDialog;

    ReplaceDialog *replaceDialog;
    QDialog *aboutDialog;

    // 自动保存定时器
    QTimer *autoSaveTimer;

    // 文件修改状态
    QMap<CodeEditor*, bool> modifiedStatus;
    QMap<CodeEditor*, QString> fileNames;
};

#endif // MAINWINDOW_H
