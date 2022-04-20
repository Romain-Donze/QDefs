#ifndef QREGISTERDEFS_H
#define QREGISTERDEFS_H

#include <QDebug>
#include <QtQml>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Macros qmlRegisterType
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define ERR_ENUM_CLASS    "Enum-class !"
#define ERR_ATTACHED_OBJ  "Attached-object class !"
#define ERR_ABSTRACT_BASE "Abstract base class !"

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Private: for declaration purpose
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define _Q_REGISTER_METATYPE_AT_STARTUP(TYPE, FUNC, NAME) \
    static void registerMetaType##FUNC() { \
        _Q_REGISTER_METATYPE(TYPE,NAME); \
    } \
    Q_COREAPP_STARTUP_FUNCTION(registerMetaType##FUNC) \

#define _Q_REGISTER_METATYPE(TYPE, NAME) \
    qRegisterMetaType<TYPE>(NAME); \

#define _Q_REGISTER(TYPE, QML_NAME) \
private: QML_ELEMENT \
public: \
    static void qmlRegister(const char * uri, const int majorVersion, const int minorVersion) { \
            qmlRegisterType<TYPE>(uri, majorVersion, minorVersion, QML_NAME ); \
    } \
private:

#define _Q_REGISTER_ABSTRACT(TYPE, QML_NAME) \
private: QML_ELEMENT \
private: QML_UNCREATABLE(ERR_ABSTRACT_BASE) \
public: \
    static void qmlRegister(const char * uri, const int majorVersion, const int minorVersion) { \
            qmlRegisterUncreatableType<TYPE>(uri, majorVersion, minorVersion, QML_NAME, ERR_ABSTRACT_BASE); \
    } \
private:

#define _Q_REGISTER_SINGLETON(TYPE, QML_NAME) \
private: QML_ELEMENT \
private: QML_SINGLETON \
public: \
    static void qmlRegister(const char * uri, const int majorVersion, const int minorVersion) { \
        qmlRegisterSingletonType<TYPE>(uri, majorVersion, majorVersion, QML_NAME, &TYPE::qmlSingletonProvider); \
    } \
private:

#define _Q_REGISTER_SINGLETON_INSTANCE(TYPE, QML_NAME) \
private: QML_ELEMENT \
private: QML_SINGLETON \
public: \
    static void qmlRegister(const char * uri, const int majorVersion, const int minorVersion) { \
        qmlRegisterSingletonInstance<TYPE>(uri, majorVersion, minorVersion, QML_NAME, TYPE::Get()); \
    } \
private:

#define _Q_REGISTER_AT_STARTUP(TYPE, FUNC, MODULE) \
    static void registerTypes##FUNC() { \
        TYPE::qmlRegister(MODULE, 1, 0); \
    } \
    Q_COREAPP_STARTUP_FUNCTION(registerTypes##FUNC) \

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Public: use these instead
//---------------------------------------------------------------------------------------------------------------------------------------------------------

#define Q_REGISTER_METATYPE(TYPE)                                           _Q_REGISTER_METATYPE(TYPE, #TYPE)
#define Q_REGISTER_METATYPE_NAMED(TYPE, NAME)                               _Q_REGISTER_METATYPE(TYPE, #NAME)

#define Q_REGISTER(TYPE)                                                    _Q_REGISTER(TYPE, #TYPE)
#define Q_REGISTER_NAMED(TYPE, NAME)                                        _Q_REGISTER(TYPE, #NAME)

#define Q_REGISTER_ABSTRACT(TYPE)                                           _Q_REGISTER_ABSTRACT(TYPE, #TYPE)
#define Q_REGISTER_ABSTRACT_NAMED(TYPE, NAME)                               _Q_REGISTER_ABSTRACT(TYPE, #NAME)

#define Q_REGISTER_SINGLETON(TYPE)                                          _Q_REGISTER_SINGLETON(TYPE, #TYPE)
#define Q_REGISTER_SINGLETON_NAMED(TYPE, NAME)                              _Q_REGISTER_SINGLETON(TYPE, #NAME)

#define Q_REGISTER_SINGLETON_INSTANCE(TYPE)                                 _Q_REGISTER_SINGLETON_INSTANCE(TYPE, #TYPE)
#define Q_REGISTER_SINGLETON_INSTANCE_NAMED(TYPE, NAME)                     _Q_REGISTER_SINGLETON_INSTANCE(TYPE, #NAME)

#define Q_REGISTER_AT_STARTUP(TYPE, MODULE)                                 _Q_REGISTER_AT_STARTUP(TYPE, TYPE, MODULE)

#define Q_REGISTER_METATYPE_NAMED_AT_STARTUP(TYPE, NAME)                    _Q_REGISTER_METATYPE_AT_STARTUP(TYPE, TYPE, #NAME)
#define Q_REGISTER_METATYPE_AT_STARTUP(TYPE)                                _Q_REGISTER_METATYPE_AT_STARTUP(TYPE, TYPE, #TYPE)

#define Q_INIT_MODULE(MODULE, MAJOR, MINOR)       \
    qmlRegisterUncreatableType<QObject>   (MODULE, MAJOR, MINOR, MODULE"_Module_Object", "Default object for module creation"); \
    qmlRegisterModule(MODULE, MAJOR, MINOR);

struct _QREGISTERDEFS_ { Q_GADGET }; // mock object

#endif // QREGISTERDEFS_H
