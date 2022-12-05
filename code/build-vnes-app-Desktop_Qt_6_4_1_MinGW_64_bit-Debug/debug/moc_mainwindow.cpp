/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../vnes-app/mainwindow.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[36];
    char stringdata0[11];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[31];
    char stringdata4[38];
    char stringdata5[25];
    char stringdata6[25];
    char stringdata7[25];
    char stringdata8[26];
    char stringdata9[20];
    char stringdata10[20];
    char stringdata11[24];
    char stringdata12[24];
    char stringdata13[25];
    char stringdata14[30];
    char stringdata15[6];
    char stringdata16[30];
    char stringdata17[30];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 11),  // "createChart"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 30),  // "unordered_map<QString,QString>"
        QT_MOC_LITERAL(55, 37),  // "unordered_map<QString,vector<..."
        QT_MOC_LITERAL(93, 24),  // "onFetchDataButtonClicked"
        QT_MOC_LITERAL(118, 24),  // "on_trafficButton_clicked"
        QT_MOC_LITERAL(143, 24),  // "on_weatherButton_clicked"
        QT_MOC_LITERAL(168, 25),  // "on_combinedButton_clicked"
        QT_MOC_LITERAL(194, 19),  // "setTimelineDropDown"
        QT_MOC_LITERAL(214, 19),  // "setLocationDropDown"
        QT_MOC_LITERAL(234, 23),  // "setTrafficDataDropDowns"
        QT_MOC_LITERAL(258, 23),  // "setWeatherDataDropDowns"
        QT_MOC_LITERAL(282, 24),  // "setCombinedDataDropDowns"
        QT_MOC_LITERAL(307, 29),  // "on_locationDropDown_activated"
        QT_MOC_LITERAL(337, 5),  // "index"
        QT_MOC_LITERAL(343, 29),  // "on_timelineDropDown_activated"
        QT_MOC_LITERAL(373, 29)   // "on_datatypeDropDown_activated"
    },
    "MainWindow",
    "createChart",
    "",
    "unordered_map<QString,QString>",
    "unordered_map<QString,vector<double>>",
    "onFetchDataButtonClicked",
    "on_trafficButton_clicked",
    "on_weatherButton_clicked",
    "on_combinedButton_clicked",
    "setTimelineDropDown",
    "setLocationDropDown",
    "setTrafficDataDropDowns",
    "setWeatherDataDropDowns",
    "setCombinedDataDropDowns",
    "on_locationDropDown_activated",
    "index",
    "on_timelineDropDown_activated",
    "on_datatypeDropDown_activated"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    6,   92,    2, 0x08,    1 /* Private */,
       5,    0,  105,    2, 0x08,    8 /* Private */,
       6,    0,  106,    2, 0x08,    9 /* Private */,
       7,    0,  107,    2, 0x08,   10 /* Private */,
       8,    0,  108,    2, 0x08,   11 /* Private */,
       9,    0,  109,    2, 0x08,   12 /* Private */,
      10,    0,  110,    2, 0x08,   13 /* Private */,
      11,    0,  111,    2, 0x08,   14 /* Private */,
      12,    0,  112,    2, 0x08,   15 /* Private */,
      13,    0,  113,    2, 0x08,   16 /* Private */,
      14,    1,  114,    2, 0x08,   17 /* Private */,
      16,    1,  117,    2, 0x08,   19 /* Private */,
      17,    1,  120,    2, 0x08,   21 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 3, 0x80000000 | 4, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'createChart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<unordered_map<QString,QString>, std::false_type>,
        QtPrivate::TypeAndForceComplete<unordered_map<QString,vector<double>>, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'onFetchDataButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_trafficButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_weatherButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_combinedButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setTimelineDropDown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setLocationDropDown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setTrafficDataDropDowns'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setWeatherDataDropDowns'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setCombinedDataDropDowns'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_locationDropDown_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_timelineDropDown_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_datatypeDropDown_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->createChart((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<unordered_map<QString,QString>>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<unordered_map<QString,vector<double>>>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6]))); break;
        case 1: _t->onFetchDataButtonClicked(); break;
        case 2: _t->on_trafficButton_clicked(); break;
        case 3: _t->on_weatherButton_clicked(); break;
        case 4: _t->on_combinedButton_clicked(); break;
        case 5: _t->setTimelineDropDown(); break;
        case 6: _t->setLocationDropDown(); break;
        case 7: _t->setTrafficDataDropDowns(); break;
        case 8: _t->setWeatherDataDropDowns(); break;
        case 9: _t->setCombinedDataDropDowns(); break;
        case 10: _t->on_locationDropDown_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->on_timelineDropDown_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->on_datatypeDropDown_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
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
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
