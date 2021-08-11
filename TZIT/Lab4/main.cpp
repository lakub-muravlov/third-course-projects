#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "transform_bmp.h"
using namespace std;

string ModulesToBinary (vector <int> code) {
    int n = code.size();
    string res = "";
    for (int i = 0; i < n; i += 2)
    {
        for (int j = 0; j < code[i]; j++)
            res += "1";
        if (i + 1 < n)
            for (int j = 0; j < code[i + 1]; j++)
                res += "0";
    }
    return res;
}

string FirstNumberFromParityScheme (string code)
{
    if (!code.compare("AAAAAA"))
        return "0";
    if (!code.compare("AABABB"))
        return "1";
    if (!code.compare("AABBAB"))
        return "2";
    if (!code.compare("AABBBA"))
        return "3";
    if (!code.compare("ABAABB"))
        return "4";
    if (!code.compare("ABBAAB"))
        return "5";
    if (!code.compare("ABBBAA"))
        return "6";
    if (!code.compare("ABABAB"))
        return "7";
    if (!code.compare("ABABBA"))
        return "8";
    if (!code.compare("ABBABA"))
        return "9";
    return "";
}

string DecodeSymbol (string code)
{
    {
        if (!code.compare("0001101A") || !code.compare("0100111B") || !code.compare("1110010"))
            return "0";
        if (!code.compare("0011001A") || !code.compare("0110011B") || !code.compare("1100110"))
            return "1";
        if (!code.compare("0010011A") || !code.compare("0011011B") || !code.compare("1101100"))
            return "2";
        if (!code.compare("0111101A") || !code.compare("0000001B") || !code.compare("1000010"))
            return "3";
        if (!code.compare("0100011A") || !code.compare("0011101B") || !code.compare("1011100"))
            return "4";
        if (!code.compare("0110001A") || !code.compare("0111001B") || !code.compare("1001110"))
            return "5";
        if (!code.compare("0101111A") || !code.compare("0000101B") || !code.compare("1010000"))
            return "6";
        if (!code.compare("0111011A") || !code.compare("0010001B") || !code.compare("1000100"))
            return "7";
        if (!code.compare("0110111A") || !code.compare("0001001B") || !code.compare("1001000"))
            return "8";
        if (!code.compare("0001011A") || !code.compare("0010111B") || !code.compare("1110100"))
            return "9";
    }
    return "";
}

int main()
{
    auto bmpTransform = new BmpTransform();
    std::vector<int> code = bmpTransform->ReadBarCode((char*)R"(D:\Documents\Learn_3Course\TZIT\Lab4\V17s.bmp)");
    string b = ModulesToBinary(code);

    string bin[13];
    bin[0] = "";
    int i = 0, j = 0, temp = 0;
    for (i = 1; i <= 6; i++)
    {
        bin[i] = b.substr(7*i - 4, 7);
    }
    for (i = 7; i <= 12; i++)
    {
        bin[i] = b.substr(7*i + 1, 7);
    }

    string parityScheme = "";
    for (j = 1; j <= 6; j++)
    {
        temp = 0;
        for (i = 0; i < 7; i++)
            if (bin[j][i] == '1')
                temp++;
        if (temp % 2)
        {
            parityScheme += "A";
            bin[j] += "A";
        }
        else
        {
            parityScheme += "B";
            bin[j] += "B";
        }
    }
    string result = "";
    result += FirstNumberFromParityScheme(parityScheme);
    for (i = 1; i <= 12; i++)
        result += DecodeSymbol(bin[i]);
    cout << result << endl;
    return 0;
}
