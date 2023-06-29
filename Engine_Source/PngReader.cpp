#include "PngReader.h"

//roka::IHDRInfo roka::PngReader::Read(const unsigned char* data)
//{
//    IHDRInfo result = {};
//    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//    if (!png)
//    {
//        //error
//        return result;
//    }
//
//    png_infop info = png_create_info_struct(png);
//    if (!info)
//    {
//        //error
//        png_destroy_read_struct(&png, NULL, NULL);
//        return result;
//    }
//
//    if (setjmp(png_jmpbuf(png)))
//    {
//        //error
//        png_destroy_read_struct(&png, &info, NULL);
//        return result;
//    }
//
//    png_set_read_fn(png, static_cast<png_voidp>(const_cast<unsigned char*>(data)), [](png_structp png_ptr, png_bytep data, png_size_t length)
//        {
//            png_voidp io_ptr = png_get_io_ptr(png_ptr);
//        });
//
//    return result;
//}
//

