#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "Data.h"
#include <cstdint>

struct Data;

class Serializer
{
  public:
    // Orthodox canonical form requirements
    Serializer( const Serializer& other )            = delete;
    Serializer& operator=( const Serializer& other ) = delete;
    virtual ~Serializer();

    // The main static methods
    static uintptr_t serialize( Data* ptr );
    static Data*     deserialize( uintptr_t raw );

  protected:
    // Make the constructor protected so the class cannot be instantiated
    Serializer() = default;
};

#endif /* SERIALIZER_H */
