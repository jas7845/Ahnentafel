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

int toBinary(int base10, int binary[]){
	int i =0;
	int revBin[50];
	while(base10>0){
		revBin[i] = base10 % 2;
		base10 = base10/2;
		i++;
	}
	int a =0;
	for(int j = i-1; j>=0; --j){
		binary[a]= revBin[j];
		a++;
	}
	printf("\n print arr: ");
	for(int c=0; c<i; c++){

		printf("%i", binary[c]);
	}
	return i;
}



int main(int argc, char **argv){

	if(argc == 1){
		char num[2]; 
		char *end;
		printMenu();
		fgets(num, 2, stdin);
		int imp = strtol(num, &end, 10);
	        printf("num: %i", imp); //debig stmt
		int binary[50];

		if(imp == 1)
			prDescription();
		
		if(imp == 2){
			char base10[30];
			printf("\nEnter the ahnentafel number in base-10: ");
			setbuf(stdin, NULL);
			fgets(base10, 30, stdin);

			int intB10 = strtol(base10, &end, 10);
			printf("\nintb10: %i\n", intB10);
			int len = toBinary(intB10, binary);
			printf("ahnentafel number in binary: ");
			for(int c=0; c<len; c++){

         		       printf("%i", binary[c]);
       			 }
		}

	}

	return 0;
}
