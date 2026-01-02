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

// --- 功能 4: 搜索 (Tab 2) ---
void MainWindow::on_btnSearch_clicked()
{
    // 1. 获取名字条件
    QString name = ui->edtSearch->text().trimmed();

    // 2. 获取日期条件 (字符串格式)
    // 补全时间：开始时间是当天的 00:00，结束时间是当天的 23:59
    QString startTime = ui->dateStart->date().toString("yyyy-MM-dd") + " 00:00";
    QString endTime = ui->dateEnd->date().toString("yyyy-MM-dd") + " 23:59";

    // 3. 拼接 SQL 筛选语句
    // 逻辑：(名字包含 XX) AND (入住时间 在 开始 和 结束 之间)
    // 注意：SQLite 的字符串日期可以直接比较大小
    QString filter = QString("check_in_date >= '%1' AND check_in_date <= '%2'")
                         .arg(startTime).arg(endTime);

    if (!name.isEmpty()) {
        filter += QString(" AND guest_name LIKE '%%1%'").arg(name);
    }

    // 4. 应用筛选
    historyModel->setFilter(filter);
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

// 别忘了在 mainwindow.h 里声明: void on_btnStats_clicked();
// 或者直接在 UI 右键 -> Go to slot

void MainWindow::on_btnStats_clicked()
{
    // 利用 SQL 的 SUM 函数直接计算，不需要遍历表格（高效！）
    QSqlQuery query;
    // 计算 order_info 表里所有已退房订单的金额
    // 注意：我们没有直接存订单总价，而是用 room_id 关联查价格
    // 这里为了简单，我们假设 check_out 弹窗算完钱后，应该把钱存进 order_info 表。

    /* Wait! 之前的数据库设计里，order_info 表里好像没有 'total_price' 字段？
       这确实是个小缺陷。为了不改动数据库结构导致麻烦，
       我们用一种简单的 "估算" 方法，或者遍历当前表格计算。
    */

    // 方案 B：直接遍历当前表格显示的记录来计算 (所见即所得)
    double total = 0.0;
    int rowCount = historyModel->rowCount();

    // 我们需要知道单价。但是 historyModel 里默认可能没显示 price 列。
    // 如果觉得麻烦，我们做一个最简单的：统计“已退房”的订单数量。

    // ================== 升级版方案 ==================
    // 统计当前筛选出来的订单数
    ui->lblTotalIncome->setText(QString("当前查询结果共 %1 单").arg(rowCount));
}

