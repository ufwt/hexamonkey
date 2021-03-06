#include "objectscope.h"

#include "core/log/logmanager.h"

#include "core/object.h"

#include "core/variable/typescope.h"
#include "core/variable/variablecollector.h"
#include "core/objecttypetemplate.h"
#include "core/variable/parserscope.h"

#define A_SIZE 0
#define A_PARENT 1
#define A_ROOT 2
#define A_VALUE 3
#define A_RANK 4
#define A_POS 5
#define A_REM 6
#define A_NUMBER_OF_CHILDREN 7
#define A_BEGINNING_POS 8
#define A_LINK_TO 9
#define A_ATTR 10
#define A_CONTEXT 11
#define A_GLOBAL 12
#define A_ENDIANNESS 13
#define A_ABS_POS 14
#define A_TYPE 15
#define A_ARGS 16
#define A_PARSER 17

const std::unordered_map<std::string, int> reserved = {
    {"@size",             A_SIZE},
    {"@value",            A_VALUE},
    {"@parent",           A_PARENT},
    {"@root",             A_ROOT},
    {"@rank",             A_RANK},
    {"@pos",              A_POS},
    {"@rem",              A_REM},
    {"@numberOfChildren", A_NUMBER_OF_CHILDREN},
    {"@beginningPos",     A_BEGINNING_POS},
    {"@linkTo",           A_LINK_TO},
    {"@attr",             A_ATTR},
    {"@context",          A_CONTEXT},
    {"@global",           A_GLOBAL},
    {"@endianness",       A_ENDIANNESS},
    {"@absPos",           A_ABS_POS},
    {"@type",             A_TYPE},
    {"@args",             A_ARGS},
    {"@parser",           A_PARSER}
};

class ObjectPosVariableImplementation : public VariableImplementation
{
public:
    ObjectPosVariableImplementation(Object& object)
        : VariableImplementation(object.collector()),
          _object(object) {}

protected:
    virtual void doSetValue(const Variant& value) override {
        if (value.hasNumericalType()) {
            _object.setPos(value.toInteger());
        } else {
            Log::warning("Trying to set a non numerical value for a pos");
        }
    }

    virtual Variant doGetValue() override {
        return Variant((long long) _object.pos());
    }
private:
    Object& _object;
};

class ObjectAbsPosVariableImplementation : public VariableImplementation
{
public:
    ObjectAbsPosVariableImplementation(Object& object)
        : VariableImplementation(object.collector()),
          _object(object)
    {

    }

protected:
    virtual void doSetValue(const Variant& value) override {
        if (value.hasNumericalType()) {
            _object.setPos(value.toInteger() - _object.beginningPos());
        } else {
            Log::warning("Trying to set a non numerical value for a pos");
        }
    }

    virtual Variant doGetValue() override {
        return Variant(_object.beginningPos() + (long long) _object.pos());
    }
private:
    Object& _object;
};

class ObjectSizeVariableImplementation : public VariableImplementation
{
public:
    ObjectSizeVariableImplementation(Object& object)
        : VariableImplementation(object.collector()),
          _object(object)
    {

    }

protected:
    virtual void doSetValue(const Variant& value) override {
        if (value.hasNumericalType()) {
            _object.setSize(value.toInteger());
        } else {
            Log::warning("Trying to set a non numerical value for a size");
        }
    }

    virtual Variant doGetValue() override {
        return Variant((long long) _object.size());
    }
private:
    Object& _object;
};

class ObjectLinkToVariableImplementation : public VariableImplementation
{
public:
    ObjectLinkToVariableImplementation(Object& object)
        : VariableImplementation(object.collector()),
          _object(object)
    {

    }

protected:
    virtual void doSetValue(const Variant& value) override {
        if (value.hasNumericalType()) {
            _object.setLinkTo(value.toInteger());
        } else if (value.isNull()) {
            _object.removeLinkTo();
        } else {
            Log::warning("Trying to set a non numerical value for a linkTo");
        }
    }

    virtual Variant doGetValue() override {
        return _object.hasLinkTo() ? Variant((long long) _object.linkTo()) : Variant();
    }
private:
    Object& _object;
};

class ObjectEndiannessVariableImplementation : public VariableImplementation
{
public:
    ObjectEndiannessVariableImplementation(Object& object)
        : VariableImplementation(object.collector()),
          _object(object)
    {

    }

protected:
    virtual void doSetValue(const Variant& value) override {
        if (value.type() == Variant::stringType) {
            switch (value.toString()[0]) {
                case 'b':
                    _object.setEndianness(Object::bigEndian);
                    break;

                case 'l':
                    _object.setEndianness(Object::littleEndian);
                    break;

                default:
                    Log::warning("Trying to set an invalid value for endianness, the acceptable value are \"bigEndian\" and \"littleEndian\"");

            }
        } else {
            Log::warning("Trying to set a non string value for endianness, the acceptable value are \"bigEndian\" and \"littleEndian\"");
        }
    }

    virtual Variant doGetValue() override {
        switch (_object.endianness()) {
            case Object::bigEndian:
                return Variant("bigEndian");

            case Object::littleEndian:
                return Variant("littleEndian");
        }
        return Variant();
    }
private:
    Object& _object;
};


ObjectScope::ObjectScope(Object &object)
    : VariableImplementation(object.collector()),
      _object(object)
{
}

ObjectScope::ObjectScope(std::shared_ptr<Parser *> sharedParserAccess)
    : VariableImplementation((*sharedParserAccess)->object().collector()),
      _object((*sharedParserAccess)->object()),
      _sharedType((*sharedParserAccess)->sharedType()),
      _sharedParserAccess(sharedParserAccess),
      _parserScope(Variable(new ParserTypeScope(**sharedParserAccess), true))
{
}

void ObjectScope::collect(const VariableAdder &addAccessible)
{
    addAccessible(_parserScope);
}

Variable ObjectScope::doGetField(const Variant &key, bool /*modifiable*/, bool createIfNeeded)
{
    if (key.isValueless()) {

        int numberOfChildren = _object.numberOfChildren();
        if (numberOfChildren > 0) {
            Object* elem = _object.access(numberOfChildren - 1, true);
            if(elem != nullptr) {
                return elem->variable();
            } else {
                return Variable();
            }
        } else {
            return Variable();
        }

    } else if (key.type() == Variant::stringType) {

        const std::string& name = key.toString();
        if (name[0] == '@')
        {
            auto it = reserved.find(name);
            if (it == reserved.end()) {
                return Variable();
            } else {

                switch (it->second) {
                    case A_SIZE:
                        return Variable(new ObjectSizeVariableImplementation(_object), true);

                    case A_VALUE:
                        return collector().ref(_object.value());

                    case A_PARENT:
                    {
                        Object* parent = _object.parent();

                        if (parent != nullptr) {
                            return parent->variable();
                        } else {
                            return Variable();
                        }
                    }

                    case A_ROOT:
                        return _object.root().variable();

                    case A_RANK:
                        return collector().copy(_object.rank());

                    case A_POS:
                        return Variable(new ObjectPosVariableImplementation(_object), true);

                    case A_ABS_POS:
                        return Variable(new ObjectAbsPosVariableImplementation(_object), true);

                    case A_REM:
                        return collector().copy(_object.size() - _object.pos());

                    case A_NUMBER_OF_CHILDREN:
                        _object.explore(1);
                        return collector().copy(_object.numberOfChildren());

                    case A_BEGINNING_POS:
                        return collector().copy((long long) _object.beginningPos());

                    case A_LINK_TO:
                        return Variable(new ObjectLinkToVariableImplementation(_object), true);

                    case A_ATTR:
                        return _object.attributesVariable(createIfNeeded);

                    case A_CONTEXT:
                        return _object.contextVariable(createIfNeeded);

                    case A_GLOBAL:
                        return _object.root().contextVariable(createIfNeeded);

                    case A_ENDIANNESS:
                        return Variable(new ObjectEndiannessVariableImplementation(_object), true);

                    case A_TYPE:
                        return Variable(new TypeScope(collector(), _object.type()), false);

                    case A_ARGS:
                        return _parserScope;

                    case A_PARSER:
                        if (_sharedParserAccess) {
                            return Variable(new ParserScope(collector(), _sharedParserAccess), false);
                        } else {
                            return Variable();
                        }

                    default:
                        return Variable();
                }
            }
        } else {
            if (_sharedType) {
                Object* elem = _object.lookUp(name, false);
                if (elem != nullptr) {
                    return elem->variable();
                } else {
                    const ObjectType& type = _sharedType->first ?
                                                 _sharedType->second
                                               : _object.type();
                    int parameterIndex = type.typeTemplate().parameterNumber(name);
                    if (parameterIndex != -1) {
                        return collector().copy(type.parameterValue(parameterIndex));
                    } else {
                        return Variable();
                    }
                }
            } else {
                Object* elem = _object.lookUp(name, true);
                if (elem != nullptr) {
                    return elem->variable();
                } else {
                    return Variable();
                }
            }
        }

    } else if (key.hasNumericalType()) {

        Object* elem = _object.access(key.toInteger(), true);
        if (elem != nullptr) {
            return elem->variable();
        } else {
            return Variable();
        }

    } else if (key.type() == Variant::objectType) {

        Object* elem = _object.lookForType(key.toObjectType(), true);
        if (elem != nullptr) {
            return elem->variable();
        } else {
            return Variable();
        }

    } else {
        return Variable();
    }
}

void ObjectScope::doSetValue(const Variant &value)
{
    _object.setValue(value);
}

Variant ObjectScope::doGetValue()
{
    return _object.value();
}
