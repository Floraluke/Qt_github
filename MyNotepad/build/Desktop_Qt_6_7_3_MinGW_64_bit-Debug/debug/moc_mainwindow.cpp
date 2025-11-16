/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSFindDialogENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSFindDialogENDCLASS = QtMocHelpers::stringData(
    "FindDialog",
    "onFindButtonClicked",
    ""
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFindDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject FindDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSFindDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFindDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFindDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FindDialog, std::true_type>,
        // method 'onFindButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void FindDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FindDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onFindButtonClicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *FindDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FindDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFindDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int FindDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSReplaceDialogENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSReplaceDialogENDCLASS = QtMocHelpers::stringData(
    "ReplaceDialog",
    "onFindNextClicked",
    "",
    "onReplaceClicked",
    "onReplaceAllClicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSReplaceDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x08,    1 /* Private */,
       3,    0,   33,    2, 0x08,    2 /* Private */,
       4,    0,   34,    2, 0x08,    3 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ReplaceDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSReplaceDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSReplaceDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSReplaceDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ReplaceDialog, std::true_type>,
        // method 'onFindNextClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onReplaceClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onReplaceAllClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ReplaceDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ReplaceDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onFindNextClicked(); break;
        case 1: _t->onReplaceClicked(); break;
        case 2: _t->onReplaceAllClicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *ReplaceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReplaceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSReplaceDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ReplaceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "on_actionNew_triggered",
    "",
    "on_action_O_triggered",
    "on_action_S_triggered",
    "on_action_A_triggered",
    "on_action_X_triggered",
    "on_action_Z_triggered",
    "on_action_Shift_Z_triggered",
    "on_action_X_2_triggered",
    "on_action_C_triggered",
    "on_action_V_triggered",
    "on_action_F_triggered",
    "on_action_R_triggered",
    "on_action_A_2_triggered",
    "on_action_W_triggered",
    "on_action_L_triggered",
    "on_action_F_2_triggered",
    "on_action_3_triggered",
    "on_action_4_triggered",
    "on_action_5_triggered",
    "on_action_L_2_triggered",
    "on_action_7_triggered",
    "on_action_A_3_triggered",
    "onFindButtonClicked",
    "onFindNextClicked",
    "onReplaceClicked",
    "onReplaceAllClicked",
    "closeTab",
    "index",
    "currentTabChanged",
    "documentWasModified",
    "updateStatusBar",
    "updateEditActions",
    "autoSave"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  206,    2, 0x08,    1 /* Private */,
       3,    0,  207,    2, 0x08,    2 /* Private */,
       4,    0,  208,    2, 0x08,    3 /* Private */,
       5,    0,  209,    2, 0x08,    4 /* Private */,
       6,    0,  210,    2, 0x08,    5 /* Private */,
       7,    0,  211,    2, 0x08,    6 /* Private */,
       8,    0,  212,    2, 0x08,    7 /* Private */,
       9,    0,  213,    2, 0x08,    8 /* Private */,
      10,    0,  214,    2, 0x08,    9 /* Private */,
      11,    0,  215,    2, 0x08,   10 /* Private */,
      12,    0,  216,    2, 0x08,   11 /* Private */,
      13,    0,  217,    2, 0x08,   12 /* Private */,
      14,    0,  218,    2, 0x08,   13 /* Private */,
      15,    0,  219,    2, 0x08,   14 /* Private */,
      16,    0,  220,    2, 0x08,   15 /* Private */,
      17,    0,  221,    2, 0x08,   16 /* Private */,
      18,    0,  222,    2, 0x08,   17 /* Private */,
      19,    0,  223,    2, 0x08,   18 /* Private */,
      20,    0,  224,    2, 0x08,   19 /* Private */,
      21,    0,  225,    2, 0x08,   20 /* Private */,
      22,    0,  226,    2, 0x08,   21 /* Private */,
      23,    0,  227,    2, 0x08,   22 /* Private */,
      24,    0,  228,    2, 0x08,   23 /* Private */,
      25,    0,  229,    2, 0x08,   24 /* Private */,
      26,    0,  230,    2, 0x08,   25 /* Private */,
      27,    0,  231,    2, 0x08,   26 /* Private */,
      28,    1,  232,    2, 0x08,   27 /* Private */,
      30,    1,  235,    2, 0x08,   29 /* Private */,
      31,    0,  238,    2, 0x08,   31 /* Private */,
      32,    0,  239,    2, 0x08,   32 /* Private */,
      33,    0,  240,    2, 0x08,   33 /* Private */,
      34,    0,  241,    2, 0x08,   34 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_actionNew_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_O_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_S_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_A_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_X_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_Z_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_Shift_Z_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_X_2_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_C_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_V_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_F_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_R_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_A_2_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_W_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_L_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_F_2_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_3_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_4_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_5_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_L_2_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_7_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_A_3_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFindButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFindNextClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onReplaceClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onReplaceAllClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'currentTabChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'documentWasModified'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateStatusBar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateEditActions'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'autoSave'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_actionNew_triggered(); break;
        case 1: _t->on_action_O_triggered(); break;
        case 2: _t->on_action_S_triggered(); break;
        case 3: _t->on_action_A_triggered(); break;
        case 4: _t->on_action_X_triggered(); break;
        case 5: _t->on_action_Z_triggered(); break;
        case 6: _t->on_action_Shift_Z_triggered(); break;
        case 7: _t->on_action_X_2_triggered(); break;
        case 8: _t->on_action_C_triggered(); break;
        case 9: _t->on_action_V_triggered(); break;
        case 10: _t->on_action_F_triggered(); break;
        case 11: _t->on_action_R_triggered(); break;
        case 12: _t->on_action_A_2_triggered(); break;
        case 13: _t->on_action_W_triggered(); break;
        case 14: _t->on_action_L_triggered(); break;
        case 15: _t->on_action_F_2_triggered(); break;
        case 16: _t->on_action_3_triggered(); break;
        case 17: _t->on_action_4_triggered(); break;
        case 18: _t->on_action_5_triggered(); break;
        case 19: _t->on_action_L_2_triggered(); break;
        case 20: _t->on_action_7_triggered(); break;
        case 21: _t->on_action_A_3_triggered(); break;
        case 22: _t->onFindButtonClicked(); break;
        case 23: _t->onFindNextClicked(); break;
        case 24: _t->onReplaceClicked(); break;
        case 25: _t->onReplaceAllClicked(); break;
        case 26: _t->closeTab((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 27: _t->currentTabChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 28: _t->documentWasModified(); break;
        case 29: _t->updateStatusBar(); break;
        case 30: _t->updateEditActions(); break;
        case 31: _t->autoSave(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 32)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 32;
    }
    return _id;
}
QT_WARNING_POP
