#pragma once

namespace castel
{

    namespace ast
    {

        namespace expr
        {
            class Boolean;
            class Binary;
            class Class;
            class Dict;
            class Function;
            class List;
            class Multary;
            class Null;
            class Number;
            class String;
            class Unary;
            class Undefined;
            class Variable;
        }

        namespace stmt
        {
            namespace decl
            {
                class Variables;
            }

            class Expression;
            class If;
            class Return;
        }

    }

    namespace utils
    {

        class Visitor
        {

        public:

            virtual ~Visitor( void ) {}

        public:

            virtual void visit( ast::expr::Boolean         & ) = 0;
            virtual void visit( ast::expr::Binary          & ) = 0;
            virtual void visit( ast::expr::Class           & ) = 0;
            virtual void visit( ast::expr::Dict            & ) = 0;
            virtual void visit( ast::expr::Function        & ) = 0;
            virtual void visit( ast::expr::List            & ) = 0;
            virtual void visit( ast::expr::Multary         & ) = 0;
            virtual void visit( ast::expr::Null            & ) = 0;
            virtual void visit( ast::expr::Number          & ) = 0;
            virtual void visit( ast::expr::String          & ) = 0;
            virtual void visit( ast::expr::Unary           & ) = 0;
            virtual void visit( ast::expr::Undefined       & ) = 0;
            virtual void visit( ast::expr::Variable        & ) = 0;

        public:

            virtual void visit( ast::stmt::decl::Variables & ) = 0;
            virtual void visit( ast::stmt::Expression      & ) = 0;
            virtual void visit( ast::stmt::If              & ) = 0;
            virtual void visit( ast::stmt::Return          & ) = 0;

        };

    }

}
