#ifndef QPROPERTYDEFS_H
#define QPROPERTYDEFS_H

#include <QObject>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Private: for declaration purpose
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define _Q_PROPERTY_MEMBER_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    VAR_TYPE m_##name=__VA_ARGS__;

#define _Q_PROPERTY_PTR_MEMBER_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    VAR_TYPE m_##name=__VA_ARGS__; \
    VAR_TYPE m_default##Name=__VA_ARGS__;

#define _Q_PROPERTY_GETTER_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    RET_TYPE get##Name (void) const { \
        return m_##name; \
    }

#define _Q_PROPERTY_PTR_GETTER_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    RET_TYPE get##Name (void) const { \
        if(m_##name==nullptr) \
            return m_default##Name; \
        return m_##name; \
    }

#define _Q_ABSTRACT_GETTER_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    virtual RET_TYPE get##Name (void) const = 0;

#define _Q_PROPERTY_SETTER_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    bool set##Name (ARG_TYPE name) { \
        if (m_##name == name && name == m_##name) return false; \
        emit name##AboutToChange (m_##name, name); \
        m_##name = name; \
        emit name##Changed (m_##name); \
        return true; \
    }

#define _Q_PROPERTY_ENU_SETTER_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    bool set##Name (ARG_TYPE name) { \
        if (m_##name == name) return false; \
        emit name##AboutToChange (m_##name, (SIG_TYPE)name); \
        m_##name = (VAR_TYPE)name; \
        emit name##Changed (m_##name); \
        return true; \
    }

#define _Q_PROPERTY_FUZ_SETTER_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    bool set##Name (ARG_TYPE name) { \
        if (qFuzzyCompare(m_##name, name)) return false; \
        m_##name = (VAR_TYPE)name; \
        emit name##Changed (m_##name); \
        return true; \
    }

#define _Q_PROPERTY_NOTIFIER_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    void name##AboutToChange (SIG_TYPE old##Name, SIG_TYPE new##Name); \
    void name##Changed (SIG_TYPE name);

#define _Q_WRITABLE_PROPERTY_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    private: \
    Q_PROPERTY (PROP_TYPE name READ get##Name WRITE set##Name NOTIFY name##Changed FINAL) \
    public:         _Q_PROPERTY_GETTER_IMPL     (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    public Q_SLOTS: _Q_PROPERTY_SETTER_IMPL     (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    Q_SIGNALS:      _Q_PROPERTY_NOTIFIER_IMPL   (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:        _Q_PROPERTY_MEMBER_IMPL     (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:

#define _Q_READONLY_PROPERTY_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    private: \
    Q_PROPERTY (PROP_TYPE name READ get##Name NOTIFY name##Changed FINAL) \
    public:    _Q_PROPERTY_GETTER_IMPL   (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    public:    _Q_PROPERTY_SETTER_IMPL   (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    Q_SIGNALS: _Q_PROPERTY_NOTIFIER_IMPL (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:   _Q_PROPERTY_MEMBER_IMPL   (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:

#define _Q_WRITABLE_PTR_PROPERTY_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    private: \
    Q_PROPERTY (PROP_TYPE name READ get##Name WRITE set##Name NOTIFY name##Changed FINAL) \
    public:         _Q_PROPERTY_PTR_GETTER_IMPL     (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    public Q_SLOTS: _Q_PROPERTY_SETTER_IMPL         (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    Q_SIGNALS:      _Q_PROPERTY_NOTIFIER_IMPL       (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:        _Q_PROPERTY_PTR_MEMBER_IMPL     (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:

#define _Q_READONLY_PTR_PROPERTY_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    private: \
    Q_PROPERTY (PROP_TYPE name READ get##Name NOTIFY name##Changed FINAL) \
    public:    _Q_PROPERTY_PTR_GETTER_IMPL   (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    public:    _Q_PROPERTY_SETTER_IMPL       (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    Q_SIGNALS: _Q_PROPERTY_NOTIFIER_IMPL     (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:   _Q_PROPERTY_PTR_MEMBER_IMPL   (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:

#define _Q_WRITABLE_FUZ_PROPERTY_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    private: \
    Q_PROPERTY (PROP_TYPE name READ get##Name WRITE set##Name NOTIFY name##Changed FINAL) \
    public:         _Q_PROPERTY_GETTER_IMPL       (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    public Q_SLOTS: _Q_PROPERTY_FUZ_SETTER_IMPL   (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    Q_SIGNALS:      _Q_PROPERTY_NOTIFIER_IMPL     (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:        _Q_PROPERTY_MEMBER_IMPL       (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:

#define _Q_READONLY_FUZ_PROPERTY_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    private: \
    Q_PROPERTY (PROP_TYPE name READ get##Name NOTIFY name##Changed FINAL) \
    public:    _Q_PROPERTY_GETTER_IMPL       (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    public:    _Q_PROPERTY_FUZ_SETTER_IMPL   (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    Q_SIGNALS: _Q_PROPERTY_NOTIFIER_IMPL     (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:   _Q_PROPERTY_MEMBER_IMPL       (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:

#define _Q_WRITABLE_ENU_PROPERTY_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    private: \
    Q_PROPERTY (PROP_TYPE name READ get##Name WRITE set##Name NOTIFY name##Changed FINAL) \
    public:         _Q_PROPERTY_GETTER_IMPL         (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    public Q_SLOTS: _Q_PROPERTY_ENU_SETTER_IMPL     (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    Q_SIGNALS:      _Q_PROPERTY_NOTIFIER_IMPL       (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:        _Q_PROPERTY_MEMBER_IMPL         (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:

#define _Q_READONLY_ENU_PROPERTY_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    private: \
    Q_PROPERTY (PROP_TYPE name READ get##Name NOTIFY name##Changed FINAL) \
    public:    _Q_PROPERTY_GETTER_IMPL       (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    public:    _Q_PROPERTY_ENU_SETTER_IMPL   (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    Q_SIGNALS: _Q_PROPERTY_NOTIFIER_IMPL     (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:   _Q_PROPERTY_MEMBER_IMPL       (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:

#define _Q_CONSTANT_PROPERTY_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    private: \
    Q_PROPERTY (PROP_TYPE name READ get##Name CONSTANT FINAL) \
    public:    _Q_PROPERTY_GETTER_IMPL (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    protected: _Q_PROPERTY_MEMBER_IMPL (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:

#define _Q_ABSTRACT_PROPERTY_IMPL(name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, ...) \
    private: \
    Q_PROPERTY (PROP_TYPE name READ get##Name CONSTANT FINAL) \
    public:  _Q_ABSTRACT_GETTER_IMPL (name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE, SIG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Public: use these instead
//----------------------------------------------------------------------------------------------------------------------------------------------------------
                                                                                   // name, Name, VAR_TYPE, PROP_TYPE, ARG_TYPE,     SIG_TYPE,     RET_TYPE,     __VA_ARGS__
#define Q_WRITABLE_VAR_PROPERTY(TYPE, name, Name, ...) _Q_WRITABLE_PROPERTY_IMPL     (name, Name, TYPE,     TYPE,      const TYPE,   const TYPE,   TYPE,         __VA_ARGS__)
#define Q_READONLY_VAR_PROPERTY(TYPE, name, Name, ...) _Q_READONLY_PROPERTY_IMPL     (name, Name, TYPE,     TYPE,      const TYPE,   const TYPE,   TYPE,         __VA_ARGS__)
#define Q_CONSTANT_VAR_PROPERTY(TYPE, name, Name, ...) _Q_CONSTANT_PROPERTY_IMPL     (name, Name, TYPE,     TYPE,      const TYPE,   const TYPE,   TYPE,         __VA_ARGS__)
#define Q_ABSTRACT_VAR_PROPERTY(TYPE, name, Name, ...) _Q_ABSTRACT_PROPERTY_IMPL     (name, Name, TYPE,     TYPE,      const TYPE,   const TYPE,   TYPE,         __VA_ARGS__)

#define Q_WRITABLE_FUZ_PROPERTY(TYPE, name, Name, ...) _Q_WRITABLE_FUZ_PROPERTY_IMPL (name, Name, TYPE,     TYPE,      const TYPE,   const TYPE,   TYPE,         __VA_ARGS__)
#define Q_READONLY_FUZ_PROPERTY(TYPE, name, Name, ...) _Q_READONLY_FUZ_PROPERTY_IMPL (name, Name, TYPE,     TYPE,      const TYPE,   const TYPE,   TYPE,         __VA_ARGS__)
#define Q_CONSTANT_FUZ_PROPERTY(TYPE, name, Name, ...) _Q_CONSTANT_PROPERTY_IMPL     (name, Name, TYPE,     TYPE,      const TYPE,   const TYPE,   TYPE,         __VA_ARGS__)
#define Q_ABSTRACT_FUZ_PROPERTY(TYPE, name, Name, ...) _Q_ABSTRACT_PROPERTY_IMPL     (name, Name, TYPE,     TYPE,      const TYPE,   const TYPE,   TYPE,         __VA_ARGS__)

#define Q_WRITABLE_REF_PROPERTY(TYPE, name, Name, ...) _Q_WRITABLE_PROPERTY_IMPL     (name, Name, TYPE,     TYPE,      const TYPE &, const TYPE &, const TYPE &, __VA_ARGS__)
#define Q_READONLY_REF_PROPERTY(TYPE, name, Name, ...) _Q_READONLY_PROPERTY_IMPL     (name, Name, TYPE,     TYPE,      const TYPE &, const TYPE &, const TYPE &, __VA_ARGS__)
#define Q_CONSTANT_REF_PROPERTY(TYPE, name, Name, ...) _Q_CONSTANT_PROPERTY_IMPL     (name, Name, TYPE,     TYPE,      const TYPE &, const TYPE &, const TYPE &, __VA_ARGS__)
#define Q_ABSTRACT_REF_PROPERTY(TYPE, name, Name, ...) _Q_ABSTRACT_PROPERTY_IMPL     (name, Name, TYPE,     TYPE,      const TYPE &, const TYPE &, const TYPE &, __VA_ARGS__)

#define Q_WRITABLE_PTR_PROPERTY(TYPE, name, Name, ...) _Q_WRITABLE_PTR_PROPERTY_IMPL (name, Name, TYPE*,    TYPE*,     TYPE*,        TYPE*,        TYPE*,        __VA_ARGS__)
#define Q_READONLY_PTR_PROPERTY(TYPE, name, Name, ...) _Q_READONLY_PTR_PROPERTY_IMPL (name, Name, TYPE*,    TYPE*,     TYPE*,        TYPE*,        TYPE*,        __VA_ARGS__)
#define Q_CONSTANT_PTR_PROPERTY(TYPE, name, Name, ...) _Q_CONSTANT_PROPERTY_IMPL     (name, Name, TYPE*,    TYPE*,     TYPE*,        TYPE*,        TYPE*,        __VA_ARGS__)
#define Q_ABSTRACT_PTR_PROPERTY(TYPE, name, Name, ...) _Q_ABSTRACT_PROPERTY_IMPL     (name, Name, TYPE*,    TYPE*,     TYPE*,        TYPE*,        TYPE*,        __VA_ARGS__)

#define Q_WRITABLE_ENU_PROPERTY(TYPE, name, Name, ...) _Q_WRITABLE_ENU_PROPERTY_IMPL (name, Name, TYPE,     int,       int,          TYPE,         TYPE,         __VA_ARGS__)
#define Q_READONLY_ENU_PROPERTY(TYPE, name, Name, ...) _Q_READONLY_ENU_PROPERTY_IMPL (name, Name, TYPE,     int,       int,          TYPE,         TYPE,         __VA_ARGS__)
#define Q_CONSTANT_ENU_PROPERTY(TYPE, name, Name, ...) _Q_CONSTANT_PROPERTY_IMPL     (name, Name, TYPE,     int,       int,          TYPE,         TYPE,         __VA_ARGS__)
#define Q_ABSTRACT_ENU_PROPERTY(TYPE, name, Name, ...) _Q_ABSTRACT_PROPERTY_IMPL     (name, Name, TYPE,     int,       int,          TYPE,         TYPE,         __VA_ARGS__)

#define Q_DEFAULT_PROPERTY(name) \
    private: Q_CLASSINFO ("DefaultProperty", #name)

#if QT_VERSION < 0x050700
template<typename T> const T & qAsConst (const T & arg) {
    return arg;
}
#endif

struct _QPROPERTYDEFS_ { Q_GADGET }; // mock object

#endif // QPROPERTYDEFS_H
