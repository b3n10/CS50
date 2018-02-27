# Questions

## What's `stdint.h`?

Provides typedefs and macros for fixed-width integral types in accordance with the C99 standard. It's definitions'help ensure code portability across platforms and compilers.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

It enhances the portability of programs. These types are especially useful in embedded environments.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

`BYTE` - 1 byte
`DWORD` - 4 bytes
`LONG` - 4 bytes
`WORD` - 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first two bytes of any BMP file in ASCII is `BM`, 66 in `decimal` and 0x42 in `hexadecimal`.

## What's the difference between `bfSize` and `biSize`?

`bfSize` is the size, in bytes, of the bitmap file, while `biSize` is the number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

If `biHeight` is negative, indicating a top-down bitmap, meaning bitmap cannot be compressed.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount` determines the number of bits that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

`fopen` may return `NULL` value if the file being opened or created doesn't exist or could also be a problem in file permission.

## Why is the third argument to `fread` always `1` in our code?

It means that the program only reads 1 byte of data from the file pointer.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3 is the value assigned to `padding` if `bi.biWidth` is 3

## What does `fseek` do?

`fseek` rewind or fast-forward over padding, if any, within a file

## What is `SEEK_CUR`?

`SEEK_CUR` is the current position indicator.
