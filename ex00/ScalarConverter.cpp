#include "ScalarConverter.h"

// Empty destructor
ScalarConverter::~ScalarConverter()
{
}

// The main static method
void ScalarConverter::convert( std::string str )
{
    trimWhitespace( str );

    if ( str.empty() )
    {
        std::cout << "The input must not be an empty string." << '\n';
        return;
    }

    if ( isChar( str ) )
        return ((str.length() == 3) ? handleChar( str[1] ) : handleChar( str[0] )) ;
        // return handleChar( str[1] );

    try
    {
        std::size_t unconvertedPos;

        double d{ std::stod( str, &unconvertedPos ) };
        if ( isDouble( str, d, unconvertedPos ) )
            return handleDouble( d );

        float f{ std::stof( str, &unconvertedPos ) };
        if ( isFloat( str, f, unconvertedPos ) )
            return handleFloat( f );

        int i{ std::stoi( str, &unconvertedPos ) };
        if ( unconvertedPos == str.length() )
            return handleInt( i );
    }
    catch ( const std::out_of_range& e )
    {
        std::cout << "Invalid input. " << OVERFLOW_MSG << '\n';
        return;
    }
    catch ( const std::invalid_argument& e )
    {
        std::cout << "The input string does match the most common literal form of any of the 4 scalar types. "
                  << USAGE_MSG << '\n';
        return;
    }
    catch ( const std::exception& e )
    {
        std::cout << "Invalid input. " << USAGE_MSG << '\n';
        return;
    }

    std::cout << "Invalid input. " << USAGE_MSG << '\n';
}

/* Type handlers (entry points) */

void handleChar( char c )
{
    castPrintChar( c );

    castPrintInt( c );

    castPrintFloat( c );

    castPrintDouble( c );
}

void handleInt( int i )
{
    castPrintChar( i );

    castPrintInt( i );

    castPrintFloat( i );

    castPrintDouble( i );
}

void handleFloat( float f )
{
    double d{ static_cast<double>( f ) };

    if ( std::isinf( f ) || std::isnan( f ) )
    {
        std::cout << "char: impossible" << '\n';
        std::cout << "int: impossible" << '\n';
    }
    else
    {
        castPrintChar( d );
        castPrintInt( d );
    }

    castPrintFloat( f );

    castPrintDouble( d );
}

void handleDouble( double d )
{
    if ( std::isinf( d ) || std::isnan( d ) )
    {
        std::cout << "char: impossible" << '\n';
        std::cout << "int: impossible" << '\n';
    }
    else
    {
        castPrintChar( d );
        castPrintInt( d );
    }

    castPrintFloat( d );

    castPrintDouble( d );
}

// Whitespace helper
void trimWhitespace( std::string& str, const std::string& whitespace )
{
    const auto firstNonSpace = str.find_first_not_of( whitespace );

    if ( firstNonSpace == std::string::npos )
    {
        str.clear();
        return;
    }

    const auto lastNonSpace = str.find_last_not_of( whitespace );
    const auto strLen       = lastNonSpace - firstNonSpace + 1;

    str = str.substr( firstNonSpace, strLen );
}
