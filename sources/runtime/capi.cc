#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "castel/runtime/capi.hh"

void * castel_malloc( std::size_t size, unsigned int count )
{
    return std::malloc( size * count );
}

void castel_fatal( char const * errorMessage )
{
    std::cerr << errorMessage << std::endl;
    std::exit( 1 );
}

void castel_unaryOperatorMissing( char const * name, castel::runtime::Box * operand )
{
    std::ostringstream stream;
    stream << "Unary operator '" << name << "' is invalid on data type '" << "UNDEFINED" << "'";
    ::castel_fatal( stream.str( ).c_str( ) );
}

void castel_binaryOperatorMissing( char const * name, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    std::ostringstream stream;
    stream << "Binary operator '" << name << "' is invalid with data types '" << "UNDEFINED" << "' and '" << "UNDEFINED" << "'";
    ::castel_fatal( stream.str( ).c_str( ) );
}

bool castel_operatorBool( castel::runtime::Box * operand )
{
    return operand->operatorBool( );
}

castel::runtime::Box * castel_operatorNumericPlus( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPlus( );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( "plus", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericMinus( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericMinus( );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( "minus", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericPreIncrementation( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPreIncrementation( );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( "pre-incrementation", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericPreDecrementation( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPreDecrementation( );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( "pre-decrementation", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericPostIncrementation( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPostIncrementation( );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( "post-incrementation", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericPostDecrementation( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPostDecrementation( );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( "post-decrementation", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericAddition( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericAddition( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "addition", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorNumericSubstraction( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericSubstraction( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "substraction", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorNumericMultiplication( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericMultiplication( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "multiplication", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorNumericDivision( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericDivision( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "division", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorNumericModulo( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericModulo( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "modulo", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonLesser( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonLesser( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "lesser than", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonGreater( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonGreater( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "greater than", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonLesserOrEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonLesserOrEqual( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "lesser or equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonGreaterOrEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonGreaterOrEqual( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "greater or equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonEqual( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonNotEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonNotEqual( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "not equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryNot( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorBinaryNot( );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( "binary not", operand );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryAnd( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryAnd( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "binary and", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryOr( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryOr( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "binary or", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryXOr( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryXOr( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "binary xor", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryLShift( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryLShift( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "binary left shift", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryRShift( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryRShift( operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( "binary right shift", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorCall( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv )
{
    castel::runtime::Box * ret = operand->operatorCall( argc, argv );

    if ( ret == nullptr )
        ::castel_fatal( "Non-callable instance" );

    return ret;
}

castel::runtime::Box * castel_operatorSubscript( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv )
{
    castel::runtime::Box * ret = operand->operatorSubscript( argc, argv );

    if ( ret == nullptr )
        ::castel_fatal( "Non-subscriptable instance" );

    return ret;
}
