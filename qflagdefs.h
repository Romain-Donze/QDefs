#ifndef QFLAGDEFS_H
#define QFLAGDEFS_H

#include <QObject>
#include <QString>
#include <QMetaEnum>

#define Q_FLAG_CLASS(Name, ...) \
    class Name { \
        Q_GADGET \
        public: \
            enum Option { __VA_ARGS__ }; Q_DECLARE_FLAGS(Options, Option) Q_FLAGS(Options) \
            static QByteArray asByteArray (const int value) { \
                return QByteArray (staticMetaObject.enumerator (0).valueToKey (value)); \
            } \
            static QString asString (const int value) { \
                return QString::fromLatin1 (asByteArray (value)); \
            } \
            static Option fromByteArray (const QByteArray & str, bool * ok = nullptr) { \
                return Name::Option (staticMetaObject.enumerator (0).keyToValue (str.constData (), ok)); \
            } \
            static Option fromString (const QString & str, bool * ok = nullptr) { \
                return fromByteArray (str.toLatin1 (), ok); \
            } \
            static QString dump(Name::Options options) { \
                QStringList strList; \
                QMetaEnum me = Name::staticMetaObject.enumerator(0); \
                for (int i=0; i<me.keyCount(); ++i) { \
                    if (options.testFlag((Name::Option)me.value(i))) { \
                        strList.append(me.key(i)); \
                    } \
                } \
                return strList.join(" | "); \
            } \
        private: \
            Name (void) = delete; \
            Name (const Name &) = delete; \
            Name & operator= (const Name &) = delete; \
    }; \
    Q_DECLARE_OPERATORS_FOR_FLAGS (Name::Options) \
    Q_DECLARE_METATYPE (Name::Option)

Q_FLAG_CLASS (_Test_QmlFlagClass_, FirstVal) // NOTE : to avoid "no suitable class found" MOC note

#endif // QFLAGDEFS_H
