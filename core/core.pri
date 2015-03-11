INCLUDEPATH += ..

SOURCES += \
    ../core/variant.cpp \
    ../core/parser.cpp \
    ../core/objecttypetemplate.cpp \
    ../core/objecttype.cpp \
    ../core/object.cpp \
    ../core/moduleloader.cpp \
    ../core/module.cpp \
    ../core/mapmodule.cpp \
    ../core/containerparser.cpp \
    ../core/file/esfragmentedfile.cpp \
    ../core/file/file.cpp \
    ../core/file/psifragmentedfile.cpp \
    ../core/file/fragmentedfile.cpp \
    ../core/file/realfile.cpp \
    ../core/formatdetector/syncbyteformatdetector.cpp \
    ../core/formatdetector/standardformatdetector.cpp \
    ../core/formatdetector/magicformatdetector.cpp \
    ../core/formatdetector/formatdetector.cpp \
    ../core/formatdetector/extensionformatdetector.cpp \
    ../core/formatdetector/compositeformatdetector.cpp \
    ../core/variable/variablepath.cpp \
    ../core/variable/variable.cpp \
    ../core/interpreter/program.cpp \
    ../core/interpreter/programloader.cpp \
    ../core/interpreter/fromfileparser.cpp \
    ../core/interpreter/fromfilemodule.cpp \
    ../core/interpreter/filter.cpp \
    ../core/interpreter/evaluator.cpp \
    ../core/interpreter/blockexecution.cpp \
    ../core/interpreter/scope/typescope.cpp \
    ../core/interpreter/scope/scope.cpp \
    ../core/interpreter/scope/objectscope.cpp \
    ../core/interpreter/scope/localscope.cpp \
    ../core/interpreter/scope/functionscope.cpp \
    ../core/interpreter/scope/compositescope.cpp \
    ../core/interpreter/scope/attributescope.cpp \
    ../core/interpreter/scope/contextscope.cpp \
    ../core/interpreter/scope/constscope.cpp \
    ../core/log/logger.cpp \
    ../core/log/logmanager.cpp \
    ../core/modules/default/tupleparser.cpp \
    ../core/modules/default/fileparser.cpp \
    ../core/modules/default/defaultmodule.cpp \
    ../core/modules/default/arrayparser.cpp \
    ../core/modules/default/dataparser.cpp \
    ../core/modules/default/structparser.cpp \
    ../core/modules/standard/wordparser.cpp \
    ../core/modules/standard/standardmodule.cpp \
    ../core/modules/standard/intparser.cpp \
    ../core/modules/standard/floatparser.cpp \
    ../core/modules/standard/bitparser.cpp \
    ../core/modules/ebml/ebmlsimpleparser.cpp \
    ../core/modules/ebml/ebmlmodule.cpp \
    ../core/modules/ebml/ebmlmasterparser.cpp \
    ../core/modules/ebml/ebmllargeintegerparser.cpp \
    ../core/modules/ebml/ebmldateparser.cpp \
    ../core/modules/ebml/ebmlcontainerparser.cpp \
    ../core/modules/hmc/hmcmodule.cpp \
    ../core/modules/mkv/mkvmodule.cpp \
    ../core/modules/stream/streammodule.cpp \
    ../core/modules/stream/parentpidparser.cpp \
    ../core/util/strutil.cpp \
    ../core/util/iterutil.cpp \
    ../core/util/fileutil.cpp \
    ../core/util/csvreader.cpp \
    ../core/util/bitutil.cpp \
    ../core/util/osutil.cpp \
    ../core/variable/commonvariable.cpp \
    ../core/variable/localscopeimplementation.cpp \
    ../core/variable/objectcontext.cpp \
    ../core/variable/objectattributes.cpp \
    ../core/variable/functionscopeimplementation.cpp \

HEADERS  += \ 
    ../core/variant.h \
    ../core/parser.h \
    ../core/objecttypetemplate.h \
    ../core/objecttype.h \
    ../core/object.h \
    ../core/moduleloader.h \
    ../core/module.h \
    ../core/mapmodule.h \
    ../core/containerparser.h \
    ../core/file/esfragmentedfile.h \
    ../core/file/file.h \
    ../core/file/fragmentedfile.h \
    ../core/file/psifragmentedfile.h \
    ../core/file/realfile.h \
    ../core/formatdetector/syncbyteformatdetector.h \
    ../core/formatdetector/standardformatdetector.h \
    ../core/formatdetector/magicformatdetector.h \
    ../core/formatdetector/formatdetector.h \
    ../core/formatdetector/extensionformatdetector.h \
    ../core/formatdetector/compositeformatdetector.h \
    ../core/variable/variablepath.h \
    ../core/variable/variable.h \
    ../core/interpreter/program.h \
    ../core/interpreter/programloader.h \
    ../core/interpreter/fromfileparser.h \
    ../core/interpreter/fromfilemodule.h \
    ../core/interpreter/filter.h \
    ../core/interpreter/evaluator.h \
    ../core/interpreter/blockexecution.h \
    ../core/interpreter/scope/typescope.h \
    ../core/interpreter/scope/scope.h \
    ../core/interpreter/scope/objectscope.h \
    ../core/interpreter/scope/localscope.h \
    ../core/interpreter/scope/functionscope.h \
    ../core/interpreter/scope/compositescope.h \
    ../core/interpreter/scope/attributescope.h \
    ../core/interpreter/scope/contextscope.h \
    ../core/interpreter/scope/scopeptr.h \
    ../core/interpreter/scope/constscope.h \
    ../core/log/logger.h \
    ../core/log/logmanager.h \
    ../core/modules/default/dataparser.h \
    ../core/modules/default/tupleparser.h \
    ../core/modules/default/fileparser.h \
    ../core/modules/default/defaulttypes.h \
    ../core/modules/default/defaultmodule.h \
    ../core/modules/default/arrayparser.h \
    ../core/modules/default/structparser.h \
    ../core/modules/standard/wordparser.h \
    ../core/modules/standard/standardtypes.h \
    ../core/modules/standard/standardmodule.h \
    ../core/modules/standard/intparser.h \
    ../core/modules/standard/floatparser.h \
    ../core/modules/standard/bitparser.h \
    ../core/modules/ebml/ebmltypes.h \
    ../core/modules/ebml/ebmlsimpleparser.h \
    ../core/modules/ebml/ebmlmodule.h \
    ../core/modules/ebml/ebmlmasterparser.h \
    ../core/modules/ebml/ebmllargeintegerparser.h \
    ../core/modules/ebml/ebmldateparser.h \
    ../core/modules/ebml/ebmlcontainerparser.h \
    ../core/modules/hmc/hmcmodule.h \
    ../core/modules/mkv/mkvtypes.h \
    ../core/modules/mkv/mkvmodule.h \
    ../core/modules/stream/streammodule.h \
    ../core/modules/stream/parentpidparser.h \
    ../core/util/unused.h \
    ../core/util/strutil.h \
    ../core/util/iterutil.h \
    ../core/util/fileutil.h \
    ../core/util/csvreader.h \
    ../core/util/bitutil.h \
    ../core/util/ptrutil.h \
    ../core/util/osutil.h \
    ../core/util/rapidxml/rapidxml_utils.hpp \
    ../core/util/rapidxml/rapidxml_print.hpp \
    ../core/util/rapidxml/rapidxml_iterators.hpp \
    ../core/util/rapidxml/rapidxml.hpp \
    ../compiler/model.h \
    ../core/variable/commonvariable.h \
    ../core/variable/localscopeimplementation.h \
    ../core/variable/objectcontext.h \
    ../core/variable/objectattributes.h \
    ../core/variable/functionscopeimplementation.h \
