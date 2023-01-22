#ifndef QENUMDEFS_H
#define QENUMDEFS_H

#include <QObject>
#include <QtQml>
#include <QString>
#include <QMetaEnum>

#ifndef Q_ENUM
#   define Q_ENUM Q_ENUMS
#endif

#define Q_ENUM_CLASS(CLS_NAME, TYPE_NAME, ...) \
    class CLS_NAME { \
        private: Q_GADGET \
        private: QML_ELEMENT \
        private: QML_UNCREATABLE("Abstract enum class !") \
        public: static inline void qmlRegister(const char * uri, \
                                               const int majorVersion = 1, \
                                               const int minorVersion = 0); \
        public: \
            enum Enum  {__VA_ARGS__} ; Q_ENUM (Enum) \
            static bool isValid (const int value) { \
                return bool (staticMetaObject.enumerator (0).valueToKey (value) != nullptr); \
            } \
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
    Q_DECLARE_METATYPE (TYPE_NAME); \
    void CLS_NAME::qmlRegister(const char * uri, const int majorVersion, const int minorVersion) { \
        qmlRegisterUncreatableType<CLS_NAME>(uri, majorVersion, minorVersion, #CLS_NAME, "Abstract enum class !"); \
        qRegisterMetaType<TYPE_NAME>(#TYPE_NAME); \
    }

#endif // QENUMDEFS_H
