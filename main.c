
/////////////////////////////////////////////////////////// 
//  Name         : Hunter Scott
// T-Square login ID : hscott7
// Homework     : Project 2
// Collaboration: 
//                 "I worked on the homework assignment alone" 
//                 

/* to do:
DONE-add better comments
DONE-clean up old comments
DONE-add prototypes of new functions to lib.h
-add sprites?
-add sound
DONE-finish implementing human side of AI algorithm
DONE-implement it with BST
DONE-add a structure
*/

/* to fix:
-put in correct health, death radius, enable human death, computer death rate, etc for final version
DONE-eliminate all warnings on compile
DONE-Splash screen doesn't work. use mode 3 and try mode 4 somewhere else?
-random times the thing loads wrong
DONE-state change doesn't work
DONE-computer health won't go to 0 for some reason (win check doesn't work)
*/

/* questions
KINDA-maybe simplify ai by having you win when the computer health is low AND when you touch him.
NOPE-eliminate switch statement?
*/



#include <string.h>
#include "lib.h"
#include "view.h"
#include "PressEnter.h"
#include <stdlib.h>
#include <stdio.h>
#include "narytree.h"
#include "narybst.h"
#include "win.h"
#include "nuclear_blast.h"
#include "GameOver.h"
#include "StartScreen.h"
#include "StartScreen4.h"


STATE gameState = START;
int t = 0;


int main(void) {
	

	int r = 5; //player positions
	int c = 4;
	int r2 = 80; //first ball positions
	int c2 = 120;
	int human_speed = 2; //guess what this is?
	int width = 2; //dont bother, this is the frame width
	int human_size = 10; //duh
	int size = 10; //size of computer
	int dr = 3; //speed of player
	int dc = 3; //should = dr
	int agression; //not being used right now
	int inRange = 0; //a random count variable
	int human_health = 100; //human starting health
	int comp_health = 100; //computer starting health
	int newgame = 1; //another count var
	int loopCount = 0; 
	int numAttacks = 0; //number of times human attacks
	int justAttacked; //count var for computer attacks
	int result; //count var
	int death_radius = 4; //this is how many pixels the radius around the computer is that you have to be in to attack/be attacked
	int next_var1 = 0;
	int retreat = 0;
	int retreat_length = 100; //how long it is after going in to retreat mode that you win
	int next_var2 = 0;
	int junkVar = 0;

	//prebuild the binary search tree
	//make the data in each node be a pointer to a function, then the output of that function
	//decides which node is next

	
NaryNode *root = NULL;
root = createNaryNode(createIntData(0), 0); //make the root node (check health)
  appendChild(root, createNaryNode(createIntData(1), 0)); //make the first child (if health is ok)
  appendChild(root, createNaryNode(createIntData(2), 0)); //make the second child (if health is bad)
  appendChild(root->child[0], createNaryNode(createIntData(3), 0)); //treat the first child as the root and add another child
  appendChild(root->child[1], createNaryNode(createIntData(4), 0)); //treat the first child as the root and add another child
  appendChild(root->child[1]->child[4], createNaryNode(createIntData(5), 0)); //add another child on right parent

int *tree1;
int *tree2;
int *tree3;
tree1 = (int*)(root->child[1]);
(int*)(root->child[1]) = 4;
(int*)(root->child[0]) = 2;
(int*)(root->child[1]->child[4]) = 1;

//tree1 = root->child[1];

  /*
		[root]
		/	\
	[child1] ----------child 2]
	/	   \           \      \
 [child3]  [child4]	   [child5] [child6] 
  /			/	   \
[child7]   [child8] [child9]
			|			|
		  [child9]	   [child10]
  
  
  */
  

Junk first;
first.margin = 40; //the margin for death for the computer
first.comp_health_rate = 1; //how fast the you kill the computer
first.human_health_rate = 2; //how fast the computer kills you



	while(keepGoing()) {
		

		waitForVBlank(ON);
		switch (gameState) {
			case START:
				//start mode 4
				initializeGBA(MODE_4);
				FlipPage(ON);
				paintBackground(PressEnterBitmap);
				FlipPage(OFF);
				
				
				//in to mode 3
				GBASetup();
				initializeGBA(MODE_3);
				drawBackground(6);
				while(!keyHit(BUTTON_START)){
				
					while(keyHit(BUTTON_START)){
						break;}
				}
					
				//reset all the count vars and such
					newgame = 1;
					numAttacks = 0;
					loopCount = 0;
					justAttacked = 0;
					human_health = 100; //human starting health
					comp_health = 100; //computer starting health
					next_var1 = 0;
					next_var2 = 0;
					r = 5; //player positions
					c = 4;
					r2 = 80; //first ball positions
					c2 = 120;
					gameState = PLAY;
					retreat = 0;
				
				break;
			case PLAY:

				//start mode 3
				FlipPage(OFF);
				GBASetup();

				waitForVBlank(ON);
				loopCount++;
				drawRectDMA(0, 0, 160, 240, COLOR(0,0,0)); //the black background
				
				//nary tree usage
				tree3 = (int*)(root->child[1]);
				if(tree3){
					junkVar++;
				}


				if(comp_health < first.margin){
					gameState = WIN;
				}
				
				//frame
				drawRectDMA(1, 1, 240, 1, COLOR(0,0,31)); //left bar
				drawRectDMA(159, 1, 1, 240, COLOR(0,0,31));//bottom bar
				drawRectDMA(1, 1, 240, 1, COLOR(0,0,31));//bottom bar
				drawRectDMA(159, 1, 1, 240, COLOR(0,0,31));//bottom bar
				

				//draw health bars
				if(human_health == 100){
				drawRectDMA(5, 4, 1, 1, COLOR(0,0,31)); //human starting health
				drawRectDMA(5, 6, 1, 1, COLOR(0,0,31));
				drawRectDMA(5, 8, 1, 1, COLOR(0,0,31));
				}

				if(comp_health == 100){
				drawRectDMA(5, 230, 1, 1, COLOR(31,0,0)); //computer starting health
				drawRectDMA(5, 232, 1, 1, COLOR(31,0,0));
				drawRectDMA(5, 234, 1, 1, COLOR(31,0,0));
				//newgame = 0;
				}
				
				if((human_health < 100) && (human_health > 66)){
				drawRectDMA(5, 4, 1, 1, COLOR(0,0,31)); //human health 2/3
				drawRectDMA(5, 6, 1, 1, COLOR(0,0,31));
				drawRectDMA(5, 8, 1, 1, COLOR(0,0,0));
				}

				if((human_health < 66) && (human_health >33)){
				drawRectDMA(5, 4, 1, 1, COLOR(0,0,31)); //human health 1/3
				drawRectDMA(5, 6, 1, 1, COLOR(0,0,0));
				drawRectDMA(5, 8, 1, 1, COLOR(0,0,0));
				}

				if((human_health < 33) && (human_health >0)){
				drawRectDMA(5, 4, 1, 1, COLOR(0,0,0)); //human health 0/3
				drawRectDMA(5, 6, 1, 1, COLOR(0,0,0));
				drawRectDMA(5, 8, 1, 1, COLOR(0,0,0));
				}

				
				if((comp_health < 100) && (comp_health > 66)){
				drawRectDMA(5, 230, 1, 1, COLOR(31,0,0)); //computer health 2/3
				drawRectDMA(5, 232, 1, 1, COLOR(31,0,0));
				drawRectDMA(5, 234, 1, 1, COLOR(0,0,0));
				}

				if((comp_health < 66) && (comp_health > 33)){
				drawRectDMA(5, 230, 1, 1, COLOR(31,0,0)); //computer health 1/3
				drawRectDMA(5, 232, 1, 1, COLOR(0,0,0));
				drawRectDMA(5, 234, 1, 1, COLOR(0,0,0));
				}

				if((comp_health < 33) && (comp_health > 0)){
				drawRectDMA(5, 230, 1, 1, COLOR(0,0,0)); //computer health 0/3
				drawRectDMA(5, 232, 1, 1, COLOR(0,0,0));
				drawRectDMA(5, 234, 1, 1, COLOR(0,0,0));
				}

				waitForVBlank(ON);

			
			
				//player control
				//controls the boundries and the speed
				drawRectDMA( r, c, width, width, COLOR(0,0,0));
				
				if(keyHit(BUTTON_UP)) {
					r = r - human_speed;
					if(r <= 1) r = 2;
				}
				if(keyHit(BUTTON_DOWN)) {
					r = r + human_speed;
					if(r >= 159+human_size) r = 159;
				}
				if(keyHit(BUTTON_LEFT)) {
					c = c - human_speed;
					if(c <= 1) c = 2;
				}
				if(keyHit(BUTTON_RIGHT)) {
					c = c + human_speed;
					if(c >= 239+human_size) c = 239;
				}
			
						
				//start ball code (makes ball move)
				drawRectDMA( r2, c2, size, size, COLOR(0,0,0) );
				drawRectDMA( r2, c2, size, size, COLOR(0,0,31) );
				
				//collision detection
				//walls (make ball bounce)
			
				//computer bouncing
				
			if((r2+size) > 156) dr = -dr; //top
			if((c2+size) > 236) dc = -dc; //bottom and right
			if((c2+size) < 15) dc = -dc; //left
			if(((r2) <= 3) || ((r2) >= 158)) dr = -dr; //top and bottom
			

				
				//draw player square
				
				drawRectDMA( r, c, human_size, human_size, COLOR(0,0,0));
				
	
				drawRectDMA( r, c, human_size, human_size, COLOR(0,0,31) ); //the actual square

						
				//draw bouncing ball
				drawRectDMA( r2, c2, size, size, COLOR(31,0,0));
				

				//right wall
				drawRectDMA( 1, 238, 72 , width - 1, COLOR(0,0,31) ); 
				drawRectDMA( 87, 238, 73,  width - 1, COLOR(0,0,31) ); 
				
				//keep player in boundries
				if(r < 2) {
					r = 2;
				}
				if(r+size > (159)) {
					r = (148);
				}
				if((c+size > 239)) {
					c = 228;
				}

				if((c < 2)) {
					c = 2;
				}

				//keep computer in boundries
				//the computer boundry is smaller so he doesn't get stuck in corners
				if(r2 < 10) {
					r2 = 10;
				}
				if(r2+size >= (149)) {
					r2 = (138);
				}
				
				if((c2 < 10)) {
					c2 = 10;
				}
				
				if((c2+size > 229)) {
					c2 = 218;
				}


				//BEGIN AI
				

				//if the health is low	
				if((retreatCheck(comp_health,(first.margin)))){
					//retreat
					(int*)(root->child[1]) = 1;
	
				if(r < r2){
					r2 = r2 + 1;
				}

				if(r > r2){
					r2 = r2 - 1;
				}

				if(c < c2){
					c2 = c2 + 1;
				}

				if(c > c2){
					c2 = c2 - 1;
				}
				if(keyHit(BUTTON_A)){
			retreat = retreat + 1;
				}
			}


			//nary tree usage
			tree2 = (int*)(root->child[1]);
				if(tree2){
					junkVar++;
				}



				if(attackCheck(comp_health)){ //if health is ok
					//attack
						(int*)(root->child[0]) = 1;

					if(r < r2){
						r2 = r2 - 1;
					}

					if(r > r2){
						r2 = r2 + 1;
					}

					if(c < c2){
						c2 = c2 - 1;
					}

					if(c > c2){
						c2 = c2 + 1;
					}
				
				
					//see how aggressive the human is being
					agression = numAttacks/inRange;
					//see if the human is within striking distance
						if(inRadius(c2, death_radius, c, human_size, r2, r, size)){ //this function took forever to write

						inRange++;
						result = randGen();
						if(result){
						human_health = human_health - (first.human_health_rate);
						justAttacked++;
						}
					
						//If I ever get around to implementing this, this will allow the computer to retreat
						//when the human gets too aggressive

						/*
						if(agression > .15){
				

				//retreat
					if(r < r2){
						r2 = r2 + 1;
					}

					if(r > r2){
						r2 = r2 - 1;
					}

					if(c < c2){
						c2 = c2 + 1;
					}

					if(c > c2){
						c2 = c2 = 1;
					}

				}
				
			
*/
		
				//set up the health
				//computer (computer loses health under these conditions
					
				if(keyHit(BUTTON_A)){
						comp_health = (comp_health - (first.comp_health_rate));
						numAttacks++;
						
					}
				
			}
				}

				
				if(inRadius(c2, death_radius, c, human_size, r2, r, size)){
						if(retreat >= retreat_length){
					gameState = WIN;
				break;}
						if(human_health < 33){
							gameState = DIE;
							next_var2 = 1;
							break;
						}
				}
				
				break;

			case WIN: //if they make it past level 5, display a win screen and reset some variables
					drawBackground(7);
					if(junkVar){
						newgame = 1;
					}
				retreat = 0;
				if(keyHit(BUTTON_START)) {
					gameState = CREDITS; //next stop is the credits
				
				}
				while(keyHit(BUTTON_START)) {
					while(!keyHit(BUTTON_START)) {
						
					break; }
				next_var1 = 1;}
				
			
			break;

		case CREDITS: //display the Pony Shrapnel logo
				
			if(next_var1 == 1){
				
					drawBackground(8);
					
				
				if(keyHit(BUTTON_START)) {
					gameState = START; //next stop is the start screen
				
				}
				while(keyHit(BUTTON_START)) {
					while(!keyHit(BUTTON_START)) {
					break; }
				}
				}

			

		

		
			case DIE: //if they die, then display a death screen, reset some variables, and go back to the start screen
				
				if(next_var2){
				drawBackground(1);
					if(junkVar){
						newgame = 0;
					}
				
				if(keyHit(BUTTON_START)) {
					gameState = CREDITS2; //next stop is the credits2
				
				}
				while(keyHit(BUTTON_START)) {
					while(!keyHit(BUTTON_START)) {
						
					break; }
				}
				human_health = 100;}
				
			break;


		case CREDITS2: //display the Pony Shrapnel logo
				
			while(next_var2){
				
					drawBackground(8);
					
				
				if(keyHit(BUTTON_START)) {
					gameState = START; //next stop is the start screen
					next_var2 = 0;
				}
				while(keyHit(BUTTON_START)) {
					while(!keyHit(BUTTON_START)) {
					break; }
				}
				break;}

			



				//end switch statements


		
		}

	}
	return 0;
}
