// 
// File: ahnentafel.c 
// 
// @author Julie Sojkowski
// 
// Purpose: user either enters command line arguments or uses the menu 
// 		to select which option they would like, program then 
// 		fulfulls the option
//
// // // // // // // // // // // // // // // // // // // // // // // // 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calcualte the power of two integers
// base: the base integer
// exp: the exponent
// returns: the base number to the power of the exponent
int power( int base, int exp){

        int ret = 1;
        for (int i = 0; i< exp; i++){
                ret = ret*base;
        }
        return ret;


}
// Function to print the menu and take in an integer for the option
// returns: the integer that the user imput as the option
int  printMenu(){
	printf("\n1) description\n");
	printf("2) ahnentafel number (base 10)\n");
	printf("3) ahnentafel number (base 2)\n");
	printf("4) relation (e.g. mother's mother's father)\n");
	printf("5) female X chromosome inheritance\n");
	printf("6) exit\n");
	int implen= 4;
	char num[implen];
	char *end;
	if(fgets(num, implen, stdin)){
        	char *c;
                if((c = strchr(num, '\n'))){			//check for newline
                	*c = 0;					//assign newline to 0
                } else {
                        scanf("%*[^\n]");
			scanf("%*c");//clear upto newline
                }
	}
	
        int imp = strtol(num, &end, 10);
	return imp;
}

// Function to print the description for case 1
void prDescription(){
	printf("The ahnentafel number is used to determine the relation\n");
       	printf("between an individual and each of his/her direct ancestors.\n");
}

// Function to make the string version of the realtion
// length: legth of the binary array
// bin: the binary number represented as an array of integers
// str: the string that will contain the relation
// returns: the number of generations
int  getRelation(int length, int bin[], char str[]){
	
	char mom[] = "mother";
	char dad[] = "father";
	char moms[] = "mother's ";
	char dads[] = "father's ";
	int gen = 0;
	if (length < 1){
		strcpy(str, "none");
		return gen;
	}
	
	if( bin[1] == 1){
                strcpy(str, moms);
        	gen++;
	}
	else if (bin[1] == 0){
         	gen++;
	 	strcpy(str, dads);
	}
	
	for (int i = 2; i< length; i++){
		if(i== length-1){                    //check if it's the last digit
			if( bin[i] == 1)
				strcat(str, mom);
			else if (bin[i] == 0)
				strcat(str, dad);

		}
		else if( bin[i] == 1)
                         strcat(str, moms);
                else if (bin[i] == 0)
                         strcat(str, dads);
		++gen;
	}
	return gen;
}

// Function to convert base10 int to an integer array representing a binary number
// base10: the integer in base 10
// binary: the array that will get the binary number
// return: length of the binary array
int toBinary(int base10, int binary[]){
	int len =0;		//length of the binary array
	int numlen = 32;
	int revBin[numlen];
	while(base10>0){
		revBin[len] = base10 % 2;
		base10 = base10/2;
		len++;
	}
	int a =0;
	for(int j = len-1; j>=0; --j){
		binary[a]= revBin[j];
		a++;
	}
	
	return len;
}

// Function to convert base10 int to a string array representing a binary number
// base10: the integer in base 10
// binary: the array that will get the binary number
// return: length of the binary array
int toBinaryStr(int base10, char  binary[]){
        int len =0;	//length of the binary array
	int numlen = 32;
	int revBin[numlen];
        while(base10>0){
                revBin[len] = base10 % 2;
                base10 = base10/2;
                len++;
        }
	
        int a =0;
        for(int j = len-1; j>=0; --j){
                if(revBin[j] ==0)
			binary[a]='0';
		else binary[a]='1';
                a++;
        }
	binary[a] = '\0';
        return len;
}

// Function to convert string of "mother" / "father" into a binary string
// str: the string to be converted to binary
// binary: the string of 0's and 1's representing a binary number
// return: int, the number of generations
int strtoBin(char str[], char binary[]){
	int gen =0;
	char *pch[10];                                   
	
	pch[0] = strtok( str, " \n" );                      

	char moms[] = "mother's";
	char dads[] = "father's";
	char mom[] = "mother";
	char dad[] = "father";
	char self[] = "self";

	int i =0;

	while ( pch[i] != NULL ) {                         
	        i++;
	        pch[i] = strtok( NULL, " \n" );
	}
	int count =1;
	binary[0] = '1';
	for(int j =0; j< i; j++){
       
        	char it[10];
        	strcpy( it, pch[j]);
        	
		if (strcmp(it, mom) == 0)
        	        binary[count] = '1';
		else if (strcmp(it, dad) == 0)
        	        binary[count] = '0';
		else if (strcmp(it, dads) == 0)
                        binary[count] = '0';
		else if (strcmp(it, moms) == 0)
                        binary[count] = '1';
		else if (strcmp(it, self) == 0)
                        binary[0]='1';
		else{	
			binary[count] = '3';		//used for error checking
		}
		gen++;
		count++;	
	}
	binary[count] = '\0';
	return gen;
}

// Function for the entirety of case 4:
// 	converts the string to binary and prints it
// 	converts the binary to base10 and prints it
//	and prints the generations back
// gen: string of family relation
void case4(char gen[]){
	int numlen = 32;
        char strBin[numlen];
        int generation = strtoBin(gen, strBin); // string f/m/f's/m's to string binary

       	int true =0;
        for(unsigned int i =0;i< strlen(strBin); i++){
        	if( strBin[i] == '0'|| strBin[i] == '1')
			true = 0;
                else {
                        fprintf(stderr, "\nInvalid string! \n");
                        true = 1;
                	break;
		}
        }
        if (true == 0){
		printf("ahnentafel number in binary: %s", strBin);
        	int B10= (int) strtol(strBin, NULL, 2); //string binary to base 10
		printf("\nbase-10 value: %i", B10);
		printf("\ngenerations back: %i\n", generation);
       }
}

// Function for the entirety of case 5:
// 	checks if the number of generations back is accepatble
// 	prints out the ahnentafel numbers for femal chromosome inheritence	
void case5(void){
	int numlen = 32;
	char *end;
	int arlen =3;
	char base10[arlen];
        printf("Number of generations back: ");

        if(fgets(base10, arlen, stdin)){
        	char *p;
                if((p=strchr(base10, '\n'))){//check exist newline
                        *p = 0;
                } else {
                      	scanf("%*[^\n]");scanf("%*c");//clear upto newline
                }
        }

	int intB10 = strtol(base10, &end, 10);

        while (intB10<0 || intB10 >9){
        	fprintf(stderr, "Invalid input, number of generations must be between 0 and 9!");
                printf("\nNumber of generations back: ");

                if(fgets(base10, arlen, stdin)){
                	char *p;
                        if((p=strchr(base10, '\n'))){//check exist newline
                        	*p = 0;
                                } else {
	                                scanf("%*[^\n]");scanf("%*c");//clear upto newline                                        }
                                }
		}

                intB10 = strtol(base10, &end, 10);
	}                
		
	printf("\n Printing %i generations back: \n", intB10);
	int max = power(2, intB10+1);
	char binary[numlen];
	int length =0;
	int check =0;
	int ok;
	for( int i =1; i < max; i++){					//goes through all the numbers possible in the generations
		length = toBinaryStr(i, binary);
		check =0;
		for (int j =0; j< length; j++){				//goes though the binary array
			if(binary[j] =='0' && binary[j+1]=='0'){	//checks if there are two 0's next to eachother
				check++;
			}
		}
		if (check==0) {
			ok = (int) strtol(binary, NULL, 2);
			printf(" %i, ", ok);
		}
	}
}

// Function for entirety of case 3:
// 	error checks to make sure the imput is binary
//	converts binary to base 10 and prints out the base10 value
//	get's the family relation and prints it
//	prints the number of generations back
// bin: a charachter array of 0's and 1's representing a binary number
void case3(char bin[]){
        int true =1;
	int numlen = 32;
        int charlen = 350;
	for(unsigned int i =0; i< strlen(bin)-1; i++){
        	if( bin[i] == '0' || bin[i] == '1')
                	true = 0;
                else{
                        printf("Invalid string!\n");
                        true = 1;
                        break;
                }
        }
	int binary[numlen];
        if (true == 0){
    	   	int B10= (int) strtol(bin, NULL, 2);
                printf("base-10 value: %i", B10);

                int len = toBinary(B10, binary);

                char relation[charlen];
               	int gen =getRelation(len, binary,relation);
                printf("\nfamily relation: %s", relation);
                printf("\ngenerations back: %i\n", gen);
        }
}

//Function for the entirety of case 2:
//	converts base 10 to binary and prints it
//	gets the family relation and prints it
//	prints the number of generations
// base10: the base10 value entered to covert to binary 
void case2(char base10[]){
	char *end;
	int numlen = 32;
        int charlen = 350;
	int binary[numlen];
	int intB10 = strtol(base10, &end, 10);
        int len = toBinary(intB10, binary);
	printf("ahnentafel number in binary: ");
	for (int f =0; f<len; f++){
		printf("%i", binary[f]);

	}

        char strGen[charlen];
        int gen = getRelation(len, binary, strGen);
	printf("\nfamily relation: %s", strGen);
	printf("\ngenerations back: %i\n", gen);
}

#define numlen 32
#define charlen 350

// Main function that checks how many command line arguments there are
// 	and prints out a menu or processes the commcand line argumaents
// argc: number of command line arguments
// argv: the command line arguments
// returns: exit_sucess
int main(int argc, char **argv){

	if(argc == 1){
		int imp = printMenu();
		
		while(imp != 6){
			
			if(imp == 1)
				prDescription();
		
			else if (imp == 2){
				char base10[numlen];
				printf("\nEnter the ahnentafel number in base-10: ");
        			fgets(base10, numlen, stdin);
				case2(base10);
			}
			else if(imp == 3){
				char bin[numlen];
        			printf("\nEnter the ahnentafel number in binary: ");
        			fgets(bin, numlen, stdin);
				case3(bin);
			}

			else if(imp ==4){
			        printf("Enter family relation (e.g.) \"father's mother\": ");
			        char gen[charlen];
        			fgets(gen, charlen, stdin);
				case4(gen);
			}

			else if(imp ==5){
				case5();
			}
			
			else if(imp == 6){
				printf("Goodbye.");
				return EXIT_SUCCESS;
			}
				
			else fprintf(stderr, "\nUnknown operation!\n");
			imp = printMenu();
         	}			
	}

	else {
		char enter[charlen];
		strcpy(enter, argv[1]);
		if (enter[strlen(enter)-1] =='b'){
			case3(enter);
		}
		else if(enter[0] == 'm' || enter[0] =='f'){
			for( int i =2; i< argc; i++){
				enter[strlen(enter)] = ' ';
				strcat(enter, argv[i]);
			}
			case4(enter);	
		}
		else case2(enter);
	}

	return EXIT_SUCCESS;
}
