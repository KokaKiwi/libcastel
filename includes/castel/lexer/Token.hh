#pragma once

#include "castel/lexer/MangledTokens.hh"

namespace castel
{

    namespace lexer
    {

        enum Token {

            TInvalid      = - 1,
            TEOF          =   0,

            TFunction     = P9_LEXER_MANGLEDTOKENS_Function,
            TReturn       = P9_LEXER_MANGLEDTOKENS_Return,
            TVar          = P9_LEXER_MANGLEDTOKENS_Var,
            TIf           = P9_LEXER_MANGLEDTOKENS_If,
            TElse         = P9_LEXER_MANGLEDTOKENS_Else,

            TNumber       = P9_LEXER_MANGLEDTOKENS_Number,
            TIdentifier   = P9_LEXER_MANGLEDTOKENS_Identifier,

            TAdd          = P9_LEXER_MANGLEDTOKENS_Add,
            TSubstract    = P9_LEXER_MANGLEDTOKENS_Substract,
            TMultiply     = P9_LEXER_MANGLEDTOKENS_Multiply,
            TDivide       = P9_LEXER_MANGLEDTOKENS_Divide,
            TModulo       = P9_LEXER_MANGLEDTOKENS_Modulo,
            TAssign       = P9_LEXER_MANGLEDTOKENS_Assign,

            TLParenthesis = P9_LEXER_MANGLEDTOKENS_LParenthesis,
            TRParenthesis = P9_LEXER_MANGLEDTOKENS_RParenthesis,

            TColon        = P9_LEXER_MANGLEDTOKENS_Colon,
            TComma        = P9_LEXER_MANGLEDTOKENS_Comma,

            TSpaces       = P9_LEXER_MANGLEDTOKENS_Spaces,
            TNewline      = P9_LEXER_MANGLEDTOKENS_Newline,

            TIndent       = P9_LEXER_MANGLEDTOKENS_Indent,
            TDedent       = P9_LEXER_MANGLEDTOKENS_Dedent,

        };

    }

}
