#ifndef QSINGLETONDEFS_H
#define QSINGLETONDEFS_H

#include <QObject>
#include <QMutex>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Définition des macros Singleton
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define Q_OBJECT_SINGLETON(cls) \
    public: \
    Q_INVOKABLE static cls *Get() \
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

struct _QSINGLETONDEFS_ { Q_GADGET }; // mock object

#endif // QSINGLETONDEFS_H
