#include "Data.h"

std::ostream& operator<<( std::ostream& out, Data data )
{
    out << "id: " << data.id << ", name: " << data.name << '.';

    return out;
}

std::ostream& operator<<( std::ostream& out, Data* dataPtr )
{
    if ( dataPtr )
        out << "id: " << dataPtr->id << ", name: " << dataPtr->name << '.';
    else
        out << "Cannot dereference nullptr" << '.';

    return out;
}
