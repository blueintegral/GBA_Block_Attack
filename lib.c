// myLib.c
//
#include "lib.h"
#include "PressEnter.h"
#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include "nuclear_blast.h"
#include "GameOver.h"
#include "win.h"
#include "StartScreen.h"
#include "StartScreen4.h"



#ifdef _DEBUG
FILE *debug;
#else
volatile u16 *scanlineCounter = (volatile u16 *) 0X4000006;
volatile u16 *keyRegister = (volatile u16 *) 0X4000130;
u16 *PALETTE_MEM = (u16 *) 0X5000000;
// videobuffer is a vector of u16s
u16 *videobuffer = (u16 *) 0X6000000;
u16 *frontbuffer = (u16 *) 0X6000000;
u16 *backbuffer =  (u16 *) 0X600A000;
#endif

void FlipPage(int status) {
#ifdef _DEBUG
	fprintf(debug,"Flipped the page\n");
#else
	if(status == 1){
	if(REG_DISPCNT & DRAW_BACK_BUFFER) {
		// he's displaying the back buffer
		// tell him to disp the front one
		REG_DISPCNT = REG_DISPCNT & ~DRAW_BACK_BUFFER;
		// let us draw the back one
		videobuffer = backbuffer;
	} else {
		// he's displaying the back buffer
		// tell him to disp the front one
		REG_DISPCNT = REG_DISPCNT | DRAW_BACK_BUFFER;
		// let us draw the back one
		videobuffer = frontbuffer;
	}
	}
	 else { 
		REG_DISPCNT = 1027;
		videobuffer = frontbuffer;
	
		
	}
	

#endif
}
/* this is messy
   we will fetch an item out of videobuffer
   decide whether we're going into left side or right side
   or it in
   replace the video buffer entry
*/
void setPixel4(int r, int c, int value) {
#ifdef _DEBUG
	fprintf(debug,"setPixel4(%d, %d, %X)\n",
		r, c, value);
#else
	int offset = OFFSET(r, c);
	int index = offset / 2;
	u16 vidV = videobuffer[index];
	if( c & 1 ) {  // an odd numbered column
		vidV = (vidV & 0XFF) | (value << 8);
	} else {
		vidV = (vidV & 0XFF00) | (value & 0XFF);
	}
	videobuffer[index] = vidV;
#endif
}


void drawLineMode4(int row, int col, int width, int index) {
 	int c;
	for(c = 0; c < width; c++) {
		setPixel4 ( row, c + col, index);
	}
}


void drawRectMode4( int row, int col, 
				   int height, int width, int index ) {
	int r;
//     init; test; increment    
	for(r = 0; r < height; ++r) {
	// code body
		drawLineMode4(row+r, col, width, index);
	}
}


void drawRectDMAMode4( int row, int col, 
				   int height, int width, int index ) {
#ifdef _DEBUG
	fprintf(debug,"drawRectDMAMode4(%d, %d, %d, %d, %d)\n",
		row, col, height, width, index);
#else
	int r;
	volatile u16 it = index | (index << 8);
	int offset;
//     init; test; increment    
	for(r = 0; r < height; ++r) {
	// DMA the correct line
	    offset = OFFSET(row + r, col)/2;
	    DMA_MEMFILL3_SHRT(videobuffer + offset,
			  &it, width/2);
	}
#endif
}


void initializeGBA(u16 mode) {
#ifdef _DEBUG
	debug = fopen("debug.log","w");
	fprintf(debug,"Opened the debug log file\n");
#else
	//DMA_MEMCOPY3_SHRT(PALETTE_MEM, viewPal, 256);
	REG_DISPCNT = BG2_ENABLE | mode;
#endif
}

bool keepGoing() {
#ifdef _DEBUG
	bool res = (t < 50);
	if(!res) {
		printf("Program ended\n");
		getchar();
	}
	return res;
#else
	return true;
#endif
}


bool keyHit(int theKey){
#ifdef _DEBUG
	return true;
#else
	return !(*keyRegister & theKey);
#endif
}


void waitForVBlank(int on) {
#ifndef _DEBUG
	
	while((*scanlineCounter > 159) && on);
	while((*scanlineCounter < 160) && on);
	

#endif
}



void drawBackground(int code) {
#ifdef _DEBUG
	fprintf(debug,"drawBackground(%d\n",
		code);
#else

	switch(code) {
		case 8:
			DMA_MEMCOPY3_SHRT( videobuffer,
						nuclear_blastBitmap, 38400);
			break;

		case 6:
			DMA_MEMCOPY3_SHRT( videobuffer,
						StartScreenBitmap, 38400);
			break;

		case 5:
			DMA_MEMCOPY3_SHRT( videobuffer,
						StartScreen4Bitmap, 38400);
			break;


		case 7:
			DMA_MEMCOPY3_SHRT( videobuffer,
						winBitmap, 38400);
			break;

		case 1:
			DMA_MEMCOPY3_SHRT( videobuffer,
						GameOverBitmap, 38400);
			break;

			case 0:
			DMA_MEMCOPY3_SHRT( videobuffer,
						PressEnterBitmap, 38400);
			break;

	}
#endif
}






void paintBackground(const u16 map[]) {
#ifdef _DEBUG
	fprintf(debug,"Painted background\n");
#else
	DMA_MEMCOPY3_SHRT(videobuffer, map, viewBitmapLen/2);
#endif
}

void drawLine(int row, int col, int width, u16 color) {
#ifdef _DEBUG
	fprintf(debug,"drawLine(%d, %d, %d, %X\n",
		row, col, width, color);
#else
 	int c;
	for(c = 0; c < width; c++) {
	 	 videobuffer[OFFSET(row, c + col)] = color;
	}
#endif
}


void drawRect(int row, int col, 
              int height, int width, u16 color ) {
	int r;
//     init; test; increment    
	for(r = 0; r < height; ++r) {
	// code body
		drawLine(row+r, col, width, color);
	}
}

void drawRectDMA(int row, int col, 
              int height, int width, u16 color ) {
#ifdef _DEBUG
	fprintf(debug,"drawRectDMA(%d, %d, %d, %d, %X\n",
		row, col, height, width, color);
#else
	int r;
	volatile u16 clr = color;
	u16 *dest;
//     init; test; increment    
	for(r = 0; r < height; ++r) {
		dest = videobuffer + OFFSET(row+r, col);
//		drawLine(row+r, col, width, color);
		DMA_MEMFILL3_SHRT(dest, &clr, width);
	}
#endif
}



void pause()
{
  while(keyHit(BUTTON_START));
  while(!keyHit(BUTTON_START));
  while(keyHit(BUTTON_START));
}

void GBASetup() {
	REG_DISPCNT = 1027;
}

int randGen(){
int out;
	out = (int)((double)rand() / ((double)RAND_MAX + 1)*2);
return out;
}

void FlipPage2() {
#ifndef _DEBUG
	if(REG_DISPCNT & DRAW_BACK_BUFFER) {
		// he's displaying the back buffer
		// tell him to disp the front one
		REG_DISPCNT = REG_DISPCNT & ~DRAW_BACK_BUFFER;
		// let us draw the back one
		videobuffer = backbuffer;
	} else {
		// he's displaying the back buffer
		// tell him to disp the front one
		REG_DISPCNT = REG_DISPCNT | DRAW_BACK_BUFFER;
		// let us draw the back one
		videobuffer = frontbuffer;
	}
#endif
}


BUTTON_STATE theButton[] = {B_OFF, B_OFF, B_OFF,
            B_OFF, B_OFF, B_OFF, B_OFF, B_OFF};


BUTTON_STATE keyState(int key) {
#ifdef _DEBUG
	return true;
#else
	switch(theButton[key]) {
		case B_OFF:
			if(keyHit(1<<key)) 
				theButton[key] = B_PRESSED;
			break;
		case B_PRESSED:
			if(keyHit(1<<key)) 
				theButton[key] = B_ON;
			else
				theButton[key] = B_RELEASED;
			break;
		case B_ON:
			if(!keyHit(1<<key)) 
				theButton[key] = B_RELEASED;
			break;
		case B_RELEASED:
			if(keyHit(1<<key)) 
				theButton[key] = B_PRESSED;
			else
				theButton[key] = B_OFF;
			break;
	}
	return theButton[key];
#endif
}

int retreatCheck(int comp_health, int margin){
	if((comp_health <= 50) && (comp_health >=(margin))){
		return 1;
	} else {
		return 0;
	}
}

int attackCheck(int comp_health){
	if(comp_health >50){
		return 1;
	} else {
		return 0;
	}
}

int inRadius(int c2, int death_radius, int c, int human_size, int r2, int r, int size){
	if(((c2-death_radius) <= (c+human_size)) && \
					((r2-death_radius)<=(r)) && \
					(((c2+size+death_radius)>=(c+human_size)) && \
					((r2+size+death_radius)>=r+human_size))){ 
						return 1;
	} else {
		return 0;
	}
}





