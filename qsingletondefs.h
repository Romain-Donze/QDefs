#ifndef QSINGLETONDEFS_H
#define QSINGLETONDEFS_H

#include <QObject>
#include <QMutex>
#include <QQmlEngine>
#include <QJSEngine>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Private: for declaration purpose
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define _Q_OBJECT_SINGLETON_IMPL(TYPE) \
    public: \
    static TYPE *Get() \
    { \
        static QMutex mutex; \
        static TYPE *m_instance=nullptr; \
        if(m_instance==nullptr) \
        { \
            QMutexLocker locker(&mutex); \
            if(m_instance==nullptr) \
            { \
                m_instance = new TYPE; \
                if(qobject_cast<QObject*>(m_instance)) \
                { \
                    m_instance->setParent(nullptr); \
                    QQmlEngine::setObjectOwnership(m_instance, QQmlEngine::CppOwnership); \
                } \
            } \
        } \
        return m_instance; \
    } \
    private: \

#define _Q_OBJECT_QML_SINGLETON_IMPL(TYPE) \
    _Q_OBJECT_SINGLETON_IMPL(TYPE) \
    public: \
    static QObject *qmlSingletonProvider(QQmlEngine *engine,  QJSEngine *scriptEngine) \
    { \
        Q_UNUSED(engine); \
        Q_UNUSED(scriptEngine); \
        return Get(); \
    } \
    private: \

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Public: use these instead
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define Q_OBJECT_SINGLETON(TYPE)            _Q_OBJECT_SINGLETON_IMPL(TYPE)
#define Q_OBJECT_QML_SINGLETON(TYPE)        _Q_OBJECT_QML_SINGLETON_IMPL(TYPE)

struct _QSINGLETONDEFS_ { Q_GADGET }; // mock object

#endif // QSINGLETONDEFS_H
