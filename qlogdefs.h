#ifndef QLOGDEFS_H
#define QLOGDEFS_H

#include <QDebug>
#include <QString>
#include <QStringLiteral>

#define QDEBUG_NO_TRACE

#ifndef QDEBUG_NO_TRACE
#define qTrace QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC,"QtTraceMsg").debug
#else
#define qTrace QMessageLogger().noDebug
#endif

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Fonctions de debug
//----------------------------------------------------------------------------------------------------------------------------------------------------------

Q_GLOBAL_STATIC(QByteArray, qLogLineData)

inline const char* qLogLineMessage(const QString& title, const QChar& repeat='-')
{
    QString line(100,repeat);

    line.replace(line.size()/2-title.size()/2,title.size(),title);

    qLogLineData->clear();
    qLogLineData->append(line);

    return qLogLineData->constData();
}

inline const char* qLogLine(const QChar& repeat='-')
{
    return qLogLineMessage("",repeat);
}

#endif // QLOGDEFS_H
