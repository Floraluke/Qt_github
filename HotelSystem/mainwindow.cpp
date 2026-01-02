#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include "checkindialog.h"
#include "checkoutdialog.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 先初始化数据模型！(让 model 不再是空指针)
    // 这样即便后面触发了信号，槽函数里的 model->setFilter 也是安全的
    initModel();

    // 2. 然后再初始化 ComboBox
    ui->comboType->addItem("全部房型");
    ui->comboType->addItem("标准单人间");
    ui->comboType->addItem("豪华双人间");
    ui->comboType->addItem("总统套房"); // 这行会触发信号，但现在 model 已经存在了，所以不会崩

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initModel()
{
    // ================== Tab 1: 房态管理 ==================
    // 创建视图 (把0/1转成文字)
    QSqlQuery query;
    query.exec("CREATE VIEW IF NOT EXISTS room_view AS "
               "SELECT room_id, room_type, price, "
               "CASE status WHEN 0 THEN '空闲' ELSE '已入住' END as status_desc "
               "FROM room_info");

    model = new QSqlTableModel(this);
    model->setTable("room_view");
    model->setHeaderData(0, Qt::Horizontal, "房号");
    model->setHeaderData(1, Qt::Horizontal, "房型");
    model->setHeaderData(2, Qt::Horizontal, "单价");
    model->setHeaderData(3, Qt::Horizontal, "状态");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自动铺满宽度

    // ================== Tab 2: 历史订单 ==================
    historyModel = new QSqlTableModel(this);
    historyModel->setTable("order_info");

    // 设置表头中文
    historyModel->setHeaderData(0, Qt::Horizontal, "订单号");
    historyModel->setHeaderData(1, Qt::Horizontal, "房号");
    historyModel->setHeaderData(2, Qt::Horizontal, "住客姓名");
    historyModel->setHeaderData(3, Qt::Horizontal, "电话");
    historyModel->setHeaderData(4, Qt::Horizontal, "入住时间");
    historyModel->setHeaderData(5, Qt::Horizontal, "退房时间");
    historyModel->setHeaderData(6, Qt::Horizontal, "状态(1在住/0已退)");

    historyModel->select(); // 查询所有

    ui->viewHistory->setModel(historyModel);
    ui->viewHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->viewHistory->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->viewHistory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 隐藏不想显示的列（比如订单号）
    ui->viewHistory->hideColumn(0);
}

// --- 功能 1: 房型筛选 (Tab 1) ---
void MainWindow::on_comboType_currentTextChanged(const QString &arg1)
{
    if (arg1 == "全部房型") {
        model->setFilter(""); // 清空筛选条件
    } else {
        // 这里的语法是 SQL 的 WHERE 子句
        model->setFilter(QString("room_type = '%1'").arg(arg1));
    }


     model->select(); // 刷新
}

// --- 功能 2: 入住 (Tab 1) ---
void MainWindow::on_btnCheckIn_clicked()
{
    int curRow = ui->tableView->currentIndex().row();
    if (curRow < 0) {
        QMessageBox::warning(this, "提示", "请先选择一个房间！");
        return;
    }
    QSqlRecord record = model->record(curRow);
    int roomId = record.value("room_id").toInt();
    QString status = record.value("status_desc").toString();

    if (status != "空闲") {
        QMessageBox::warning(this, "警告", "该房间已有人入住！");
        return;
    }

    CheckInDialog dlg(this);
    dlg.setRoomId(roomId);
    if (dlg.exec() == QDialog::Accepted) {
        model->select();      // 刷新房态表
        historyModel->select(); // 顺便刷新历史表
    }
}

// --- 功能 3: 退房 (Tab 1) ---
void MainWindow::on_btnCheckOut_clicked()
{
    int curRow = ui->tableView->currentIndex().row();
    if (curRow < 0) {
        QMessageBox::warning(this, "提示", "请先选择要退房的房间！");
        return;
    }
    QSqlRecord record = model->record(curRow);
    int roomId = record.value("room_id").toInt();
    double price = record.value("price").toDouble();
    QString status = record.value("status_desc").toString();

    if (status != "已入住") {
        QMessageBox::warning(this, "提示", "该房间是空闲的！");
        return;
    }

    CheckOutDialog dlg(this);
    dlg.setRoomInfo(roomId, price);
    if (dlg.exec() == QDialog::Accepted) {
        model->select();
        historyModel->select(); // 顺便刷新历史表
    }
}

// --- 功能 4: 姓名搜索 (Tab 2) ---
void MainWindow::on_btnSearch_clicked()
{
    QString name = ui->edtSearch->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::information(this, "提示", "请输入姓名！");
        return;
    }

    // SQL模糊查询: guest_name LIKE '%张%'
    historyModel->setFilter(QString("guest_name LIKE '%%1%'").arg(name));
    historyModel->select();
}

// --- 功能 5: 显示全部 (Tab 2) ---
void MainWindow::on_btnShowAll_clicked()
{
    ui->edtSearch->clear();
    historyModel->setFilter(""); // 清除过滤
    historyModel->select();
}

void MainWindow::on_btnExport_clicked()
{
    // 1. 获取文件保存路径
    QString fileName = QFileDialog::getSaveFileName(this, "导出报表",
                                                    QDir::homePath() + "/酒店订单报表.csv",
                                                    "CSV 文件 (*.csv)");
    if (fileName.isEmpty()) {
        return; // 用户点了取消
    }

    // 2. 打开文件准备写入
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法创建文件，请检查权限！");
        return;
    }

    QTextStream out(&file);
    // 处理中文乱码 (Excel通常默认GBK，或者带BOM的UTF8，这里用UTF8带BOM)
    out.setEncoding(QStringConverter::Utf8);
    out << "\xEF\xBB\xBF"; // 写入 BOM 头，防止 Excel 打开乱码

    // 3. 写入表头
    // 这里的列数要和你 historyModel 设置的列数一致
    out << "订单号,房号,住客姓名,电话,入住时间,退房时间,状态\n";

    // 4. 遍历 Model 数据写入文件
    // historyModel 是我们在 initModel 里 new 出来的那个
    for (int i = 0; i < historyModel->rowCount(); ++i) {
        QStringList rowData;
        for (int j = 0; j < 7; j++) { // 假设你有7列数据
            // 获取第 i 行 第 j 列的数据
            QString data = historyModel->record(i).value(j).toString();
            // 处理一下可能含有的逗号（CSV里逗号是分隔符）
            data.replace(",", "，");
            rowData << data;
        }
        out << rowData.join(",") << "\n";
    }

    file.close();
    QMessageBox::information(this, "成功", "报表已成功导出至：\n" + fileName);
}
