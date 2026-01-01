#ifndef CHECKOUTDIALOG_H
#define CHECKOUTDIALOG_H

#include <QDialog>

namespace Ui {
class CheckOutDialog;
}

class CheckOutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckOutDialog(QWidget *parent = nullptr);
    ~CheckOutDialog();

    // 【核心】传入房号和单价，自动计算账单
    void setRoomInfo(int roomId, double price);

private slots:
    void on_btnSettle_clicked(); // 确认退房
    void on_btnCancel_clicked(); // 取消

private:
    Ui::CheckOutDialog *ui;
    int m_roomId;
};

#endif // CHECKOUTDIALOG_H
