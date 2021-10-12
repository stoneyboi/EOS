#include <stdio.h>
#include <string.h>
#define CHONK 16 // used to read in 16 bytes at a time


int main() {

    FILE* fp_in;
    unsigned char buf[CHONK];
    size_t n;
    int i, c, npo;
    char path[25] = " "; // initializing array for filename to empty
    char mode = '\0';
	

    printf("Please enter a filename you wish to convert: \n");
    scanf("%s", path);
	fflush(stdin); 

    printf("Please enter a mode for hexdump: (b, C, any key for default): \n");
    scanf("%c", &mode);


    // open the input file
    fp_in = fopen(path, "r");

    if (fp_in == NULL) { // if unable to open
	printf("error opening '%s'", path);
        return 0;
    }// end if

    npo = 0; // used for offset

    // display hex data CHONK bytes at a time
    while ((n = fread(buf, 1, sizeof buf, fp_in)) > 0) {
	if(mode == 'C'){
		printf("%08x  ", npo); // offset
	}//end if
	else{
		printf("%07x ", npo); //offset
	}//end else
        npo += CHONK; // increases with each new line
        //print hex values
	if(mode == 'C'){ //hex+ASCII mode
        	for (i = 0; i < CHONK; i++){             // iterates through buf array to print out result
			printf("%02x ", buf[i]);   // one character at a time with space in between
			if( i == 7 && mode == 'C'){// separate first 8 bits
				printf(" ");
			}//end if
		}//end for
	  // print ascii values
                printf(" |"); // prints bar and psace to separate
                for (i = 0; i < CHONK; i++) {   
		       	// iterates through buf array using integer c to print out char value of that integer
                        c = buf[i];
                        printf("%c", (c >= 32 && c <= 126 ? c : '.')); //if unprintable character, put "."
                }//end for
                printf("|\n");
	}//end if


	if(mode == 'b'){ // binary-octal mode
		for(i = 0; i < CHONK; i++){
			printf("%o ", buf[i]);
		} //end for
		printf("\n");
	}//end if
	 
	else{ //DEFAULT
		for(i =0; i < CHONK; i+=2){ // bytes are printed in different order in default mode
			printf("%02x", buf[i+1]);
			printf("%02x ", buf[i]);
		}//end for
		printf("\n");
	}// end else

	for(i = 0; i < CHONK; i++){ //resets buf array to empty
			buf[i]= '\0';
	}
    }
  
	return 0; //end main
}


