#include "checkoutdialog.h"
#include "ui_checkoutdialog.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlError>

CheckOutDialog::CheckOutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckOutDialog)
{
    ui->setupUi(this);
}

CheckOutDialog::~CheckOutDialog()
{
    delete ui;
}

// 核心逻辑：查订单 -> 算钱 -> 显示
void CheckOutDialog::setRoomInfo(int roomId, double price)
{
    m_roomId = roomId;
    ui->lblRoomId->setText(QString::number(roomId));

    // 1. 查询该房间当前未结束的订单 (is_active = 1)
    QSqlQuery query;
    query.prepare("SELECT guest_name, check_in_date FROM order_info "
                  "WHERE room_id = :rid AND is_active = 1");
    query.bindValue(":rid", roomId);

    if (query.exec() && query.next()) {
        QString name = query.value(0).toString();
        QString strTime = query.value(1).toString();

        // 2. 显示基本信息
        ui->lblName->setText(name);
        ui->lblTime->setText(strTime);

        // 3. 计算费用 (简单算法：不足1天按1天算)
        QDateTime inTime = QDateTime::fromString(strTime, "yyyy-MM-dd HH:mm");
        QDateTime outTime = QDateTime::currentDateTime();

        qint64 seconds = inTime.secsTo(outTime);
        double days = seconds / 86400.0; // 86400秒 = 1天
        if (days < 1.0) days = 1.0; // 最少收一天房费

        double total = days * price;


        // 4. 显示金额 (保留2位小数)
        ui->lblPrice->setText(QString::number(total, 'f', 2) + " 元");
    } else {
        QMessageBox::warning(this, "异常", "未找到该房间的入住记录！");
        reject();
    }
}

void CheckOutDialog::on_btnSettle_clicked()
{
    // 数据库事务：1. 更新订单为已完成  2. 房间变为空闲
    QSqlDatabase::database().transaction();

    QSqlQuery query;
    bool step1 = query.exec(QString("UPDATE order_info SET is_active = 0, "
                                    "check_out_date = '%1' WHERE room_id = %2 AND is_active = 1")
                                .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm"))
                                .arg(m_roomId));

    bool step2 = query.exec(QString("UPDATE room_info SET status = 0 WHERE room_id = %1").arg(m_roomId));

    if (step1 && step2) {
        QSqlDatabase::database().commit();
        QMessageBox::information(this, "成功", "退房结算完成！");
        accept();
    } else {
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "失败", "数据库更新失败：" + query.lastError().text());
    }
}

void CheckOutDialog::on_btnCancel_clicked()
{
    reject();
}
