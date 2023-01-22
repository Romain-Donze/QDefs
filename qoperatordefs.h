#ifndef QOPERATORDEFS_H
#define QOPERATORDEFS_H

#include <QObject>

/*
 *
 * Those maccro are available only if operator== and operator< are already implemented
 *
*/

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Private: for declaration purpose
//----------------------------------------------------------------------------------------------------------------------------------------------------------

// When operators are declared outside of the class
#define _Q_DECLARE_OUTSIDE_NOTEQUAL_OPERATOR(TYPE_LEFT, TYPE_RIGHT) \
    inline bool operator!=(const TYPE_LEFT& lhs, const TYPE_RIGHT& rhs) {return !operator==(lhs,rhs);} \

#define _Q_DECLARE_OUTSIDE_LESSTHAN_OPERATOR(TYPE_LEFT, TYPE_RIGHT) \
    inline bool operator> (const TYPE_LEFT& lhs, const TYPE_RIGHT& rhs) {return  operator< (rhs,lhs);} \

#define _Q_DECLARE_OUTSIDE_LESSTHANOREQUAL_OPERATOR(TYPE_LEFT, TYPE_RIGHT) \
    inline bool operator<=(const TYPE_LEFT& lhs, const TYPE_RIGHT& rhs) {return !operator> (lhs,rhs);} \

#define _Q_DECLARE_OUTSIDE_GREATERTHANOREQUAL_OPERATOR(TYPE_LEFT, TYPE_RIGHT) \
    inline bool operator>=(const TYPE_LEFT& lhs, const TYPE_RIGHT& rhs) {return !operator< (lhs,rhs);} \

#define _Q_DECLARE_OUTSIDE_OPERATORS(TYPE_LEFT, TYPE_RIGHT) \
    _Q_DECLARE_OUTSIDE_NOTEQUAL_OPERATOR(TYPE_LEFT, TYPE_RIGHT) \
    _Q_DECLARE_OUTSIDE_LESSTHAN_OPERATOR(TYPE_LEFT, TYPE_RIGHT) \
    _Q_DECLARE_OUTSIDE_LESSTHANOREQUAL_OPERATOR(TYPE_LEFT, TYPE_RIGHT) \
    _Q_DECLARE_OUTSIDE_GREATERTHANOREQUAL_OPERATOR(TYPE_LEFT, TYPE_RIGHT) \

// When operators are declared inside of the class
#define _Q_DECLARE_INSIDE_NOTEQUAL_OPERATOR(TYPE) \
    inline bool operator!=(const TYPE& rhs) const {return !(*this==rhs);} \

#define _Q_DECLARE_INSIDE_LESSTHAN_OPERATOR(TYPE) \
    inline bool operator> (const TYPE& rhs) const {return  (rhs<*this);} \

#define _Q_DECLARE_INSIDE_LESSTHANOREQUAL_OPERATOR(TYPE) \
    inline bool operator<=(const TYPE& rhs) const {return !(*this>rhs);} \

#define _Q_DECLARE_INSIDE_GREATERTHANOREQUAL_OPERATOR(TYPE) \
    inline bool operator>=(const TYPE& rhs) const {return !(*this<rhs);} \

#define _Q_DECLARE_INSIDE_OPERATORS(TYPE) \
    _Q_DECLARE_INSIDE_NOTEQUAL_OPERATOR(TYPE) \
    _Q_DECLARE_INSIDE_LESSTHAN_OPERATOR(TYPE) \
    _Q_DECLARE_INSIDE_LESSTHANOREQUAL_OPERATOR(TYPE) \
    _Q_DECLARE_INSIDE_GREATERTHANOREQUAL_OPERATOR(TYPE) \

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Public: use these instead
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define Q_DECLARE_OUTSIDE_NOTEQUAL_OPERATOR(TYPE)               _Q_DECLARE_OUTSIDE_NOTEQUAL_OPERATOR(TYPE, TYPE)
#define Q_DECLARE_OUTSIDE_LESSTHAN_OPERATOR(TYPE)               _Q_DECLARE_OUTSIDE_LESSTHAN_OPERATOR(TYPE, TYPE)
#define Q_DECLARE_OUTSIDE_LESSTHANOREQUAL_OPERATOR(TYPE)        _Q_DECLARE_OUTSIDE_LESSTHANOREQUAL_OPERATOR(TYPE, TYPE)
#define Q_DECLARE_OUTSIDE_GREATERTHANOREQUAL_OPERATOR(TYPE)     _Q_DECLARE_OUTSIDE_GREATERTHANOREQUAL_OPERATOR(TYPE, TYPE)
#define Q_DECLARE_OUTSIDE_OPERATORS(TYPE)                       _Q_DECLARE_OUTSIDE_OPERATORS(TYPE, TYPE)

#define Q_DECLARE_INSIDE_NOTEQUAL_OPERATOR(TYPE)                _Q_DECLARE_INSIDE_NOTEQUAL_OPERATOR(TYPE)
#define Q_DECLARE_INSIDE_LESSTHAN_OPERATOR(TYPE)                _Q_DECLARE_INSIDE_LESSTHAN_OPERATOR(TYPE)
#define Q_DECLARE_INSIDE_LESSTHANOREQUAL_OPERATOR(TYPE)         _Q_DECLARE_INSIDE_LESSTHANOREQUAL_OPERATOR(TYPE)
#define Q_DECLARE_INSIDE_GREATERTHANOREQUAL_OPERATOR(TYPE)      _Q_DECLARE_INSIDE_GREATERTHANOREQUAL_OPERATOR(TYPE)
#define Q_DECLARE_INSIDE_OPERATORS(TYPE)                        _Q_DECLARE_INSIDE_OPERATORS(TYPE)


#endif // QOPERATORDEFS_H
