#include <iostream>
#include "inc/bmp.hpp"
using namespace std;
using namespace image;
int main()
{
    try
    {
        BMP test;
        test.Read("in.bmp");
        test.Rotate(45);
        test.Fix();
        test.Save("test.bmp");

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}