CONFIG += C++11

SOURCES += \
        $$PWD/object.cpp \
        $$PWD/driver.cpp \
        $$PWD/code.cpp \
        $$PWD/assembly.cpp \
        $$PWD/asmgenerator.cpp \
        $$PWD/asmparser.cpp \
        $$PWD/asmlexer.cpp \
        $$PWD/asmassembler.cpp \
        $$PWD/cdchecker.cpp \
        $$PWD/debugging.cpp \
        $$PWD/asmprinter.cpp \
        $$PWD/asmchecker.cpp


HEADERS += \
        $$PWD/driver.hpp \
        $$PWD/code.hpp \
        $$PWD/assembly.hpp \
        $$PWD/object.hpp \
        $$PWD/stringpool.hpp \
        $$PWD/utilities.hpp \
        $$PWD/asmgenerator.hpp \
        $$PWD/asmparser.hpp \
        $$PWD/asmlexer.hpp \
        $$PWD/asmassembler.hpp \
        $$PWD/cdchecker.hpp \
        $$PWD/format.hpp \
        $$PWD/debugging.hpp \
        $$PWD/asmprinter.hpp \
        $$PWD/asmcheckercontext.hpp \
        $$PWD/asmchecker.hpp \
        $$PWD/strdiagnostics.hpp \
        $$PWD/diagnostics.hpp \
        $$PWD/position.hpp \
        $$PWD/error.hpp \
        $$PWD/stdcharset.hpp \
        $$PWD/charset.hpp \
        $$PWD/layout.hpp \
        $$PWD/asmgeneratorcontext.hpp \
        $$PWD/ieee.hpp \
        $$PWD/indenter.hpp \
        $$PWD/stdlayout.hpp


SOURCES += \
        $$PWD/cdemitter.cpp \
        $$PWD/cdgenerator.cpp \
        $$PWD/dbgconverter.cpp \
        $$PWD/dbgdwarfconverter.cpp

HEADERS += \
        $$PWD/cdemitter.hpp \
        $$PWD/cdgenerator.hpp \
        $$PWD/dbgconverter.hpp \
        $$PWD/dbgconvertercontext.hpp \
        $$PWD/dbgdwarfconverter.hpp
