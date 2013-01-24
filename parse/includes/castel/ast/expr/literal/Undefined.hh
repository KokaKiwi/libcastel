#pragma once

#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            namespace literal
            {

                class Undefined : public ast::Expression
                {

                public:

                    inline Undefined ( void );

                public:

                    virtual inline void accept( ast::tools::Visitor & visitor );

                };

            }

        }

    }

}

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            namespace literal
            {

                Undefined::Undefined( void )
                {
                }

                void Undefined::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
