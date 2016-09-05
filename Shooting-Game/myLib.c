/*
	JitaeKim
*/

#include "myLib.h"

u16 *videoBuffer = (u16 *) 0x6000000; // start of the video buffer
extern const unsigned char fontdata_6x8[12288];

/* setPixel4
* A mode 4 implementation of setPixel.
*/
void setPixel4(int row, int col, u8 index)
{
	int whichpixel = OFFSET(row,col,240);
	int whichShort = whichpixel/2;

	//Mode4 each pixel is represented by only 8 bits (one byte). But video memory is always written in 16 bit chunks. So 16 bits will hold two pixels. So each line would be 240/2 or 120.
	if(col&1) //chcking whether col is odd length or even length
	{
		// Odd column must insert index into left side
		videoBuffer[whichShort] = (videoBuffer[whichShort] & 0x00FF) | (index<<8);
		//clearing out rightside 8 bits
	}
	else
	{
		// Even column
		videoBuffer[whichShort] = (videoBuffer[whichShort] & 0xFF00) | index;
		//clearing out leftside 8 bits
	}
}
void drawRect4(int x, int y, int height, int width, u8 color) {
  	volatile u16 clr = color<<8 | color;
  	for(int r=0; r<height; r++) {
   		DMA[3].src = &clr;
    	DMA[3].dst = videoBuffer + OFFSET(x, y+r, 240)/2;
    	DMA[3].cnt = (width/2) | DMA_ON | DMA_SOURCE_FIXED;
  	}
}

/* drawimage4
* A function that will draw an arbitrary sized image
* onto the screen (with DMA).
* @param r row to draw the image
* @param c column to draw the image
* @param width width of the image
* @param height height of the image
* @param image Pointer to the first element of the image.
*/
void drawImage4(int row, int col, int width, int height, const u16* image)
{

	for (int y = 0; y < height; y++) {
		DMA[3].src = &image[OFFSET(y, 0, width/2)];
		DMA[3].dst = &videoBuffer[OFFSET(row + y,col, 240)/2];
		DMA[3].cnt = (width/2) | DMA_ON;
	}
}


void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void PageFlip()
{
	if(REG_DISPCNT & BUFFER1FLAG) //buffer1flag is one position
	{
		// if its true, We were displaying BUFFER1, videobuffer was buffer0
		REG_DISPCNT = REG_DISPCNT & ~BUFFER1FLAG; //clearing a bit
		videoBuffer = BUFFER1;
	}
	else
	{
		REG_DISPCNT = REG_DISPCNT | BUFFER1FLAG;
		videoBuffer = BUFFER0;
	}
}

void fillScreen4(u8 index) 
{
	volatile u16 color = index | (index << 8);
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = ((240 * 160) / 2) | DMA_ON | DMA_SOURCE_FIXED;
}


void fillPalette(const short unsigned int *palette) {
  for (int i=0; i<255; i++) {
    PALETTE[i] = palette[i];
  }
}
void drawChar4(int row, int col, char ch, u8 index)
{
	int r,c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[(r*6+c)+(48*ch)] == 1)
			{
				setPixel4(row+r, col+c, index);
			}
		}
	}
}

void drawString4(int row, int col, char *str, u8 index)
{
	while(*str)
	{
		drawChar4(row, col, *str++, index);
		col += 6;
	}
}
void delay(int n) 
{
	volatile int x = 0;
	for (int i = 0; i < n*10000; i++) {
		x++;
	} 	
}

