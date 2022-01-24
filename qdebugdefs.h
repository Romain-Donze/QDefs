#ifndef QDEBUGDEFS_H
#define QDEBUGDEFS_H

#include <QDebug>
#include <QString>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Fonctions de debug
//----------------------------------------------------------------------------------------------------------------------------------------------------------

inline void qDebugStart(const QString& title, const QChar& repeat='-')
{
    QString line=QString(100,repeat);

    line.replace(line.size()/2-title.size()/2,title.size(),title);

    qDebug()<<line;
}

inline void qDebugEnd(const QChar& repeat='-')
{
    qDebugStart("",repeat);
}

#endif // QDEBUGDEFS_H
