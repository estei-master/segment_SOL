/****************************************************************************
** Meta object code from reading C++ file 'lightmaps.h'
**
** Created: Thu Jan 30 17:04:52 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lightmaps.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lightmaps.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LightMaps[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      31,   29,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LightMaps[] = {
    "LightMaps\0\0toggleNightMode()\0r\0"
    "updateMap(QRect)\0"
};

void LightMaps::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LightMaps *_t = static_cast<LightMaps *>(_o);
        switch (_id) {
        case 0: _t->toggleNightMode(); break;
        case 1: _t->updateMap((*reinterpret_cast< const QRect(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LightMaps::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LightMaps::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LightMaps,
      qt_meta_data_LightMaps, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LightMaps::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LightMaps::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LightMaps::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LightMaps))
        return static_cast<void*>(const_cast< LightMaps*>(this));
    return QWidget::qt_metacast(_clname);
}

int LightMaps::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
