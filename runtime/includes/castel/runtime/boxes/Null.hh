#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        class Context;

        namespace boxes
        {

            class Null : public runtime::Box
            {

                friend runtime::Context;

            protected:

                inline Null( void );

            public:

                virtual bool operatorBool( runtime::Context * context );

            public:

                virtual runtime::Box * operatorLogicalEqual( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorLogicalNotEqual( runtime::Context * context, runtime::Box * operand );

            };

        }

    }

}

#include "castel/runtime/Context.hh"
#include "castel/runtime/capi.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            Null::Null( void )
                : Box( )
            {
            }

        }

    }

}
