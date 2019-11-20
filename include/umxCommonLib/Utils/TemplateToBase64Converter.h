/**************************************************************************************************\

	Author:		Ralph
	Created:	13.03.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __TEMPLATE_TO_BASE64_CONVERTER_H__
#define __TEMPLATE_TO_BASE64_CONVERTER_H__

#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

#include <Poco/Base64Encoder.h>

namespace TemplateConverter
{
    inline void write_INT32_LE( Poco::Int32 value, std::vector<unsigned char>& bitmap)
    {
        bitmap.push_back(static_cast<Poco::UInt8>(value & 0xff));
        bitmap.push_back(static_cast<Poco::UInt8>((value >> 8) & 0xff));
        bitmap.push_back(static_cast<Poco::UInt8>((value >> 16) & 0xff));
        bitmap.push_back(static_cast<Poco::UInt8>((value >> 24) & 0xff));
    }

    inline void write_UINT16_LE( Poco::UInt16 value, std::vector<unsigned char>& bitmap)
    {
        bitmap.push_back(static_cast<Poco::UInt8>(value & 0xff));
        bitmap.push_back(static_cast<Poco::UInt8>((value >> 8) & 0xff));
    }

    inline bool ConvertToBmp8_2( const unsigned char * pImage, int width, int height, std::vector<unsigned char>& bitmap)
    {
        int byteCounter = 0;
        // Write the header(s) using little-endian byte order
        const Poco::Int32 File_Hdr_Size  = 14;
        const Poco::Int32 Bmp_Hdr_Size   = 40;
        const Poco::Int32 Pal_Hdr_Size   = 4 * 256;
        const Poco::Int32 Total_Hdr_Size = File_Hdr_Size + Bmp_Hdr_Size + Pal_Hdr_Size;

        Poco::Int32 Row_Size       = ( ( width % 4 ) == 0 ) ? width : ( ( width | 4 ) & ( ~3 ) );
        Poco::Int32 Data_Size      = Row_Size * height;
        Poco::Int32 File_Size      = Total_Hdr_Size + Data_Size;
        const Poco::Int32 Reserved       = 0;

        const Poco::Int32 Color_Planes   = 1;
        const Poco::Int32 Bits_Per_Pixel = 8;
        const Poco::Int32 Compression    = 0;
        const Poco::Int32 H_Resolution   = 1000;
        const Poco::Int32 V_Resolution   = 1000;
        const Poco::Int32 Num_Colors     = 1 << Bits_Per_Pixel;
        const Poco::Int32 Num_Important  = 32;

        bitmap.push_back(static_cast<Poco::UInt8>('B'));byteCounter++;
        bitmap.push_back(static_cast<Poco::UInt8>('M'));byteCounter++;
        write_INT32_LE( File_Size,bitmap);byteCounter +=4;
        write_INT32_LE( Reserved,bitmap);byteCounter +=4;
        write_INT32_LE( Total_Hdr_Size,bitmap);byteCounter +=4;
        write_INT32_LE( Bmp_Hdr_Size,bitmap);byteCounter +=4;
        write_INT32_LE( width,bitmap);byteCounter +=4;
        write_INT32_LE( height,bitmap);byteCounter +=4;
        write_UINT16_LE((Poco::UInt16)   Color_Planes,bitmap);byteCounter +=2;
        write_UINT16_LE((Poco::UInt16) Bits_Per_Pixel,bitmap);byteCounter +=2;
        write_INT32_LE( Compression,bitmap);byteCounter +=4;
        write_INT32_LE( Data_Size,bitmap);byteCounter +=4;
        write_INT32_LE( H_Resolution,bitmap);byteCounter +=4;
        write_INT32_LE( V_Resolution,bitmap);byteCounter +=4;
        write_INT32_LE( Num_Colors,bitmap);byteCounter +=4;
        write_INT32_LE( Num_Important,bitmap);byteCounter +=4;
        // Write the palette header to the file
        for(Poco::Int32 iCol=0; iCol<256; iCol++)
        {
            Poco::UInt8 colour = static_cast<Poco::UInt8>(iCol);
            bitmap.push_back(colour);byteCounter++; // B
            bitmap.push_back(colour);byteCounter++; // G
            bitmap.push_back(colour);byteCounter++; // R
            bitmap.push_back(colour);byteCounter++; // Alpha
        }

        // Write the image data to the file. (Starting at the bottom of the image)
        Poco::UInt8 Pixel_Value;

        // if multiple of four, no padding, otherwise pad to next (higher) multiple
        int rowPad = ( ( width % 4 ) == 0 ) ? 0 : 4 - ( width % 4 );

        int k = 0;
        for(Poco::Int32 iY = 0; iY < (Poco::Int32)(height); iY++)
        {
            k = (iY * width);
            for( Poco::UInt32 iX = 0; iX < (Poco::UInt32)width; iX++)
            {
                Pixel_Value = pImage[k + iX];
                bitmap.push_back(Pixel_Value);byteCounter++;
            }

            // Pad the end of the row if necessary as it needs to end on a 4 byte
            // boundary
            for ( int iPad=0; iPad < rowPad; ++iPad )
            {
                bitmap.push_back(static_cast<Poco::UInt8>('0'));byteCounter++;
            }
        }

//        for(Poco::Int32 iY = (Poco::Int32)(height-1); iY >= 0; iY--)
//        {
//            for( Poco::UInt32 iX = 0; iX < (Poco::UInt32)width; iX++)
//            {
//                Pixel_Value = pImage[(iY * width) + iX];
//                bitmap.push_back(Pixel_Value);byteCounter++;
//            }

//            // Pad the end of the row if necessary as it needs to end on a 4 byte
//            // boundary
//            for ( int iPad=0; iPad < rowPad; ++iPad )
//            {
//                bitmap.push_back(static_cast<Poco::UInt8>('0'));byteCounter++;
//            }
//        }
        // Return
        return true;
    }

    inline bool ConvertToBmp24_2( const unsigned char * pImage, int width, int height, std::vector<unsigned char>& bitmap)
    {
        int byteCounter = 0;
        // Write the header(s) using little-endian byte order
        const Poco::Int32 File_Hdr_Size  = 14;
        const Poco::Int32 Bmp_Hdr_Size   = 40;
        //const Poco::Int32 Pal_Hdr_Size   = 4 * 256;
        const Poco::Int32 Total_Hdr_Size = File_Hdr_Size + Bmp_Hdr_Size; // + Pal_Hdr_Size;

        Poco::Int32 Row_Size       = ( ( width % 4 ) == 0 ) ? width : ( ( width | 4 ) & ( ~3 ) );
        Poco::Int32 Data_Size      = Row_Size * height * 3;
        Poco::Int32 File_Size      = Total_Hdr_Size + Data_Size;
        const Poco::Int32 Reserved       = 0;

        const Poco::Int32 Color_Planes   = 1;
        const Poco::Int32 Bits_Per_Pixel = 24;
        const Poco::Int32 Compression    = 0;
        const Poco::Int32 H_Resolution   = 1000;
        const Poco::Int32 V_Resolution   = 1000;
        const Poco::Int32 Num_Colors     = 0;
        const Poco::Int32 Num_Important  = 0;

        bitmap.push_back(static_cast<Poco::UInt8>('B'));byteCounter++;
        bitmap.push_back(static_cast<Poco::UInt8>('M'));byteCounter++;
        write_INT32_LE( File_Size,bitmap);byteCounter +=4;
        write_INT32_LE( Reserved,bitmap);byteCounter +=4;
        write_INT32_LE( Total_Hdr_Size,bitmap);byteCounter +=4;
        write_INT32_LE( Bmp_Hdr_Size,bitmap);byteCounter +=4;
        write_INT32_LE( width,bitmap);byteCounter +=4;
        write_INT32_LE( height,bitmap);byteCounter +=4;
        write_UINT16_LE((Poco::UInt16)   Color_Planes,bitmap);byteCounter +=2;
        write_UINT16_LE((Poco::UInt16) Bits_Per_Pixel,bitmap);byteCounter +=2;
        write_INT32_LE( Compression,bitmap);byteCounter +=4;
        write_INT32_LE( Data_Size,bitmap);byteCounter +=4;
        write_INT32_LE( H_Resolution,bitmap);byteCounter +=4;
        write_INT32_LE( V_Resolution,bitmap);byteCounter +=4;
        write_INT32_LE( Num_Colors,bitmap);byteCounter +=4;
        write_INT32_LE( Num_Important,bitmap);byteCounter +=4;
        // Write the palette header to the file
//        for(Poco::Int32 iCol=0; iCol<256; iCol++)
//	    {
//            Poco::UInt8 colour = static_cast<Poco::UInt8>(iCol);
//		    bitmap.push_back(colour);byteCounter++; // B
//		    bitmap.push_back(colour);byteCounter++; // G
//		    bitmap.push_back(colour);byteCounter++; // R
//		    bitmap.push_back(colour);byteCounter++; // Alpha
//	    }



        // Write the image data to the file. (Starting at the bottom of the image)
        Poco::UInt8 Pixel_Value;

        // if multiple of four, no padding, otherwise pad to next (higher) multiple
        int rowPad = ( ( width % 4 ) == 0 ) ? 0 : 4 - ( width % 4 );

        int k = 0;
        for(Poco::Int32 iY = 0; iY < (Poco::Int32)(height); iY++)
        {
            k = (iY * width * 3);
            for( Poco::UInt32 iX = 0; iX < (Poco::UInt32)(width * 3); iX++)
            {
                Pixel_Value = pImage[k + iX];
                bitmap.push_back(Pixel_Value);byteCounter++;
            }

            // Pad the end of the row if necessary as it needs to end on a 4 byte
            // boundary
            for ( int iPad=0; iPad < rowPad; ++iPad )
            {
                bitmap.push_back(static_cast<Poco::UInt8>('0'));byteCounter++;
            }
        }

//        for(Poco::Int32 iY = (Poco::Int32)(height-1); iY >= 0; iY--)
//        {
//            for( Poco::UInt32 iX = 0; iX < (Poco::UInt32)width; iX++)
//            {
//                Pixel_Value = pImage[(iY * width) + iX];
//                bitmap.push_back(Pixel_Value);byteCounter++;
//            }

//            // Pad the end of the row if necessary as it needs to end on a 4 byte
//            // boundary
//            for ( int iPad=0; iPad < rowPad; ++iPad )
//            {
//                bitmap.push_back(static_cast<Poco::UInt8>('0'));byteCounter++;
//            }
//        }
        // Return
        return true;
    }

    inline bool ConvertToBmp8( const unsigned char * pImage, int width, int height, std::vector<unsigned char>& bitmap)
    {
        int byteCounter = 0;
        // Write the header(s) using little-endian byte order
        const Poco::Int32 File_Hdr_Size  = 14;
        const Poco::Int32 Bmp_Hdr_Size   = 40;
        const Poco::Int32 Pal_Hdr_Size   = 4 * 256;
        const Poco::Int32 Total_Hdr_Size = File_Hdr_Size + Bmp_Hdr_Size + Pal_Hdr_Size;

        Poco::Int32 Row_Size       = ( ( width % 4 ) == 0 ) ? width : ( ( width | 4 ) & ( ~3 ) );
        Poco::Int32 Data_Size      = Row_Size * height;
        Poco::Int32 File_Size      = Total_Hdr_Size + Data_Size;
        const Poco::Int32 Reserved       = 0;

        const Poco::Int32 Color_Planes   = 1;
        const Poco::Int32 Bits_Per_Pixel = 8;
        const Poco::Int32 Compression    = 0;
        const Poco::Int32 H_Resolution   = 1000;
        const Poco::Int32 V_Resolution   = 1000;
        const Poco::Int32 Num_Colors     = 1 << Bits_Per_Pixel;
        const Poco::Int32 Num_Important  = 32;

        bitmap.push_back(static_cast<Poco::UInt8>('B'));byteCounter++;
        bitmap.push_back(static_cast<Poco::UInt8>('M'));byteCounter++;
        write_INT32_LE( File_Size,bitmap);byteCounter +=4;
        write_INT32_LE( Reserved,bitmap);byteCounter +=4;
        write_INT32_LE( Total_Hdr_Size,bitmap);byteCounter +=4;
        write_INT32_LE( Bmp_Hdr_Size,bitmap);byteCounter +=4;
        write_INT32_LE( width,bitmap);byteCounter +=4;
        write_INT32_LE( height,bitmap);byteCounter +=4;
        write_UINT16_LE((Poco::UInt16)   Color_Planes,bitmap);byteCounter +=2;
        write_UINT16_LE((Poco::UInt16) Bits_Per_Pixel,bitmap);byteCounter +=2;
        write_INT32_LE( Compression,bitmap);byteCounter +=4;
        write_INT32_LE( Data_Size,bitmap);byteCounter +=4;
        write_INT32_LE( H_Resolution,bitmap);byteCounter +=4;
        write_INT32_LE( V_Resolution,bitmap);byteCounter +=4;
        write_INT32_LE( Num_Colors,bitmap);byteCounter +=4;
        write_INT32_LE( Num_Important,bitmap);byteCounter +=4;
        // Write the palette header to the file
        for(Poco::Int32 iCol=0; iCol<256; iCol++)
        {
            Poco::UInt8 colour = static_cast<Poco::UInt8>(iCol);
            bitmap.push_back(colour);byteCounter++; // B
            bitmap.push_back(colour);byteCounter++; // G
            bitmap.push_back(colour);byteCounter++; // R
            bitmap.push_back(colour);byteCounter++; // Alpha
        }

        // Write the image data to the file. (Starting at the bottom of the image)
        Poco::UInt8 Pixel_Value;

        // if multiple of four, no padding, otherwise pad to next (higher) multiple
        int rowPad = ( ( width % 4 ) == 0 ) ? 0 : 4 - ( width % 4 );

        for(Poco::Int32 iY = (Poco::Int32)(height-1); iY >= 0; iY--)
        {
            for( Poco::UInt32 iX = 0; iX < (Poco::UInt32)width; iX++)
            {
                Pixel_Value = pImage[(iY * width) + iX];
                bitmap.push_back(Pixel_Value);byteCounter++;
            }

            // Pad the end of the row if necessary as it needs to end on a 4 byte
            // boundary
            for ( int iPad=0; iPad < rowPad; ++iPad )
            {
                bitmap.push_back(static_cast<Poco::UInt8>('0'));byteCounter++;
            }
        }
        // Return
        return true;
    }

    inline bool ConvertToBmp24( const unsigned char * pImage, int width, int height, std::vector<unsigned char>& bitmap)
    {
        int byteCounter = 0;
	    // Write the header(s) using little-endian byte order
        const Poco::Int32 File_Hdr_Size  = 14;
	    const Poco::Int32 Bmp_Hdr_Size   = 40;
	    const Poco::Int32 Pal_Hdr_Size   = 4 * 256;
	    const Poco::Int32 Total_Hdr_Size = File_Hdr_Size + Bmp_Hdr_Size + Pal_Hdr_Size;

        Poco::Int32 Row_Size       = ( ( width % 4 ) == 0 ) ? width : ( ( width | 4 ) & ( ~3 ) );
        Poco::Int32 Data_Size      = Row_Size * height * 3;
	    Poco::Int32 File_Size      = Total_Hdr_Size + Data_Size;
	    const Poco::Int32 Reserved       = 0;

	    const Poco::Int32 Color_Planes   = 1;
        const Poco::Int32 Bits_Per_Pixel = 24;
	    const Poco::Int32 Compression    = 0;
	    const Poco::Int32 H_Resolution   = 1000;
	    const Poco::Int32 V_Resolution   = 1000;
	    const Poco::Int32 Num_Colors     = 1 << Bits_Per_Pixel;
	    const Poco::Int32 Num_Important  = 32;

	    bitmap.push_back(static_cast<Poco::UInt8>('B'));byteCounter++;
	    bitmap.push_back(static_cast<Poco::UInt8>('M'));byteCounter++;
	    write_INT32_LE( File_Size,bitmap);byteCounter +=4;
	    write_INT32_LE( Reserved,bitmap);byteCounter +=4;
	    write_INT32_LE( Total_Hdr_Size,bitmap);byteCounter +=4;
	    write_INT32_LE( Bmp_Hdr_Size,bitmap);byteCounter +=4;
	    write_INT32_LE( width,bitmap);byteCounter +=4;
	    write_INT32_LE( height,bitmap);byteCounter +=4;
        write_UINT16_LE((Poco::UInt16)   Color_Planes,bitmap);byteCounter +=2;
        write_UINT16_LE((Poco::UInt16) Bits_Per_Pixel,bitmap);byteCounter +=2;
	    write_INT32_LE( Compression,bitmap);byteCounter +=4;
	    write_INT32_LE( Data_Size,bitmap);byteCounter +=4;
	    write_INT32_LE( H_Resolution,bitmap);byteCounter +=4;
	    write_INT32_LE( V_Resolution,bitmap);byteCounter +=4;
	    write_INT32_LE( Num_Colors,bitmap);byteCounter +=4;
	    write_INT32_LE( Num_Important,bitmap);byteCounter +=4;
	    // Write the palette header to the file
//        for(Poco::Int32 iCol=0; iCol<256; iCol++)
//	    {
//            Poco::UInt8 colour = static_cast<Poco::UInt8>(iCol);
//		    bitmap.push_back(colour);byteCounter++; // B
//		    bitmap.push_back(colour);byteCounter++; // G
//		    bitmap.push_back(colour);byteCounter++; // R
//		    bitmap.push_back(colour);byteCounter++; // Alpha
//	    }



	    // Write the image data to the file. (Starting at the bottom of the image)
        Poco::UInt8 Pixel_Value;

        // if multiple of four, no padding, otherwise pad to next (higher) multiple
        int rowPad = ( ( width % 4 ) == 0 ) ? 0 : 4 - ( width % 4 );

        for(Poco::Int32 iY = (Poco::Int32)(height-1); iY >= 0; iY--)
        {
            for( Poco::UInt32 iX = 0; iX < (Poco::UInt32)width; iX++)
            {
                Pixel_Value = pImage[(iY * width) + iX];
                bitmap.push_back(Pixel_Value);byteCounter++;
            }

            // Pad the end of the row if necessary as it needs to end on a 4 byte
            // boundary
            for ( int iPad=0; iPad < rowPad; ++iPad )
            {
                bitmap.push_back(static_cast<Poco::UInt8>('0'));byteCounter++;
            }
        }
	    // Return
	    return true;
    }

    inline void ConvertToBase64( const unsigned char* pTemplate, const int templateLength, std::string& base64Template )
    {
#ifndef ANDROID // need to fix - Base64Decoder
        std::ostringstream os;
        Poco::Base64Encoder encoder(os);
        std::ostream_iterator<unsigned char> osIt(encoder);
        std::copy(pTemplate, pTemplate + templateLength, osIt);
        encoder.close();
        base64Template = os.str();
#endif
    }

    inline std::string ConvertToBase64( const unsigned char* pTemplate, const int templateLength )
    {
        std::ostringstream os;
        Poco::Base64Encoder encoder(os);
        std::ostream_iterator<unsigned char> osIt(encoder);
        std::copy(pTemplate, pTemplate + templateLength, osIt);
        encoder.close();
        return os.str();
    }

    inline std::string ConvertToBase64Bmp8_2( const unsigned char* pImage, const int width, const int height )
    {
        std::vector<unsigned char> bitmap;
        std::ostringstream os;
        Poco::Base64Encoder encoder(os);
        ConvertToBmp8_2( pImage, width, height, bitmap );
        std::ostream_iterator<unsigned char> osIt(encoder);
        std::copy(bitmap.begin(), bitmap.end(), osIt);
        encoder.close();
        return os.str();
    }

    inline std::string ConvertToBase64Bmp24_2( const unsigned char* pImage, const int width, const int height )
    {
        std::vector<unsigned char> bitmap;
        std::ostringstream os;
        Poco::Base64Encoder encoder(os);
        ConvertToBmp24_2( pImage, width, height, bitmap );
        std::ostream_iterator<unsigned char> osIt(encoder);
        std::copy(bitmap.begin(), bitmap.end(), osIt);
        encoder.close();
        return os.str();
    }

    inline std::string ConvertToBase64Bmp8( const unsigned char* pImage, const int width, const int height )
    {
        std::vector<unsigned char> bitmap;
        std::ostringstream os;
        Poco::Base64Encoder encoder(os);
        ConvertToBmp8( pImage, width, height, bitmap );
        std::ostream_iterator<unsigned char> osIt(encoder);
        std::copy(bitmap.begin(), bitmap.end(), osIt);
        encoder.close();
        return os.str();
    }

    inline std::string ConvertToBase64Bmp24( const unsigned char* pImage, const int width, const int height )
    {
        std::vector<unsigned char> bitmap;
        std::ostringstream os;
        Poco::Base64Encoder encoder(os);
        ConvertToBmp24( pImage, width, height, bitmap );
        std::ostream_iterator<unsigned char> osIt(encoder);
        std::copy(bitmap.begin(), bitmap.end(), osIt);
        encoder.close();
        return os.str();
    }

    inline std::string ConvertToBase64YUVSub2( const unsigned char* pImage, const int width, const int height )
    {
        std::ostringstream os;
        Poco::Base64Encoder encoder(os);
        std::ostream_iterator<unsigned char> osIt(encoder);
        std::copy(pImage, pImage + ( width * height ), osIt);


        // bmp header
        std::vector<unsigned char> bitmap;
        int byteCounter = 0;
        // Write the header(s) using little-endian byte order
        const Poco::Int32 File_Hdr_Size  = 14;
        const Poco::Int32 Bmp_Hdr_Size   = 40;
        //const Poco::Int32 Pal_Hdr_Size   = 4 * 256;
        const Poco::Int32 Total_Hdr_Size = File_Hdr_Size + Bmp_Hdr_Size; // + Pal_Hdr_Size;

        Poco::Int32 Row_Size       = ( ( width % 4 ) == 0 ) ? width : ( ( width | 4 ) & ( ~3 ) );
        Poco::Int32 Data_Size      = Row_Size * height * 3;
        Poco::Int32 File_Size      = Total_Hdr_Size + Data_Size;
        const Poco::Int32 Reserved       = 0;

        const Poco::Int32 Color_Planes   = 1;
        const Poco::Int32 Bits_Per_Pixel = 24;
        const Poco::Int32 Compression    = 0;
        const Poco::Int32 H_Resolution   = 1000;
        const Poco::Int32 V_Resolution   = 1000;
        const Poco::Int32 Num_Colors     = 0;
        const Poco::Int32 Num_Important  = 0;

        bitmap.push_back(static_cast<Poco::UInt8>('B'));byteCounter++;
        bitmap.push_back(static_cast<Poco::UInt8>('M'));byteCounter++;
        write_INT32_LE( File_Size,bitmap);byteCounter +=4;
        write_INT32_LE( Reserved,bitmap);byteCounter +=4;
        write_INT32_LE( Total_Hdr_Size,bitmap);byteCounter +=4;
        write_INT32_LE( Bmp_Hdr_Size,bitmap);byteCounter +=4;
        write_INT32_LE( width,bitmap);byteCounter +=4;
        write_INT32_LE( height,bitmap);byteCounter +=4;
        write_UINT16_LE((Poco::UInt16)   Color_Planes,bitmap);byteCounter +=2;
        write_UINT16_LE((Poco::UInt16) Bits_Per_Pixel,bitmap);byteCounter +=2;
        write_INT32_LE( Compression,bitmap);byteCounter +=4;
        write_INT32_LE( Data_Size,bitmap);byteCounter +=4;
        write_INT32_LE( H_Resolution,bitmap);byteCounter +=4;
        write_INT32_LE( V_Resolution,bitmap);byteCounter +=4;
        write_INT32_LE( Num_Colors,bitmap);byteCounter +=4;
        write_INT32_LE( Num_Important,bitmap);byteCounter +=4;

        std::copy(bitmap.data(), bitmap.data() + Total_Hdr_Size, osIt);

        // cmi header
        unsigned char header[2];
        header[0] = 'Y';
        header[1] = 'U';
        std::copy(header, header + 2, osIt);


        encoder.close();
        return os.str();
    }
}

#endif // __TEMPLATE_TO_BASE64_CONVERTER_H__
