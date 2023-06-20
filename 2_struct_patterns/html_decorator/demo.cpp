#include "html_formatter.h"
#include <iostream>
#include <cassert>


int main() 
{
    Text* printer = new Text;

    Text* pStyle;
    Text* hStyle;
    Text* iStyle;
    Text* bStyle;
    Text* boldItalicStyle;
    Link* lStyle;

    std::cout << "Which style do you prefer? (1/2) ";
    int choise;
    std::cin >> choise;

    if (choise == 1)
    {
        pStyle = new Paragraph(printer);
        hStyle = new Header(printer, 1);
        iStyle = new ItalicText(printer);
        bStyle = new BoldText(printer);
        boldItalicStyle = new BoldText(iStyle);
        lStyle = new Link(printer);
    }
    else 
    {
        pStyle = new Header(printer, 1);
        hStyle = new Header(printer, 2);
        iStyle = new ItalicText(printer);
        bStyle = new BoldText(printer);
        boldItalicStyle = new BoldText(iStyle);
        lStyle = new Link(bStyle);
    }

    pStyle->render("My first website");
    std::cout << std::endl;
    iStyle->render("My epigraph website");
    std::cout << std::endl;
    hStyle->render("Chapter 1");
    std::cout << std::endl;
    boldItalicStyle->render("gbrjbegjebgjbe er gejk wjej wkwj bekjgbwgb wkg bwkj 1"); 
    std::cout << std::endl;
    lStyle->render("For more information click here", "google.com");
    std::cout << std::endl;
}