/****************************************************************************
** Meta object code from reading C++ file 'config_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../config_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'config_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_config_widget_t {
    QByteArrayData data[20];
    char stringdata0[314];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_config_widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_config_widget_t qt_meta_stringdata_config_widget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "config_widget"
QT_MOC_LITERAL(1, 14, 17), // "configWidgetClose"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 11), // "stopManuPWM"
QT_MOC_LITERAL(4, 45, 12), // "startManuPWM"
QT_MOC_LITERAL(5, 58, 12), // "ChangeTarget"
QT_MOC_LITERAL(6, 71, 15), // "ReDisplayScreen"
QT_MOC_LITERAL(7, 87, 10), // "BuzzerOpen"
QT_MOC_LITERAL(8, 98, 11), // "BuzzerClose"
QT_MOC_LITERAL(9, 110, 18), // "QTimerBuzzermsdell"
QT_MOC_LITERAL(10, 129, 19), // "button_home_pressed"
QT_MOC_LITERAL(11, 149, 20), // "button_home_released"
QT_MOC_LITERAL(12, 170, 22), // "button_logsave_pressed"
QT_MOC_LITERAL(13, 193, 23), // "button_logsave_released"
QT_MOC_LITERAL(14, 217, 15), // "P_show_keyboard"
QT_MOC_LITERAL(15, 233, 15), // "F_show_keyboard"
QT_MOC_LITERAL(16, 249, 18), // "Get_keyboard_value"
QT_MOC_LITERAL(17, 268, 17), // "change_brightness"
QT_MOC_LITERAL(18, 286, 5), // "value"
QT_MOC_LITERAL(19, 292, 21) // "on_pb_zylight_pressed"

    },
    "config_widget\0configWidgetClose\0\0"
    "stopManuPWM\0startManuPWM\0ChangeTarget\0"
    "ReDisplayScreen\0BuzzerOpen\0BuzzerClose\0"
    "QTimerBuzzermsdell\0button_home_pressed\0"
    "button_home_released\0button_logsave_pressed\0"
    "button_logsave_released\0P_show_keyboard\0"
    "F_show_keyboard\0Get_keyboard_value\0"
    "change_brightness\0value\0on_pb_zylight_pressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_config_widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,
       4,    0,  101,    2, 0x06 /* Public */,
       5,    0,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  103,    2, 0x0a /* Public */,
       7,    0,  104,    2, 0x0a /* Public */,
       8,    0,  105,    2, 0x0a /* Public */,
       9,    0,  106,    2, 0x0a /* Public */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    0,  109,    2, 0x08 /* Private */,
      13,    0,  110,    2, 0x08 /* Private */,
      14,    0,  111,    2, 0x08 /* Private */,
      15,    0,  112,    2, 0x08 /* Private */,
      16,    0,  113,    2, 0x08 /* Private */,
      17,    1,  114,    2, 0x08 /* Private */,
      19,    0,  117,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

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
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,

       0        // eod
};

void config_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        config_widget *_t = static_cast<config_widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->configWidgetClose(); break;
        case 1: _t->stopManuPWM(); break;
        case 2: _t->startManuPWM(); break;
        case 3: _t->ChangeTarget(); break;
        case 4: _t->ReDisplayScreen(); break;
        case 5: _t->BuzzerOpen(); break;
        case 6: _t->BuzzerClose(); break;
        case 7: _t->QTimerBuzzermsdell(); break;
        case 8: _t->button_home_pressed(); break;
        case 9: _t->button_home_released(); break;
        case 10: _t->button_logsave_pressed(); break;
        case 11: _t->button_logsave_released(); break;
        case 12: _t->P_show_keyboard(); break;
        case 13: _t->F_show_keyboard(); break;
        case 14: _t->Get_keyboard_value(); break;
        case 15: _t->change_brightness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_pb_zylight_pressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (config_widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&config_widget::configWidgetClose)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (config_widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&config_widget::stopManuPWM)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (config_widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&config_widget::startManuPWM)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (config_widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&config_widget::ChangeTarget)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject config_widget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_config_widget.data,
      qt_meta_data_config_widget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *config_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *config_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_config_widget.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int config_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void config_widget::configWidgetClose()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void config_widget::stopManuPWM()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void config_widget::startManuPWM()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void config_widget::ChangeTarget()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
