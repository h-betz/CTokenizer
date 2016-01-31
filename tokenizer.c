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
int ind = 0;

//Append the string "Word: " to the token and return the token as a new string
char * buildWord(char * t) {
    
    char * word = "word: ";
    char * token = (char *) malloc(strlen(t) + strlen(word));       //allocate memory for new string token
    strcpy(token, word);                                            //copy the string "word" into the new token
    strcat(token, t);                                               //append original token to the end
    
    return token;
}

//Append the string "decimal: " to the token and return the token as a new string
char * buildDecimal(char * t) {
    
    char * decimal = "decimal integer: ";
    char * token = (char *) malloc(strlen(t) + strlen(decimal));    //allocate memory for new string token
    strcpy(token, decimal);                                         //copy the string "decimal integer" into the new token
    strcat(token, t);                                               //append original token to the end
    
    return token;
}

//Append the string "float: " to the token and return the token as a new string
char * buildFloat(char * t) {
    
    char * floater = "float: ";
    char * token = (char *) malloc(strlen(t) + strlen(floater));
    strcpy(token, floater);
    strcat(token, t);
    
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
                }
            } else if (isdigit(tempChar)) {             //if there isn't a + or -, check to see if next character is a digit 
                token[i] = c;                           //if it is, add it to the token
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
    
    char * str = ts;                                            //store string in a temporary character array                         
    if (str == NULL) {                                          //if string is null, return null
        return NULL;
    } else {
        TokenizerT * token = malloc(sizeof(TokenizerT));        //allocates space for token
        token->input_string = str;                              //assigns string to the token
        return token;                                           //returns token 
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
    token[0] = '\0';
    int i = 0;
    
    c = tk->input_string[ind];
    if (c == '\0') {
        return 0;                           //return null if end of the input string
    }
    
    if (isspace(c)) {                       //return null if character is a space
        ind++;                              //increment index in input string so we're not stuck in a loop
        return 0;
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
                token = buildWord(token);   //apppend "word: " to the token
                return token;               //return token since this marks the end of the word
            } else if (c == '\0') {         //check to see if its the end of the string
                token[i] = '\0';            //add null character to make token a string
                token = buildWord(token);   //append "word: " to the token
                return token;               //return string
            } else {
                token = buildWord(token);
                return token;
            }
            i++;                            //increment token index
            ind++;                          //increment index of input string
        }
    } else if (isdigit(c) && c != '0') {    //if character is digit between 1 and 9
        token[i] = c;                       //begin building new token
        ind++;                              //increment to next index in input string
        i++;                                //increment to next index in token
        int j;                              //loop counter, avoids getting a warning
        for (j = ind; j < length; j++) {    //loop through input string
            c = tk->input_string[ind];      //get character at index ind in the input string
            if (isdigit(c)) {               //check to see if its a decimal digit
                token[i] = c;               //add to token
            } else if (isspace(c)) {            //check to see if character is a space
                ind++;                          //increment index of input string
                token[i] = '\0';
                token = buildDecimal(token);    //append decimal to beginning of the token
                return token;                   //return new string
            } else if (c == '\0') {             //check to see if the character is a null character
                token[i] = '\0';                //append null character to token to terminate it as a string
                token = buildDecimal(token);    //get new string token with the words "decimal integer" added
                return token;                   //return new string
            } else if (c == '.') {                          //checks to see if this is the start of a float
                char nextChar = tk->input_string[ind+1];    //checks next character to see if it is a digit
                if (isdigit(nextChar)) {                    
                    token[i] = c;                           //if next character is a digit, continue building token
                    token = floater(token, tk, ++i);        //call the floater function which puts the float together
                    token = buildFloat(token);              //convert the token to a string with "float:" added to the front
                    return token;                           //return new string
                }
                
            } else {                            //decimal integer has reached the end, new token begins
                token = buildDecimal(token);    //get new string token 
                return token;                   //return new string
            }
            
            i++;                                //increment the index for the token string
            ind++;                              //increment the index for the input string
        }
    } else if (c == '.' && isdigit(tk->input_string[ind+1])) {      //check to see if this is the start of a float token
        token[i] = c;                                               //if it is, add the . character to the token
        token = floater(token, tk, ++i);                            //call the floater function to build the float token
        token = buildFloat(token);                                  //finish building the string by appending the word float to the front
        return token;                                               //return the token
    } else {
        return 0;
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
  
  p = argv;
  ++p;
  TokenizerT * t = NULL;
  t = TKCreate(*p);
  do {
      
      str = TKGetNextToken(t);
      if (str == NULL) {
          break;
      }
      printf("%s\n", str);
      free(str);
      
  } while (str != 0 || str[0] != '\0');
  
  TKDestroy(t);
  

  return 0;
}