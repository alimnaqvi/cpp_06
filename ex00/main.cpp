#include "ScalarConverter.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "The program accepts one and only one argument." << '\n';
        std::cout << USAGE_MSG << '\n';
        return 1;
    }

    ScalarConverter::convert(argv[1]);

    return 0;
}
