#ifndef QUTILDEFS_H
#define QUTILDEFS_H

#include <QObject>
#include <QString>
#include <QStringBuilder>
#include <QtMath>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Math methods
//----------------------------------------------------------------------------------------------------------------------------------------------------------

Q_REQUIRED_RESULT static inline Q_DECL_UNUSED double qFuzzyModulo(double p1, double p2, double precision=12)
{
    precision = qBound(-12.,precision,12.);
    qint64 val1 = qRound64(p1*qPow(10, precision));
    qint64 val2 = qRound64(p2*qPow(10, precision));
    return (val1 % val2)/qPow(10, precision);
}

Q_REQUIRED_RESULT static inline Q_DECL_UNUSED bool qFuzzyCompare(double p1, double p2, double precision)
{
    precision = qBound(-12.,precision,12.);
    qint64 val1 = qRound64(p1*qPow(10, precision));
    qint64 val2 = qRound64(p2*qPow(10, precision));
    return val1 == val2;
}

Q_REQUIRED_RESULT static inline Q_DECL_UNUSED bool qFuzzyIsNull(double d, double precision)
{
    precision = qBound(-12.,precision,12.);
    qint64 val = qRound64(d*qPow(10, precision));
    return val == 0;
}

template <typename T>
Q_DECL_CONSTEXPR inline int qSign(const T &a) { return (a < 0) ? -1 : 1; }

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// QString methods
//----------------------------------------------------------------------------------------------------------------------------------------------------------

inline QString hex(long long num, int digits=0) {
    if(digits==0)
        return QStringLiteral("0x") % QString::number(num, 16).toUpper();
    return (QStringLiteral("0x") % QString::number(num, 16).rightJustified(digits, QLatin1Char ('0')).toUpper());
}

inline QString hex(const QByteArray& byteArray) {
    return (QStringLiteral("0x") % byteArray.toHex().toUpper());
}

inline QString bin(long long num, int digits=0) {
    if(digits==0)
        return QStringLiteral("0b") % QString::number(num, 2).toUpper();
    return (QStringLiteral("0b") % QString::number(num, 2).rightJustified (digits, QLatin1Char('0')).toUpper());
}

inline QString bin(const QByteArray& byteArray) {
    QString bin;
    for(char byte: byteArray) {
        bin.append(QString::number(byte, 2).toUpper());
    }
    return (QStringLiteral("0b") % bin);
}

inline QByteArray fromHex(const QString& byteArray) {
    return QByteArray::fromHex(byteArray.toUtf8());
}

inline QString bytes(long long num, int decimals=3) {
    static long long oneByte = 1;
    static long long kiloByte = 1024;
    static long long megaByte = 1048576;
    static long long gigaByte = 1073741824;
    static long long terraByte = 1099511627776;
    static long long pettaByte = 1125899906842624;

    if(num < kiloByte)
        return QString("%1 B").arg((double)num/oneByte,0,'g',decimals);
    if(num < megaByte)
        return QString("%1 KB").arg((double)num/kiloByte,0,'g',decimals);
    if(num < gigaByte)
        return QString("%1 MB").arg((double)num/megaByte,0,'g',decimals);
    if(num < terraByte)
        return QString("%1 GB").arg((double)num/gigaByte,0,'g',decimals);
    if(num < pettaByte)
        return QString("%1 TB").arg((double)num/pettaByte,0,'g',decimals);
    return QString("%1 B").arg(num);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Math macros
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define ABS(N)              qAbs(N) //(((N)<0)?(-(N)):(N))
#define ROUND(N)            qRound(N)
#define SIGN(N)             qSign(N) //(((N)<0)?(-1):(1))
#define BOUND(N,V,M)        qBound(N,V,M)

#define MIN(N,M)            qMin(N,M) //(((N)<(M))?(N):(M))
#define MAX(N,M)            qMax(N,M) //(((N)>(M))?(N):(M))

#define MAX_FLOAT_VAL       std::numeric_limits<float>::max()
#define MAX_DOUBLE_VAL      std::numeric_limits<double>::max()
#define MAX_INT_VAL         std::numeric_limits<int>::max()
#define MAX_UINT_VAL        std::numeric_limits<unsigned int>::max()

#define MIN_FLOAT_VAL       std::numeric_limits<float>::min()
#define MIN_DOUBLE_VAL      std::numeric_limits<double>::min()
#define MIN_INT_VAL         std::numeric_limits<int>::min()
#define MIN_UINT_VAL        std::numeric_limits<unsigned int>::min()

struct _QUTILDEFS_ { Q_GADGET }; // mock object

#endif // QUTILDEFS_H
