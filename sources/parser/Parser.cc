#include <cstdlib>
#include <sstream>
#include <string>

#include "p9/lexer/Lexeme.hh"
#include "p9/lexer/LexemeTypes.hh"
#include "p9/lexer/Lexer.hh"
#include "p9/parser/Exception.hh"
#include "p9/parser/Parser.hh"

using namespace p9;
using namespace p9::parser;

#include "./sources/parser/parse.cc"

Parser::Parser( lexer::Lexer & lexer )
: mLexer( lexer )
, mLineNo( 0 )
{
}

ast::Token * Parser::exec( void )
{
	lexer::Lexeme lexeme;
	ast::Token * token = 0;
	
	void * lparse = ParseAlloc( malloc );
	
 loop:
	lexeme = mLexer.consume( );
	
	if ( lexeme == T_Spaces )
		goto loop;
	
	if ( lexeme == T_Newline )
		goto newline;
	
	p9parserIsValid = true;
	Parse( lparse, lexeme, 0 );
	
	if ( ! p9parserIsValid )
		goto syntaxError;
	
	if ( lexeme == lexer::Lexeme::endOfFile )
		goto endOfFile;
	
	goto loop;
	
 newline:
	++ mLineNo;
	goto loop;
	
 endOfFile:
	token = p9parserRootToken;
	goto end;
	
 syntaxError:
	ParseFree( lparse, free );
	throw Exception( position( ), "Unexpected token" );
	
 end:
	ParseFree( lparse, free );
	return token;
}

void Parser::triggerError( std::string const & message )
{
	std::stringstream sstream;
	sstream << ( mLineNo + 1 ) << ": " << message;
	mErrorString = sstream.str( );
}
