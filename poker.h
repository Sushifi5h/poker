/*******************************************************************************************
* Student: Vikram Singh StudentID: 11491025                                                *
* Class: CptS 121, Fall  2015; Lab Section 5                                               *
* Programming Assignment: Extra credit: Poker                                              *
* Date: December 05, 2015                                                                  *
* Description: I will be writing a C program that will try to miror poker.				   *
* Some functions taken from http://eecs.wsu.edu/~aofallon/cpts121/schedule.htm             *
*******************************************************************************************/

//intiatate gaurd code
#ifndef POKER_H
#define POKER_H

//remove warnings
#define _CRT_SECURE_NO_WARNINGS

//include libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//struct to cotain generic player values
typedef struct {
	int score;
	int ask_things;
	int hand[2][5];
	int wins;
	int loss;
} Generic_temp_Player;


//prototypes
void main_game (void); //contains main game logic
void shuffle_deck (int deck[][13]); //shuffles deck from 1 to 52
void deal (int* current_card, int deal, const int wDeck[][13], int hand[][5]); //Deal cards from a certain number to deal
void print_hand (int hand[][5], const char *wFace[], const char *wSuit[]);//displays the players hand to the screen
int contains_pair (int hand[][5]);//checks for a combination
int contains_two_pair (int hand[][5]);//checks for a combination
int contains_three_kind (int hand[][5]);//checks for a combination
int contains_four_kind (int hand[][5]);//checks for a combination
int contains_flush (int hand[][5]);//checks for a combination
int contains_straight (int hand[][5]);//checks for a combination
int eval_computer_hand (int* current_card, const int wDeck[][13], int hand[][5]); //initial eval of computer hand
int replace_hand_eval (int hand[][5]);//find eval of computer and player hand
int ask_human_how_many_replace (int hand[][5], const char *wFace[], const char *wSuit[]); //ask if player would like to keep hand
void simple_replace_cards (int* current_card, const int wDeck[][13], int hand[][5], const char *wFace[], const char *wSuit[]); //replace the cards that are not needed
int intro_poker (void);//small intro to the game returns the selected options

//end gaurd code
#endif /* POKER_H */