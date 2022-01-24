#ifndef QPROPERTYDEFS_H
#define QPROPERTYDEFS_H

#include <QObject>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Private: for declaration purpose
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define _Q_PROPERTY_MEMBER_IMPL(name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, ...) \
    VAR_TYPE m_##name=def;

#define _Q_PROPERTY_GETTER_IMPL(name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, ...) \
    RET_TYPE get##Name (void) const { \
        return m_##name; \
    }

#define _Q_PROPERTY_SETTER_IMPL(name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, ...) \
    bool set##Name (ARG_TYPE name) { \
        if (m_##name == name) return false; \
        m_##name = name; \
        emit name##Changed (m_##name); \
        return true; \
    }

#define _Q_PROPERTY_NOTIFIER_IMPL(name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, ...) \
    void name##Changed (ARG_TYPE name);

#define _Q_WRITABLE_PROPERTY_IMPL(name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, ...) \
    private: \
    Q_PROPERTY (VAR_TYPE name READ get##Name WRITE set##Name NOTIFY name##Changed FINAL __VA_ARGS__) \
    private:        _Q_PROPERTY_MEMBER_IMPL   (name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, __VA_ARGS__) \
    public:         _Q_PROPERTY_GETTER_IMPL   (name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, __VA_ARGS__) \
    public Q_SLOTS: _Q_PROPERTY_SETTER_IMPL   (name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, __VA_ARGS__) \
    Q_SIGNALS:      _Q_PROPERTY_NOTIFIER_IMPL (name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:

#define _Q_READONLY_PROPERTY_IMPL(name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, ...) \
    private: \
    Q_PROPERTY (VAR_TYPE name READ get##Name NOTIFY name##Changed FINAL __VA_ARGS__) \
    private:   _Q_PROPERTY_MEMBER_IMPL   (name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, __VA_ARGS__) \
    public:    _Q_PROPERTY_GETTER_IMPL   (name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, __VA_ARGS__) \
    public:    _Q_PROPERTY_SETTER_IMPL   (name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, __VA_ARGS__) \
    Q_SIGNALS: _Q_PROPERTY_NOTIFIER_IMPL (name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:

#define _Q_CONSTANT_PROPERTY_IMPL(name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, ...) \
    private: \
    Q_PROPERTY (VAR_TYPE name READ get##Name CONSTANT FINAL __VA_ARGS__) \
    private: _Q_PROPERTY_MEMBER_IMPL (name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, __VA_ARGS__) \
    public:  _Q_PROPERTY_GETTER_IMPL (name, Name, def, VAR_TYPE, ARG_TYPE, RET_TYPE, __VA_ARGS__) \
    private:

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Public: use these instead
//----------------------------------------------------------------------------------------------------------------------------------------------------------

#define Q_WRITABLE_VAR_PROPERTY(TYPE, name, Name, def, ...) _Q_WRITABLE_PROPERTY_IMPL(name, Name, def, TYPE, const TYPE, TYPE, __VA_ARGS__)
#define Q_READONLY_VAR_PROPERTY(TYPE, name, Name, def, ...) _Q_READONLY_PROPERTY_IMPL(name, Name, def, TYPE, const TYPE, TYPE, __VA_ARGS__)
#define Q_CONSTANT_VAR_PROPERTY(TYPE, name, Name, def, ...) _Q_CONSTANT_PROPERTY_IMPL(name, Name, def, TYPE, const TYPE, TYPE, __VA_ARGS__)

#define Q_WRITABLE_REF_PROPERTY(TYPE, name, Name, def, ...) _Q_WRITABLE_PROPERTY_IMPL(name, Name, def, TYPE, const TYPE &, const TYPE &, __VA_ARGS__)
#define Q_READONLY_REF_PROPERTY(TYPE, name, Name, def, ...) _Q_READONLY_PROPERTY_IMPL(name, Name, def, TYPE, const TYPE &, const TYPE &, __VA_ARGS__)
#define Q_CONSTANT_REF_PROPERTY(TYPE, name, Name, def, ...) _Q_CONSTANT_PROPERTY_IMPL(name, Name, def, TYPE, const TYPE &, const TYPE &, __VA_ARGS__)

#define Q_WRITABLE_PTR_PROPERTY(TYPE, name, Name, def, ...) _Q_WRITABLE_PROPERTY_IMPL(name, Name, def, TYPE *, TYPE *, TYPE *, __VA_ARGS__)
#define Q_READONLY_PTR_PROPERTY(TYPE, name, Name, def, ...) _Q_READONLY_PROPERTY_IMPL(name, Name, def, TYPE *, TYPE *, TYPE *, __VA_ARGS__)
#define Q_CONSTANT_PTR_PROPERTY(TYPE, name, Name, def, ...) _Q_CONSTANT_PROPERTY_IMPL(name, Name, def, TYPE *, TYPE *, TYPE *, __VA_ARGS__)

#define Q_DEFAULT_PROPERTY(name) \
    private: Q_CLASSINFO ("DefaultProperty", #name)

#if QT_VERSION < 0x050700
template<typename T> const T & qAsConst (const T & arg) {
    return arg;
}
#endif

struct _QPROPERTYDEFS_ { Q_GADGET }; // mock object

#endif // QPROPERTYDEFS_H
