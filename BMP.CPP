#include<stdio.h>
#include<string.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
struct rgb_data {
    float r, g, b;
};

//void save_bitmap(const char *file_name, int width, int height, int dpi, rgb_type *pixel_data);



// create a file object that we will use to write our image
FILE *image;


// bitmap file header (14 bytes)
// we could be savages and just create 2 array but since this is for learning lets
// use structs so it can be parsed by someone without having to refer to the spec

// since we have a non-natural set of bytes, we must explicitly tell the
// compiler to not pad anything, on gcc the attribute alone doesn't work so
// a nifty trick is if we declare the smallest data type last the compiler
// *might* ignore padding, in some cases we can use a pragma or gcc's
// __attribute__((__packed__)) when declaring the struct
// we do this so we can have an accurate sizeof() which should be 14, however
// this won't work here since we need to order the bytes as they are written
struct bitmap_file_header {
    unsigned char   bitmap_type[2];     // 2 bytes
    int             file_size;          // 4 bytes
    short           reserved1;          // 2 bytes
    short           reserved2;          // 2 bytes
    unsigned int    offset_bits;        // 4 bytes
} bfh;

// bitmap image header (40 bytes)
struct bitmap_image_header {
    unsigned int    size_header;        // 4 bytes
    unsigned int    width;              // 4 bytes
    unsigned int    height;             // 4 bytes
    short int       planes;             // 2 bytes
    short int       bit_count;          // 2 bytes
    unsigned int    compression;        // 4 bytes
    unsigned int    image_size;         // 4 bytes
    unsigned int    ppm_x;              // 4 bytes
    unsigned int    ppm_y;              // 4 bytes
    unsigned int    clr_used;           // 4 bytes
    unsigned int    clr_important;      // 4 bytes
} bih;

// if you are on Windows you can include <windows.h>
// and make use of the BITMAPFILEHEADER and BITMAPINFOHEADER structs

void saveBMP();

void printBMP();
int main(){


 printBMP();


return 0;


}


void printBMP()
{
struct bitmap_file_header  BMP_FILE_HEADER;
struct bitmap_image_header BMP_IMG_HEADER;
 image=fopen("mybmp.bmp","rb");
	fread(&BMP_FILE_HEADER,sizeof(BMP_FILE_HEADER),1,image);
	fread(&BMP_IMG_HEADER,sizeof(BMP_IMG_HEADER),1,image);

fclose(image);

cout<<"File Type: "<<BMP_FILE_HEADER.bitmap_type[0]<<BMP_FILE_HEADER.bitmap_type[1]<< endl;
cout<<"File Size: "<<BMP_FILE_HEADER.file_size/1024<<" Kb"<<endl;
cout<<"Image Size: "<<BMP_IMG_HEADER.image_size/1024<<" Kb"<<endl;
cout<<"HEader Size: "<<BMP_IMG_HEADER.size_header<<endl;
cout<<"Image Width: "<<BMP_IMG_HEADER.width<<endl;
cout<<"Image Height: "<<BMP_IMG_HEADER.height<<endl;
cout<<"ppm-x: "<<BMP_IMG_HEADER.ppm_x<<endl;
cout<<"ppm-y: "<<BMP_IMG_HEADER.ppm_y<<endl;

		
}


void saveBMP()
{



int width=200,height=200,i;
// we want to know how many pixels to reserve
int image_size = width * height;
// a byte is 4 bits but we are creating a 24 bit image so we can represent a pixel with 3
// our final file size of our image is the width * height * 4 + size of bitmap header
int file_size = 54 + 4 * image_size;
// pixels per meter https://www.wikiwand.com/en/Dots_per_inch
int ppm = 72 * 39.375;
memcpy(&bfh.bitmap_type, "BM", 2);
bfh.file_size       = file_size;
bfh.reserved1       = 0;
bfh.reserved2       = 0;
bfh.offset_bits     = 0;
bih.size_header     = sizeof(bih);
bih.width           = width;
bih.height          = height;
bih.planes          = 1;
bih.bit_count       = 24;
bih.compression     = 0;
bih.image_size      = file_size;
bih.ppm_x           = ppm;
bih.ppm_y           = ppm;
bih.clr_used        = 0;
bih.clr_important   = 0;

image = fopen("mybmp.bmp", "wb");

// compiler woes so we will just use the constant 14 we know we have
fwrite(&bfh, 1, 14, image);
fwrite(&bih, 1, sizeof(bih), image);

// write out pixel data, one last important this to know is the ordering is backwards
// we have to go BGR as opposed to RGB
for ( i = 0; i < height; i++)
{
	for(int j=0;j<width;j++)
		{
  // rgb_data BGR = data[i];
float red   ;//=rand()%256; //(BGR.r);
   float green ;//=rand()%256; //(BGR.g);
   float blue ;// =rand()%256;// (BGR.b);

if(i<height/2)
{
red=0;
green=0; 
blue=0;
}
else
{


red=255;
green=255; 
blue=255;
}

   
   // if you don't follow BGR image will be flipped!
   unsigned char color[3] = {
       blue, green, red
   };

   fwrite(color, 1, sizeof(color), image);
                  }
}

fclose(image);






}
