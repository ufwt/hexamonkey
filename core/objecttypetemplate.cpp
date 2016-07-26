//This file is part of the HexaMonkey project, a multimedia analyser
//Copyright (C) 2013  Sevan Drapeau-Martin, Nicolas Fleury

//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include "core/objecttypetemplate.h"
#include "core/objecttype.h"


ObjectTypeTemplate::ObjectTypeTemplate(const std::string &name,
                                       const std::vector<std::string> &parameterNames,
                                       const std::function<void (ObjectTypeTemplate&)> initialization)
    : ObjectTypeTemplate(name, parameterNames)

{
    initialization(*this);
}

ObjectTypeTemplate::ObjectTypeTemplate(const std::string &name, const std::vector<std::string> &parameterNames)
    :_name(name),
      _parametersNames(parameterNames),
      _virtual(false)

{
    for(unsigned int i = 0; i < _parametersNames.size(); ++i)
    {
        _parametersNumbers[_parametersNames[i]] = i;
    }
}

ObjectTypeTemplate::ObjectTypeTemplate(const std::string& name)
    : ObjectTypeTemplate(name, std::vector<std::string>())
{
}

bool ObjectTypeTemplate::isParameterPrivate(int index) const
{
    const std::string& name = parameterName(index);
    return !name.empty() && name[0] == '_';
}

int ObjectTypeTemplate::parameterNumber(const std::string &name) const
{
    const auto it = _parametersNumbers.find(name);
    if(it != _parametersNumbers.end())
        return it->second;
    return -1;
}

bool ObjectTypeTemplate::isNull() const
{
    return _name.empty();
}

void ObjectTypeTemplate::addParameter(const std::string& parameterName)
{
    _parametersNames.push_back(parameterName);
}

bool ObjectTypeTemplate::isVirtual() const
{
    return _virtual;
}

void ObjectTypeTemplate::setVirtual(bool value)
{
    _virtual = value;
}

bool operator==(const ObjectTypeTemplate& a, const ObjectTypeTemplate& b)
{
    return &a == &b;
}

bool operator!=(const ObjectTypeTemplate& a, const ObjectTypeTemplate& b)
{
    return &a != &b;
}

bool operator< (const ObjectTypeTemplate& a, const ObjectTypeTemplate& b)
{
    return &a < &b;
}

bool operator<= (const ObjectTypeTemplate& a, const ObjectTypeTemplate& b)
{
    return &a <= &b;
}

ObjectTypeTemplate _nullTypeTemplate("");
const ObjectTypeTemplate& ObjectTypeTemplate::nullTypeTemplate = _nullTypeTemplate;


Parser *ObjectTypeTemplate::parseOrGetParser(const ObjectType &, ParsingOption &) const
{
    return nullptr;
}

int64_t ObjectTypeTemplate::fixedSize(const ObjectType &) const
{
    return unknownSize;
}

Variant ObjectTypeTemplate::attributeValue(const ObjectType &, ObjectTypeTemplate::Attribute) const
{
    return Variant();
}

std::shared_ptr<ObjectType> nullParent(new ObjectType);

std::shared_ptr<ObjectType> ObjectTypeTemplate::parent(const ObjectType &) const
{
    return nullParent;
}
