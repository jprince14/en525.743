/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      41,   11,   11,   11, 0x08,
      76,   11,   11,   11, 0x08,
     119,  113,   11,   11, 0x08,
     167,   11,   11,   11, 0x08,
     200,   11,   11,   11, 0x08,
     236,   11,   11,   11, 0x08,
     278,  270,   11,   11, 0x08,
     311,  270,   11,   11, 0x08,
     345,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_Enable_receiver_clicked()\0"
    "on_beaglebone_ip_editingFinished()\0"
    "on_beaglebone_port_editingFinished()\0"
    "index\0on_modulation_combobox_currentIndexChanged(int)\0"
    "on_fm_freq_BOX_editingFinished()\0"
    "on_CB_channel_box_editingFinished()\0"
    "on_mp3_location_editingFinished()\0"
    "checked\0on_enable_speakers_clicked(bool)\0"
    "on_enable_recording_clicked(bool)\0"
    "on_beaglebone_data_port_editingFinished()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_Enable_receiver_clicked(); break;
        case 1: _t->on_beaglebone_ip_editingFinished(); break;
        case 2: _t->on_beaglebone_port_editingFinished(); break;
        case 3: _t->on_modulation_combobox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_fm_freq_BOX_editingFinished(); break;
        case 5: _t->on_CB_channel_box_editingFinished(); break;
        case 6: _t->on_mp3_location_editingFinished(); break;
        case 7: _t->on_enable_speakers_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_enable_recording_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_beaglebone_data_port_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
