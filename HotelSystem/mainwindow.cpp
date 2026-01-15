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
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 先初始化数据模型(让 model 不再是空指针)
    // 这样即便后面触发了信号，槽函数里的 model->setFilter 也是安全的
    initModel();

    ui->comboType->addItem("全部房型");
    ui->comboType->addItem("标准单人间");
    ui->comboType->addItem("豪华双人间");
    ui->comboType->addItem("商务大床房");
    ui->comboType->addItem("行政套房");
    ui->comboType->addItem("总统套房");

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
    // Tab 1 的表格
    ui->tableView->setAlternatingRowColors(true); // 【新增】开启隔行变色
    // Tab 2 的表格
    ui->viewHistory->setAlternatingRowColors(true); // 【新增】开启隔行变色

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

    // 【新增】双击 Tab 1 的表格，触发 Smart Action
    connect(ui->tableView, &QTableView::doubleClicked, this, [=](const QModelIndex &index){
        // 获取状态
        QSqlRecord record = model->record(index.row());
        QString status = record.value("status_desc").toString();

        if (status == "空闲") {
            on_btnCheckIn_clicked(); // 调用入住
        } else {
            on_btnCheckOut_clicked(); // 调用退房
        }
    });
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



void MainWindow::on_btnStats_clicked()
{
    double totalIncome = 0.0;
    int rowCount = historyModel->rowCount();

    // 遍历表格里的每一行，算钱
    for (int i = 0; i < rowCount; i++) {
        // 1. 获取入住和退房时间
        QString strIn = historyModel->record(i).value("check_in_date").toString();
        QString strOut = historyModel->record(i).value("check_out_date").toString();

        // 2. 如果还没退房（时间为空），就不算它的钱
        if (strOut.isEmpty()) continue;

        // 3. 计算住了几天
        QDateTime inDate = QDateTime::fromString(strIn, "yyyy-MM-dd HH:mm");
        QDateTime outDate = QDateTime::fromString(strOut, "yyyy-MM-dd HH:mm");

        if (inDate.isValid() && outDate.isValid()) {
            qint64 secs = inDate.secsTo(outDate);
            double days = secs / 86400.0; // 换算成天
            if (days < 1.0) days = 1.0;   // 不足1天按1天算

            // 4. 【核心】因为历史表没存房价，我们这里用“估算”
            // 如果你想精确，可以用 SQL 联表查询，但这里为了作业演示，
            // 我们假设平均房价是 288 元 (或者你可以根据房号判断价格)
            double pricePerDay = 288.0;

            // 高级一点：如果是 808 房，算 8888 元
            int roomId = historyModel->record(i).value("room_id").toInt();
            if (roomId == 808) pricePerDay = 8888.0;
            else if (roomId >= 200) pricePerDay = 288.0;
            else pricePerDay = 168.0;

            totalIncome += days * pricePerDay;
        }
    }

    // 5. 显示结果
    ui->lblTotalIncome->setText(QString("当前列表总营收： %1 元").arg(QString::number(totalIncome, 'f', 2)));

    // 顺便弹个窗炫耀一下
    QMessageBox::information(this, "财务统计",
                             QString("统计完成！\n\n共涉及订单： %1 单\n总营业额： %2 元")
                                 .arg(rowCount)
                                 .arg(totalIncome));
}


void MainWindow::on_btnLogout_clicked()
{

    if (QMessageBox::question(this, "注销", "确定要退出当前账号吗？",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {

        qApp->exit(773);
    }
}


void MainWindow::on_btnLogout_2_clicked()
{

    if (QMessageBox::question(this, "注销", "确定要退出当前账号吗？",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {

        qApp->exit(773);
    }
}

