typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;

#define WIDTH 240
#define HEIGHT 160

#define REG_DISPCNT *(u16 *)0x4000000
#define MODE3 3
#define MODE4 4

#define BUFFER0 (u16 *)0x6000000
#define BUFFER1 (u16 *)0x600A000
#define BUFFER1FLAG (1<<4)
#define PALETTE ((u16 *)0x5000000)

//Background Enables
#define BG0_ENABLE  (1<<8)
#define BG1_ENABLE  (1<<9)
#define BG2_ENABLE  (1<<10)
#define BG3_ENABLE  (1<<11)


//background control registers
#define REG_BG0CNT *(volatile unsigned short*)0x4000008
#define REG_BG1CNT *(volatile unsigned short*)0x400000A
#define REG_BG2CNT *(volatile unsigned short*)0x400000C
#define REG_BG3CNT *(volatile unsigned short*)0x400000E


#define BG2_ENABLE (1<<10)
#define COLOR(r,g,b) ((r) | (g) << 5 | (b) << 10)
#define RED COLOR(31,0,0)
#define WHITE COLOR(31,31,31)
#define BLACK 0
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define CYAN COLOR(0,31,31)
#define MAGENTA COLOR(31,0,31)
#define YELLOW COLOR(31, 31, 0)
#define LTGRAY COLOR(20, 20, 20)

#define OFFSET(r, c, rowlen) ((r)*(rowlen)+(c))

/* Buttons */

#define BUTTON_A      (1<<0)
#define BUTTON_B      (1<<1)
#define BUTTON_SELECT (1<<2)
#define BUTTON_START  (1<<3)
#define BUTTON_RIGHT  (1<<4)
#define BUTTON_LEFT   (1<<5)
#define BUTTON_UP     (1<<6)
#define BUTTON_DOWN   (1<<7)
#define BUTTON_R      (1<<8)
#define BUTTON_L      (1<<9)



#define BUTTONS (*( volatile unsigned int *)0x04000130)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define SCANLINECOUNTER (*(volatile unsigned short *)0x4000006)

/* DMA      NOTE!!! USES U32...don't forget to typedef it */

typedef struct 
{
	const volatile void *src;
	volatile void *dst;
	volatile u32 cnt;
} DMAREC;

#define DMA ((volatile DMAREC *)0x040000B0)

#define REG_DMA0SAD         *(u32*)0x40000B0  // source address
#define REG_DMA0DAD         *(u32*)0x40000B4  // destination address
#define REG_DMA0CNT         *(u32*)0x40000B8  // control register

/* DMA channel 1 register definitions */
#define REG_DMA1SAD         *(u32*)0x40000BC  // source address
#define REG_DMA1DAD         *(u32*)0x40000C0  // destination address
#define REG_DMA1CNT         *(u32*)0x40000C4  // control register

/* DMA channel 2 register definitions */
#define REG_DMA2SAD         *(u32*)0x40000C8  // source address
#define REG_DMA2DAD         *(u32*)0x40000CC  // destination address
#define REG_DMA2CNT         *(u32*)0x40000D0  // control register

/* DMA channel 3 register definitions */
#define REG_DMA3SAD         *(u32*)0x40000D4  // source address
#define REG_DMA3DAD         *(u32*)0x40000D8  // destination address
#define REG_DMA3CNT         *(u32*)0x40000DC  // control register

/* Defines */
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define START_ON_FIFO_EMPTY 0x30000000



extern u16 *videoBuffer;


// Prototypes
void setPixel4(int row, int col, u8 index);
void drawImage4(int row, int col, int height, int width, const u16* image);
void fillPalette(const short unsigned int *palette);
void drawChar4(int row, int col, char ch, u8 index);
void drawString4(int row, int col, char *str, u8 index);
void PageFlip();
void waitForVblank();
void drawRect4(int r, int c, int width, int height, u8 color);
void setup();
void fillScreen4(u8 index);
void delay(int n);
void drawRect(int x, int y, int width, int height, u16 color);
typedef struct
{
    int x;
    int y;
    int height;
    int width;
    int oldx;
    int oldy;
    int isplayer;	
    const u16* image;

}Object;


typedef struct
{
	int row, col;
	int rd, cd;
	int width, height;
	int up, down, left, right;	
	const u16* image;
	int exist;
	int bulletRow, bulletCol;
	u16 color;	
}M_OBJECT;

typedef struct
{
    int x;
    int y;
    int height;
    int width;
    int oldx;
    int oldy;
    int isenemy;
    int drop;
    	const u16* image;
}ENEMY;

typedef struct {
	int x;
	int y;
	int dx;
	int right, down;
	const u16* image1;
	const u16* image2;
	const u16* image3;
	const u16* image4;
	const u16* image5;
}SNAKE;

