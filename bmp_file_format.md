# BMP FILE FORMAT

# Header
The fist 14 bytes of data of the bmp file are the header data.
The structure of the header is:

Signature 	2 bytes 	0000h 	'BM'
FileSize 	4 bytes 	0002h 	File size in bytes
reserved 	4 bytes 	0006h 	unused (=0)
DataOffset 	4 bytes 	000Ah 	Offset from beginning of file to the beginning of the bitmap data

# Info header


The next 40 bytes are the info header data.
The structure of info header data is:

Width 	        4 bytes 	0012h 	Horizontal width of bitmap in pixels
Height 	        4 bytes 	0016h 	Vertical height of bitmap in pixels
Planes 	        2 bytes 	001Ah 	Number of Planes (=1)
Bits Per Pixel 	2 bytes 	001Ch

(Bits per Pixel used to store palette entry information. This also identifies in an indirect way the number of possible colors. Possible values are:
1 = monochrome palette. NumColors = 1  
4 = 4bit palletized. NumColors = 16  
8 = 8bit palletized. NumColors = 256 
16 = 16bit RGB. NumColors = 65536
24 = 24bit RGB. NumColors = 16M)

Compression 	4 bytes 	001Eh 	

(Type of Compression  
0 = BI_RGB   no compression  
1 = BI_RLE8 8bit RLE encoding  
2 = BI_RLE4 4bit RLE encoding)

ImageSize 	4 bytes 	0022h 	

(compressed Size of Image 
It is valid to set this =0 if Compression = 0
XpixelsPerM 	4 bytes 	0026h 	horizontal resolution: Pixels/meter)

YpixelsPerM 	4 bytes 	002Ah 	vertical resolution: Pixels/meter
Colors Used 	4 bytes 	002Eh 	

(Number of actually used colors. For a 8-bit / pixel bitmap this will be 100h or 256).

Important Colors 	4 bytes 	0032h
 	
(Number of important colors 0 = all)