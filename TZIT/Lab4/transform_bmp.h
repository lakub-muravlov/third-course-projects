//
// Created by Kub on 12/21/2020.
//

#ifndef LAB4_TRANSFORM_BMP_H
#define LAB4_TRANSFORM_BMP_H
#pragma once
#include <string>
#include <vector>
#include <fstream>
class BmpTransform {
private:
    int _imgWidth;
    int _imgHeigth;
    const int _zoom = 4;
public:
    BmpTransform()
    {
        this->_imgHeigth = 0;
        this->_imgWidth = 0;
    }

    std::vector<int> ReadBarCode(char* filePath)
    {
        FILE* f = fopen(filePath, "rb");
        unsigned char info[54];
        unsigned char* buff{};
        fread(info, sizeof(unsigned char), 54, f);
        this->_imgWidth = *(int*)&info[18];
        this->_imgHeigth = *(int*)&info[22];

        std::vector <std::vector <unsigned char*> > data(this->_imgHeigth);
        for (int i = 0; i < this->_imgHeigth; i++)
        {
            for (int j = 0; j < this->_imgWidth; j++)
            {
                buff = new unsigned char[3];
                fread(buff, sizeof(unsigned char), 3, f);
                std::swap(buff[0], buff[2]);
                data[i].push_back(buff);
            }
            fread(buff, sizeof(unsigned char), 3, f);
        }
        fclose(f);
        int i = this->_imgHeigth / 2, j = 0, temp = 0;
        int mint = 1e6;
        std::vector <int> code;
        while ((int)data[i][j][0] == 255)
        {
            j++;
        }
        while (j < this->_imgWidth)
        {
            temp = 0;
            while (j < this->_imgWidth && (!data[i][j][0]))
            {
                temp++;
                j++;
            }
            if (temp != 0)
            {
                code.push_back(temp);
                if (temp < mint)
                    mint = temp;
            }

            temp = 0;
            while (j < this->_imgWidth && data[i][j][0])
            {
                temp++;
                j++;
            }
            if (temp != 0)
            {
                code.push_back(temp);
                if (temp < mint)
                    mint = temp;
            }
        }

        code.pop_back();
        code.pop_back();

        for (int& x : code)
            x /= this->_zoom;
        return code;
    }

};

#endif //LAB4_TRANSFORM_BMP_H
