#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int power( int base, int exp){

        int ret = 1;
        for (int i = 0; i< exp; i++){
                ret = ret*base;
        }
        return ret;


}

int  printMenu(){
	printf("\n1) description\n");
	printf("2) ahnentafel number (base 10)\n");
	printf("3) ahnentafel number (base 2)\n");
	printf("4) relation (e.g. mother's mother's father)\n");
	printf("5) female X chromosome inheritance\n");
	printf("6) exit\n");
	char num[2];
	char *end;
	if(fgets(num, 2, stdin)){
                                char *p;
                                if(p=strchr(num, '\n')){//check exist newline
                                        *p = 0;
                                } else {
                                        scanf("%*[^\n]");scanf("%*c");//clear upto newline
                                }
                }

                int imp = strtol(num, &end, 10);
	return imp;
}

void prDescription(){
	printf("\nThe ahnentafel number is used to determine the relation between an individual and each of his/her direct ancestors.\n");
}

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

int toBinary(int base10, int binary[]){
	int len =0;				//length of the binary array
	int revBin[32];
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

int toBinaryStr(int base10, char  binary[]){
        int len =0;                             //length of the binary array
        int revBin[32];
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
			binary[count] = '3';		//error checking
		}
		gen++;
		count++;	
	}

	binary[count] = '\0';
	return gen;


}


void case4(){
	printf("Enter family relation (e.g.) \"father's mother\": ");
        char gen[350];
        fgets(gen, 350, stdin);
        char strBin[32];
        int generation = strtoBin(gen, strBin); // string f/m/f's/m's to string binary

       	int true =0;
        for(int i =0;i< strlen(strBin); i++){
        	if( strBin[i] == '0'|| strBin[i] == '1')
			true = 0;
                else {
                        fprintf(stderr, "\nInvalid string! \n");
                        true = 1;
                	break;
		}
        }
        if (true == 0){
		printf("\nahnentafel number in binary: %s", strBin);
        	int B10= (int) strtol(strBin, NULL, 2); //string binary to base 10
		printf("\nbase-10 value: %i", B10);
		printf("\ngenerations back: %i\n", generation);
       }
}


void case5(void){
	char *end;
	char base10[3];
        printf("Number of generations back: ");

        if(fgets(base10, 3, stdin)){
        	char *p;
                if(p=strchr(base10, '\n')){//check exist newline
                        *p = 0;
                } else {
                      	scanf("%*[^\n]");scanf("%*c");//clear upto newline
                }
        }

	int intB10 = strtol(base10, &end, 10);

        while (intB10<0 ||intB10 >9){
        	fprintf(stderr, "Invalid input, number of generations must be between 0 and 9!");
                printf("\nNumber of generations back: ");

                if(fgets(base10, 3, stdin)){
                	char *p;
                        if(p=strchr(base10, '\n')){//check exist newline
                        	*p = 0;
                                } else {
	                                scanf("%*[^\n]");scanf("%*c");//clear upto newline                                        }
                                }
		}

                intB10 = strtol(base10, &end, 10);
	}                
		
	printf("\n Printing %i generations back: \n", intB10);
        int chrom[233];
	chrom[0] = 1;
	int max = power(2, intB10+1);
	//printf( " max : %i\n", max);
	
	char binary[32];
	
	int length =0;
	int check =0;
	int index=1;
	int ok;
	for( int i =1; i < max; i++){					//goes through all the numbers possible in the generations
		length = toBinaryStr(i, binary);
		//printf("\n binary: %s", binary);
		//printf("\n");
		check =0;
		for (int j =0; j< length; j++){				//goes though the binary array
			if(binary[j] =='0' && binary[j+1]=='0'){	//checks if there are two 0's next to eachother
				check++;
				//printf(" two 0 ");
			}
		}
		if (check==0) {
			ok = (int) strtol(binary, NULL, 2);
			printf(" %i, ", ok);
		}
	
		
	}
}

void case3(){
	char bin[32];
        printf("\nEnter the ahnentafel number in binary: ");

        fgets(bin, 32, stdin);

        int true =1;
	for(int i =0;i< strlen(bin)-1; i++){
        	if( bin[i] == '0' || bin[i] == '1')
                	true = 0;
                else{
                        printf("Invalid string!\n");
                        true = 1;
                        break;
                }
        }
	int binary[32];
        if (true == 0){
    	   	int B10= (int) strtol(bin, NULL, 2);
                printf("\nbase-10 value: %i", B10);

                int len = toBinary(B10, binary);

                char relation[350];
               	int gen =getRelation(len, binary,relation);
                printf("\nfamily relation: %s", relation);
                printf("\ngenerations back: %i", gen);
        }
}

void case2(){
	char *end;
	int binary[32];
	char base10[30];
        printf("\nEnter the ahnentafel number in base-10: ");

       	fgets(base10, 30, stdin);

	int intB10 = strtol(base10, &end, 10);
        int len = toBinary(intB10, binary);
	printf("\nahnentafel number in binary: ");
	for (int f =0; f<len; f++){
		printf("%i", binary[f]);

	}

        char strGen[350];
        int gen = getRelation(len, binary, strGen);
	printf("\nfamily relation: %s", strGen);
	printf("\ngenerations back: %i\n", gen);
}


int main(int argc, char **argv){

	if(argc == 1){
		int imp = printMenu();
		
		while(imp != 6){
			
			if(imp == 1)
				prDescription();
		
			else if (imp == 2){
				case2();
			}
			else if(imp == 3){
				case3();
			}

			else if(imp ==4) case4();

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

	return 0;
}
