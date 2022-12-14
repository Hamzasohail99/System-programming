
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LEN 512
#define MAXARGS 10  
#define ARGLEN 30

char* read_cmd(FILE*);
char** tokenize(char* cmdline);
int main(){
   printf("Enter a command of your choice:- ");
   char *cmdline;
   cmdline = read_cmd(stdin);
   char** arglist = tokenize(cmdline);
   execvp(arglist[0], arglist);
   perror("Exec failed");   
   return 0;
}
//this function gets character by character input, creates and returns a string 
char* read_cmd(FILE* fp){
   int c; //input character
   int pos = 0; //position of character in cmdline
   char* cmdline = (char*) malloc(sizeof(char)*MAX_LEN);
   while((c = getc(fp)) != EOF){
      if(c == '\n')
         break;
      cmdline[pos++] = c;       
   }
   cmdline[pos] = '\0';
   return cmdline;
}

char** tokenize(char* cmdline){
   char** arglist = (char**)malloc(sizeof(char*)* (MAXARGS+1));
   for(int i=0; i < MAXARGS+1; i++){
	   arglist[i] = (char*)malloc(sizeof(char)* ARGLEN);
      bzero(arglist[i],ARGLEN);
   }
   char* cp = cmdline; // pos in string
   char* start;
   int len;
   int argnum = 0; //slots used
   while(*cp != '\0'){
      while(*cp == ' ' || *cp == '\t') //skip leading spaces
          cp++;
      start = cp; //start of the word
      len = 1;   //initialize length of the word to 1
      //find the end of the word
      while(*++cp != '\0' && !(*cp ==' ' || *cp == '\t'))
              len++;
      strncpy(arglist[argnum], start, len);
      arglist[argnum][len] = '\0';
      argnum++;
   }
   arglist[argnum] = NULL;
   return arglist;
}    