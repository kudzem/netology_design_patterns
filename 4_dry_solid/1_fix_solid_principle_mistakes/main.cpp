#include "solid_example.h"
#include <iostream>

int main() 
{
    FormatterJSON f1;
    FormatterHTML f2;

    auto text_to_print = "hello, solid principles!";

    std::ofstream log("log.txt");

    formatAndPrint(log, text_to_print, f1);
    formatAndPrint(std::cout, text_to_print, f2);
}