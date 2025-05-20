#include "Serializer.h"

// Empty destructor
Serializer::~Serializer()
{
}

// The main static methods

uintptr_t Serializer::serialize( Data* ptr )
{
    return reinterpret_cast<uintptr_t>( ptr );
}

Data* Serializer::deserialize( uintptr_t raw )
{
    return reinterpret_cast<Data*>( raw );
}
