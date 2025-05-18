#include "ScalarConverter.h"

// Empty destructor
ScalarConverter::~ScalarConverter()
{
}

// The main static method
void ScalarConverter::convert( const std::string& str )
{
    LiteralType inputType{ inferType( str ) };

    switch ( inputType )
    {
    case LiteralType::INVALID:
        std::cout << USAGE_MSG;
        break;
    case LiteralType::CHAR:
        handleChar( str );
        break;
    case LiteralType::INT:
        handleInt( str );
        break;
    case LiteralType::FLOAT:
        handleFloat( str );
        break;
    case LiteralType::DOUBLE:
        handleDouble( str );
        break;
    default: // This should never be reached but just to be safe
        std::cout << USAGE_MSG;
        break;
    }
}

// Helper functions

void trimTrailingWhitespace( std::string& str, const std::string& whitespace = " \t\n\r\f\v" ) {
    if (!str.length())
        return;
    
    str = str.substr( 0, str.find_last_not_of( whitespace ) + 1 );
}

LiteralType inferType( std::string str )
{
    trimTrailingWhitespace(str);

    // To be completed
}
