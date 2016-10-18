/*******************************************************************************************
* Student: Vikram Singh StudentID: 11491025                                                *
* Class: CptS 121, Fall  2015; Lab Section 5                                               *
* Programming Assignment: Extra credit: Poker                                              *
* Date: December 05, 2015                                                                  *
* Description: I will be writing a C program that will try to miror poker.				   *
* Some functions taken from http://eecs.wsu.edu/~aofallon/cpts121/schedule.htm             *
*******************************************************************************************/

//Include local header file
#include "poker.h"


/*Contains main logic of the game*/
void main_game (void)
{
	//int
	int current_card = 1, num_games = 0, row_counter = 0, col_counter = 0,
		main_menu = 0; //current card

	//deck
	int deck[4][13] = {0}; //initialize everything to 0 which is information

	/* initialize suit array */
	const char *suit_strings[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};

	/* initialize face array */
	const char *face_strings[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King"};

	//initialize players
	Generic_temp_Player computer;
	Generic_temp_Player human;

	//initialize some vars
	computer.score = 0;
	computer.wins = 0;
	computer.loss = 0;

	human.score = 0;
	human.wins = 0;
	human.loss = 0;
	human.ask_things = 0;

	 /* seed random-number generator */
	srand ((unsigned) time (NULL));

	//get player main menu choice
	main_menu = intro_poker ();

	switch (main_menu)
	{
		case 1:
			for (num_games = 0; num_games < 10; num_games++)
			{
				//reset current card
				current_card = 1;

				//reset deck
				for(row_counter = 0; row_counter < 4; row_counter++)
				{
					for (col_counter = 0; col_counter < 13; col_counter++)
					{
						deck[row_counter][col_counter] = 0;
					}
				}

				/*Prepares deck*/
				shuffle_deck (deck);

				//deal cards to computer and player
				deal (&current_card, 5, deck, computer.hand);
				deal (&current_card, 5, deck, human.hand);

				computer.score = eval_computer_hand (&current_card, deck, computer.hand);

				if (!computer.score)
				{
					computer.score = replace_hand_eval (computer.hand);
				}

				human.ask_things = ask_human_how_many_replace (human.hand, face_strings, suit_strings);

				if (human.ask_things == 100)
				{
					puts ("Error: Please contact Vikram.\nExit Code: 100.\n");
					exit (100);
				}

				if (human.ask_things)
				{
					simple_replace_cards (&current_card, deck, human.hand, face_strings, suit_strings);
				}

				human.score = replace_hand_eval (human.hand);

				if (human.score == computer.score)
				{
					system ("cls");
					puts ("This round was a tie.");
					puts ("================Your Hand===============");
					print_hand (human.hand, face_strings, suit_strings);
					puts ("=============Computers' Hand============");
					print_hand (computer.hand, face_strings, suit_strings);
					puts ("===========================================");
					system ("pause");
				}

				if (human.score > computer.score)
				{
					system ("cls");
					human.wins++;
					computer.loss++;
					puts ("You won this round. Great job.");
					puts ("================Your Hand===============");
					print_hand (human.hand, face_strings, suit_strings);
					puts ("=============Computers' Hand============");
					print_hand (computer.hand, face_strings, suit_strings);
					puts ("===========================================");
					system ("pause");
				}

				if (human.score < computer.score)
				{
					system ("cls");
					human.loss++;
					computer.wins++;
					puts ("Computer won this round. You will get him next time.");
					puts ("================Your Hand===============");
					print_hand (human.hand, face_strings, suit_strings);
					puts ("=============Computers' Hand============");
					print_hand (computer.hand, face_strings, suit_strings);
					puts ("===========================================");
					system ("pause");
				}
			}
			break;

		case 2:
			puts ("You selected to exit. Have a good day.");
			exit (1);
			break;
	}

	//End game
	if (human.wins == computer.wins)
		{
			system ("cls");
			puts ("This Game was a tie. Good bye.");
			system ("pause");
			exit (1);
		}

		if (human.wins > computer.wins)
		{
			system ("cls");
			human.wins++;
			computer.loss++;
			puts ("You won this Game. Great job. Good bye.");
			system ("pause");
			exit (1);
		}

		if (human.wins < computer.wins)
		{
			system ("cls");
			human.loss++;
			computer.wins++;
			puts ("Computer won this Game. You will get him next time. Good bye.");
			system ("pause");
			exit (1);
		}
	

}

//make deck
void shuffle_deck (int deck[][13])
{
	//local vars
	int face = 0, suite = 0, card = 0;

	//placing cards into the array
	for (card = 1; card <= 52; card++)
	{
		do{
			suite = rand () % 4;
			face = rand () % 13;
		} while (deck[suite][face] != 0);

		deck[suite][face] = card;
	}
}


//old void deal (int* current_card, int deal, const int wDeck[][13], const char *wFace[], const char *wSuit[], int hand[][5])
void deal (int* current_card, int deal, const int wDeck[][13], int hand[][5])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card_to_deal = *current_card + deal - 1;   /* card counter */
	int load_hand = 0; //to load hand array
 	

	/* deal each of the deal cards */
	for (*current_card; *current_card <= card_to_deal; *current_card = *current_card + 1)
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				/* if slot contains current *current_card, display *current_card */
				if (wDeck[row][column] == *current_card)
				{
					// printf ("Card: %d is %s of %s\n", *current_card, wFace[column], wSuit[row]);
					hand[0][load_hand] = row;
					hand[1][load_hand] = column;
					load_hand++;
				}
			}
		}
	}
}
/* just prints witht the hand held by computer or player */
void print_hand (int hand[][5], const char *wFace[], const char *wSuit[])
{
	//local var
	int counter = 0;

	//loop to print cards
	for (counter = 0; counter < 5; counter++)
	{
		printf ("Your Card: %d is %s of %s.\n", counter + 1, wFace[hand[1][counter]], wSuit[hand[0][counter]]);
	}

}

/* return 0 if no pair return 1 if pair */
int contains_pair (int hand[][5])
{
	//local var
	int num_cards = 0, track_face[13] = {0};

	for (num_cards; num_cards < 5; num_cards++)
	{
		track_face[hand[1][num_cards]]++;
	}

	for (num_cards = 0; num_cards < 13; num_cards++)
	{
		if (track_face[num_cards] >= 2)
		{
			return num_cards;
		}
	}

	return 0;
}

/* return 0 if does ! conatin two pair else return 1 */
int contains_two_pair (int hand[][5])
{
	//local var
	int num_cards = 0, track_face[13] = {0}, two_pair_check = 0;

	for (num_cards; num_cards < 5; num_cards++)
	{
		track_face[hand[1][num_cards]]++;
	}

	for (num_cards = 0; num_cards < 13; num_cards++)
	{
		if (track_face[num_cards] >= 2)
		{
			two_pair_check++;
		}
	}

	if (two_pair_check >= 2)
	{
		return 1;
	}

	return 0;
}

/* return 0 if no three of a kind else return 1*/
int contains_three_kind (int hand[][5])
{
	//local var
	int num_cards = 0, track_face[13] = {0};

	for (num_cards; num_cards < 5; num_cards++)
	{
		track_face[hand[1][num_cards]]++;
	}

	for (num_cards = 0; num_cards < 13; num_cards++)
	{
		if (track_face[num_cards] >= 3)
		{
			return num_cards;
		}
	}

	return 0;
}

/* return 0 if no four of a kind else return 1*/
int contains_four_kind (int hand[][5])
{
	//local var
	int num_cards = 0, track_face[13] = {0};

	for (num_cards; num_cards < 5; num_cards++)
	{
		track_face[hand[1][num_cards]]++;
	}

	for (num_cards = 0; num_cards < 13; num_cards++)
	{
		if (track_face[num_cards] >= 4)
		{
			return 1;
		}
	}

	return 0;
}

/* return 0 if no flush else return 1*/
int contains_flush (int hand[][5])
{
	//local var
	int num_cards = 0, flush_tracker = 0;

	flush_tracker = hand[0][0];

	for (num_cards = 1; num_cards < 5; num_cards++)
	{
		if (flush_tracker != hand[0][num_cards])
		{
			return 0;
		}
	}

	return 1;
}

/* return 0 if no straight else return 1*/
int contains_straight (int hand[][5])
{
	//local var
	int num_cards = 0, straight_tracker = 0, track_face[13] = {0}, number_cards_in_straight = 0;

	//order cards
	for (num_cards = 0; num_cards < 5; num_cards++)
	{
		track_face[hand[1][num_cards]]++;	
	}

	//build a straight
	for (num_cards = 0; num_cards < 13; num_cards++)
	{

		if (number_cards_in_straight == 5)
		{
			return 1;
		}

		if (track_face[num_cards] == 1)
		{
			number_cards_in_straight++;
		}else{
			number_cards_in_straight = 0;
		}
	}

	return 0;
}

/* evaluate hand for a reroll */
int eval_computer_hand (int* current_card, const int wDeck[][13], int hand[][5])
{
	//local var
	int replace_cards[2][5] = {0,0}, counter = 0, hold_card = 0, replaced_cards = 0;

	//Handle best hands
	if (contains_four_kind (hand))
	{
		return 10;
	}

	if (contains_flush (hand))
	{
		return 8;
	}

	if (contains_straight (hand))
	{
		return 7;
	}

	if (contains_three_kind (hand))
	{
		//set card to not replace
		hold_card = contains_three_kind (hand);

		//deal cards to temp array to hold cards
		deal (current_card, 2, wDeck, replace_cards);

		//replaced need cards
		for (counter = 0; counter < 5; counter++)
		{
			if (hand[1][counter] != hold_card)
			{

				hand[1][counter] = replace_cards[1][replaced_cards];
				hand[0][counter] = replace_cards[0][replaced_cards];

				replaced_cards++;
			}
		}

		return 0;
	}

	if ( !(contains_three_kind (hand)) && contains_two_pair(hand))
	{
		return 3;
	}

	if (!(contains_three_kind (hand)) && !(contains_two_pair(hand)) && contains_pair (hand))
	{
		//set card to not replace
		hold_card = contains_pair (hand);

		//deal cards to temp array to hold cards
		deal (current_card, 3, wDeck, replace_cards);

		//replaced need cards
		for (counter = 0; counter < 5; counter++)
		{
			if (hand[1][counter] != hold_card)
			{

				hand[1][counter] = replace_cards[1][replaced_cards];
				hand[0][counter] = replace_cards[0][replaced_cards];

				replaced_cards++;
			}
		}

		return 0;
	}

	//deal cards to temp array to hold cards
	deal (current_card, 3, wDeck, replace_cards);

	//replaced need cards
		for (counter = 0; counter < 5; counter++)
		{
			if (replaced_cards < 3)
			{
				hand[1][counter] = replace_cards[1][replaced_cards];
				hand[0][counter] = replace_cards[0][replaced_cards];
				replaced_cards++;
			}
		}


	return 0;
}

/*Simple score scheme*/
int replace_hand_eval (int hand[][5])
{
	//Handle best hands
	if (contains_four_kind (hand))
	{
		return 10;
	}

	if (contains_flush (hand))
	{
		return 8;
	}

	if (contains_straight (hand))
	{
		return 7;
	}

	if (contains_three_kind (hand))
	{
		return 5;
	}

	if ( !(contains_three_kind (hand)) && contains_two_pair(hand))
	{
		return 3;
	}

	if (!(contains_three_kind (hand)) && !(contains_two_pair(hand)) && contains_pair (hand))
	{
		return 2;
	}

	return 1;
}

/*Ask player if he/she wants to replace cards*/
int ask_human_how_many_replace (int hand[][5], const char *wFace[], const char *wSuit[])
{
	//local var
	char number_of_cards_to_replace = 0;


	while(1){
		//clear screen
		system ("cls");

		//print hand
		print_hand (hand, wFace, wSuit);


		printf ("Would you like to replace any cards?\n"
			"Enter the (Y/y) for yes or (N/n) for no: ");

		scanf (" %c", &number_of_cards_to_replace);

		if (toupper (number_of_cards_to_replace) == 'Y')
		{
			return 1;
		}


		if (toupper (number_of_cards_to_replace) == 'N')
		{
			return 0;
		}

		if (1)
		{
			//message for user and pause to show them
			printf ("Please enter (Y/y) or (N/n). You enered: %c.\n", 
				number_of_cards_to_replace);
			system ("pause");
		}

	}

	//error code;
	return 100;
}

/*Do a simple replacement of cards*/
void simple_replace_cards (int* current_card, const int wDeck[][13], 
							int hand[][5], const char *wFace[], const char *wSuit[])
{
	//local vars
	int num_to_replace = 0, counter = 0, counter_to_replace = 0, local_array[2][5] = {0};
	char input_user = '\0';

	do{
		//clear screen
		system ("cls");

		printf ("Please enter the number of cards you would like to replace up to 3.\n"
			"Enter number of cards (up to 3): ");

		scanf (" %d", &num_to_replace);

	} while ((num_to_replace <= 0) || (num_to_replace >= 4));

	deal (current_card, num_to_replace, wDeck, local_array);

	for (counter = 0; counter < 5; counter++)
	{
		//clear screen
		system ("cls");

		//print deck
		print_hand (hand, wFace, wSuit);


		if (counter_to_replace < num_to_replace)
		{
			printf("Replace Card: %d? (Enter: (Y/y) or (N/n)): ", counter + 1);
			scanf (" %c", &input_user);

			if (toupper (input_user) == 'Y')
			{
				hand[0][counter] = local_array[0][counter_to_replace];
				hand[1][counter] = local_array[1][counter_to_replace];
				counter_to_replace++;
			}
		}
	}

	//clear screen
	system ("cls");
}
/*Small intro to the game*/
int intro_poker (void)
{
	//local var
	int choice = 0;

	do{
		//clear screen
		system ("cls");

		printf("\tWelcome to Poker!\n"
			"Please Choose from the following options.\n"
				"\t1. Start game.\n"
				"\t2. Exit game.\n"
				"Enter choice: ");
		scanf ("%d", &choice);

		if ((choice <= 0) || (choice >= 3))
		{
			printf ("Please choose 1 or 2. You enered: %d.\n", choice);
			system ("pause");
		}

	} while ((choice <= 0) || (choice >= 3));

	//clear screen
	system ("cls");

	//return choice
	return choice;
}