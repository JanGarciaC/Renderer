// =========================================
//  C++ TGA Image Library
//  Source: https://github.com/ssloy/tinyrenderer
//  This code has been slighlty modified to be more readable
// =========================================

#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

#pragma pack(push,1) // 1 byte packing
struct TGAHeader 
{
    uint8_t  idlength = 0;
    uint8_t  colormaptype = 0;
    uint8_t  datatypecode = 0;
    uint16_t colormaporigin = 0;
    uint16_t colormaplength = 0;
    uint8_t  colormapdepth = 0;
    uint16_t x_origin = 0;
    uint16_t y_origin = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t  bitsperpixel = 0;
    uint8_t  imagedescriptor = 0;
};
#pragma pack(pop) // restore previous packing

struct TGAColor 
{
    uint8_t bgra[4] = { 0,0,0,0 };
    uint8_t bytespp = 4;
    uint8_t& operator[](const int i) { return bgra[i]; }
};

struct TGAImage 
{
    enum Format { GRAYSCALE = 1, RGB = 3, RGBA = 4 };

    TGAImage() = default;
    TGAImage(const int w, const int h, const int bpp) : w(w), h(h), bpp(bpp), data(w* h* bpp, 0) {}

    bool  read_tga_file(const string filename);
    bool write_tga_file(const string filename, const bool vflip = true, const bool rle = true) const;
    void flip_horizontally();
    void flip_vertically();
    TGAColor get(const int x, const int y) const;
    void set(const int x, const int y, const TGAColor& c);
	int width()  const { return w; }
	int height() const { return h; }

private:
    bool   load_rle_data(ifstream& in);
    bool unload_rle_data(ofstream& out) const;
    int w = 0, h = 0;
    uint8_t bpp = 0;
    vector<uint8_t> data = {};
};