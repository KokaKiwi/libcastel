#pragma once

#include <memory>

#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class Visitor;

        }

        namespace expr
        {

            class List : public ast::Expression
            {

            public:

                class Item;

            public:

                inline List( ast::expr::List::Item * items );

            public:

                inline ast::expr::List::Item * items( void ) const;

                inline List & items( ast::expr::List::Item * items );

                inline ast::expr::List::Item * takeItems( void );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                std::unique_ptr< ast::expr::List::Item > mItems;

            };

            class List::Item : public utils::Linked< List::Item >
            {

            public:

                inline Item( ast::Expression * value );

            public:

                inline ast::Expression * value( void ) const;

                inline Item & value( ast::Expression * value );

                inline ast::Expression * takeValue( void );

            private:

                std::unique_ptr< ast::Expression > mValue;

            };

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

            List::Item::Item( ast::Expression * value )
                : mValue( value )
            {
            }

            ast::Expression * List::Item::value( void ) const
            {
                return mValue.get( );
            }

            List::Item & List::Item::value( ast::Expression * value )
            {
                mValue.reset( value );

                return * this;
            }

            ast::Expression * List::Item::takeValue( void )
            {
                return mValue.release( );
            }

            List::List( ast::expr::List::Item * items )
                : mItems( items )
            {
            }

            ast::expr::List::Item * List::items( void ) const
            {
                return mItems.get( );
            }

            List & List::items( ast::expr::List::Item * items )
            {
                mItems.reset( items );

                return * this;
            }

            ast::expr::List::Item * List::takeItems( void )
            {
                return mItems.release( );
            }

            void List::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
