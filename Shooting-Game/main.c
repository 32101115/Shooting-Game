/*
	JitaeKim
*/


#include <stdlib.h> // Include this because we are using rand
#include <stdio.h> // Include this header because we are using sprintf
#include "myLib.h"
#include "ColorPalette.h"
#include "screen.h"
#include <stdlib.h>
#include <stdio.h>
#define BULLETCOUNT 12


char buffer[41];

int stage;
int gameon;
int shoot1, shoot2;
int bulletIndex;
int life;
int Frame = 0;
int numOfSnakes;
int OldNum = 0;
SNAKE snakes[20];
int count = 0;
int status;

ENEMY enemy[10];
Object player;
//Prototype
void setup();
void game();
void playerMovement();
void PageFlip();
void setBulletShadow(int index, int r, int c);
void getBulletShadow(int index, int r, int c);
void bulletFire(int i);
void fire();
void play();
void initialize();
void SnakesMovement(); 
void lose();
void collisionCheck();
void end();
void win();

M_OBJECT bullet[BULLETCOUNT];
u16 colors[BULLETCOUNT][4];

int main()
{
	REG_DISPCNT = MODE4 | BG2_ENABLE;
	
	setup();
	while(1)	
	{	
		if(KEY_DOWN_NOW(BUTTON_START) && status ==0 )
		{
		status = 1;
		initialize();

		}
		if (status == 1)
		{
			play();
		}

	}
	return(0);
}
		



void setup()
{	
	//pre-game screen

	status = 0;
	PALETTE[0] = BLACK;
	fillPalette(screen_palette);
	drawImage4(0,0, 302, 198, titlescreen);
	PALETTE[1] = RED;
	sprintf(buffer, "Press ENTER to start");
	drawString4(70, 55, buffer, 1);
	sprintf(buffer, "Z: Bullet fire");
	drawString4(90, 55, buffer, 1);
	sprintf(buffer, "Defense");
	drawString4(80, 55, buffer, 1);
	stage = 1;
	life = 3;
	numOfSnakes = 0 ;
	OldNum = 0;

}
void initialize()
{
	player.y = 50; //initial setting position of player in the middle
	player.x = 1;
	player.oldy= player.y;
	player.oldx = player.x;
	numOfSnakes = 1 + OldNum ;

		bulletIndex = 0;
	for(int i = 0; i < BULLETCOUNT; i++)
	{	bullet[i].exist = 0;
	}

	int dist = 0;
	
	for (int i = 0; i < numOfSnakes; i++) 
	{
		
		snakes[i].x = 210-dist;
		snakes[i].y = (rand()%120)+10; 
		snakes[i].dx = -1;
		snakes[i].image1 = snake1;
		snakes[i].image2 = snake2;
		snakes[i].image3 = snake3;
		snakes[i].image4 = snake4;
		snakes[i].image5 = snake5;
		dist += (rand()%10);
		
	}

}

void play()
{
	PALETTE[0] = BLACK;
	PALETTE[1] = RED;
	fillScreen4(0); //fill screen with black
	switch(life)
	{
		case 3:
			sprintf(buffer, "Life : 3 ");
			drawString4(0, 30, buffer, 1);
			break;
		case 2: 
			sprintf(buffer, "Life : 2 ");
			drawString4(0, 30, buffer, 1);
			break;
		case 1:
			sprintf(buffer, "Life : 1 ");
			drawString4(0, 30, buffer, 1);
			break;

	}

	switch(stage)
	{
		case 1:
			sprintf(buffer, "Stage : 1 ");
			drawString4(0, 100, buffer, 1);
			break;
		case 2: 
			sprintf(buffer, "Stage : 2 ");
			drawString4(0, 100, buffer, 1);
			break;
		case 3:
			sprintf(buffer, "Last Stage");
			drawString4(0, 100, buffer, 1);
			break;
	
	}
	SnakesMovement();
	playerMovement();

	fire();
	collisionCheck();
	waitForVblank();

	if(life ==0)
	{	
		fillPalette(screen_palette);
		drawImage4(0,0, 240, 160, GameEnd);
		sprintf(buffer, "You lose!");
		drawString4(40, 50, buffer, PALETTE[56]);
		PageFlip();	
		player.x = 300;
		player.y = 200;
		while(status == 1)
		{
			if(KEY_DOWN_NOW(BUTTON_SELECT))
			{
				setup();	
				PageFlip();
				status = 0;

			}	
		}
	}
	if(stage ==4)
	{
		
		fillPalette(screen_palette);
		drawImage4(0,0, 240, 160, GameWin);
		PageFlip();	
		player.x = 300;
		player.y = 200;
		while(status == 1)
		{
			if(KEY_DOWN_NOW(BUTTON_SELECT))
			{
				setup();	
				PageFlip();
				status = 0;

			}	
		}
	}

	if(KEY_DOWN_NOW(BUTTON_SELECT)) //using select key go back to title screen.
	{
		setup();
	}
	PageFlip();
	
	
}


void playerMovement()
{		
	fillPalette(Player_palette);
	drawImage4(player.y, player.x,PLAYER_WIDTH,PLAYER_HEIGHT,Player);
	player.oldy = 3;
	player.oldx = 3;	
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			player.y -=player.oldy;
			drawImage4(player.y, player.x,PLAYER_WIDTH,PLAYER_HEIGHT,Player);
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			player.y +=player.oldx;
			drawImage4(player.y, player.x,PLAYER_WIDTH,PLAYER_HEIGHT,Player);
		}
		if(player.y <= 1) player.y = 1; // limit row
        	if(player.y >= 160- PLAYER_HEIGHT) player.y = 160-PLAYER_HEIGHT;


}
void SnakesMovement() 
{

	for (int i = 0; i < numOfSnakes; i++) 
	{	
		snakes[i].x += snakes[i].dx;
		switch (Frame) 
		{
			case 1:
				drawImage4(snakes[i].y, snakes[i].x, 30, 14, snakes[i].image1);
				break;
			case 2:
				drawImage4(snakes[i].y, snakes[i].x, 30, 14, snakes[i].image2);
				break;
			case 3:
				drawImage4(snakes[i].y, snakes[i].x, 30, 14, snakes[i].image3);
				break;
			case 4:
				drawImage4(snakes[i].y, snakes[i].x, 30, 14, snakes[i].image4);
				break;
			case 5:
				drawImage4(snakes[i].y, snakes[i].x, 30, 14, snakes[i].image5);
				break;
			case 6:
				drawImage4(snakes[i].y, snakes[i].x, 30, 14, snakes[i].image4);
				break;
			case 7:
				drawImage4(snakes[i].y, snakes[i].x, 30, 14, snakes[i].image3);
				break;
			case 8:
				drawImage4(snakes[i].y, snakes[i].x, 30, 14, snakes[i].image2);
				break;
			default:
				drawImage4(snakes[i].y, snakes[i].x, 30, 14, snakes[i].image1);
				Frame = 0;
		}

		Frame++;
	}
}


void bulletFire(int i)
{	
	bullet[i].row = player.y + 15;
	bullet[i].col = player.x + 30;
	bullet[i].cd = 5;
	bullet[i].width = 2;
	bullet[i].height = 2;
	bullet[i].left = bullet[i].col;
	bullet[i].right = bullet[i].col + 1;
	bullet[i].up = bullet[i].row;
	bullet[i].down = bullet[i].row + 1;
	bullet[i].exist = 1;
}

void fire()
{
	if(KEY_DOWN_NOW(BUTTON_A))
		shoot1 = 1;
	if(shoot2 == 1 && shoot1 == 0)	//bullet fire. can't continuously click
	{
		bulletFire(bulletIndex);
		bulletIndex++;
	}
	shoot2 = shoot1;
	shoot1 = 0;
	

	for(int i = 0; i < BULLETCOUNT; i++)		//bullet movement
	{
		if(bullet[i].exist)
		{	

			if(bullet[i].col >= 240 - bullet[i].cd)	//if bullet reaches the end of screen
			{
				bullet[i].exist = 0;
			}
			else					//move bullet
			{
				bullet[i].col += bullet[i].cd;
				drawRect4(bullet[i].row, bullet[i].col, 5, 10, PALETTE[56]);
				bullet[i].left = bullet[i].col;
				bullet[i].right = bullet[i].col + 1;
			}
		}		
	}
}


void collisionCheck()
{

	for (int i = 0; i < numOfSnakes; i++) 
	{
		snakes[i].right = snakes[i].x + 30 - 1;
		snakes[i].down = snakes[i].y + 14 - 1;
		if (player.x + 30 >= snakes[i].x && player.x <= snakes[i].x + 30  &&
		    player.y + 40 >= snakes[i].y && player.y <= snakes[i].y + 14) 
		    {
			lose();
		    }
		else if(snakes[i].x < 1)
		{
			lose();
		}
		
	
		for(int j = 0; j < BULLETCOUNT; j++)
			if(bullet[j].exist)
				if((snakes[i].x <= bullet[j].right)&&(snakes[i].y <= bullet[j].down)&&(snakes[i].down >= bullet[j].up)&&
					(snakes[i].right >= bullet[j].left))
							{	
							bullet[j].exist = 0;
							numOfSnakes --;

							count ++;
							}
							

	}
	if (numOfSnakes == 0)
	{
		OldNum++; 
		stage++;
		initialize();
	}
	

}
void lose()
{
	life--;
	
	initialize();

}

/*
void win()
{
	fillPalette(screen_palette);
	drawImage4(0,0, 240, 160, GameWin);
	PageFlip();	
	numOfSnakes =0;
	player.x = 300;
	player.y = 200;
	while(1)
	{
		if(KEY_DOWN_NOW(BUTTON_SELECT))
		{
			setup();	
			PageFlip();

		}	
	}
	
}


void end()
{

	fillPalette(screen_palette);
	drawImage4(0,0, 240, 160, GameEnd);
	sprintf(buffer, "You lose!");
	drawString4(40, 50, buffer, PALETTE[56]);
	PageFlip();	
	numOfSnakes =0;
	player.x = 300;
	player.y = 200;
	while(1)
	{
		if(KEY_DOWN_NOW(BUTTON_SELECT))
		{
			setup();	
			PageFlip();

		}	
	}
}
*/