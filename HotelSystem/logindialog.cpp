#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // 设置标题
    this->setWindowTitle("系统登录");

    // 固定窗口大小，不让拖拽
    this->setFixedSize(this->width(), this->height());
}

LoginDialog::~LoginDialog()
{
    delete ui;
}



void LoginDialog::on_btnLogin_clicked()
{
    QString user = ui->edtUser->text().trimmed();
    QString pwd = ui->edtPwd->text();


    // 【设置账号密码】
    if (user == "admin" && pwd == "123456") {
        accept(); // 这是一个 QDialog 的标准方法，表示“成功/同意”，窗口会关闭并返回 QDialog::Accepted
    } else {
        QMessageBox::warning(this, "错误", "账号或密码错误！");
        ui->edtPwd->clear();
        ui->edtPwd->setFocus();
    }
}

void LoginDialog::on_btnExit_clicked()
{
    reject(); // 表示“拒绝/取消”，窗口会关闭并返回 QDialog::Rejected
}
