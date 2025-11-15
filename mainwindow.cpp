#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QTextBlock>
#include <QScrollBar>
#include <QTextCharFormat>


// FindDialog 实现
FindDialog::FindDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("查找");
    setModal(false);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 查找目标
    QHBoxLayout *findLayout = new QHBoxLayout();
    findLayout->addWidget(new QLabel("查找目标："));
    findEdit = new QLineEdit();
    findLayout->addWidget(findEdit);
    mainLayout->addLayout(findLayout);

    // 查找按钮
    QPushButton *findButton = new QPushButton("查找下一个(F)");
    mainLayout->addWidget(findButton);

    // 方向选择
    QHBoxLayout *directionLayout = new QHBoxLayout();
    directionLayout->addWidget(new QLabel("方向"));
    upRadio = new QRadioButton("向上(U)");
    downRadio = new QRadioButton("向下(D)");
    downRadio->setChecked(true);
    directionLayout->addWidget(upRadio);
    directionLayout->addWidget(downRadio);
    directionLayout->addStretch();
    mainLayout->addLayout(directionLayout);

    // 选项
    caseCheckBox = new QCheckBox("区分大小写");
    mainLayout->addWidget(caseCheckBox);

    // 按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    QPushButton *cancelButton = new QPushButton("取消");
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(findButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString FindDialog::getFindText() const { return findEdit->text(); }
bool FindDialog::caseSensitive() const { return caseCheckBox->isChecked(); }
bool FindDialog::searchUp() const { return upRadio->isChecked(); }

// ReplaceDialog 实现
ReplaceDialog::ReplaceDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("替换");
    setModal(false);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 查找目标
    QHBoxLayout *findLayout = new QHBoxLayout();
    findLayout->addWidget(new QLabel("查找目标："));
    findEdit = new QLineEdit();
    findLayout->addWidget(findEdit);
    mainLayout->addLayout(findLayout);

    QPushButton *findNextButton = new QPushButton("查找下一个(F)");
    mainLayout->addWidget(findNextButton);

    // 替换为
    QHBoxLayout *replaceLayout = new QHBoxLayout();
    replaceLayout->addWidget(new QLabel("替换为："));
    replaceEdit = new QLineEdit();
    replaceLayout->addWidget(replaceEdit);
    mainLayout->addLayout(replaceLayout);

    // 选项和方向
    QHBoxLayout *optionsLayout = new QHBoxLayout();
    caseCheckBox = new QCheckBox("区分大小写");
    optionsLayout->addWidget(caseCheckBox);
    optionsLayout->addStretch();
    optionsLayout->addWidget(new QLabel("方向"));
    upRadio = new QRadioButton("向上(U)");
    downRadio = new QRadioButton("向下(D)");
    downRadio->setChecked(true);
    optionsLayout->addWidget(upRadio);
    optionsLayout->addWidget(downRadio);
    mainLayout->addLayout(optionsLayout);

    // 按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *replaceAllButton = new QPushButton("全部替换(A)");
    buttonLayout->addWidget(replaceAllButton);
    buttonLayout->addStretch();
    QPushButton *cancelButton = new QPushButton("取消");
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(findNextButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(replaceAllButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString ReplaceDialog::getFindText() const { return findEdit->text(); }
QString ReplaceDialog::getReplaceText() const { return replaceEdit->text(); }
bool ReplaceDialog::caseSensitive() const { return caseCheckBox->isChecked(); }
bool ReplaceDialog::searchUp() const { return upRadio->isChecked(); }

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 先设置UI
    setupUI();

    // 然后设置连接
    setupConnections();
    createAboutDialog();
    createFindDialog();
    createReplaceDialog();

    setWindowTitle("新建文本文件 - 编辑器");

    // 初始化编辑动作状态
    updateEditActions();

    // 最后创建初始标签页
    on_actionNew_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    // 创建标签页控件
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);

    // 替换centralWidget中的内容
    QLayout *layout = ui->centralwidget->layout();
    if (layout) {
        // 移除原有组件
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                item->widget()->setParent(nullptr);
            }
            delete item;
        }
        layout->addWidget(tabWidget);
    }

    statusBar = ui->statusbar;

    // 确保工具栏和状态栏初始可见
    ui->toolBar->setVisible(true);
    statusBar->setVisible(true);

    // 设置菜单项的初始选中状态
    ui->action_L_2->setChecked(true);  // 工具栏菜单项选中
    ui->action_7->setChecked(true);    // 状态栏菜单项选中

    // 自动保存定时器
    autoSaveTimer = new QTimer(this);
    autoSaveTimer->start(30000); // 30秒
}
void MainWindow::setupConnections()
{
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::currentTabChanged);
    connect(autoSaveTimer, &QTimer::timeout, this, &MainWindow::autoSave);
}

void MainWindow::createAboutDialog()
{
    aboutDialog = new QDialog(this);
    aboutDialog->setWindowTitle("关于");

    QVBoxLayout *layout = new QVBoxLayout(aboutDialog);

    QLabel *titleLabel = new QLabel("小牛文本编辑器");
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    QLabel *devLabel = new QLabel("开发者：陆泳倩");
    QLabel *idLabel = new QLabel("学号：2023414290121");
    QLabel *emailLabel = new QLabel("email: kiby1025@qq.com");
    QLabel *versionLabel = new QLabel("V1.0 build 202110");

    QPushButton *okButton = new QPushButton("OK");

    layout->addWidget(titleLabel);
    layout->addWidget(devLabel);
    layout->addWidget(idLabel);
    layout->addWidget(emailLabel);
    layout->addWidget(versionLabel);
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, aboutDialog, &QDialog::accept);
}


void MainWindow::createFindDialog()
{
    findDialog = new FindDialog(this);
}

void MainWindow::createReplaceDialog()
{
    replaceDialog = new ReplaceDialog(this);
}

// 文件操作
// 在新建文件时设置初始换行状态
void MainWindow::on_actionNew_triggered()
{
    CodeEditor *editor = new CodeEditor(this);
    int index = tabWidget->addTab(editor, "新建文档");
    tabWidget->setCurrentIndex(index);

    // 设置初始换行状态
    bool wordWrap = ui->action_W->isChecked();
    if (wordWrap) {
        editor->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        editor->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    } else {
        editor->setLineWrapMode(QPlainTextEdit::NoWrap);
    }

    // 连接所有必要的信号
    connect(editor, &QPlainTextEdit::textChanged, this, &MainWindow::documentWasModified);
    connect(editor, &QPlainTextEdit::cursorPositionChanged, this, &MainWindow::updateStatusBar);
    connect(editor, &QPlainTextEdit::cursorPositionChanged, this, &MainWindow::updateEditActions);
    connect(editor, &QPlainTextEdit::selectionChanged, this, &MainWindow::updateEditActions);
    connect(editor, &QPlainTextEdit::copyAvailable, this, &MainWindow::updateEditActions);

    modifiedStatus[editor] = false;
    fileNames[editor] = "";

    updateStatusBar();
    updateEditActions();
}

void MainWindow::on_action_O_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", "", "文本文件 (*.txt);;所有文件 (*)");
    if (!fileName.isEmpty()) {
        loadFile(fileName);
    }
}

// 修复保存文件函数
void MainWindow::on_action_S_triggered()
{
    CodeEditor *editor = currentEditor();
    if (!editor) return;

    if (fileNames[editor].isEmpty()) {
        on_action_A_triggered();
    } else {
        if (saveFile(fileNames[editor])) {
            // 保存成功后清除修改状态
            modifiedStatus[editor] = false;
            QString displayName = QFileInfo(fileNames[editor]).fileName();
            int index = tabWidget->currentIndex();
            tabWidget->setTabText(index, displayName);
            setWindowTitle(QString("%1 - 编辑器").arg(displayName));
        }
    }
}
// 修复另存为函数
void MainWindow::on_action_A_triggered()
{
    CodeEditor *editor = currentEditor();
    if (!editor) return;

    QString fileName = QFileDialog::getSaveFileName(this, "另存为", "", "文本文件 (*.txt);;所有文件 (*)");
    if (!fileName.isEmpty()) {
        if (saveFile(fileName)) {
            // 保存成功后更新文件名和状态
            fileNames[editor] = fileName;
            modifiedStatus[editor] = false;
            setCurrentFileName(fileName);
        }
    }
}
void MainWindow::on_action_X_triggered()
{
    close();
}

// 编辑操作
// 修复编辑操作，确保操作后更新状态
void MainWindow::on_action_Z_triggered()
{
    CodeEditor *editor = currentEditor();
    if (editor) {
        editor->undo();
        // 操作后立即更新状态
        QTimer::singleShot(0, this, &MainWindow::updateEditActions);
    }
}

void MainWindow::on_action_Shift_Z_triggered()
{
    CodeEditor *editor = currentEditor();
    if (editor) {
        editor->redo();
        // 操作后立即更新状态
        QTimer::singleShot(0, this, &MainWindow::updateEditActions);
    }
}
void MainWindow::on_action_X_2_triggered()
{
    CodeEditor *editor = currentEditor();
    if (editor) {
        editor->cut();
        // 操作后立即更新状态
        updateEditActions();
    }
}
void MainWindow::on_action_C_triggered()
{
    CodeEditor *editor = currentEditor();
    if (editor) {
        editor->copy();
        // 操作后立即更新状态
        updateEditActions();
    }
}
void MainWindow::on_action_V_triggered()
{
    CodeEditor *editor = currentEditor();
    if (editor) {
        editor->paste();
        // 操作后立即更新状态
        updateEditActions();
    }
}
void MainWindow::on_action_F_triggered()
{
    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

void MainWindow::on_action_R_triggered()
{
    replaceDialog->show();
    replaceDialog->raise();
    replaceDialog->activateWindow();
}

void MainWindow::on_action_A_2_triggered()
{
    CodeEditor *editor = currentEditor();
    if (editor) editor->selectAll();
}

// 格式操作
// 修复自动换行功能
// 在 mainwindow.cpp 中修复自动换行功能
void MainWindow::on_action_W_triggered()
{
    CodeEditor *editor = currentEditor();
    if (editor) {
        bool wordWrap = ui->action_W->isChecked();

        if (wordWrap) {
            // 启用自动换行 - 使用正确的方法
            editor->setLineWrapMode(QPlainTextEdit::WidgetWidth);
            editor->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        } else {
            // 禁用自动换行
            editor->setLineWrapMode(QPlainTextEdit::NoWrap);
        }

        // 确保菜单项状态正确
        ui->action_W->setChecked(wordWrap);
    }
}
void MainWindow::on_action_L_triggered()
{
    // 行号功能已在CodeEditor中实现
}

void MainWindow::on_action_F_2_triggered()
{
    CodeEditor *editor = currentEditor();
    if (editor) {
        bool ok;
        QFont font = QFontDialog::getFont(&ok, editor->font(), this);
        if (ok) {
            editor->setFont(font);
        }
    }
}

void MainWindow::on_action_3_triggered()
{
    CodeEditor *editor = currentEditor();
    if (editor) {
        QColor currentColor = editor->palette().color(QPalette::Text);
        QColor color = QColorDialog::getColor(currentColor, this, "选择字体颜色");
        if (color.isValid()) {
            QPalette palette = editor->palette();
            palette.setColor(QPalette::Text, color);
            editor->setPalette(palette);
        }
    }
}

void MainWindow::on_action_4_triggered()
{
    CodeEditor *editor = currentEditor();
    if (editor) {
        QColor color = QColorDialog::getColor(Qt::white, this, "选择字体背景色");
        if (color.isValid()) {
            QTextCharFormat format;
            format.setBackground(color);
            QTextCursor cursor = editor->textCursor();
            cursor.mergeCharFormat(format);
        }
    }
}

void MainWindow::on_action_5_triggered()
{
    CodeEditor *editor = currentEditor();
    if (editor) {
        QColor currentColor = editor->palette().color(QPalette::Base);
        QColor color = QColorDialog::getColor(currentColor, this, "选择编辑器背景色");
        if (color.isValid()) {
            QPalette palette = editor->palette();
            palette.setColor(QPalette::Base, color);
            editor->setPalette(palette);
        }
    }
}

// 查看操作
void MainWindow::on_action_L_2_triggered()
{
    // 直接切换工具栏的可见性
    bool visible = ui->toolBar->isVisible();
    ui->toolBar->setVisible(!visible);

    // 更新菜单项的选中状态
    ui->action_L_2->setChecked(!visible);
}
void MainWindow::on_action_7_triggered()
{
    // 直接切换状态栏的可见性
    bool visible = statusBar->isVisible();
    statusBar->setVisible(!visible);

    // 更新菜单项的选中状态
    ui->action_7->setChecked(!visible);
}
// 帮助
void MainWindow::on_action_A_3_triggered()
{
    aboutDialog->exec();
}

// 其他功能
CodeEditor* MainWindow::currentEditor() const
{
    return qobject_cast<CodeEditor*>(tabWidget->currentWidget());
}

QString MainWindow::currentFileName() const
{
    CodeEditor *editor = currentEditor();
    return editor ? fileNames[editor] : "";
}

void MainWindow::setCurrentFileName(const QString &fileName)
{
    CodeEditor *editor = currentEditor();
    if (editor) {
        fileNames[editor] = fileName;
        QString displayName = fileName.isEmpty() ? "新建文档" : QFileInfo(fileName).fileName();
        int index = tabWidget->currentIndex();
        tabWidget->setTabText(index, displayName);
        setWindowTitle(QString("%1 - 编辑器").arg(displayName));
    }
}

// 修复关闭标签页函数
void MainWindow::closeTab(int index)
{
    CodeEditor *editor = qobject_cast<CodeEditor*>(tabWidget->widget(index));
    if (editor) {
        if (modifiedStatus[editor]) {
            QMessageBox::StandardButton result = QMessageBox::question(this, "保存文件",
                                                                       "文档已被修改，是否保存？",
                                                                       QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

            if (result == QMessageBox::Save) {
                // 切换到要关闭的标签页再保存
                tabWidget->setCurrentIndex(index);
                on_action_S_triggered();
            } else if (result == QMessageBox::Cancel) {
                return;
            }
        }

        tabWidget->removeTab(index);
        modifiedStatus.remove(editor);
        fileNames.remove(editor);
        delete editor;

        // 关闭标签页后更新状态
        updateEditActions();
    }
}

// 修复标签页切换函数
void MainWindow::currentTabChanged(int index)
{
    if (index >= 0) {
        updateStatusBar();
        updateEditActions();

        CodeEditor *editor = currentEditor();
        if (editor) {
            QString fileName = fileNames[editor];
            QString displayName = fileName.isEmpty() ? "新建文档" : QFileInfo(fileName).fileName();
            if (modifiedStatus[editor]) {
                displayName += " *";
            }
            setWindowTitle(QString("%1 - 编辑器").arg(displayName));
        }
    } else {
        // 没有标签页时也更新状态
        updateEditActions();
        setWindowTitle("编辑器");
    }
}

// 修复文档修改状态函数
void MainWindow::documentWasModified()
{
    CodeEditor *editor = currentEditor();
    if (editor) {
        modifiedStatus[editor] = true;

        QString fileName = fileNames[editor];
        QString displayName = fileName.isEmpty() ? "新建文档" : QFileInfo(fileName).fileName();
        displayName += " *";
        int index = tabWidget->currentIndex();
        tabWidget->setTabText(index, displayName);
        setWindowTitle(QString("%1 - 编辑器").arg(displayName));

        // 文档修改后更新编辑动作状态
        updateEditActions();
    }
}

void MainWindow::updateStatusBar()
{
    CodeEditor *editor = currentEditor();
    if (editor) {
        QTextCursor cursor = editor->textCursor();
        int line = cursor.blockNumber() + 1;
        int column = cursor.positionInBlock() + 1;
        int length = editor->toPlainText().length();
        int lines = editor->document()->blockCount();

        QString status = QString("length: %1  lines: %2  Ln: %3  Col: %4  陆泳倩")
                             .arg(length).arg(lines).arg(line).arg(column);
        statusBar->showMessage(status);
    }
}

void MainWindow::updateEditActions()
{
    CodeEditor *editor = currentEditor();
    bool hasEditor = (editor != nullptr);

    if (hasEditor) {
        QTextCursor cursor = editor->textCursor();
        bool hasSelection = cursor.hasSelection();
        bool canUndo = editor->document()->isUndoAvailable();
        bool canRedo = editor->document()->isRedoAvailable();

        // 调试信息（可选，可以删除）
        // qDebug() << "Has selection:" << hasSelection << "Can undo:" << canUndo << "Can redo:" << canRedo;

        // 更新撤销/恢复状态
        ui->action_Z->setEnabled(canUndo);
        ui->action_Shift_Z->setEnabled(canRedo);

        // 更新剪切/复制状态 - 只要有选中文本就启用
        ui->action_X_2->setEnabled(hasSelection);
        ui->action_C->setEnabled(hasSelection);

        // 更新粘贴状态 - 只要有编辑器就启用（假设剪贴板可能有内容）
        ui->action_V->setEnabled(true);

        // 更新全选状态 - 只要有文本就启用
        ui->action_A_2->setEnabled(!editor->toPlainText().isEmpty());
    } else {
        // 没有编辑器时禁用所有编辑动作
        ui->action_Z->setEnabled(false);
        ui->action_Shift_Z->setEnabled(false);
        ui->action_X_2->setEnabled(false);
        ui->action_C->setEnabled(false);
        ui->action_V->setEnabled(false);
        ui->action_A_2->setEnabled(false);
    }
}
void MainWindow::autoSave()
{
    for (auto it = modifiedStatus.begin(); it != modifiedStatus.end(); ++it) {
        if (it.value() && !fileNames[it.key()].isEmpty()) {
            saveFile(fileNames[it.key()]);
        }
    }
}

bool MainWindow::maybeSave()
{
    CodeEditor *editor = currentEditor();
    if (editor && modifiedStatus[editor]) {
        QMessageBox::StandardButton ret = QMessageBox::warning(this, "保存文件",
                                                               "文档已被修改，是否保存？",
                                                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (ret == QMessageBox::Save) {
            on_action_S_triggered();
            return true;
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

// 在打开文件时也设置换行状态
// 在打开文件时也设置换行状态
void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "打开文件", "无法打开文件: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    in.setAutoDetectUnicode(true);

    CodeEditor *editor = new CodeEditor(this);
    editor->setPlainText(in.readAll());

    // 设置换行状态
    bool wordWrap = ui->action_W->isChecked();
    if (wordWrap) {
        editor->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        editor->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    } else {
        editor->setLineWrapMode(QPlainTextEdit::NoWrap);
    }

    int index = tabWidget->addTab(editor, QFileInfo(fileName).fileName());
    tabWidget->setCurrentIndex(index);

    // 连接所有必要的信号
    connect(editor, &QPlainTextEdit::textChanged, this, &MainWindow::documentWasModified);
    connect(editor, &QPlainTextEdit::cursorPositionChanged, this, &MainWindow::updateStatusBar);
    connect(editor, &QPlainTextEdit::cursorPositionChanged, this, &MainWindow::updateEditActions);
    connect(editor, &QPlainTextEdit::selectionChanged, this, &MainWindow::updateEditActions);
    connect(editor, &QPlainTextEdit::copyAvailable, this, &MainWindow::updateEditActions);

    modifiedStatus[editor] = false;
    fileNames[editor] = fileName;

    setCurrentFileName(fileName);
    updateStatusBar();
    updateEditActions();
}
bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "保存文件", "无法保存文件: " + file.errorString());
        return false;
    }

    CodeEditor *editor = currentEditor();
    if (!editor) return false;

    QTextStream out(&file);
    out.setAutoDetectUnicode(true);
    out << editor->toPlainText();

    modifiedStatus[editor] = false;
    setCurrentFileName(fileName);

    return true;
}
