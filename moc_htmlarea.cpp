/****************************************************************************
** Meta object code from reading C++ file 'htmlarea.h'
**
** Created: Mon Mar 29 11:57:07 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "htmlarea.h"

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HtmlArea[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      14,   10,    9,    9, 0x0a,
      28,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_HtmlArea[] = {
    "HtmlArea\0\0txt\0linking(QUrl)\0getRandom()\0"
};

const QMetaObject HtmlArea::staticMetaObject = {
    { &QTextBrowser::staticMetaObject, qt_meta_stringdata_HtmlArea,
      qt_meta_data_HtmlArea, 0 }
};

const QMetaObject *HtmlArea::metaObject() const
{
    return &staticMetaObject;
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
        case 1: getRandom(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
