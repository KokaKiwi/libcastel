#pragma once

#include "castel/runtime/Box.hh"
#include "castel/runtime/Function.hh"

extern "C"
{
    castel::runtime::Function * castelFunction_create( castel::runtime::Function::InternalFunction function, castel::runtime::Box *** environmentTable );
}
