#include <cmath> // std::isnan, std::isinf
#include <string>

// It is char if length is 1 or 3 (surrounded by single quotes) and is not a digit
bool isChar( std::string_view str )
{
    if ( str.length() == 3 && str[0] == '\'' && str[2] == '\'' )
        return true;

    if ( str.length() == 1 && !std::isdigit( str[0] ) )
        return true;

    return false;
}

// It is double if '.'/nan/inf is present and stod succeeds without any leftover string
bool isDouble( std::string_view str, double d, std::size_t unconvertedPos )
{
    if ( unconvertedPos != str.length() )
        return false;

    if ( std::isnan( d ) || std::isinf( d ) )
        return true;

    if ( str.find( '.' ) != std::string::npos )
        return true;

    return false;
}

// It is float if '.'/nan/inf is present and stof succeeds with only 'f' or 'F' as leftover
bool isFloat( std::string_view str, float f, std::size_t unconvertedPos )
{
    if ( unconvertedPos + 1 != str.length() )
        return false;

    if ( str[unconvertedPos] != 'f' && str[unconvertedPos] != 'F' )
        return false;

    if ( std::isnan( f ) || std::isinf( f ) )
        return true;

    if ( str.find( '.' ) != std::string::npos )
        return true;

    return false;
}
