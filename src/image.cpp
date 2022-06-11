#include "../inc/image.hpp"
#include <fstream>
#include <stdexcept>

namespace img
{
    BMP::BMP(std::ifstream& in) {
        if (!in.is_open())
        {
            std::cout << "No image!" << std::endl;
            return;
        }

        in.read(reinterpret_cast<char*>(&_header), sizeof(BMPHEADER));
        in.read(reinterpret_cast<char*>(&_info), sizeof(BMPINFO));

        _height = _info.Height;
        _width = _info.Width;

        for (int i = 0; i < _info.Height; i++)
        {
            BitVec row_pixels(_info.Width);
            _pixelMatrix.push_back(row_pixels);

            CordRow row_cords;
            for (int j = 0; j < _info.Width; j++)
            {
                Vec2d tmp({ {
                    { static_cast<double>(j) },
                    { static_cast<double>(i) }
                } });
                row_cords.push_back(tmp);
            }
            _coordinates.push_back(row_cords);
        }

        for (int i = 0; i < _info.Height; i++)
        {
            for (int j = 0; j < _info.Width; j++)
                in.read(reinterpret_cast<char*>(&_pixelMatrix[i][j]), sizeof(Pixel));

            if ((3 * _info.Width) % 4 != 0)
            {
                for (int j = 0; j < 4 - 3 * _info.Width % 4; j++)
                {
                    char c;
                    in.read(&c, 1);
                }
            }
        }

    }

    void BMP::writeHead(int height, int width, std::ofstream& out)
    {
        BMPHEADER bmpHeader_new;
        bmpHeader_new.Type = 0x4D42; // Type BMP (from hex)
        bmpHeader_new.Size = 14 + 40 + (3 * width * height);
        if (width % 4 != 0)
            bmpHeader_new.Size += (4 - 3 * width % 4) * height;
        bmpHeader_new.OffBits = 54;
        bmpHeader_new.Reserved1 = 0;
        bmpHeader_new.Reserved2 = 0;
        out.write(reinterpret_cast<char*>(&bmpHeader_new), sizeof(BMPHEADER));

        BMPINFO bmpInfo_new;
        bmpInfo_new.BitCount = 24;
        bmpInfo_new.ClrImportant = 0;
        bmpInfo_new.ClrUsed = 0;
        bmpInfo_new.Compression = 0;
        bmpInfo_new.Height = height;
        bmpInfo_new.Planes = 1;
        bmpInfo_new.Size = 40;
        bmpInfo_new.SizeImage = bmpHeader_new.Size - 54;
        bmpInfo_new.Width = width;
        bmpInfo_new.XPelsPerMeter = 0;
        bmpInfo_new.YPelsPerMeter = 0;
        out.write(reinterpret_cast<char*>(&bmpInfo_new), sizeof(BMPINFO));
    }

    void Image::writeBits(std::ofstream& out)
    {
        for (int i = 0; i < _height; i++)
        {
            for (int j = 0; j < _width; j++)
                out.write(reinterpret_cast<char*>(&_pixelMatrix[i][j]), sizeof(Pixel));
            if ((3 * _width) % 4 != 0)
            {
                for (int j = 0; j < 4 - 3 * _width % 4; j++)
                {
                    char c;
                    out.write(&c, 1);
                }
            }
        }
    }

    void BMP::save(std::string way)
    {
        std::ofstream out(way, std::ios::binary);
        this->writeHead(_height, _width, out);
        this->writeBits(out);
    }

}