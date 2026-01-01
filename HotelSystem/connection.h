#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QCoreApplication>

static bool createConnection()
{
    // 1. 添加 SQLite 数据库驱动
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // 2. 设置数据库文件路径（直接生成在构建目录中，名为 hotel.db）
    db.setDatabaseName("hotel.db");

    // 3. 打开数据库
    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error",
                              "无法建立数据库连接，请检查驱动！");
        return false;
    }

    // 4. 创建 Query 对象执行 SQL
    QSqlQuery query;

    // --- 建表：客房表 ---
    query.exec("CREATE TABLE IF NOT EXISTS room_info ("
               "room_id INTEGER PRIMARY KEY, "
               "room_type TEXT, "
               "price REAL, "
               "status INTEGER DEFAULT 0)");

    // --- 建表：订单表 ---
    query.exec("CREATE TABLE IF NOT EXISTS order_info ("
               "order_id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "room_id INTEGER, "
               "guest_name TEXT, "
               "phone_num TEXT, "
               "check_in_date TEXT, "
               "check_out_date TEXT, "
               "is_active INTEGER DEFAULT 1)");

    // --- 初始化测试数据（避免每次运行都重复插入，先检查是否为空） ---
    query.exec("SELECT COUNT(*) FROM room_info");
    if (query.next() && query.value(0).toInt() == 0) {
        // 如果表是空的，才插入数据
        query.exec("INSERT INTO room_info VALUES (101, '标准单人间', 168.0, 0)");
        query.exec("INSERT INTO room_info VALUES (102, '标准单人间', 168.0, 0)");
        query.exec("INSERT INTO room_info VALUES (201, '豪华双人间', 288.0, 0)");
        query.exec("INSERT INTO room_info VALUES (202, '豪华双人间', 288.0, 1)"); // 预设一个已入住
        query.exec("INSERT INTO room_info VALUES (808, '总统套房', 8888.0, 0)");
        qDebug() << "测试数据已初始化...";
    }

    return true;
}

#endif // CONNECTION_H
