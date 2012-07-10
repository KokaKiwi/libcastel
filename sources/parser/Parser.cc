#include <cstdlib>
#include <memory>

#include "build/generated/lexemes"

#include "p9/lexer/Lexeme.hh"
#include "p9/lexer/Lexer.hh"
#include "p9/parser/Exception.hh"
#include "p9/parser/Parser.hh"

using namespace p9;
using namespace p9::parser;

#include "build/generated/parser"

Parser::Parser( lexer::Lexer & lexer )
    : mLexer( lexer )
{
}

ast::Token * Parser::exec( void )
{
    std::auto_ptr< lexer::Lexeme > lexeme;

    void * lemonParser = ParseAlloc( malloc );

 loop:
    lexeme.reset( mLexer.consume( ) );

    if ( lexeme->type( ) == T_Spaces || lexeme->type( ) == T_Newline )
        goto loop;

    p9parserIsValid = true;
    Parse( lemonParser, lexeme->type( ) != T_EOF ? lexeme->type( ) : 0, lexeme.get( ) );

    if ( ! p9parserIsValid )
        goto syntaxError;

    if ( lexeme->type( ) == T_EOF )
        goto endOfFile;

    lexeme.release( );

    goto loop;

 syntaxError:
    ParseFree( lemonParser, free );

    throw Exception( "Unexpected token", lexeme.release( ) );

 endOfFile:
    ParseFree( lemonParser, free );

    return p9parserRootToken;
}
