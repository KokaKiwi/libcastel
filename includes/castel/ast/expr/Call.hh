#pragma once

#include <memory>

#include "castel/ast/Expression.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Call : public ast::Expression
            {

            public:

                class Argument;

            public:

                Call         ( ast::Expression * callee = nullptr, ast::expr::Call::Argument * arguments = nullptr )
                : mCallee    ( callee )
                , mArguments ( arguments )
                {
                }

            public:

                ast::Expression * callee( void ) const
                {
                    return mCallee.get( );
                }

                Call & callee( ast::Expression * callee )
                {
                    mCallee.reset( callee );

                    return *this;
                }

                ast::Expression * takeCallee( void )
                {
                    return mCallee.release( );
                }

            public:

                ast::expr::Call::Argument * arguments( void ) const
                {
                    return mArguments.get( );
                }

                Call & arguments( ast::expr::Call::Argument * arguments )
                {
                    mArguments.reset( arguments );

                    return *this;
                }

                ast::expr::Call::Argument * takeArguments( void )
                {
                    return mArguments.release( );
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( *this );
                }

            private:

                std::unique_ptr< ast::Expression > mCallee;
                std::unique_ptr< ast::expr::Call::Argument > mArguments;

            };

        }

    }

}

#include "castel/ast/expr/Call/Argument.hh"
