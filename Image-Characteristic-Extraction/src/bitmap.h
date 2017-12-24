#pragma once
#include<d3d9.h>
#include<D3d9types.h>
#include<iostream>
#include "image.h"
struct BitmapFileHeader {         
	unsigned int size;                       /* File size in bytes          */
	unsigned short int reserved1, reserved2;
	unsigned int offset;                     /* Offset to image data, bytes */
} ;

struct BitmapInfoHeader {
	unsigned int Headersize;               /* Header size in bytes      */
	int width, height;                /* Width and height of image */
	unsigned short int planes;       /* Number of colour planes   */
	unsigned short int bits;         /* Bits per pixel            */
	unsigned int compression;        /* Compression type          */
	unsigned int imagesize;          /* Image size in bytes       */
	int xresolution, yresolution;     /* Pixels per meter          */
	unsigned int ncolours;           /* Number of colours         */
	unsigned int importantcolours;   /* Important colours         */
} ;
struct Piexl24
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;

};
struct Piexl32
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char alpha;
};
struct Piexl4
{
	unsigned char blue;
};

void LoadBmp(img_config&config,D3DCOLOR* surface,std::string src);
void LoadBmp4(D3DCOLOR** surface, std::string src);
