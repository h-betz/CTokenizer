/*
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
    
    char *input_string;
};

typedef struct TokenizerT_ TokenizerT;
int ind = 0;                                                        //this will be the index value of our input string as we iterate through it

//Append the string "bad token: " to the token and return the token as a new string
char * badToken(char * t) {
    
    char * bad = "bad token: ";										
    char * token = (char *) malloc(strlen(t) + strlen(bad));		//allocate memory for new string token
    if (token == NULL) {                                            //checks to see if malloc was a success
        printf("Failed to allocate memory. Program closing.\n");
    }
    strcpy(token, bad);												//copy the string "bad token: " into the new token
    strcat(token, t);												//append the original token to the end
    free(t);                                                        //free the memory we allocated for the old token
    
    return token;
    
}

char * buildZero(char * t) {

	char * zero = "zero: ";
	char * token = (char *) malloc(strlen(t) + strlen(zero));		//allocate memory for new string token
    if (token == NULL) {                                            //checks to see if malloc was a success
        printf("Failed to allocate memory. Program closing.\n");
    }
	strcpy(token, zero);											//copy the string "zero: " into the new token
	strcat(token, t);												//append the original token to the end
    free(t);                                                        //free the memory we allocated for the old token
    
	return token;
}

//Append the string "Word: " to the token and return the token as a new string
char * buildWord(char * t) {
    
    char * word = "word: ";
    char * token = (char *) malloc(strlen(t) + strlen(word));       //allocate memory for new string token
    if (token == NULL) {                                            //checks to see if malloc was a success
        printf("Failed to allocate memory. Program closing.\n");
    }
    strcpy(token, word);                                            //copy the string "word" into the new token
    strcat(token, t);                                               //append original token to the end
    free(t);
    
    return token;
}

//Append the string "decimal: " to the token and return the token as a new string
char * buildDecimal(char * t) {
    
    char * decimal = "decimal integer: ";
    char * token = (char *) malloc(strlen(t) + strlen(decimal));    //allocate memory for new string token
    if (token == NULL) {                                            //checks to see if malloc was a success
        printf("Failed to allocate memory. Program closing.\n");
    }
    strcpy(token, decimal);                                         //copy the string "decimal integer" into the new token
    strcat(token, t);                                               //append original token to the end
    free(t);                                                        //free the memory we allocated for the old token
    
    return token;
}

//Append the string "float: " to the token and return the token as a new string
char * buildFloat(char * t) {
    
    char * floater = "float: ";										
    char * token = (char *) malloc(strlen(t) + strlen(floater));	//allocate memory for new string token
    if (token == NULL) {                                            //checks to see if malloc was a success
        printf("Failed to allocate memory. Program closing.\n");
    }
    strcpy(token, floater);											//copy the string "float: " into the new token
    strcat(token, t);												//append the original token to the end
    free(t);                                                        //free the memory we allocated for the old token
    
    return token;
}

//Append the string "hex: " to the token and return the token as a new string
char * buildHex(char * t) {
    
    char * hex = "hex: ";
    char * token = (char *) malloc(strlen(t) + strlen(hex));		//allocate memory for new string token
    if (token == NULL) {                                            //checks to see if malloc was a success
        printf("Failed to allocate memory. Program closing.\n");
    }
    strcpy(token, hex);												//copy the string "hex: " into the new token
    strcat(token, t);												//append the original token to the end
    free(t);                                                        //free the memory we allocated for the old token
    
    return token;
}

//Append the string "octal: " to the token and return the token as a new string
char * buildOct(char * t) {

	char * oct = "octal: ";
	char * token = (char *) malloc(strlen(t) + strlen(oct));		//allocate memory for new string token
    if (token == NULL) {                                            //checks to see if malloc was a success
        printf("Failed to allocate memory. Program closing.\n");
    }
	strcpy(token, oct);												//copy the string "octal: " into the new token
	strcat(token, t);												//append the original token to the end
    free(t);                                                        //free the memory we allocated for the old token
    
	return token;
}

//Build the float token
char * floater(char * t, TokenizerT * tk, int i) {
    
    char tempChar = 0;
    char nextChar = 0;
    char * token = t;                           //create a temporary token string
    int length = strlen(tk->input_string);      //create a temporary variable to store length of input string
    int j = 0;                                  //initialize loop variable
    ind++;                                      //increment index of input string 
    
    for (j = ind; j < length; j++) {            //loop through input string
        char c = tk->input_string[ind];         //get character at index in the input string
        if (isdigit(c)) {                       //check to see if it's a digit
            token[i] = c;                       //add digit to token
        } else if (c == 'e' || c == 'E') {              //check for scientific notation
            tempChar = tk->input_string[ind+1];         //look ahead to the next character in input string
            nextChar = tk->input_string[ind+2];         //look ahead to two ahead in input string
            if (tempChar == '+' || tempChar == '-') {   //check to see if next character in input string is a + or -
                if (isdigit(nextChar)) {                //if it is, check to see if following character is a digit
                    token[i] = c;                       //add character c to the token string
                    i++;                                //increment index for token string
                    ind++;                              //increment index for input string
                    token[i] = tempChar;                //assign next character in input string to the token, this would be the + or -
                } else {
                    token[i] = '\0';
                    return token;
                }
            } else if (isdigit(tempChar)) {             //if there isn't a + or -, check to see if next character is a digit 
                token[i] = c;                           //if it is, add it to the token
            } else {                                    //
                
            }
        } else if (isspace(c)) {                //check to see if its a space
            ind++;                              //increment index so we're not stuck in a loop
            token[i] = '\0';                    //add null terminator to end of token to make it a string
            return token;                       //return token
        } else if (c == '\0') {                 //check to see if this is the end of the input string
            token[i] = c;                       //add null terminator to end of token to make it a string
            return token;                       //return token
        } else {                                //any other result is the start of a new token
            token[i] = '\0';                    //add null terminator to end of token to make it a string
            return token;                       //return token
        }
        
        ind++;                                  //increment index of input string
        i++;                                    //increment index of token string
    }
    
    
    return token;
}

char * Hex(char * t, TokenizerT * tk, int i) {					//checks if the given char is part of hex
	
    char * token = t;											//local string 
    char c = 0;													//temporary character
    int length = strlen(tk->input_string);						//get the length of the input string
    int j = 0;													//our for loop variable
    
    for (j = ind; j < length; j++) {							//set j equal to the index of the input string and loop until it reaches the end
        c = tk->input_string[ind];								//get the character at the index ind in the input string
        if (isxdigit(c)) {										//if the character c is a hex value
            token[i] = c;										//add it to the token string
            i++;												//increment the index of the token string
        } else {
            token[i] = '\0';									//otherwise this marks the end of this token so add a null character to the end to make the token a string
            return token;										//return the new token
        }
        ind++;													//increment the index of the input string
    }

	return token;
}

int Oct(char b){					//checks if the given char is part of octal 
	int r = 0;
	switch(b){
		case '0' :
			r = 1;
			break;
		case '1' :
			r = 1;
			break;
		case '2' :
			r = 1;
			break;
		case '3' :
			r = 1;
			break;
		case '4' :
			r = 1;
			break;
		case '5' :
			r = 1;
			break;
		case '6' :
			r = 1;
			break;
		case '7' :
			r = 1;
			break;
	}
	return r;
}


/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
    
    char * str = ts;                                                    //store string in a temporary character array                         
    if (str == NULL) {                                                  //if string is null, return null
        return NULL;
    } else {
        TokenizerT * token = malloc(sizeof(TokenizerT));                //allocates space for token
        if (token == NULL) {                                            //checks to see if malloc was a success
            printf("Failed to allocate memory. Program closing.\n");
        }
        token->input_string = str;                                      //assigns string to the token
        return token;                                                   //returns token 
    }

}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
    
    free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
    
    char c = tk->input_string[0];
    int length = strlen(tk->input_string) + 1;
    char * token = (char *) malloc(sizeof(char)*length);
    
    if (token == NULL) {
        printf("Failed to allocate memory. Program closing.\n");
    }
    
    token[0] = '\0';
    int i = 0;
    
    c = tk->input_string[ind];
    if (c == '\0') {
        return 0;                           //return null if end of the input string
    }
    
    if (isspace(c)) {                       //goes to next index in input string and calls itself
        ind++;
        token = TKGetNextToken(tk);         //keeps calling itself until it reaches end of string or a character that is not a space
        return token;
    } else if (isalpha(c) && i == 0) {      //if the character is a letter and the start of the new token
        token[i] = c;                       //build new token
        ind++;                              //increment to next index in input string
        i++;                                //increment to next index in token
        int j;                              //loop counter, otherwise we get a warning which is annoying
        for (j = ind; j < length; j++) {    //loop through input string
            c = tk->input_string[ind];      //get character at index in input string
            if (isalnum(c)) {               //check to see if it's alphanumeric
                token[i] = c;
            } else if (isspace(c)) {        //check to see if it's a space
                ind++;                      //increment index so we're not stuck in a loop
                token[i] = '\0';
                token = buildWord(token);   //apppend "word: " to the token
                return token;               //return token since this marks the end of the word
            } else if (c == '\0') {         //check to see if its the end of the string
                token[i] = '\0';            //add null character to make token a string
                token = buildWord(token);   //append "word: " to the token
                return token;               //return string
            } else {
                token[i] = '\0';
                token = buildWord(token);							//marks the end of the token, so append the word "word: " to front
                return token;										//return the new string
            }
            i++;													//increment token index
            ind++;													//increment index of input string
        }
    } else if (isdigit(c) && c != '0') {							//if character is digit between 1 and 9
        token[i] = c;												//begin building new token
        ind++;														//increment to next index in input string
        i++;														//increment to next index in token
        int j;														//loop counter, avoids getting a warning
        for (j = ind; j < length; j++) {							//loop through input string
            c = tk->input_string[ind];								//get character at index ind in the input string
            if (isdigit(c)) {										//check to see if its a decimal digit
                token[i] = c;										//add to token
            } else if (isspace(c)) {								//check to see if character is a space
                ind++;												//increment index of input string
                token[i] = '\0';
                token = buildDecimal(token);						//append decimal to beginning of the token
                return token;										//return new string
            } else if (c == '\0') {									//check to see if the character is a null character
                token[i] = '\0';									//append null character to token to terminate it as a string
                token = buildDecimal(token);						//get new string token with the words "decimal integer" added
                return token;										//return new string
            } else if (c == '.') {									//checks to see if this is the start of a float
                char nextChar = tk->input_string[ind+1];			//checks next character to see if it is a digit
                if (isdigit(nextChar)) {                    
                    token[i] = c;									//if next character is a digit, continue building token
                    token = floater(token, tk, ++i);				//call the floater function which puts the float together
                    token = buildFloat(token);						//convert the token to a string with "float:" added to the front
                    return token;									//return new string
                }
                
            } else {												//decimal integer has reached the end, new token begins
                token[i] = '\0';
                token = buildDecimal(token);						//get new string token 
                return token;										//return new string
            }
            
            i++;													//increment the index for the token string
            ind++;													//increment the index for the input string
        }
    } else if (c == '.' && isdigit(tk->input_string[ind+1])) {      //check to see if this is the start of a float token
        token[i] = c;                                               //if it is, add the . character to the token
        token = floater(token, tk, ++i);                            //call the floater function to build the float token
        token = buildFloat(token);                                  //finish building the string by appending the word float to the front
        return token;                                               //return the token
    } else if (c == '0') {                                          //if a zero, check to see if it's hex or octal
        char next = tk->input_string[ind+1];                        //check the next character in the input string
        char nextNext = tk->input_string[ind+2];                    //look at the character after the next one
        if (next == 'x' && isxdigit(nextNext)) {                    //start of a hex token if the next character is an x followed by a digit
            token[i] = c;                                           //add character '0' to the token
            token[++i] = next;                                      //add the next character, x, to the token
            ++i;
            ind += 2;                                               //increment the index of input string to account for the 0 and x being added
            token = Hex(token, tk, i);                              //build the hex token
            token = buildHex(token);                                //get the new string with the word "hex: " added to the token
            return token;                                           //return the new string
        } else if (Oct(next)) {										//check to see if the next character is octal
			token[i] = c;											//add the character, c, to the token
			token[++i] = next;										//add the next character to the next space in the token
			++i;													//increment index of token
			ind += 2;												//increment index of input string to account for the two tokens we added from it
			while(Oct(tk->input_string[ind]) != 0){					//while loop terminates when the char found is not oct
				token[i] = tk->input_string[ind];					//adds the char to token
				i++;												//increment index of token
				ind++;												//increment index of input string
			}
			token[i] = '\0';										//add null terminator to the end of the token
			token = buildOct(token);								//append the word "octal: " to the beginning to the token and return as new string
			return token;											//return the new token string
		} else if (next == '\0' || isspace(next)) {					//if the next token is null or a space, then this is just a lonely zero
            token[i] = c;                                           //add character to the token
            token[++i] = '\0';                                      //append null termination character to the end of the string
            token = buildDecimal(token);                               //append the word "zero: " to the beginning of the token
            ind++;                                                  //increment index of input string
            return token;                                           //return the new string
        } else if (nextNext == '\0' || isspace(nextNext)) {         //if the string only has 0x followed by nothing else then this is a bad token
            token[i] = c;                                           //add 0 to the token
            token[++i] = next;                                      //add x to the token
            token[++i] = '\0';                                      //add null character to end of the token
            token = badToken(token);                                //build the final string with "bad token:" added to it
            ind += 3;                                               //increment index of input string to account for the two characters we added
            return token;                                           //return the new string
        } else if (next == '.' && isdigit(nextNext)) {              //consider 0.#### to be a float
            token[i] = c;
            token[++i] = next;
            ind++;
            token = floater(token, tk, ++i);
            token = buildFloat(token);
            return token;         
        } else if (next == 'x' && !isxdigit(nextNext)){             //0x followed by non hex values is considered it's own token
            token[i] = c;                                           //add the 0 to the token
            token[++i] = next;                                      //add the x to the token 
            ind++;                                                  //increment the index of the input string
            token[++i] = '\0';                                      //add null terminator to end of token to make it a string
            token = badToken(token);                                //get the bad token string
            ind++;                                                  //increment the index of the input string so we are looking at the start of the next token
            return token;                                           //return the bad token string
        }
    } else {                                                        //if all of the above fail, then this is a bad token
        token[i] = c;                                               //add character to token string
        token[++i] = '\0';                                          //add null terminator to token
        token = badToken(token);                                    //get the bad token string
        ind++;                                                      //increment the index of our input string to the next spot in our input string
        return token;                                               //return the bad token
    }    
    
    
    return 0;
}


/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {

  char **p = NULL;
  char * str = NULL;
  if (argc > 2 || argc == 1) {                          //checks to see if user input was valid or not
      printf("Please enter input as a string.\n");
      return 0;
  }
  p = argv;
  ++p;
  TokenizerT * t = NULL;
  t = TKCreate(*p);
  do {											//iterate through the input string parsing it into tokens. Iterate until you reach the end of the input string

      str = TKGetNextToken(t);					//str is a char array that stores the string returned from TKGetNextToken
      if (str == NULL) {						//if str is null, break from the loop
          break;
      }
      printf("%s\n", str);						//print the token string
      free(str);								//free the memory allocated for the token string
      
  } while (str != 0 || str[0] != '\0');
  
  TKDestroy(t);									//free the allocated memory for the tokenizer 
  

  return 0;
}
