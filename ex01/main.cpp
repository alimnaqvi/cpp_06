#include "Data.h"
#include "Serializer.h"
#include <cstdint>
#include <iomanip>
#include <iostream>

int main()
{
    Data* data1Ptr{ new Data{ 1, "Shrek" } };
    Data* data2Ptr{ new Data{ 2, "Fiona" } };

    Data data3{ 3, "Donkey" };
    Data data4{ 4, "Farquaad" };

    std::cout << "data1: " << *data1Ptr << '\n';
    std::cout << "data2: " << *data2Ptr << '\n';
    std::cout << "data3: " << data3 << '\n';
    std::cout << "data4: " << data4 << '\n';

    std::cout << "data1 address: " << data1Ptr << '\n';
    std::cout << "data2 address: " << data2Ptr << '\n';
    std::cout << "data3 address: " << &data3 << '\n';
    std::cout << "data4 address: " << &data4 << '\n';

    uintptr_t serialized1{ Serializer::serialize( data1Ptr ) };
    uintptr_t serialized2{ Serializer::serialize( data2Ptr ) };
    uintptr_t serialized3{ Serializer::serialize( &data3 ) };
    uintptr_t serialized4{ Serializer::serialize( &data4 ) };

    std::cout << "serialized1 value: " << serialized1 << '\n';
    std::cout << "serialized2 value: " << serialized2 << '\n';
    std::cout << "serialized3 value: " << serialized3 << '\n';
    std::cout << "serialized4 value: " << serialized4 << '\n';

    Data* data1Returned{ Serializer::deserialize( serialized1 ) };
    Data* data2Returned{ Serializer::deserialize( serialized2 ) };
    Data* data3Returned{ Serializer::deserialize( serialized3 ) };
    Data* data4Returned{ Serializer::deserialize( serialized4 ) };

    std::cout << "data1Returned: " << *data1Returned << '\n';
    std::cout << "data2Returned: " << *data2Returned << '\n';
    std::cout << "data3Returned: " << *data3Returned << '\n';
    std::cout << "data4Returned: " << *data4Returned << '\n';

    std::cout << "data1 == data1Returned: " << std::boolalpha << ( data1Ptr == data1Returned ) << '\n';
    std::cout << "data2 == data2Returned: " << std::boolalpha << ( data2Ptr == data2Returned ) << '\n';
    std::cout << "data3 == data3Returned: " << std::boolalpha << ( &data3 == data3Returned ) << '\n';
    std::cout << "data4 == data4Returned: " << std::boolalpha << ( &data4 == data4Returned ) << '\n';

    delete data1Ptr;
    delete data2Ptr;

    return 0;
}
