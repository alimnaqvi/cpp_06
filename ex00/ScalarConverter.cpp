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
    // case LiteralType::PSEUDO:
    //     handlePseudo( str );
    //     break;
    default: // This should never be reached but just to be safe
        std::cout << USAGE_MSG;
        break;
    }
}

// Helper functions

void trimWhitespace( std::string& str, const std::string& whitespace = " \t\n\r\f\v" )
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

LiteralType inferType( std::string str )
{
    trimWhitespace( str );

    if ( str.empty() )
        return LiteralType::INVALID;

    const auto strLen{ str.length() };

    // It is char if length is 1 and it is not a digit
    if ( strLen == 1 && !std::isdigit( str[0] ) )
        return LiteralType::CHAR;

    try
    {
        std::size_t unconvertedPos;

        double d{ std::stod( str, &unconvertedPos ) };
        // It is double if '.' is present and stod succeeds without any leftover string
        if ( str.find( '.' ) != std::string::npos && unconvertedPos == strLen )
            return LiteralType::DOUBLE;

        float f{ std::stof( str, &unconvertedPos ) };
        // It is float if '.' is present and stof succeeds with only 'f' or 'F' as leftover
        if ( str.find( '.' ) != std::string::npos && unconvertedPos == strLen + 1 &&
             ( str[unconvertedPos] == 'f' || str[unconvertedPos] == 'F' ) )
            return LiteralType::FLOAT;

        int i{ std::stoi( str, &unconvertedPos ) };
        // It is int if stoi succeeds without any leftover string
        if ( unconvertedPos == strLen )
            return LiteralType::INT;
    }
    catch ( const std::exception& e )
    {
        std::cout << "Invalid input." << '\n';
    }

    return LiteralType::INVALID;
}

void printChar( char c )
{
    if ( std::isprint( static_cast<unsigned char>( c ) ) )
        std::cout << "char: " << c << '\n';
    else
        std::cout << "char: " << "non-displayable" << '\n';
}

void handleChar( std::string str )
{
    char c{ str[0] };
    std::cout << "char: " << c << '\n';

    int i{ static_cast<int>( c ) };
    std::cout << "int: " << i << '\n';

    std::cout << std::fixed << std::setprecision( 1 );

    float f{ static_cast<float>( c ) };
    std::cout << "float: " << f << '\n';

    double d{ static_cast<double>( c ) };
    std::cout << "double: " << d << '\n';
}

void handleInt( std::string str )
{
    int i{ std::stoi( str ) };
    std::cout << "int: " << i << '\n';

    if ( i > std::numeric_limits<char>::max() || i < std::numeric_limits<char>::min() )
        std::cout << "char: impossible (will overflow)" << '\n';
    else
    {
        char c{ static_cast<char>( i ) };
        printChar( c );
    }

    std::cout << std::fixed << std::setprecision( 1 );

    float f{ static_cast<float>( i ) };
    std::cout << "float: " << f << '\n';

    double d{ static_cast<double>( i ) };
    std::cout << "double: " << d << '\n';
}

void handleFloat( std::string str )
{
    float f{ std::stof( str ) };
    std::cout << std::fixed << std::setprecision( 1 );
    std::cout << "float: " << f << '\n';

    double d{ static_cast<double>( f ) };
    std::cout << "double: " << d << '\n';

    if ( std::isinf( f ) || std::isnan( f ) )
    {
        std::cout << "char: impossible" << '\n';
        std::cout << "int: impossible" << '\n';
    }
    else
    {
        if ( d > std::numeric_limits<char>::max() || d < std::numeric_limits<char>::min() )
            std::cout << "char: impossible (will overflow/underflow)" << '\n';
        else
        {
            char c{ static_cast<char>( f ) };
            printChar( c );
        }

        if ( d > std::numeric_limits<int>::max() || d < std::numeric_limits<int>::min() )
            std::cout << "int: impossible (will overflow/underflow)" << '\n';
        else
        {
            int i{ static_cast<int>( f ) };
            std::cout << "int: " << i << '\n';
        }
    }
}

void handleDouble( std::string str )
{
    double d{ std::stod( str ) };
    std::cout << std::fixed << std::setprecision( 1 );
    std::cout << "double: " << d << '\n';

    if ( std::isfinite( d ) && ( d > std::numeric_limits<float>::max() || d < std::numeric_limits<float>::lowest() ) )
        std::cout << "float: impossible (will overflow/underflow)" << '\n';
    else
    {
        float f{ static_cast<float>( d ) };
        std::cout << "float: " << f << '\n';
    }

    if ( std::isinf( d ) || std::isnan( d ) )
    {
        std::cout << "char: impossible" << '\n';
        std::cout << "int: impossible" << '\n';
    }
    else
    {
        if ( d > std::numeric_limits<char>::max() || d < std::numeric_limits<char>::min() )
            std::cout << "char: impossible (will overflow/underflow)" << '\n';
        else
        {
            char c{ static_cast<char>( d ) };
            printChar( c );
        }

        if ( d > std::numeric_limits<int>::max() || d < std::numeric_limits<int>::min() )
            std::cout << "int: impossible (will overflow/underflow)" << '\n';
        else
        {
            int i{ static_cast<int>( d ) };
            std::cout << "int: " << i << '\n';
        }
    }
}
