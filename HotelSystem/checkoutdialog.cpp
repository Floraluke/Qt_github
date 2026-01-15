#include "checkoutdialog.h"
#include "ui_checkoutdialog.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>

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
        // 注意：这里建议精确到秒，跟入住时保持一致，防止解析失败
        QString strTime = query.value(1).toString();

        // 2. 显示基本信息
        ui->lblName->setText(name);
        ui->lblTime->setText(strTime);

        // 3. 计算费用 (简单算法：不足1天按1天算)
        // 尝试用带秒的格式解析，如果数据库里没存秒，Qt会自动处理
        QDateTime inTime = QDateTime::fromString(strTime, "yyyy-MM-dd HH:mm:ss");
        if (!inTime.isValid()) {
            // 兼容旧数据的格式
            inTime = QDateTime::fromString(strTime, "yyyy-MM-dd HH:mm");
        }

        QDateTime outTime = QDateTime::currentDateTime();

        qint64 seconds = inTime.secsTo(outTime);
        double days = seconds / 86400.0; // 86400秒 = 1天

        // 逻辑：哪怕住1秒钟，也要收1天的钱（防止负数或0元）
        if (days < 1.0) days = 1.0;

        double total = days * price;

        // 4. 显示金额 (保留2位小数)
        // 格式化显示，例如 "288.00 元"
        ui->lblPrice->setText(QString::number(total, 'f', 2) + " 元");

    } else {
        QMessageBox::warning(this, "异常", "未找到该房间的入住记录！");
        reject(); // 如果查不到记录，直接关掉窗口
    }
}

// 点击“确认退房”按钮（请确保你的 UI 里按钮名字叫 btnSettle 或 btnConfirm）
void CheckOutDialog::on_btnSettle_clicked()
{
    // 1. 获取界面上已经算好的金额
    // 去掉 " 元" 后缀，转成 double
    QString priceText = ui->lblPrice->text().remove(" 元");
    double finalPrice = priceText.toDouble();

    // 2. 开启事务
    QSqlDatabase::database().transaction();

    QSqlQuery query;
    bool step1 = false;
    bool step2 = false;

    // 3. 第一步：更新订单表 (结束时间 + 总金额 + 状态归0)
    // 【关键修改】这里增加了 total_price = :price
    query.prepare("UPDATE order_info SET "
                  "is_active = 0, "
                  "check_out_date = :time, "
                  "total_price = :price "
                  "WHERE room_id = :rid AND is_active = 1");

    query.bindValue(":time", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":price", finalPrice); // 把钱存进去！
    query.bindValue(":rid", m_roomId);

    if (query.exec()) {
        step1 = true;
    } else {
        qDebug() << "Step 1 Fail:" << query.lastError().text();
    }

    // 4. 第二步：更新房间表 (状态变回 0-空闲)
    QSqlQuery queryRoom;
    queryRoom.prepare("UPDATE room_info SET status = 0 WHERE room_id = :rid");
    queryRoom.bindValue(":rid", m_roomId);

    if (queryRoom.exec()) {
        step2 = true;
    } else {
        qDebug() << "Step 2 Fail:" << queryRoom.lastError().text();
    }

    // 5. 提交或回滚
    if (step1 && step2) {
        QSqlDatabase::database().commit();
        QMessageBox::information(this, "成功", "退房结算完成！");
        accept(); // 关闭窗口并返回 Accepted
    } else {
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "失败", "数据库更新失败，请重试。");
    }
}

void CheckOutDialog::on_btnCancel_clicked()
{
    reject();
}
