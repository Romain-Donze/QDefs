#ifndef QENUMDEFS_H
#define QENUMDEFS_H

#include <QObject>
#include <QString>
#include <QMetaEnum>

#ifndef Q_ENUM
#   define Q_ENUM Q_ENUMS
#endif

#define Q_ENUM_CLASS(Name, ...) \
    class Name { \
        Q_GADGET \
        public: \
            enum Type { __VA_ARGS__ }; Q_ENUM (Type) \
            static QByteArray asByteArray (const int value) { \
                return QByteArray (staticMetaObject.enumerator (0).valueToKey (value)); \
            } \
            static QString asString (const int value) { \
                return QString::fromLatin1 (asByteArray (value)); \
            } \
            static Type fromByteArray (const QByteArray & str, bool * ok = nullptr) { \
                return Name::Type (staticMetaObject.enumerator (0).keyToValue (str.constData (), ok)); \
            } \
            static Type fromString (const QString & str, bool * ok = nullptr) { \
                return fromByteArray (str.toLatin1 (), ok); \
            } \
        private: \
            Name (void) = delete; \
            Name (const Name &) = delete; \
            Name & operator= (const Name &) = delete; \
    }; \
    Q_DECLARE_METATYPE (Name::Type)

Q_ENUM_CLASS (_Test_QmlEnumClass_, FirstVal) // NOTE : to avoid "no suitable class found" MOC note

#endif // QENUMDEFS_H
