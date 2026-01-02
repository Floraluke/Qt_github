#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QCoreApplication>


static bool createConnection()
{
    // 1. 添加数据库驱动
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("hotel.db");

    // 2. 打开数据库
    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error", "无法建立数据库连接！");
        return false;
    }

    QSqlQuery query;


    // 3. 创建表结构 (如果没有则创建)
    // --- 客房表 ---
    query.exec("CREATE TABLE IF NOT EXISTS room_info ("
               "room_id INTEGER PRIMARY KEY, "
               "room_type TEXT, "
               "price REAL, "
               "status INTEGER DEFAULT 0)");

    // --- 订单表 ---
    query.exec("CREATE TABLE IF NOT EXISTS order_info ("
               "order_id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "room_id INTEGER, "
               "guest_name TEXT, "
               "phone_num TEXT, "
               "check_in_date TEXT, "
               "check_out_date TEXT, "
               "is_active INTEGER DEFAULT 1)");

    // 4. 【关键】判断表里有没有数据，如果没数据(说明是刚建的)，就批量插入房间
    query.exec("SELECT COUNT(*) FROM room_info");
    if (query.next() && query.value(0).toInt() == 0) {

        // --- 1楼：标准单人间 (101 - 105) ---
        for (int i = 1; i <= 8; i++) {
            int id = 100 + i;
            // 语法: INSERT INTO 表名 VALUES (房号, 类型, 价格, 状态0=空闲)
            query.exec(QString("INSERT INTO room_info VALUES (%1, '标准单人间', 168.0, 0)").arg(id));
        }

        // --- 2楼：豪华双人间 (201 - 208) ---
        for (int i = 1; i <= 8; i++) {
            int id = 200 + i;
            query.exec(QString("INSERT INTO room_info VALUES (%1, '豪华双人间', 288.0, 0)").arg(id));
        }

        // --- 3楼：商务大床房 (301 - 305) ---
        for (int i = 1; i <= 5; i++) {
            int id = 300 + i;
            query.exec(QString("INSERT INTO room_info VALUES (%1, '商务大床房', 368.0, 0)").arg(id));
        }

        // --- 8楼：顶级套房 ---
        query.exec("INSERT INTO room_info VALUES (801, '总统套房', 8888.0, 0)");
        query.exec("INSERT INTO room_info VALUES (802, '行政套房', 6666.0, 0)");

        qDebug() << "数据库初始化完成：已生成大量空闲房间...";
    }

    // 注意：这里我们故意不插入 order_info 的数据，这样历史订单就是空的！

    return true;
}

#endif // CONNECTION_H
