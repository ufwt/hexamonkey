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

#include "compiler/model.h"
#include "core/objecttypetemplate.h"
#include "core/interpreter/fromfileparser.h"
#include "core/interpreter/programloader.h"
#include "core/variable/localscope.h"
#include "core/variable/typescope.h"
#include "core/variable/objectscope.h"
#include "core/util/unused.h"

FromFileParser::FromFileParser(ParsingOption &option, const Module &module, Program classDefinition, Program::const_iterator headerEnd, bool needTailParsing)
    : Parser(option),
      _sharedAccess(new Parser*(this)),
      _scope(new LocalScope(Variable(new ObjectScope(_sharedAccess), true), module), true),
      _headerEnd(headerEnd),
      _evaluator(_scope, module),
      _bodyExecution(classDefinition.node(0), _evaluator, _scope, &object()),
      _tailExecution(classDefinition.node(1), _evaluator, _scope, &object()),
      _needTailParsing(needTailParsing)
{
    UNUSED(hmcElemNames);

    auto bodyBlock = classDefinition.node(0);

    if (constType().fixedSize() == -1 && headerEnd == bodyBlock.begin()) {
        setHeadParsed();
        if(_bodyExecution.done()) {
            setParsed();
        }
    }

    auto tailProgram = classDefinition.node(1);
    if (tailProgram.begin() == tailProgram.end()) {
        setNoTail();
    }
}

FromFileParser::~FromFileParser()
{
    *_sharedAccess = nullptr;
}

void FromFileParser::doParseHead()
{
    int64_t fixedSize = constType().fixedSize();
    if(fixedSize > 0) {
        object().setSize(fixedSize);
    }

    _bodyExecution.execute(_headerEnd);
    if(_bodyExecution.done()) {
        setParsed();
    }
}

void FromFileParser::doParse()
{
    _bodyExecution.execute();
}

bool FromFileParser::doParseSome(int hint)
{
    size_t parseQuota = hint;
    _bodyExecution.execute(parseQuota);
    if(_bodyExecution.done())
        return true;
    return false;
}

void FromFileParser::doParseTail()
{
    _tailExecution.execute();
}

bool FromFileParser::doNeedTailParsing()
{
    return _needTailParsing;
}
