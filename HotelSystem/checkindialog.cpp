#include "checkindialog.h"
#include "ui_checkindialog.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QDateTime>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QSqlError>     // 用于获取错误信息
#include <QSqlDatabase>  // 用于事务处理
#include <QDebug>        // 用于控制台打印
// ========================================================

CheckInDialog::CheckInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckInDialog)
{
    ui->setupUi(this);

    // 【保留你原本的逻辑】只允许输入 11 位数字
    QRegularExpression rx("^1[3-9]\\d{9}$");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->edtPhone->setValidator(validator);

    // 【保留你原本的逻辑】设置最大长度
    ui->edtName->setMaxLength(10);
}

CheckInDialog::~CheckInDialog()
{
    delete ui;
}


void CheckInDialog::setRoomId(int id)
{
    m_roomId = id;
    ui->lblRoomId->setText(QString::number(id)); // 界面上显示房号
}

void CheckInDialog::on_btnCancel_clicked()
{
    reject(); // 关闭窗口
}


void CheckInDialog::on_btnConfirm_clicked()
{
    // ================= 1. 数据校验 =================
    QString name = ui->edtName->text().trimmed();
    QString phone = ui->edtPhone->text().trimmed();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "住客姓名不能为空！");
        ui->edtName->setFocus();
        return;
    }

    QRegularExpression rx("^1[3-9]\\d{9}$");
    if (!rx.match(phone).hasMatch()) {
        QMessageBox::warning(this, "输入错误", "请输入有效的 11 位手机号码！");
        ui->edtPhone->setFocus();
        return;
    }

    // ================= 2. 数据库事务操作 =================

    // 获取数据库连接
    QSqlDatabase db = QSqlDatabase::database();

    // 开启事务 (Transaction)
    if (!db.transaction()) {
        QMessageBox::critical(this, "错误", "无法开启数据库事务！");
        return;
    }

    QSqlQuery query;
    bool success = true; // 标记整个流程是否成功

    // --- 步骤 A: 插入订单记录 ---
    query.prepare("INSERT INTO order_info (room_id, guest_name, phone_num, check_in_date, is_active) "
                  "VALUES (:rid, :name, :phone, :time, 1)");
    query.bindValue(":rid", m_roomId);
    query.bindValue(":name", name);
    query.bindValue(":phone", phone);
    query.bindValue(":time", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

    if (!query.exec()) {
        // 【关键修改】加上 .text() 解决编译报错
        qDebug() << "插入订单失败: " << query.lastError().text();
        success = false;
    }

    // --- 步骤 B: 更新房间状态 (只有A成功了才做B) ---
    if (success) {
        // 将 status 设为 1 (已入住)
        query.prepare("UPDATE room_info SET status = 1 WHERE room_id = :rid");
        query.bindValue(":rid", m_roomId);

        if (!query.exec()) {
            // 【关键修改】加上 .text() 解决编译报错
            qDebug() << "更新房态失败: " << query.lastError().text();
            success = false;
        }
    }

    // ================= 3. 提交或回滚 =================
    if (success) {
        db.commit(); // 全部成功，提交事务
        QMessageBox::information(this, "成功", "入住办理成功！");
        accept(); // 关闭窗口
    } else {
        db.rollback(); // 有任何一步失败，回滚操作
        QMessageBox::critical(this, "错误", "数据库操作失败，请查看控制台日志。");
    }
}
