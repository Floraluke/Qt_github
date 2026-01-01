#ifndef CHECKINDIALOG_H
#define CHECKINDIALOG_H

#include <QDialog>

namespace Ui {
class CheckInDialog;
}

class CheckInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckInDialog(QWidget *parent = nullptr);
    ~CheckInDialog();

    // 【新增】设置房号的公开函数
    void setRoomId(int id);


private slots:
    // 【新增】按钮点击槽函数
    void on_btnConfirm_clicked();
    void on_btnCancel_clicked();


private:
    Ui::CheckInDialog *ui;
    int m_roomId; // 【新增】存房号
};

#endif // CHECKINDIALOG_H
