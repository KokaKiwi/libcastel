#include <vector>

#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/capi.hh"

using namespace castel;

static runtime::boxes::Class * classPrototype = nullptr;

static std::vector< runtime::boxes::Class * > incompleteClasses;

runtime::boxes::Class * Castel_Class_create( runtime::boxes::Class * parent, runtime::boxes::Class::InitializerSignature * initializer, runtime::Box *** environment )
{
    auto instance = runtime::helper::create< runtime::boxes::Class >( parent, initializer, environment );

    if ( classPrototype )
        instance->type( classPrototype );
    else
        incompleteClasses.push_back( instance );

    return instance;
}

runtime::Box * Castel_Class_installPrototype( runtime::Box ***, int argc, runtime::Box ** argv )
{
    auto prototype = dynamic_cast< runtime::boxes::Class * >( argv[ 0 ] );

    classPrototype = prototype;

    for ( auto classBox : incompleteClasses )
        classBox->type( prototype );
    incompleteClasses.clear( );

    return prototype;
}

runtime::Box * Castel_Class_parent( runtime::Box ***, int argc, runtime::Box ** argv )
{
    auto classBox = dynamic_cast< runtime::boxes::Class * >( argv[ 0 ] );

    return classBox->parent( );
}
