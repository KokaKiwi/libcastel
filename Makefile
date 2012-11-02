LIBRARY_PARSE    = libCastelParse.a
LIBRARY_BUILD    = libCastelBuild.a
LIBRARY_RUNTIME  = libCastelRuntime.a

CXX              = clang++ -Xclang -fcolor-diagnostics
AR               = ar
RANLIB           = ranlib
RAGEL            = ragel
LEMON            = lemon
MKDIR            = mkdir
MV               = mv
RM               = rm

SRCS_PARSE       = $(shell (find sources/lexer sources/parser \( -name '*.cc' -a -not -name '.*' -a -not -path sources/parser/parse.cc \) ; echo sources/lexer/Lexer.cc) | sort | uniq)
HDRS_PARSE       = $(shell (find includes/castel/lexer includes/castel/parser includes/castel/ast \( -name '*.hh' -a -not -name '.*' \) ; echo includes/castel/lexer/MangledLexemesTypes.hh) | sort | uniq)
DEPS_PARSE       = $(addprefix build/dependencies/,$(SRCS_PARSE:.cc=.d))
OBJS_PARSE       = $(addprefix build/objects/,$(SRCS_PARSE:.cc=.o))

SRCS_BUILD       = $(shell (find sources/builder \( -name '*.cc' -a -not -name '.*' \) ) | sort | uniq)
HDRS_BUILD       = $(shell (find includes/castel/builder \( -name '*.hh' -a -not -name '.*' \) ) | sort | uniq)
DEPS_BUILD       = $(addprefix build/dependencies/,$(SRCS_BUILD:.cc=.d))
OBJS_BUILD       = $(addprefix build/objects/,$(SRCS_BUILD:.cc=.o))

SRCS_RUNTIME     = $(shell (find sources/runtime \( -name '*.cc' -a -not -name '.*' \) ) | sort | uniq)
HDRS_RUNTIME     = $(shell (find includes/castel/runtime \( -name '*.hh' -a -not -name '.*' \) ) | sort | uniq)
DEPS_RUNTIME     = $(addprefix build/dependencies/,$(SRCS_RUNTIME:.cc=.d))
OBJS_RUNTIME     = $(addprefix build/objects/,$(SRCS_RUNTIME:.cc=.o))

PURPLE           = $(shell printf "\033[35m")
CYAN             = $(shell printf "\033[36m")
GREEN            = $(shell printf "\033[32m")
BROWN            = $(shell printf "\033[33m")
EOS              = $(shell printf "\033[00m")

override CXXFLAGS += -fPIC -std=c++11 -I./includes -I.

CXXFLAGS_PARSE   = $(CXXFLAGS) -g
CXXFLAGS_BUILD   = $(CXXFLAGS) -g $(shell llvm-config --cppflags)
CXXFLAGS_RUNTIME = $(CXXFLAGS) -g

all: $(LIBRARY_PARSE) $(LIBRARY_BUILD) $(LIBRARY_RUNTIME)
	@printf "Compilation done.\n"

$(LIBRARY_PARSE): build/$(LIBRARY_PARSE)
$(LIBRARY_BUILD): build/$(LIBRARY_BUILD)
$(LIBRARY_RUNTIME): build/$(LIBRARY_RUNTIME)

-include $(DEPS_PARSE) $(DEPS_BUILD) $(DEPS_RUNTIME)

build/$(LIBRARY_PARSE): $(OBJS_PARSE) includes/castel/lexer/MangledLexemesTypes.hh
	@test -t && printf "%s# Merging object files for $(LIBRARY_PARSE).%s\n" "$(PURPLE)" "$(EOS)"
	@$(RM) -f build/$(LIBRARY_PARSE)
	@$(AR) rcs build/$(LIBRARY_PARSE) $(OBJS_PARSE)
	@$(RANLIB) build/$(LIBRARY_PARSE)

build/$(LIBRARY_BUILD): $(OBJS_BUILD)
	@test -t && printf "%s# Merging object files for $(LIBRARY_BUILD).%s\n" "$(PURPLE)" "$(EOS)"
	@$(RM) -f build/$(LIBRARY_BUILD)
	@$(AR) rcs build/$(LIBRARY_BUILD) $(OBJS_BUILD)
	@$(RANLIB) build/$(LIBRARY_BUILD)

build/$(LIBRARY_RUNTIME): $(OBJS_RUNTIME)
	@test -t && printf "%s# Merging object files for $(LIBRARY_RUNTIME).%s\n" "$(PURPLE)" "$(EOS)"
	@$(RM) -f build/$(LIBRARY_RUNTIME)
	@$(AR) rcs build/$(LIBRARY_RUNTIME) $(OBJS_RUNTIME)
	@$(RANLIB) build/$(LIBRARY_RUNTIME)

sources/lexer/Lexer.cc: sources/lexer/Lexer.rl
	@test -t && printf "%s+ Generating ragel castel lexer.%s\n" "$(CYAN)" "$(EOS)"
	@$(RAGEL) -C -o sources/lexer/Lexer.cc sources/lexer/Lexer.rl

includes/castel/lexer/MangledLexemesTypes.hh sources/parser/parse.cc: sources/parser/parse.lm
	@test -t && printf "%s@ Generating lemon castel parser.%s\n" "$(CYAN)" "$(EOS)"
	@$(LEMON) sources/parser/parse.lm
	@$(RM) sources/parser/parse.out
	@$(MV) sources/parser/parse.h includes/castel/lexer/MangledLexemesTypes.hh
	@$(MV) sources/parser/parse.c sources/parser/parse.cc

$(DEPS_PARSE): build/dependencies/%.d: %.cc | includes/castel/lexer/MangledLexemesTypes.hh sources/parser/parse.cc
	@test -t && printf "%s+ Generating dependency file for %s.%s\n" "$(GREEN)" "$(<)" "$(EOS)"
	@$(MKDIR) -p "$(dir $(@))"
	@$(CXX) $(CXXFLAGS_PARSE) -MM -MG -MT "$(patsubst build/dependencies/%,build/objects/%,$(@:.d=.o))" "$(<)" > $(@)

$(DEPS_BUILD): build/dependencies/%.d: %.cc | includes/castel/lexer/MangledLexemesTypes.hh sources/parser/parse.cc
	@test -t && printf "%s+ Generating dependency file for %s.%s\n" "$(GREEN)" "$(<)" "$(EOS)"
	@$(MKDIR) -p "$(dir $(@))"
	@$(CXX) $(CXXFLAGS_BUILD) -MM -MG -MT "$(patsubst build/dependencies/%,build/objects/%,$(@:.d=.o))" "$(<)" > $(@)

$(DEPS_RUNTIME): build/dependencies/%.d: %.cc | includes/castel/lexer/MangledLexemesTypes.hh sources/parser/parse.cc
	@test -t && printf "%s+ Generating dependency file for %s.%s\n" "$(GREEN)" "$(<)" "$(EOS)"
	@$(MKDIR) -p "$(dir $(@))"
	@$(CXX) $(CXXFLAGS_RUNTIME) -MM -MG -MT "$(patsubst build/dependencies/%,build/objects/%,$(@:.d=.o))" "$(<)" > $(@)

$(OBJS_PARSE): build/objects/%.o: %.cc
	@test -t && printf "%s+ Compiling %s.%s\n" "$(GREEN)" "$(<)" "$(EOS)"
	@$(MKDIR) -p "$(dir $(@))"
	@$(CXX) $(CXXFLAGS_PARSE) -c -o "$(@)" "$(<)"

$(OBJS_BUILD): build/objects/%.o: %.cc
	@test -t && printf "%s+ Compiling %s.%s\n" "$(GREEN)" "$(<)" "$(EOS)"
	@$(MKDIR) -p "$(dir $(@))"
	@$(CXX) $(CXXFLAGS_BUILD) -c -o "$(@)" "$(<)"

$(OBJS_RUNTIME): build/objects/%.o: %.cc
	@test -t && printf "%s+ Compiling %s.%s\n" "$(GREEN)" "$(<)" "$(EOS)"
	@$(MKDIR) -p "$(dir $(@))"
	@$(CXX) $(CXXFLAGS_RUNTIME) -c -o "$(@)" "$(<)"

clean:
	@test -t && printf "%s- Removing temporary files.%s\n" "$(BROWN)" "$(EOS)"
	@$(RM) -rf build/generated
	@$(RM) -rf build/objects
	@$(RM) -f includes/castel/lexer/MangledLexemesTypes.hh
	@$(RM) -f sources/lexer/Lexer.cc
	@$(RM) -f sources/parser/parse.cc

clean-dependencies:
	@test -t && printf "%s- Removing dependencies listing.%s\n" "$(BROWN)" "$(EOS)"
	@$(RM) -rf build/dependencies

fclean: clean
	@test -t && printf "%s- Removing binary files.%s\n" "$(BROWN)" "$(EOS)"
	@$(RM) -rf build/$(LIBRARY_PARSE)
	@$(RM) -rf build/$(LIBRARY_BUILD)
	@$(RM) -rf build/$(LIBRARY_RUNTIME)

re: clean-dependencies fclean
	@$(MAKE) --no-print-directory all

check-syntax:
	@$(MAKE) CXXFLAGS=-fsyntax-only -W $(patsubst %_flymake.cc,%.cc,$(CHK_SOURCES)) $(patsubst %_flymake.cc,build/objects/%.o,$(CHK_SOURCES))

.PHONY: $(LIBRARY_PARSE) $(LIBRARY_BUILD) $(LIBRARY_RUNTIME) all clean fclean re clean-depends check-syntax libcastel
