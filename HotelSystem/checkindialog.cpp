#include "checkindialog.h"
#include "ui_checkindialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDateTime>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

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
    // 1. 获取用户输入
    QString name = ui->edtName->text().trimmed(); // 去除首尾空格
    QString phone = ui->edtPhone->text().trimmed();

    // 2. 校验姓名：不能为空
    if (name.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "住客姓名不能为空！");
        ui->edtName->setFocus(); // 光标跳回去
        return; // 【关键】直接打断，不让代码往下走
    }

    // 3. 校验手机号：必须符合格式 (1开头，11位数字)
    // 正则表达式解释：^1 (1开头) + [3-9] (第二位是3-9) + \\d{9} (后面跟9个数字)
    QRegularExpression rx("^1[3-9]\\d{9}$");
    QRegularExpressionMatch match = rx.match(phone);

    if (!match.hasMatch()) {
        QMessageBox::warning(this, "输入错误", "请输入有效的 11 位手机号码！\n(例如：13800138000)");
        ui->edtPhone->clear();
        ui->edtPhone->setFocus();
        return; // 【关键】打断！
    }

    // 4. 只有上面都通过了，才允许通过
    accept(); // 这句话一旦执行，主界面就会以为“成功了”并去读数据
}
