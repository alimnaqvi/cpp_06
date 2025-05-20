#include "ScalarConverter.h"

// Check for overflow before static-casting to char and printing
template <typename T>
void castPrintChar( T x )
{
    if ( x > std::numeric_limits<char>::max() || x < std::numeric_limits<char>::min() )
        std::cout << "char: impossible (will overflow/underflow)" << '\n';
    else
    {
        char c{ static_cast<char>( x ) };
        if ( std::isprint( static_cast<unsigned char>( c ) ) )
            std::cout << "char: '" << c << "'\n";
        else
            std::cout << "char: " << "non-displayable" << '\n';
    }
}

// Check for overflow before static-casting to int and printing
template <typename T>
void castPrintInt( T x )
{
    if ( x > std::numeric_limits<int>::max() || x < std::numeric_limits<int>::min() )
        std::cout << "int: impossible (will overflow/underflow)" << '\n';
    else
    {
        int i{ static_cast<int>( x ) };
        std::cout << "int: " << i << '\n';
    }
}

// Print float/double with at least 1 decimal place
template <typename T>
void atLeastOneDecimal( T x )
{
    if ( std::floor( x ) == x )
        std::cout << std::fixed << std::setprecision( 1 ) << x << std::defaultfloat;
    else
        std::cout << x;
}

// Check for overflow before static-casting to float and printing
template <typename T>
void castPrintFloat( T x )
{
    if ( std::isfinite( x ) && ( x > std::numeric_limits<float>::max() || x < std::numeric_limits<float>::lowest() ) )
        std::cout << "float: impossible (will overflow/underflow)" << '\n';
    else
    {
        float f{ static_cast<float>( x ) };
        std::cout << "float: ";
        atLeastOneDecimal( f );
        std::cout << 'f' << '\n';
    }
}

// Check for overflow before static-casting to double and printing
template <typename T>
void castPrintDouble( T x )
{
    if ( std::isfinite( x ) && ( x > std::numeric_limits<double>::max() || x < std::numeric_limits<double>::lowest() ) )
        std::cout << "double: impossible (will overflow/underflow)" << '\n';
    else
    {
        double d{ static_cast<double>( x ) };
        std::cout << "double: ";
        atLeastOneDecimal( d );
        std::cout << '\n';
    }
}

// Type handlers (entry points)

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
