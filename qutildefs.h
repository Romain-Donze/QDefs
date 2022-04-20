#ifndef QUTILDEFS_H
#define QUTILDEFS_H

#include <QObject>
#include <QtMath>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Math methods
//----------------------------------------------------------------------------------------------------------------------------------------------------------

Q_REQUIRED_RESULT static inline Q_DECL_UNUSED bool qFuzzyCompare(double p1, double p2, double precision)
{
    precision = qBound(-10.,precision,10.);
    int val1 = qRound(p1*qPow(10, precision));
    int val2 = qRound(p2*qPow(10, precision));
    return val1 == val2;
}

Q_REQUIRED_RESULT static inline Q_DECL_UNUSED bool qFuzzyIsNull(double d, double precision)
{
    precision = qBound(-10.,precision,10.);
    int val = qRound(d*qPow(10, precision));
    return val == 0;
}

template <typename T>
constexpr inline int qSign(const T &a) { return (a < 0) ? -1 : 1; }

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Math macros
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define ABS(N)        qAbs(N) //(((N)<0)?(-(N)):(N))
#define ROUND(N)      qRound(N)
#define SIGN(N)       qSign(N) //(((N)<0)?(-1):(1))
#define BOUND(N,V,M)  qBound(N,V,M)

#define MIN(N,M)   qMin(N,M) //(((N)<(M))?(N):(M))
#define MAX(N,M)   qMax(N,M) //(((N)>(M))?(N):(M))

struct _QUTILDEFS_ { Q_GADGET }; // mock object

#endif // QUTILDEFS_H
