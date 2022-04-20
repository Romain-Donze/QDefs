#ifndef QFLAGDEFS_H
#define QFLAGDEFS_H

#include <QObject>
#include <QtQml>
#include <QString>
#include <QMetaEnum>

#include "qregisterdefs.h"

#define Q_FLAG_CLASS(CLS_NAME, TYPE_NAME, ...) \
    class CLS_NAME { \
        Q_GADGET \
        Q_REGISTER_ABSTRACT(CLS_NAME) \
        public: \
            enum Option { __VA_ARGS__ }; Q_DECLARE_FLAGS(Options, Option) Q_FLAGS(Options) \
            static QByteArray asByteArray (const int value) { \
                return QByteArray (staticMetaObject.enumerator (0).valueToKey (value)); \
            } \
            static QString asString (const int value) { \
                return QString::fromLatin1 (asByteArray (value)); \
            } \
            static Option fromByteArray (const QByteArray & str, bool * ok = nullptr) { \
                return CLS_NAME::Option (staticMetaObject.enumerator (0).keyToValue (str.constData (), ok)); \
            } \
            static Option fromString (const QString & str, bool * ok = nullptr) { \
                return fromByteArray (str.toLatin1 (), ok); \
            } \
            static QString dump(CLS_NAME::Options options) { \
                QStringList strList; \
                QMetaEnum me = CLS_NAME::staticMetaObject.enumerator(0); \
                for (int i=0; i<me.keyCount(); ++i) { \
                    if (options.testFlag((CLS_NAME::Option)me.value(i))) { \
                        strList.append(me.key(i)); \
                    } \
                } \
                return strList.join(" | "); \
            } \
        private: \
            CLS_NAME (void) = delete; \
            CLS_NAME (const CLS_NAME &) = delete; \
            CLS_NAME & operator= (const CLS_NAME &) = delete; \
    }; \
    typedef CLS_NAME::Options TYPE_NAME; \
    Q_DECLARE_OPERATORS_FOR_FLAGS (CLS_NAME::Options) \
    Q_DECLARE_METATYPE (CLS_NAME::Option)

Q_FLAG_CLASS (Test_QmlFlagClass_,Test_QmlFlagClass_Type_, FirstVal) // NOTE : to avoid "no suitable class found" MOC note

#endif // QFLAGDEFS_H
