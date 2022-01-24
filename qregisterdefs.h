#ifndef QREGISTERDEFS_H
#define QREGISTERDEFS_H

#include <QtQml>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Macros qmlRegisterType
//----------------------------------------------------------------------------------------------------------------------------------------------------------

static const QString ERR_ENUM_CLASS    { QStringLiteral ("Enum-class !") };
static const QString ERR_ATTACHED_OBJ  { QStringLiteral ("Attached-object class !") };
static const QString ERR_ABSTRACT_BASE { QStringLiteral ("Abstract base class !") };

// qmlRegisterSingletonType
#define Q_REGISTER_SINGLETON(cls, qmlName, impName) \
static void registerSingletonTypes##cls() { \
    qmlRegisterSingletonInstance<cls>(impName, 1,0, qmlName, cls::Get()); \
} \
Q_COREAPP_STARTUP_FUNCTION(registerSingletonTypes##cls) \

// qmlRegisterType
#define Q_REGISTER(cls, qmlName, impName) \
static void registerTypes##cls() { \
    qmlRegisterType<cls>(impName, 1,0, qmlName); \
} \
Q_COREAPP_STARTUP_FUNCTION(registerTypes##cls) \

// qmlRegisterUncreatableType
#define Q_REGISTER_ABSTRACT(cls, qmlName, impName) \
static void registerTypes##cls() { \
    qmlRegisterUncreatableType<cls>(impName, 1,0, qmlName, ERR_ABSTRACT_BASE); \
} \
Q_COREAPP_STARTUP_FUNCTION(registerTypes##cls) \

// qRegisterMetaType
#define Q_REGISTER_METATYPE(cls, name) \
static void registerMetaType##cls() { \
    qRegisterMetaType<cls>(name); \
} \
Q_COREAPP_STARTUP_FUNCTION(registerMetaType##cls) \

struct _QREGISTERDEFS_ { Q_GADGET }; // mock object

#endif // QREGISTERDEFS_H
