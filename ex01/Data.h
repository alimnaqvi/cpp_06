#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>

struct Data
{
    int         id{};
    std::string name{};
};

std::ostream& operator<<( std::ostream& out, Data data );
std::ostream& operator<<( std::ostream& out, Data* dataPtr );

#endif /* DATA_H */
