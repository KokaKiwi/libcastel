#pragma once

#include "castel/runtime/boxes/Bool.hh"

extern "C" {

    castel::runtime::boxes::Bool * castelBool_create( castel::runtime::Context * context, bool value );

}
