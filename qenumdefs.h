#ifndef QENUMDEFS_H
#define QENUMDEFS_H

#include <QObject>
#include <QtQml>
#include <QString>
#include <QMetaEnum>

#include "qregisterdefs.h"

#ifndef Q_ENUM
#   define Q_ENUM Q_ENUMS
#endif

#define Q_ENUM_CLASS(CLS_NAME, TYPE_NAME, ...) \
    class CLS_NAME { \
        Q_GADGET \
        Q_REGISTER_ABSTRACT(CLS_NAME) \
        public: \
            enum Enum  {__VA_ARGS__} ; Q_ENUM (Enum) \
            static QByteArray asByteArray (const int value) { \
                return QByteArray (staticMetaObject.enumerator (0).valueToKey (value)); \
            } \
            static QString asString (const int value) { \
                return QString::fromLatin1 (asByteArray (value)); \
            } \
            static Enum fromByteArray (const QByteArray & str, bool * ok = nullptr) { \
                return CLS_NAME::Enum (staticMetaObject.enumerator (0).keyToValue (str.constData (), ok)); \
            } \
            static Enum fromString (const QString & str, bool * ok = nullptr) { \
                return fromByteArray (str.toLatin1 (), ok); \
            } \
        private: \
            CLS_NAME (void) = delete; \
            CLS_NAME (const CLS_NAME &) = delete; \
            CLS_NAME & operator= (const CLS_NAME &) = delete; \
    }; \
    typedef CLS_NAME::Enum TYPE_NAME; \
    Q_DECLARE_METATYPE (TYPE_NAME)

Q_ENUM_CLASS (Test_QmlEnumClass_, Test_QmlEnumClass_Type_, FirstVal) // NOTE : to avoid "no suitable class found" MOC note

#endif // QENUMDEFS_H
