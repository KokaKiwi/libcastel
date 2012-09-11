#pragma once

#include <llvm/Support/IRBuilder.h>
#include <llvm/Support/TypeBuilder.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>
#include <llvm/Type.h>
#include <llvm/Value.h>

#include "castel/utils/LLVMExtensions.hh"

namespace castel
{

    namespace builder
    {

        class IRBuilder : public llvm::IRBuilder< >
        {

        public:

            IRBuilder            ( llvm::LLVMContext & llvmContext, llvm::Module & llvmModule )
            : llvm::IRBuilder< > ( llvmContext )
            , Module             ( llvmModule  )
            {
            }

        public:

            llvm::Value * CreateCastelSizeOf( llvm::Type * type )
            {
                llvm::ConstantPointerNull * nullPointer = llvm::ConstantPointerNull::get( llvm::PointerType::getUnqual( type ) );
                return this->CreatePtrToInt( this->CreateConstGEP1_32( nullPointer, 1 ), llvm::IntegerType::get( Context, 32 ) );
            }

            llvm::Value * CreateCastelAllocate( llvm::Type * type, llvm::Value * count, bool stackAllocation = false )
            {
                if ( stackAllocation ) {
                    return this->CreateAlloca( type, count );
                } else {
                    llvm::Value * raw = this->CreateCastelCall( "castel_allocate", count, this->CreateCastelSizeOf( type ) );
                    return this->CreateBitCast( raw, llvm::PointerType::getUnqual( type ) );
                }
            }

            llvm::Value * CreateCastelAllocate( llvm::Type * type, unsigned int count, bool stackAllocation = false )
            {
                return this->CreateCastelAllocate( type, llvm::ConstantInt::get( Context, llvm::APInt( 32, count ) ), stackAllocation );
            }

            template < typename Type >
            llvm::Value * CreateCastelAllocate( llvm::Value * count, bool stackAllocation = false )
            {
                return this->CreateCastelAllocate( llvm::TypeBuilder< Type, false >::get( Context ), count, stackAllocation );
            }

            template < typename Type >
            llvm::Value * CreateCastelAllocate( unsigned int count, bool stackAllocation = false )
            {
                return this->CreateCastelAllocate( llvm::TypeBuilder< Type, false >::get( Context ), count, stackAllocation );
            }

            template < typename... Types >
            llvm::Value * CreateCastelCall( std::string const & name, Types... args )
            {
                return this->CreateCall( Module.getFunction( name ), std::vector< llvm::Value * >( { args... } ) );
            }

        protected:

            llvm::Module & Module;

        };

    }

}
