#pragma once

#include <functional>
#include <map>
#include <string>

#include <llvm/Module.h>

namespace castel
{

    namespace runtime
    {

        class Box;

    }

    namespace toolchain
    {

        class Runner
        {

        private:

            static void staticInitializer( void );

        private:

            static castel::runtime::Box * staticDependencyInitializer( Runner * runner, char const * global );

        public:

            Runner( llvm::Module * module, std::string const & name = "main" );

        public:

            inline std::map< std::string, std::function< castel::runtime::Box * ( void ) > > const & globals( void ) const;

            inline std::map< std::string, std::function< castel::runtime::Box * ( void ) > > & globals( void );

        public:

            castel::runtime::Box * operator()( void );

        private:

            llvm::Module * mModule;

            std::string mName;

            std::map< std::string, std::function< castel::runtime::Box * ( void ) > > mGlobals;

        };

    }

}

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace toolchain
    {

        std::map< std::string, std::function< castel::runtime::Box * ( void ) > > const & Runner::globals( void ) const
        {
            return mGlobals;
        }

        std::map< std::string, std::function< castel::runtime::Box * ( void ) > > & Runner::globals( void )
        {
            return mGlobals;
        }

    }

}
