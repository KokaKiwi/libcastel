#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_multiplicationOperator( runtime::Box *** environment, runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    return leftOperand->multiplicationOperator( environment, rightOperand );
}
