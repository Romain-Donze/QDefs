#ifndef QREGISTERDEFS_H
#define QREGISTERDEFS_H

#include <QDebug>
#include <QtQml>
#include <QMetaType>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Macros qmlRegisterType
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define ERR_ENUM_CLASS    "Enum-class !"
#define ERR_ATTACHED_OBJ  "Attached-object class !"
#define ERR_ABSTRACT_BASE "Abstract base class !"

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Private: for declaration purpose
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define _Q_REGISTER_METATYPE(TYPE, NAME) \
    qRegisterMetaType<TYPE>(NAME); \

#define _Q_REGISTER_METATYPE_AT_STARTUP(TYPE, FUNC, NAME) \
    static inline void registerMetaType##FUNC() { \
        _Q_REGISTER_METATYPE(TYPE,NAME); \
    } \
    Q_COREAPP_STARTUP_FUNCTION(registerMetaType##FUNC) \

#define _Q_REGISTER_TYPE(TYPE, QML_NAME) \
    private: QML_NAMED_ELEMENT(QML_NAME) \
    private: QML_UNCREATABLE(ERR_ABSTRACT_BASE) \
    public: \
        static inline void qmlRegister(const char * uri, \
                                       const int majorVersion = 1, \
                                       const int minorVersion = 0) \
        { \
            qRegisterMetaType<TYPE>(); \
            qmlRegisterUncreatableType<TYPE>(uri, majorVersion, minorVersion, QML_NAME, ERR_ABSTRACT_BASE); \
        } \
    private:

#define _Q_REGISTER(TYPE, QML_NAME) \
private: QML_NAMED_ELEMENT(QML_NAME) \
public: \
    static inline void qmlRegister(const char * uri, \
                                   const int majorVersion = 1, \
                                   const int minorVersion = 0) \
    { \
        qmlRegisterType<TYPE>(uri, majorVersion, minorVersion, QML_NAME); \
    } \
private:

#define _Q_REGISTER_ABSTRACT(TYPE, QML_NAME) \
private: QML_NAMED_ELEMENT(QML_NAME) \
private: QML_UNCREATABLE(ERR_ABSTRACT_BASE) \
public: \
    static inline void qmlRegister(const char * uri, \
                                   const int majorVersion = 1, \
                                   const int minorVersion = 0) \
    { \
        qmlRegisterUncreatableType<TYPE>(uri, majorVersion, minorVersion, QML_NAME, ERR_ABSTRACT_BASE); \
    } \
private:

#define _Q_REGISTER_ANONYMOUS(TYPE, QML_NAME) \
private: QML_ANONYMOUS \
public: \
    static inline void qmlRegister(const char * uri, \
                                   const int majorVersion = 1, \
                                   const int minorVersion = 0) \
    { \
        qmlRegisterAnonymousType<TYPE>(uri, majorVersion); \
    } \
private:

#define _Q_REGISTER_SINGLETON(TYPE, QML_NAME) \
private: QML_NAMED_ELEMENT(QML_NAME) \
private: QML_SINGLETON \
public: \
    static inline void qmlRegister(const char * uri, \
                                   const int majorVersion = 1, \
                                   const int minorVersion = 0) \
    { \
        qmlRegisterSingletonType<TYPE>(uri, majorVersion, minorVersion, QML_NAME, &TYPE::qmlSingletonProvider); \
    } \
private:

#define _Q_REGISTER_STATIC(TYPE, QML_NAME) \
private: QML_NAMED_ELEMENT(QML_NAME) \
private: QML_SINGLETON \
public: \
    static inline QObject *create_qmlStatic(QQmlEngine *qmlEngine, QJSEngine *jsEngine) \
    { \
        Q_UNUSED(qmlEngine) \
        return new TYPE(jsEngine); \
    } \
    static inline void qmlRegister(const char * uri, \
                                   const int majorVersion = 1, \
                                   const int minorVersion = 0) \
    { \
        qmlRegisterSingletonType<TYPE>(uri, majorVersion, minorVersion, QML_NAME, &TYPE::create_qmlStatic); \
    } \
private:

#define _Q_REGISTER_SINGLETON_INSTANCE(TYPE, QML_NAME) \
private: QML_NAMED_ELEMENT(QML_NAME) \
private: QML_SINGLETON \
public: \
    static inline void qmlRegister(const char * uri, \
                                   const int majorVersion = 1, \
                                   const int minorVersion = 0) \
    { \
        qmlRegisterSingletonInstance<TYPE>(uri, majorVersion, minorVersion, QML_NAME, TYPE::Get()); \
    } \
private:

#define _Q_REGISTER_AT_STARTUP(TYPE, FUNC, MODULE) \
    static inline void registerTypes##FUNC() { \
        TYPE::qmlRegister(MODULE); \
    } \
    Q_COREAPP_STARTUP_FUNCTION(registerTypes##FUNC) \

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Public: use these instead
//---------------------------------------------------------------------------------------------------------------------------------------------------------

#define Q_REGISTER_METATYPE(TYPE)                                           _Q_REGISTER_METATYPE(TYPE, #TYPE)
#define Q_REGISTER_METATYPE_NAMED(TYPE, NAME)                               _Q_REGISTER_METATYPE(TYPE, #NAME)

#define Q_REGISTER_TYPE(TYPE)                                               _Q_REGISTER_TYPE(TYPE, #TYPE)
#define Q_REGISTER_TYPE_NAMED(TYPE, NAME)                                   _Q_REGISTER_TYPE(TYPE, #NAME)

#define Q_REGISTER(TYPE)                                                    _Q_REGISTER(TYPE, #TYPE)
#define Q_REGISTER_NAMED(TYPE, NAME)                                        _Q_REGISTER(TYPE, #NAME)

#define Q_REGISTER_ABSTRACT(TYPE)                                           _Q_REGISTER_ABSTRACT(TYPE, #TYPE)
#define Q_REGISTER_ABSTRACT_NAMED(TYPE, NAME)                               _Q_REGISTER_ABSTRACT(TYPE, #NAME)

#define Q_REGISTER_ANONYMOUS(TYPE)                                          _Q_REGISTER_ANONYMOUS(TYPE, #TYPE)

#define Q_REGISTER_SINGLETON(TYPE)                                          _Q_REGISTER_SINGLETON(TYPE, #TYPE)
#define Q_REGISTER_SINGLETON_NAMED(TYPE, NAME)                              _Q_REGISTER_SINGLETON(TYPE, #NAME)

#define Q_REGISTER_STATIC(TYPE)                                             _Q_REGISTER_STATIC(TYPE, #TYPE)
#define Q_REGISTER_STATIC_NAMED(TYPE, NAME)                                 _Q_REGISTER_STATIC(TYPE, #NAME)

#define Q_REGISTER_SINGLETON_INSTANCE(TYPE)                                 _Q_REGISTER_SINGLETON_INSTANCE(TYPE, #TYPE)
#define Q_REGISTER_SINGLETON_INSTANCE_NAMED(TYPE, NAME)                     _Q_REGISTER_SINGLETON_INSTANCE(TYPE, #NAME)

#define Q_REGISTER_AT_STARTUP(TYPE, MODULE)                                 _Q_REGISTER_AT_STARTUP(TYPE, TYPE, MODULE)

#define Q_REGISTER_METATYPE_NAMED_AT_STARTUP(TYPE, NAME)                    _Q_REGISTER_METATYPE_AT_STARTUP(TYPE, TYPE, #NAME)
#define Q_REGISTER_METATYPE_AT_STARTUP(TYPE)                                _Q_REGISTER_METATYPE_AT_STARTUP(TYPE, TYPE, #TYPE)

#define Q_INIT_MODULE(MODULE, MAJOR, MINOR)       \
    qmlRegisterUncreatableType<QObject>   (MODULE, MAJOR, MINOR, "Module_Object", "Default object for module creation"); \
    qmlRegisterModule(MODULE, MAJOR, MINOR);

struct _QREGISTERDEFS_ { Q_GADGET }; // mock object

#endif // QREGISTERDEFS_H
