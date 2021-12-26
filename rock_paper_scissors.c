/*-----------------------------------------------
ROCK PAPER SCISSORS

Copyright (C) 2021 by William Lupinacci <will.lupinacci@gmail.com>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

This software is licensed under BSD Zero Clause
https://spdx.org/licenses/0BSD.html

To compile and run on Debian-based Linux systems:
Put all this text in rock_paper_scissors.c, then enter in command line
sudo apt update && sudo apt install build-essential -y
gcc -o rock_paper_scissors rock_paper_scissors.c -O2
./rock_paper_scissors
*///--------------------------------------------

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include <assert.h>

//assign global, numeric codes to rock, paper, and scissors
//rock is 0, paper is 1, and scissors is 2
//don't change these  codes
typedef struct choice {
	char *name;
	int8_t code;
} instance;
instance rock = {"rock",0};
instance paper = {"paper",1};
instance scissors = {"scissors",2};

//exit on error function
void exit_error(char *the_error) {
	perror(the_error);
	exit(EXIT_FAILURE);
}

//let user enter the text: 'rock', 'paper', 'scissors', or 'x'
//and loop indefinitely on anything else
void main_user_input(char *string_human_choice,int8_t *human_choice) {
	while(1) {
		printf("Enter rock, paper, or scissors (or 'x' to exit)\n\n");
		printf("> ");
		if(!fgets(string_human_choice,20,stdin)) 
			exit_error("Couldn't parse user input");

		//remove newline from user input
		char *newline_ptr;
		if(newline_ptr = strchr(string_human_choice,'\n')) 
			*newline_ptr = 0; 
		
		if (!strcmp("x",string_human_choice) || !strcmp ("X",string_human_choice)) {
			printf("exiting...\n");
			exit(EXIT_SUCCESS);
		} else if(strcasestr(string_human_choice,rock.name)) {
			*human_choice = rock.code;
			return;
		} else if (strcasestr(string_human_choice,paper.name)) {
			*human_choice = paper.code;
			return;
		} else if (strcasestr(string_human_choice,scissors.name)) {
			*human_choice = scissors.code;
			return;
		} 
		printf("Invalid input, try again\n");
	}
}

//ask user if they want to play again, and loop on input error
void play_again_prompt(char *string_human_choice) {
	while(1) {
		printf("play again? ('y'es or 'n'o): ");
		if(!fgets(string_human_choice,20,stdin)) 
			exit_error("error reading from stdin");

		//remove newline from user input
		char *newline_ptr;
		if(newline_ptr = strchr(string_human_choice,'\n'))
			*newline_ptr = 0;

		if(!strcmp("y",string_human_choice) || strcasestr(string_human_choice,"yes")) {
			return;
		} else if (!strcmp("n",string_human_choice) || strcasestr(string_human_choice,"no")) {
			printf("exiting...\n");
			exit(EXIT_SUCCESS);
		}	
		printf("Invalid input, try again\n");
	}
}

//sleep function
void program_sleep(time_t seconds, long nanoseconds) {
	struct timespec first, second;
	first.tv_sec = seconds;
	first.tv_nsec = nanoseconds;
	if(nanosleep(&first,&second) < 0)
		exit_error("nanosleep failed");
}

int main() {

	//define variables
	int8_t human_choice = rock.code; 
	int8_t computer_choice = rock.code; 
	int8_t result;
	char string_human_choice[20];
	char *choice_array[] = {rock.name,paper.name,scissors.name};

	//clear screen
	printf("\e[1;1H\e[2J");

	//initialize random function with unix epoch
	//time (in seconds) as the seed
	srand((unsigned int)time(NULL));

	//main while loop
	while(1) {
		printf("ROCK, PAPER, SCISSORS 1.0\n\n\n");

		//computer chooses rock, paper, or scissors
		//uses code value for each as shown in global choice struct
		computer_choice = rand() % (scissors.code - rock.code + 1) + rock.code;
	
		//ask user to enter 'rock', 'paper', or 'scissors'	
		main_user_input(string_human_choice,&human_choice);
	
		//repeat the user choice to user	
		printf("\nYou chose %s\n",string_human_choice);
		
		//sleep for 1.5 seconds
		program_sleep(1,500000000);

		//show user know what computer chose
		assert(computer_choice >= rock.code && computer_choice <= scissors.code);
		printf("Computer chose %s\n\n",choice_array[computer_choice]);

		//sleep for 0.5 seconds
		program_sleep(0,500000000);	
	
		//determine win based on the difference
		//between the code values of the humand and computer choice 	
		result = human_choice - computer_choice;
		if(result == 1 || result == -2) {
			printf("You won!\n\n");
		} else if (!result) {
			printf("You tied!\n\n");
		} else {
			printf("You lost :\(\n\n");
		}

		//ask user to play again;
		play_again_prompt(string_human_choice);

		//clear screen
		printf("\e[1;1H\e[2J");
	//end of main while loop
	}


	//end of program
	return 0;
}
