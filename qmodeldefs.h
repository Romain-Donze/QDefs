#ifndef QMODELDEFS_H
#define QMODELDEFS_H

#include "qobjectlistmodel.h"
#include "qregisterdefs.h"

#define Q_DECLARE_OBJECT_MODEL(ModelName, ObjectName) \
    class ModelName : public QObjectListModel<ObjectName> { \
    Q_OBJECT \
    Q_REGISTER(ModelName) \
    public: ModelName(QObject* parent = nullptr):QObjectListModel<ObjectName>(parent){} }; \

#endif // QMODELDEFS_H
