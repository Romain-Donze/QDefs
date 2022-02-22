#ifndef QTIMEDEFS_H
#define QTIMEDEFS_H

#include <QElapsedTimer>
#include <QDebug>

#define timeDebug QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC,"TIME").debug

#define Q_MEASURE_TIME(method) \
    { \
        QElapsedTimer _timer; \
        _timer.start(); \
        method; \
        timeDebug()<<#method<<"took:"<<_timer.nsecsElapsed()/1000000.0<<"ms"; \
    }\

struct _QTIMEDEFS_ { Q_GADGET }; // mock object

#endif // QTIMEDEFS_H
