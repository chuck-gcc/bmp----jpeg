# Just playing with the raw data of bmp image.

open a file descriptor and read each bytes as unsigned char.

Build a structure object designed by the bmp file format.

## first step undersand and display the raw data in different format. The calme before the storm


``` bash

export IMG_PATH="your image path"

make run

```

Start fonction: 
display header

File signature: BM
File size: 873234 kb
Offset Data: 54 kb

Start fonction: display header info

Size info header: 40 kb
Image width: 660 px
Image height: 441 px
Plane: 1 kb
B_per_pixel: 24 kb
Compression type: 0 kb
Image size: 873180 kb
XpixelsPerM: 2834 kb
YpixelsPerM: 2834 kb
Color used: 0 kb
Color: 0 kb

Start fonction: display hex header info

Size info header:00000000000000000000000000101000
Image width: 00000000000000000000001010010100
Image height: 00000000000000000000000110111001
Plane: 00000000000000000000000000000001
B_per_pixel:00000000000000000000000000011000
Compression type: 00000000000000000000000000000000
Image size:00000000000011010101001011011100
XpixelsPerM:00000000000000000000101100010010
YpixelsPerM00000000000000000000101100010010
Color used00000000000000000000000000000000
Color:00000000000000000000000000000000

Start fonction: display hex header info

Size info header:0x00028
Image width: 0x00294
Image height: 0x001B9
Plane: 0x01
B_per_pixel: 0x018
Compression type: 0x0000
Image size: 0x0D52DC
XpixelsPerM: 0x00B12
YpixelsPerM: 0x00B12
Color used: 0x0000
Color: 0x0000


## build 3d matrice:    

number of line = info.height
number of column = info.width  
depth = 3 (rgb)

[ 
    [ [255, 255, 0],[255, 255, 0], ... ],
    [ [255, 255, 0],[255, 255, 0], ... ],
    ...
]

## build jpeg compressor / decompressor

## explore some test in gpu programmation on image.

