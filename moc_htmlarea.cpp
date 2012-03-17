/****************************************************************************
** Meta object code from reading C++ file 'htmlarea.h'
**
** Created: Sat Mar 17 16:34:30 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "htmlarea.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'htmlarea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UserEventFilter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_UserEventFilter[] = {
    "UserEventFilter\0"
};

const QMetaObject UserEventFilter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UserEventFilter,
      qt_meta_data_UserEventFilter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UserEventFilter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UserEventFilter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UserEventFilter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserEventFilter))
        return static_cast<void*>(const_cast< UserEventFilter*>(this));
    return QObject::qt_metacast(_clname);
}

int UserEventFilter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_HtmlArea[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   10,    9,    9, 0x0a,
      28,   10,    9,    9, 0x0a,
      47,    9,    9,    9, 0x0a,
      59,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_HtmlArea[] = {
    "HtmlArea\0\0txt\0linking(QUrl)\0"
    "sourceChange(QUrl)\0getRandom()\0goToTop()\0"
};

const QMetaObject HtmlArea::staticMetaObject = {
    { &QTextBrowser::staticMetaObject, qt_meta_stringdata_HtmlArea,
      qt_meta_data_HtmlArea, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HtmlArea::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HtmlArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HtmlArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HtmlArea))
        return static_cast<void*>(const_cast< HtmlArea*>(this));
    return QTextBrowser::qt_metacast(_clname);
}

int HtmlArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextBrowser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: linking((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 1: sourceChange((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 2: getRandom(); break;
        case 3: goToTop(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
