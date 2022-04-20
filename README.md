QDefs
==============

A set of one-line C++ macros to simplify the creation of reccurent things in Qt projects (like Qt Meta Properties) so that doing them in C++ is not harder than in QML, and requires no boilerplate glue-code.

(Exemples must be added)

Installation
------------
1. clone or download this repository
2. add `include  (<path/to/QDefs>/QDefs.pri)` in your `.pro`

### For one-line creation of QML properties

* `Q_WRITABLE_***_PROPERTY` : a macro that takes a type and a name, and creates automatically the member attribute, the public getter and setter, and the Qt signal for notifier, and allow use in QML by exposing a read/write `Q_PROPERTY`.

* `Q_READONLY_***_PROPERTY` : another macro that does almost the same as `Q_WRITABLE_PROPERTY` except that the property is not modifiable from the QML side, only C++ can access the setter.

* `Q_CONSTANT_***_PROPERTY` : a simplified version of the previous macros, that exposes a constant property with only a getter, from C++ or QML side.

* `Q_ABSTRACT_***_PROPERTY` : a simplified version of the previous macros, that exposes a purely virtual constant getter to be override by derrived class.

The `***` can be either `VAR`, `PTR`, `REF`, `ENU` or `FUZ`. The three first are simple macros that you use by simply passing the non-qualified type (`T`) and it'll add the qualifiers for var (none), pointer (`*`), or constant-reference (`const &`) where needed. The fourth one will do the same as `VAR` except it will be casted to `int` in QML -> usefull for properties based on `Q_ENUM_CLASS`. The fifth one will do the same as `VAR` except the comparison in the setter will be donne using `qFuzzyCompare`.

### For simple enum class that can be used in C++ and QML

* `Q_ENUM_CLASS` : a macro to declare a "gadget" struct that only contains a `Q_ENUM` and can be exposed as is to QML. It can be used with very similar syntax from both C++ and QML (`<Name>::<Key>` in C++ vs `<Name>.<Key>` in QML/JS).

### For simple Singleton creation

* `Q_OBJECT_SINGLETON` : a macro that make a Q_OBJECT class singleton (constructor must be declared private manually)

### For simple QML registering

* `Q_REGISTER` : a macro that register a Q_OBJECT class to a QML module

* `Q_REGISTER_ABSTRACT` : a macro that register an abstract Q_OBJECT or Q_GADGET class to a QML module

* `Q_REGISTER_METATYPE_AT_STARTUP` : a macro that register a metatype to QML

* `Q_REGISTER_SINGLETON` : a macro that register a Q_OBJECT singleton instance to a QML module

### For simple C++ time measuring

* `Q_MEASURE_TIME` : a macro that wraps arround a method to measure the time it takes to execute

## License

Well, license here is pretty "super-open"
