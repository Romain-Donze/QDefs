#ifndef QSINGLETONDEFS_H
#define QSINGLETONDEFS_H

#include <QObject>
#include <QMutex>
#include <QQmlEngine>
#include <QJSEngine>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Définition des macros Singleton
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define Q_OBJECT_SINGLETON(cls) \
    public: \
    static cls *Get() \
    { \
        static QMutex mutex; \
        static cls *m_instance=nullptr; \
        if(m_instance==nullptr) \
        { \
            QMutexLocker locker(&mutex); \
            if(m_instance==nullptr) \
            { \
                m_instance = new cls; \
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

#define Q_OBJECT_QML_SINGLETON(cls) \
    Q_OBJECT_SINGLETON(cls) \
    public: \
    static cls *GetQML(QQmlEngine *engine,  QJSEngine *scriptEngine) \
    { \
        Q_UNUSED(engine); \
        Q_UNUSED(scriptEngine); \
        return Get(); \
    } \
    private: \

struct _QSINGLETONDEFS_ { Q_GADGET }; // mock object

#endif // QSINGLETONDEFS_H
