//Emperor Advincula
//Procject 10 twordle
//april 2025
#include <stdio.h>
#include <stdbool.h>
#define WORDFILE "mystery.txt"
#define TEMP 10
#define COL 6
#define ROW 6

void misalignedletters(char word[],char guess[],char arrows[][COL],int attempt);
void caseshift(char word[],char guess[]);
void wordcheck(char guess[],int count);
void Prompt(char guess[],int count);
void letterplacecheck(char tracker[][COL],char guess[],char word[],int attempt);
void display(char tracker[][COL],char arrow[][COL],int attempt,bool wincondition);
void insertguess(char guess[],char tracker[][COL],int attempt);
bool finalwincheck(char word[],char guess[]);

int main(){

	char word[ROW],guess[TEMP];
	char tracker[ROW][COL],arrow[ROW][COL];
	bool wincondition = false;
	FILE* WordFilePointer;

	WordFilePointer = fopen(WORDFILE,"r");
	
	if (WordFilePointer == NULL){
		printf("ERROR Acessing Word File");
		return 0;
	}else{
		printf("...Word prompt loaded!\n");
		
		fscanf(WordFilePointer,"%s",word);
		fclose(WordFilePointer);
	}
		
		printf("(X)The Word is :%s\n",word);
	
	for(int attempt = 0;attempt <= 5 && wincondition == false ;attempt++){
		Prompt(guess,attempt);
		wordcheck(guess,attempt);
		wincondition = finalwincheck(word,guess);
		caseshift(word,guess);
		letterplacecheck(tracker,guess,word,attempt);
		misalignedletters(word,guess,arrow,attempt);
		insertguess(guess,tracker,attempt);
		display(tracker,arrow,attempt,wincondition);
	
	}
	
	

return 0;

}

void Prompt(char guess[],int attempt){

	int count = attempt + 1;
	switch(attempt){
		case 0:
			printf("GUESS #1 ! Enter your guess!\n Remember! Your guess MUST be 5 letters long!\nEnter your Guess:");
			break;
		case 1:
		case 2:
		case 3:
		case 4:
			printf("GUESS #%d! Enter Your Guess:",count);
			break;
		case 5:
			printf("GUESS #6! Your Final Guess:");
			break;
	}
}

void wordcheck(char guess[],int attempt){

	bool valid = true;
	bool length = true;
	int checkin;
	do{
		scanf(" %s",guess);
		valid = true;
		length = true;
		
		for(checkin = 0;guess[checkin] != '\0' ;checkin++){
		
			int letterid = guess[checkin];
			_Bool capletter = letterid >= 65 && letterid <= 90;
			_Bool lowerletter = letterid >= 97 && letterid <= 122;
			if(capletter == false && lowerletter == false && guess[checkin] != '\0'){ 
				valid = false;
			}
		}
		
		if(checkin < 5 || checkin > 5 ){
			length = false;	
		}
		if(length == false){
			printf("(!)Your guess must be 5 Letters long\n");
		}
		if(valid == false){
			printf("(!)Invalid characters in guess\n");
		}
		if(valid == false || length == false){
			printf("(!)try again: ");
		}
	}while(length == false || valid == false);
}

void caseshift(char word[],char guess[]){

	int letterid;
	for(int caseind = 0; caseind < 5 ;caseind++){
		
		letterid = guess[caseind];
		if(letterid >= 65 && letterid <= 90){
			guess[caseind] = guess[caseind] + 32;	
		}	
	}
}

void letterplacecheck(char tracker[][COL],char guess[],char word[],int attempt){

	int letterID;
	for(int i = 0;i < 5;i++){
		_Bool match = word[i] == guess[i];
		
		if(match == true){
			letterID = guess[i];
			guess[i] = letterID - 32;
		}
	}
}

void misalignedletters(char word[],char guess[],char arrow[][COL],int attempt){
	
	for(int i = 0; i < 5;i++){
	bool present = false;
	
		for(int check = 0; check < 5;check++){
			if (guess[i] == word[check] && guess[i] != word[i]){
				present = true;
			}
			if(present == true){
				arrow[attempt][i] = '^';
			}else{
				arrow[attempt][i] = ' ';
			}
		}
	}
}


void insertguess(char guess[],char tracker[][COL],int attempt){
	
	for(int i = 0; i <= 5; i++){
	
		tracker[attempt][i] = guess[i];
		
	}
}
	
bool finalwincheck(char word[],char guess[]){
	bool win = false;
	int correct;
	correct = 0;
	for(int i = 0;i < 5;i++){
		if( word[i] == guess[i]){
		correct++;
		}
	}
	if(correct == 5){
	win = true;
	
	}
return win;
}

void display(char tracker[][COL],char arrow[][COL],int attempt,bool wincondition){
	int count;
	count = attempt + 1;
	
	printf("============[  GUESSES!  ]=============\n");
	for(int row = 0; row <= attempt; row ++){
		printf("%s\n",tracker[row]);
		printf("%s\n",arrow[row]);
	}
	
	if(wincondition == true ){

		printf("============[  YOU WIN!  ]=============\n");
		printf("                %s\n",tracker[attempt]);
		
		switch(count){
				case 1:
				printf("           YOU WON in %d Guess!\n            PERFECT!\n",count); 
				break;
			case 2:
				printf("         YOU WON in %d Guesses!\n             GOATED!\n",count); 
				break;
			case 3:
				printf("         YOU WON in %d Guesses!\n             WOW!\n",count); 
				break;
			case 4:
				printf("         YOU WON in %d Guesses!\n             Great!\n",count); 
				break;
			case 5:
				printf("         YOU WON in %d Guesses!\n              Nice!\n",count); 
				break;
			case 6:
				printf("         YOU WON in %d Guesses!\n           Well done!\n",count); 
				break;
			}	
	}
	else if(wincondition == false && count >= 6){
	
		printf("============[  YOU LOSE!  ]=============\n");
		printf("\n   YOU LOSE... try again next time...\n\n");
		
	}
}



