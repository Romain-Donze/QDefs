#ifndef QDEBUGDEFS_H
#define QDEBUGDEFS_H

#include <QDebug>
#include <QString>

#define qTrace QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC,"QtTraceMsg").debug

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Fonctions de debug
//----------------------------------------------------------------------------------------------------------------------------------------------------------

inline void qDebugStart(const QString& title, const QChar& repeat='-')
{
    QString line=QString(100,repeat);

    line.replace(line.size()/2-title.size()/2,title.size(),title);

    qInfo()<<line;
}

inline void qDebugEnd(const QChar& repeat='-')
{
    qDebugStart("",repeat);
}

#endif // QDEBUGDEFS_H
