#include <stdio.h>
#include <stdlib.h>

void printMenu(){
	printf("1) description\n");
	printf("2) ahnentafel number (base 10)\n");
	printf("3) ahnentafel number (base 2)\n");
	printf("4) relation (e.g. mother's mother's father)\n");
	printf("5) female X chromosome inheritance\n");
	printf("6) exit\n");
}

void prDescription(){
	printf("\nThe ahnentafel number is used to determine the relation between an individual and each of his/her direct ancestors.\n");
}


int main(int argc, char **argv){

	if(argc == 1){
		char num[2]; 
		char *end;
		printMenu();
		fgets(num, 2, stdin);
		int imp = strtol(num, &end, 10);
	        printf("num: %i", imp); //debig stmt
		if(imp == 1)
			prDescription();
		
	}

	return 0;
}
