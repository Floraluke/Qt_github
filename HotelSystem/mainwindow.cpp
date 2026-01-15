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
    // ================== Tab 1: 房态管理 (视图模型) ==================

    // 创建视图，将数据库里的 0/1 状态转为中文显示
    QSqlQuery query;
    query.exec("CREATE VIEW IF NOT EXISTS room_view AS "
               "SELECT room_id, room_type, price, "
               "CASE status WHEN 0 THEN '空闲' ELSE '已入住' END as status_desc "
               "FROM room_info");

    model = new QSqlTableModel(this);
    model->setTable("room_view");

    // 设置表头
    model->setHeaderData(0, Qt::Horizontal, "房号");
    model->setHeaderData(1, Qt::Horizontal, "房型");
    model->setHeaderData(2, Qt::Horizontal, "单价(元)");
    model->setHeaderData(3, Qt::Horizontal, "当前状态");
    model->select(); // 加载数据

    // 配置 Tab 1 表格UI
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止双击编辑
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // 选中整行
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自动铺满
    ui->tableView->setAlternatingRowColors(true); // 隔行变色

    // ================== Tab 2: 历史订单 (直连表) ==================

    historyModel = new QSqlTableModel(this);
    historyModel->setTable("order_info");
    historyModel->select(); // 加载所有历史数据

    // 设置表头 (对应数据库字段顺序)
    // 0:order_id, 1:room_id, 2:guest_name, 3:phone, 4:in_time, 5:out_time, 6:price, 7:active
    historyModel->setHeaderData(0, Qt::Horizontal, "订单号");
    historyModel->setHeaderData(1, Qt::Horizontal, "房号");
    historyModel->setHeaderData(2, Qt::Horizontal, "住客姓名");
    historyModel->setHeaderData(3, Qt::Horizontal, "联系电话");
    historyModel->setHeaderData(4, Qt::Horizontal, "入住时间");
    historyModel->setHeaderData(5, Qt::Horizontal, "退房时间");
    historyModel->setHeaderData(6, Qt::Horizontal, "消费金额(元)"); // 【修正】这里是金额
    // 第7列 is_active 是内部状态，不设置表头，直接隐藏

    // 配置 Tab 2 表格UI
    ui->viewHistory->setModel(historyModel);
    ui->viewHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->viewHistory->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->viewHistory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->viewHistory->setAlternatingRowColors(true);

    // 隐藏不需要给用户看的列
    ui->viewHistory->hideColumn(0); // 隐藏订单ID
    ui->viewHistory->hideColumn(7); // 隐藏内部状态位(is_active)

    // ================== 交互逻辑 ==================

    // 双击 Tab 1 房间，自动判断是入住还是退房
    connect(ui->tableView, &QTableView::doubleClicked, this, [=](const QModelIndex &index){
        QSqlRecord record = model->record(index.row());
        QString status = record.value("status_desc").toString();

        if (status == "空闲") {
            on_btnCheckIn_clicked(); // 没人的话去入住
        } else {
            on_btnCheckOut_clicked(); // 有人的话去退房
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
    out << "订单号,房号,住客姓名,电话,入住时间,退房时间,消费金额\n";

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
    // 1. 刷新一下模型，确保拿到最新的退房数据
    historyModel->select();

    double totalIncome = 0.0;
    int rowCount = historyModel->rowCount();

    // 2. 遍历表格，直接累加数据库里存好的 "total_price"
    for (int i = 0; i < rowCount; i++) {
        // 直接读 "total_price" 字段，不需要再算时间差了，那样容易有误差
        // toDouble() 如果遇到空值会自动变成 0.0，非常安全
        double price = historyModel->record(i).value("total_price").toDouble();
        totalIncome += price;
    }

    // 3. 更新界面上的大字标签
    // 注意：请确认你 UI 界面上那个显示金额的 Label 名字是不是叫 lblTotalIncome
    // 如果叫 lblTotalRevenue 或者其他名字，请在这里改一下！
    ui->lblTotalIncome->setText(QString("当前总收入： %1 元").arg(QString::number(totalIncome, 'f', 2)));

    // 4. 弹窗显示详细信息
    QMessageBox::information(this, "财务统计",
                             QString("统计完成！\n\n"
                                     "当前列表共有订单： %1 单\n"
                                     "累计实际营业额： %2 元")
                                 .arg(rowCount)
                                 .arg(QString::number(totalIncome, 'f', 2)));
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

