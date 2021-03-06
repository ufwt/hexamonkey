#include "structtypetemplate.h"

#include "core/modules/default/structparser.h"

#include "core/module.h"
#include "core/objecttype.h"

StructTypeTemplate::StructTypeTemplate()
    :ObjectTypeTemplate("Struct", {"_name"})
{
}

Parser *StructTypeTemplate::parseOrGetParser(const ObjectType &type, ParsingOption &option) const
{
    auto parser = new StructParser(option);
    for (int i = 0, n = (type.numberOfParameters()-1)/2; i < n; ++i) {
        parser->addElement(type.parameterValue(2*i+1).toObjectType(), type.parameterValue(2*i+2).toString());
    }
    return parser;
}

int64_t StructTypeTemplate::fixedSize(const ObjectType &type) const
{
    int s = 0;
    for (int i = 1; i < type.numberOfParameters(); i += 2) {
        int t = type.parameterValue(i).toObjectType().fixedSize();
        if (t != -1) {
            s += t;
        } else {
            return -1;
        }
    }
    return s;
}

Variant StructTypeTemplate::attributeValue(const ObjectType &type, ObjectTypeTemplate::Attribute attribute) const
{
    if (attribute == ObjectTypeTemplate::Attribute::name) {
        return type.parameterValue(0);
    } else {
        return Variant();
    }
}
