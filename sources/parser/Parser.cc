#include <cstdlib>
#include <memory>

#include "p9/ast/Statement.hh"
#include "p9/lexer/Lexeme.hh"
#include "p9/lexer/Lexer.hh"
#include "p9/lexer/Token.hh"
#include "p9/parser/Exception.hh"
#include "p9/parser/Parser.hh"

using namespace p9;
using namespace p9::parser;

#include "sources/parser/parse.cc"

Parser::Parser( lexer::Lexer & lexer )
    : mLexer( lexer )
{
}

ast::Statement * Parser::exec( void )
{
    std::unique_ptr< lexer::Lexeme > lexeme;

    void * lemonParser = ParseAlloc( malloc );

 loop:
    lexeme.reset( mLexer.consume( ) );

    if ( lexeme->type( ) == lexer::TSpaces )
        goto loop;

    p9parserIsValid = true;
    std::cout << '[' << lexeme->type() << ']' << std::endl;
    Parse( lemonParser, lexeme->type( ), lexeme.get( ) );

    if ( ! p9parserIsValid )
        goto syntaxError;

    if ( lexeme->type( ) == lexer::TEOF )
        goto endOfFile;

    lexeme.release( );

    goto loop;

 syntaxError:
    ParseFree( lemonParser, free );

    throw Exception( "Unexpected token", lexeme.release( ) );

 endOfFile:
    ParseFree( lemonParser, free );

    return p9parserRootStatement;
}
