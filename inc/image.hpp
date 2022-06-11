#pragma once
#include <vector>
#include "matrix.hpp"

namespace img
{
    #pragma pack(1)
    struct Pixel
    {
        unsigned char b;
        unsigned char g;
        unsigned char r;
    };
    #pragma pack()

    #pragma pack(1)
    struct BMPHEADER
    {
        unsigned short    Type;
        unsigned int      Size;
        unsigned short    Reserved1;
        unsigned short    Reserved2;
        unsigned int      OffBits;
    };
    #pragma pack()

    #pragma pack(1)
    struct BMPINFO
    {
        unsigned int    Size;
        int             Width;
        int             Height;
        unsigned short  Planes;
        unsigned short  BitCount;
        unsigned int    Compression;
        unsigned int    SizeImage;
        int             XPelsPerMeter;
        int             YPelsPerMeter;
        unsigned int    ClrUsed;
        unsigned int    ClrImportant;
    };
    #pragma pack()

    using BitMap = std::vector<std::vector<Pixel>>;
    using BitVec = std::vector<Pixel>;
    using math::Vec2i;
    using math::Vec2d;
    using math::Mat22d;
    using CordMap = std::vector<std::vector<Vec2d>>;
    using CordRow = std::vector<Vec2d>;

	class Image
	{
	protected:
		int _height;
		int _width;
        BitMap _pixelMatrix;
        CordMap _coordinates;

        void writeBits(std::ofstream& out);
	};

    class BMP : public Image
    {  
    private:
        BMPHEADER _header;
        BMPINFO _info;
        void writeHead(int height, int width, std::ofstream& out);
    public:
        BMP(std::ifstream& in);
        void save(std::string way);
    };

    class JPG : public Image
    {
    private:
        // ...
    };

}