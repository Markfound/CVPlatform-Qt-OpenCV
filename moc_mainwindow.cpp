/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[219];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "openProcess"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "newProcess"
QT_MOC_LITERAL(4, 35, 11), // "saveProcess"
QT_MOC_LITERAL(5, 47, 12), // "closeProcess"
QT_MOC_LITERAL(6, 60, 12), // "startProcess"
QT_MOC_LITERAL(7, 73, 15), // "showContextMenu"
QT_MOC_LITERAL(8, 89, 5), // "point"
QT_MOC_LITERAL(9, 95, 10), // "addProcess"
QT_MOC_LITERAL(10, 106, 5), // "Index"
QT_MOC_LITERAL(11, 112, 10), // "endProcess"
QT_MOC_LITERAL(12, 123, 11), // "stopProcess"
QT_MOC_LITERAL(13, 135, 12), // "gGetFilePath"
QT_MOC_LITERAL(14, 148, 11), // "clickAction"
QT_MOC_LITERAL(15, 160, 13), // "UpperCVAction"
QT_MOC_LITERAL(16, 174, 14), // "DownerCVAction"
QT_MOC_LITERAL(17, 189, 14), // "DeleteCVAction"
QT_MOC_LITERAL(18, 204, 14) // "SetProCVAction"

    },
    "MainWindow\0openProcess\0\0newProcess\0"
    "saveProcess\0closeProcess\0startProcess\0"
    "showContextMenu\0point\0addProcess\0Index\0"
    "endProcess\0stopProcess\0gGetFilePath\0"
    "clickAction\0UpperCVAction\0DownerCVAction\0"
    "DeleteCVAction\0SetProCVAction"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x0a /* Public */,
       3,    0,   90,    2, 0x0a /* Public */,
       4,    0,   91,    2, 0x0a /* Public */,
       5,    0,   92,    2, 0x0a /* Public */,
       6,    0,   93,    2, 0x0a /* Public */,
       7,    1,   94,    2, 0x0a /* Public */,
       9,    1,   97,    2, 0x0a /* Public */,
      11,    0,  100,    2, 0x0a /* Public */,
      12,    0,  101,    2, 0x0a /* Public */,
      13,    0,  102,    2, 0x0a /* Public */,
      14,    1,  103,    2, 0x0a /* Public */,
      15,    0,  106,    2, 0x0a /* Public */,
      16,    0,  107,    2, 0x0a /* Public */,
      17,    0,  108,    2, 0x0a /* Public */,
      18,    0,  109,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    8,
    QMetaType::Void, QMetaType::QModelIndex,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openProcess(); break;
        case 1: _t->newProcess(); break;
        case 2: _t->saveProcess(); break;
        case 3: _t->closeProcess(); break;
        case 4: _t->startProcess(); break;
        case 5: _t->showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 6: _t->addProcess((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 7: _t->endProcess(); break;
        case 8: _t->stopProcess(); break;
        case 9: _t->gGetFilePath(); break;
        case 10: _t->clickAction((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 11: _t->UpperCVAction(); break;
        case 12: _t->DownerCVAction(); break;
        case 13: _t->DeleteCVAction(); break;
        case 14: _t->SetProCVAction(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
