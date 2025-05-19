#include "ScalarConverter.h"

// Check for overflow before static-casting to char and printing
template <typename T>
void checkPrintChar( T x )
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
void checkPrintInt( T x )
{
    if ( x > std::numeric_limits<int>::max() || x < std::numeric_limits<int>::min() )
        std::cout << "int: impossible (will overflow/underflow)" << '\n';
    else
    {
        int i{ static_cast<int>( x ) };
        std::cout << "int: " << i << '\n';
    }
}

// Print float with at least 1 decimal place
void printFloat( float f )
{
    std::cout << "float: ";

    if ( std::floor( f ) == f )
        std::cout << std::fixed << std::setprecision( 1 ) << f << std::defaultfloat;
    else
        std::cout << f;
    std::cout << 'f' << '\n';
}

// Print double with at least 1 decimal place
void printDouble( double d )
{
    std::cout << "double: ";

    if ( std::floor( d ) == d )
        std::cout << std::fixed << std::setprecision( 1 ) << d << std::defaultfloat;
    else
        std::cout << d;
    std::cout << '\n';
}

void handleChar( char c )
{
    checkPrintChar( c );

    int i{ static_cast<int>( c ) };
    std::cout << "int: " << i << '\n';

    float f{ static_cast<float>( c ) };
    printFloat( f );

    double d{ static_cast<double>( c ) };
    printDouble( d );
}

void handleInt( int i )
{
    std::cout << "int: " << i << '\n';

    checkPrintChar( i );

    float f{ static_cast<float>( i ) };
    printFloat( f );

    double d{ static_cast<double>( i ) };
    printDouble( d );
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
        checkPrintChar( d );
        checkPrintInt( d );
    }

    printFloat( f );

    std::cout << "double: " << d << '\n';
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
        checkPrintChar( d );
        checkPrintInt( d );
    }

    if ( std::isfinite( d ) && ( d > std::numeric_limits<float>::max() || d < std::numeric_limits<float>::lowest() ) )
        std::cout << "float: impossible (will overflow/underflow)" << '\n';
    else
    {
        float f{ static_cast<float>( d ) };
        printFloat( f );
    }

    printDouble( d );
}
