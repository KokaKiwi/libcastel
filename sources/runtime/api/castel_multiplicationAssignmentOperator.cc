#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_multiplicationAssignmentOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->multiplicationAssignmentOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "multiplication assignment", leftOperand, rightOperand );

    return result;
}