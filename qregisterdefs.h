#ifndef QREGISTERDEFS_H
#define QREGISTERDEFS_H

#include <QtQml>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Macros qmlRegisterType
//----------------------------------------------------------------------------------------------------------------------------------------------------------

static const QString ERR_ENUM_CLASS    { QStringLiteral ("Enum-class !") };
static const QString ERR_ATTACHED_OBJ  { QStringLiteral ("Attached-object class !") };
static const QString ERR_ABSTRACT_BASE { QStringLiteral ("Abstract base class !") };

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Private: for declaration purpose
//----------------------------------------------------------------------------------------------------------------------------------------------------------

// qmlRegisterSingletonInstance
#define _Q_REGISTER_SINGLETON_INSTANCE_IMPL(TYPE, FUNC, QML_NAME, MODULE) \
    static void registerSingletonInstance##FUNC() { \
        qmlRegisterSingletonInstance<TYPE>(MODULE, 1,0, QML_NAME, TYPE::Get()); \
    } \
    Q_COREAPP_STARTUP_FUNCTION(registerSingletonInstance##FUNC) \

// qmlRegisterSingletonType
#define _Q_REGISTER_SINGLETON_IMPL(TYPE, FUNC, QML_NAME, MODULE) \
    static void registerSingletonType##FUNC() { \
        qmlRegisterSingletonType<TYPE>(MODULE, 1,0, QML_NAME, TYPE::GetQML); \
    } \
    Q_COREAPP_STARTUP_FUNCTION(registerSingletonType##FUNC) \

// qmlRegisterType
#define _Q_REGISTER_IMPL(TYPE, FUNC, QML_NAME, MODULE) \
    static void registerTypes##FUNC() { \
        qmlRegisterType<TYPE>(MODULE, 1,0, QML_NAME); \
    } \
    Q_COREAPP_STARTUP_FUNCTION(registerTypes##FUNC) \

// qmlRegisterUncreatableType
#define _Q_REGISTER_ABSTRACT_IMPL(TYPE, FUNC, QML_NAME, MODULE) \
    static void registerTypes##FUNC() { \
        qmlRegisterUncreatableType<TYPE>(MODULE, 1,0, QML_NAME, ERR_ABSTRACT_BASE); \
    } \
    Q_COREAPP_STARTUP_FUNCTION(registerTypes##FUNC) \

// qRegisterMetaType
#define _Q_REGISTER_METATYPE_IMPL(TYPE, FUNC, NAME) \
    static void registerNamedMetaType##FUNC() { \
        qRegisterMetaType<TYPE>(NAME); \
    } \
    Q_COREAPP_STARTUP_FUNCTION(registerNamedMetaType##FUNC) \

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Public: use these instead
//---------------------------------------------------------------------------------------------------------------------------------------------------------

#define Q_REGISTER_SINGLETON_INSTANCE_NAMED(TYPE, NAME, MODULE)     _Q_REGISTER_SINGLETON_INSTANCE_IMPL(TYPE, TYPE, #NAME, MODULE)
#define Q_REGISTER_SINGLETON_INSTANCE(TYPE, MODULE)                 _Q_REGISTER_SINGLETON_INSTANCE_IMPL(TYPE, TYPE, #TYPE, MODULE)

#define Q_REGISTER_SINGLETON_NAMED(TYPE, NAME, MODULE)              _Q_REGISTER_SINGLETON_IMPL(TYPE, TYPE, #NAME, MODULE)
#define Q_REGISTER_SINGLETON(TYPE, MODULE)                          _Q_REGISTER_SINGLETON_IMPL(TYPE, TYPE, #TYPE, MODULE)

#define Q_REGISTER_NAMED(TYPE, NAME, MODULE)                        _Q_REGISTER_IMPL(TYPE, TYPE, #NAME, MODULE)
#define Q_REGISTER(TYPE, MODULE)                                    _Q_REGISTER_IMPL(TYPE, TYPE, #TYPE, MODULE)

#define Q_REGISTER_ABSTRACT_NAMED(TYPE, NAME, MODULE)               _Q_REGISTER_ABSTRACT_IMPL(TYPE, TYPE, #NAME, MODULE)
#define Q_REGISTER_ABSTRACT(TYPE, MODULE)                           _Q_REGISTER_ABSTRACT_IMPL(TYPE, TYPE, #TYPE, MODULE)

#define Q_REGISTER_METATYPE_NAMED(TYPE, NAME)                       _Q_REGISTER_METATYPE_IMPL(TYPE, TYPE, #NAME)
#define Q_REGISTER_METATYPE(TYPE)                                   _Q_REGISTER_METATYPE_IMPL(TYPE, TYPE, #TYPE)

struct _QREGISTERDEFS_ { Q_GADGET }; // mock object

#endif // QREGISTERDEFS_H
