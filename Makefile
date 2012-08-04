LIBRARY_PARSE    = libCastelParse.a
LIBRARY_ENGINE   = libCastelEngine.a
LIBRARY_RUNTIME  = libCastelRuntime.a

CXX              = clang++
AR               = ar
RAGEL            = ragel
LEMON            = lemon
MKDIR            = mkdir
MV               = mv
RM               = rm

SRCS_PARSE       = $(shell (find sources/lexer sources/parser -name '*.cc' ; echo sources/lexer/Lexer.cc) | sort | uniq)
HDRS_PARSE       = $(shell (find includes/castel/lexer includes/castel/parser includes/castel/ast -name '*.hh' ; echo includes/castel/lexer/MangledLexemesTypes.hh) | sort | uniq)
DEPS_PARSE       = $(addprefix build/dependencies/,$(SRCS_PARSE:.cc=.d))
OBJS_PARSE       = $(addprefix build/objects/,$(SRCS_PARSE:.cc=.o))

SRCS_ENGINE      = $(shell (find sources/engine -name '*.cc') | sort | uniq)
HDRS_ENGINE      = $(shell (find includes/castel/engine -name '*.hh') | sort | uniq)
DEPS_ENGINE      = $(addprefix build/dependencies/,$(SRCS_ENGINE:.cc=.d))
OBJS_ENGINE      = $(addprefix build/objects/,$(SRCS_ENGINE:.cc=.o))

SRCS_RUNTIME     = $(shell (find sources/runtime -name '*.cc') | sort | uniq)
HDRS_RUNTIME     = $(shell (find includes/castel/runtime -name '*.hh') | sort | uniq)
DEPS_RUNTIME     = $(addprefix build/dependencies/,$(SRCS_RUNTIME:.cc=.d))
OBJS_RUNTIME     = $(addprefix build/objects/,$(SRCS_RUNTIME:.cc=.o))

PURPLE           = $(shell printf "\033[35m")
CYAN             = $(shell printf "\033[36m")
GREEN            = $(shell printf "\033[32m")
BROWN            = $(shell printf "\033[33m")
EOS              = $(shell printf "\033[00m")

CXXFLAGS         = -fPIC -std=c++11 -I./includes -I.
CXXFLAGS_PARSE   = $(CXXFLAGS) -g -O0
CXXFLAGS_ENGINE  = $(CXXFLAGS) $(shell llvm-config --cxxflags) -fexceptions -g -O0
CXXFLAGS_RUNTIME = $(CXXFLAGS) -g -O0

all: $(LIBRARY_PARSE) $(LIBRARY_ENGINE) $(LIBRARY_RUNTIME)
	@printf "Compilation done.\n"

$(LIBRARY_PARSE): build/$(LIBRARY_PARSE)
$(LIBRARY_ENGINE): build/$(LIBRARY_ENGINE)
$(LIBRARY_RUNTIME): build/$(LIBRARY_RUNTIME)

-include $(DEPS_PARSE) $(DEPS_ENGINE) $(DEPS_RUNTIME)

build/$(LIBRARY_PARSE): $(OBJS_PARSE) includes/castel/lexer/MangledLexemesTypes.hh
	@printf "%s# Merging object files for $(LIBRARY_PARSE).%s\n" "$(PURPLE)" "$(EOS)"
	@$(AR) rcs build/$(LIBRARY_PARSE) $(OBJS_PARSE)

build/$(LIBRARY_ENGINE): $(OBJS_ENGINE)
	@printf "%s# Merging object files for $(LIBRARY_ENGINE).%s\n" "$(PURPLE)" "$(EOS)"
	@$(AR) rcs build/$(LIBRARY_ENGINE) $(OBJS_ENGINE)

build/$(LIBRARY_RUNTIME): $(OBJS_RUNTIME)
	@printf "%s# Merging object files for $(LIBRARY_RUNTIME).%s\n" "$(PURPLE)" "$(EOS)"
	@$(AR) rcs build/$(LIBRARY_RUNTIME) $(OBJS_RUNTIME)

sources/lexer/Lexer.cc: sources/lexer/Lexer.rl
	@printf "%s+ Generating ragel castel lexer.%s\n" "$(CYAN)" "$(EOS)"
	@$(RAGEL) -C -o sources/lexer/Lexer.cc sources/lexer/Lexer.rl

includes/castel/lexer/MangledLexemesTypes.hh sources/parser/parse.cc: sources/parser/parse.lm
	@printf "%s@ Generating lemon castel parser.%s\n" "$(CYAN)" "$(EOS)"
	@$(LEMON) sources/parser/parse.lm
	@$(RM) sources/parser/parse.out
	@$(MV) sources/parser/parse.h includes/castel/lexer/MangledLexemesTypes.hh
	@$(MV) sources/parser/parse.c sources/parser/parse.cc

$(DEPS_PARSE): build/dependencies/%.d: %.cc | includes/castel/lexer/MangledLexemesTypes.hh sources/parser/parse.cc
	@printf "%s+ Generating dependency file for %s.%s\n" "$(GREEN)" "$(<)" "$(EOS)"
	@$(MKDIR) -p "$(dir $(@))"
	@$(CXX) $(CXXFLAGS_PARSE) -MM -MG -MT "$(patsubst build/dependencies/%,build/objects/%,$(@:.d=.o))" "$(<)" > $(@)

$(DEPS_ENGINE): build/dependencies/%.d: %.cc | includes/castel/lexer/MangledLexemesTypes.hh sources/parser/parse.cc
	@printf "%s+ Generating dependency file for %s.%s\n" "$(GREEN)" "$(<)" "$(EOS)"
	@$(MKDIR) -p "$(dir $(@))"
	@$(CXX) $(CXXFLAGS_ENGINE) -MM -MG -MT "$(patsubst build/dependencies/%,build/objects/%,$(@:.d=.o))" "$(<)" > $(@)

$(DEPS_RUNTIME): build/dependencies/%.d: %.cc | includes/castel/lexer/MangledLexemesTypes.hh sources/parser/parse.cc
	@printf "%s+ Generating dependency file for %s.%s\n" "$(GREEN)" "$(<)" "$(EOS)"
	@$(MKDIR) -p "$(dir $(@))"
	@$(CXX) $(CXXFLAGS_RUNTIME) -MM -MG -MT "$(patsubst build/dependencies/%,build/objects/%,$(@:.d=.o))" "$(<)" > $(@)

$(OBJS_PARSE): build/objects/%.o: %.cc
	@printf "%s+ Compiling %s.%s\n" "$(GREEN)" "$(<)" "$(EOS)"
	@$(MKDIR) -p "$(dir $(@))"
	@$(CXX) $(CXXFLAGS_PARSE) -c -o "$(@)" "$(<)"

$(OBJS_ENGINE): build/objects/%.o: %.cc
	@printf "%s+ Compiling %s.%s\n" "$(GREEN)" "$(<)" "$(EOS)"
	@$(MKDIR) -p "$(dir $(@))"
	@$(CXX) $(CXXFLAGS_ENGINE) -c -o "$(@)" "$(<)"

$(OBJS_RUNTIME): build/objects/%.o: %.cc
	@printf "%s+ Compiling %s.%s\n" "$(GREEN)" "$(<)" "$(EOS)"
	@$(MKDIR) -p "$(dir $(@))"
	@$(CXX) $(CXXFLAGS_RUNTIME) -c -o "$(@)" "$(<)"

clean:
	@printf "%s- Removing temporary files.%s\n" "$(BROWN)" "$(EOS)"
	@$(RM) -rf build/generated
	@$(RM) -rf build/objects
	@$(RM) -f includes/castel/lexer/MangledLexemesTypes.hh
	@$(RM) -f sources/lexer/Lexer.cc
	@$(RM) -f sources/parser/parse.cc

clean-dependencies:
	@printf "%s- Removing dependencies listing.%s\n" "$(BROWN)" "$(EOS)"
	@$(RM) -rf build/dependencies

fclean: clean
	@printf "%s- Removing binary files.%s\n" "$(BROWN)" "$(EOS)"
	@$(RM) -rf build/$(LIBRARY_PARSE)
	@$(RM) -rf build/$(LIBRARY_ENGINE)
	@$(RM) -rf build/$(LIBRARY_RUNTIME)

re: clean-dependencies fclean
	@$(MAKE) --no-print-directory all

.PHONY: $(LIBRARY_PARSE) $(LIBRARY_ENGINE) $(LIBRARY_RUNTIME) all clean fclean re clean-depends libcastel
