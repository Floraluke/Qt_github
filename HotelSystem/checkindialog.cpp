#include "checkindialog.h"
#include "ui_checkindialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDateTime>
#include <QRegularExpressionValidator>

CheckInDialog::CheckInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckInDialog)
{
    ui->setupUi(this);
    // 【新增】只允许输入 11 位数字
    QRegularExpression rx("^1[3-9]\\d{9}$"); // 中国手机号正则
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->edtPhone->setValidator(validator);

    // 也可以给 edtName 设个最大长度
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
    // 1. 获取输入
    QString name = ui->edtName->text();
    QString phone = ui->edtPhone->text();

    if(name.isEmpty()) {
        QMessageBox::warning(this, "提示", "姓名不能为空！");
        return;
    }

    // 2. 数据库事务操作 (写订单 + 改房间状态)
    QSqlDatabase::database().transaction(); // 开启事务

    QSqlQuery query;
    // A. 插入订单记录
    query.prepare("INSERT INTO order_info (room_id, guest_name, phone_num, check_in_date) "
                  "VALUES (:rid, :name, :phone, :time)");
    query.bindValue(":rid", m_roomId);
    query.bindValue(":name", name);
    query.bindValue(":phone", phone);
    query.bindValue(":time", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm"));
    bool step1 = query.exec();

    // B. 更新房间状态为 1 (已入住)
    query.prepare("UPDATE room_info SET status = 1 WHERE room_id = :rid");
    query.bindValue(":rid", m_roomId);
    bool step2 = query.exec();

    if (step1 && step2) {
        QSqlDatabase::database().commit(); // 提交事务
        QMessageBox::information(this, "成功", "入住办理成功！");
        accept(); // 关闭窗口并返回 QDialog::Accepted
    } else {
        QSqlDatabase::database().rollback(); // 回滚
        QMessageBox::critical(this, "错误", "数据库写入失败！");
    }
}
