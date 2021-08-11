#include <iostream>
#include <fstream>
using namespace std;

int main() {
    //SET CONTROLL CODE TO 0x1B
    char esc = 27;

    ofstream myfile;
    myfile.open ("Lab1.pcl", std::ios::out | std::ios::binary);

    //FIRST PAGE
    //DEFAULTS
    myfile << esc << "E";

    //PAGE SIZE = A4
    myfile <<esc<<"&l26A";

    //PRIMARY SPACING PROPORTIONAL
    myfile <<esc<<"(s1p";
    //STYLE SHADOWED
    myfile << esc <<"(s128S";
    //FONT ALBERTUS
    myfile << esc <<"(s16901T";
    myfile << "Muravlov Andrii Dmitrovich ";
    myfile << "01/12/2020 ";

    //NEXT LINE
    myfile << "\n\r\n\r";

    //STYLE CONDENSED
    myfile << esc <<"(s4S";
    //FONT UNIVERS
    myfile << esc <<"(s4148T";
    myfile << "Muravlov Andrii Dmitrovich ";
    myfile << "01/12/2020 ";

    //NEXT LINE
    myfile << "\n\r\n\r";

    //STYLE EXTRA CONDENSED
    myfile << esc <<"(s2B" << esc << "(s8S";
    //FONT ARIAL
    myfile << esc <<"(s16602T";
    myfile << "Muravlov Andrii Dmitrovich ";
    myfile << "01/12/2020 ";

    //SECOND PAGE
    //DEFAULTS
    myfile << esc << "E";
    //PAGE SIZE = A4
    myfile << esc << "&l26A";

    //COLUMN SHIFT
    myfile << esc << "&a46C";
    //ROW SHIFT
    myfile << esc << "&a9R";
    myfile << "Muravlov Andrii";

    //COLUMN SHIFT
    myfile << esc << "&a46C";
    //ROW SHIFT
    myfile << esc << "&a10R";
    myfile << "Dmitrovich";

    //COLUMN SHIFT
    myfile << esc << "&a55C";
    //ROW SHIFT
    myfile << esc << "&a13R";
    myfile << "Email";

    //COLUMN SHIFT
    myfile << esc << "&a46C";
    //ROW SHIFT
    myfile << esc << "&a14R";
    myfile << esc << "(s12H" "ardwiz9@gmail.com";

    /*RECTANGLES
     * %0B = ENTER HP-GL/2 mode
     * IN = INITIALIZE HP-GL/2 mode
     * SP = SELECT PEN
     * PA = PLOT ABSOLUTE where attributes is pens start coordinates
     * EA = EDGE RECTANGLE ABSOLUTE where attributes are pens end coordinate
     * (opposite corner of rectangle)
     * */

    myfile <<esc<<"%0B"<<"IN"<<"SP1"<<"PA2000,7000"<<"EA7000,10000"<<"%0A"; //BIG RECTANGLE
    myfile <<esc<<"%0B"<<"IN"<<"SP2"<<"PA2400,7600"<<"EA4300,9400"<<"%0A";  // SMALL RECTANGLE

    myfile.close();
    return 0;
}
