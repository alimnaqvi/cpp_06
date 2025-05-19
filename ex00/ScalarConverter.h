#ifndef SCALARCONVERTER_H
#define SCALARCONVERTER_H

#include <cctype> // std::isprint
#include <cmath>  // std::isnan, std::isinf
#include <exception>
#include <iomanip> // std::fixed, std::setprecision
#include <iostream>
#include <limits>
#include <string>

#define USAGE_MSG                                                                                                      \
    "Ensure that the inputted string is one literal value (multiple values separated by whitespaces are not valid) of one of these types:\n\
- char (e.g., 'a'): An ASCII character.\n\
- int (e.g., '42'): A signed integer that fits in the implementation-defined limits of largest and smallest integer.\n\
- float (e.g., '42.0f'): A decimal number (must contain a '.' and must respect implementation-defined limits of float type) followed by 'f' or 'F'. In addition, '-inff', '+inff', and 'nanf' are also valid.\n\
- double (e.g., '42.0'): A decimal number (must contain a '.' and must respect implementation-defined limits of double type). In addition, '-inf', '+inf', and 'nan' are also valid.\n\
Note that any leading and trailing whitespaces will be stripped from inputted literal.\n"

enum class LiteralType
{
    INVALID,
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
};

class ScalarConverter
{
  public:
    // Orthodox canonical form requirements
    ScalarConverter( const ScalarConverter& other )            = delete;
    ScalarConverter& operator=( const ScalarConverter& other ) = delete;
    virtual ~ScalarConverter();

    // The main static method
    static void convert( const std::string& str );

  protected:
    // Make the constructor protected so the class cannot be instantiated
    ScalarConverter() = default;
};

// Helper functions
LiteralType inferType( std::string str );
void        handleChar( std::string str );
void        handleInt( std::string str );
void        handleFloat( std::string str );
void        handleDouble( std::string str );
void        printChar( char c );
// void        printTypes( char c, int i, float f, double d );

#endif /* SCALARCONVERTER_H */
