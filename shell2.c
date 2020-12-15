#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <sys/wait.h>


void letterNull(char *letter){
    while (*letter == ' '){
        *letter = getchar();
    }
}
int howSymbol(char *word){
    int i = 0,countSymbol = 0;
    while(word[i] != '\0'){
        if(word[i] == '"'){
            countSymbol++;
        }
        i++;
    }
    return countSymbol;
}

char **functionForCdAndCat(char **arrayWords,char *word,int *i,int *k,int howLetter){
    if((word[*i] == 'c')&&(word[1] == 'd')&&(word[2] == ' ')){
        arrayWords[*k][0] = 'c';
        arrayWords[*k][1] = 'd';
        arrayWords[*k][2] = '\n';
        (*k)++;
        arrayWords[*k] = malloc (10 * howLetter * sizeof (char));
        *i = *i + 3;
    }
    if((word[*i] == 'l')&&(word[*i+1] == 's')&&(word[*i+2] == ' ')){
        arrayWords[*k][0] = 'l';
        arrayWords[*k][1] = 's';
        arrayWords[*k][2] = '\n';
        (*k)++;
        arrayWords[*k] = malloc (10 * howLetter * sizeof (char));
        *i = *i + 3;
        
    }
    if((word[*i] == 'c')&&(word[1] == 'a')&&(word[2] == 't')&&(word[3] == ' ')){
        arrayWords[*k][0] = 'c';
        arrayWords[*k][1] = 'a';
        arrayWords[*k][2] = 't';
        arrayWords[*k][3] = '\n';
        (*k)++;
        arrayWords[*k] = malloc (10 * howLetter * sizeof (char));
        *i = *i + 4;
        
    }
    if((word[*i] == 's')&&(word[1] == 'a')&&(word[2] == 'y')&&(word[3] == ' ')){
        arrayWords[*k][0] = 's';
        arrayWords[*k][1] = 'a';
        arrayWords[*k][2] = 'y';
        arrayWords[*k][3] = '\n';
        (*k)++;
        arrayWords[*k] = malloc (10 * howLetter * sizeof (char));
        *i = *i + 4;
        
    }
    return arrayWords;
}

char **functionForPartingWord(char **arrayWords,char *word,int *i,int *k,int *j,int howLetter){                        //функция для разделителей слов при | & >
    int i1,k1,j1;
    i1 = *i; j1 = *j; k1 = *k;
    if((word[i1] == '|')||(word[i1] == '&')||(word[i1] == '>')){
        if((i1 > 1)&&(word[i1-1] != ' ')){
            arrayWords[k1][j1] = '\n';
            k1++;
        }
        j1 = 0;
        arrayWords[k1] = malloc (10 * howLetter * sizeof (char));
        arrayWords[k1][j1] = word[i1];
        j1++;
        if (word[i1 + 1] == '&'){
            arrayWords[k1][j1] = word[i1];
            j1++;
            i1++;
        }
        arrayWords[k1][j1] = '\n';
        if((word[i1+1] == '\n')&&(word[i1+2] == '\0')){
            j1++;
            i1++;
        }
        else{
            k1++;
            arrayWords[k1] = malloc (10 * howLetter * sizeof (char));
            i1++;
            j1 = 0;
        }
    }
    
    *i = i1; *j = j1; *k = k1;
    return arrayWords;
}

char **functionIfSymbol1(char **arrayWords,char *word,int *i2,int *k1,int *j1,int howLetter){     //Symbol1 = <
    int i,k,j,i1,countSymbol2 = 0;
    i = *(i2); j = *(j1); k = *(k1);
    
    if(word[i] == '<'){
        i1 = i+1;
        countSymbol2 = 0;
        while(word[i1] != '\0'){
            if(word[i1] == '>'){
                countSymbol2++;
            }
            i1++;
        }
        if (countSymbol2 == 0){
            arrayWords[k][j] = '\n';
            k++;
            arrayWords[k] = malloc (10 * howLetter * sizeof (char));
            arrayWords[k][0] = '<';
            arrayWords[k][1] = '\n';
            k++;
            arrayWords[k] = malloc (10 * howLetter * sizeof (char));
            j = 0;
            i++;
        }
        else{
            arrayWords[k][j] = '\n';
            k++;
            j = 0;
            arrayWords[k] = malloc (10 * howLetter * sizeof (char));
            while(word[i] != '>'){
                arrayWords[k][j] = word[i];
                j++;
                i++;
                
            }
            arrayWords[k][j] = word[i];
            i++;
            if((word[i] == '\n')&&(word[i+1] == '\0')){
                j++;
                arrayWords[k][j] = '\n';
                i++;
            }
            else{
                j++;
                arrayWords[k][j] = '\n';
                j = 0;
                k++;
                arrayWords[k] = malloc (10 * howLetter * sizeof (char));
            }
        }
    }
    
    *i2 = i; *j1 = j; *k1 = k;
    return arrayWords;
}

char **functionIfSymbol2(char **arrayWords,char *word,int *i1,int *k1,int *j1,int *countSymbol2,int howLetter){       //Symbol2 = "
    int i,k,j,countSymbol;
    i = *(i1); j = *(j1); k = *(k1); countSymbol = *(countSymbol2);
    
    if((countSymbol > 2)&&(countSymbol % 2 == 0) && (word[i] == '"')){
        arrayWords[k][j] = '\n';
        k++;
        arrayWords[k] = malloc (10 * howLetter * sizeof (char));
        j = 0;
        while(countSymbol != 0){
            if(word[i] == '"'){
                i++;
                countSymbol--;
            }
            if(countSymbol != 0){
                arrayWords[k][j] = word[i];
                i++;
                j++;
            }
        }
        arrayWords[k][j] = '\n';
        j = 0;
        k++;
        arrayWords[k] = malloc (10 * howLetter * sizeof (char));
    }
    
     if((countSymbol == 2)&&(word[i] == '"')){
        arrayWords[k][j] = '\n';
        k++;
        arrayWords[k] = malloc (10 * howLetter * sizeof (char));
        j = 0;
        while(countSymbol != 0){
            if(word[i] == '"'){
                i++;
                countSymbol--;
            }
            if(countSymbol != 0){
                arrayWords[k][j] = word[i];
                i++;
                j++;
            }
        }
        arrayWords[k][j] = '\n';
        if(word[i] == '"'){
            i++;
        }
        if((word[i] == '\n')&&(word[i+1] == '\0')){
            j++;
            arrayWords[k][j] = '\n';
            i++;
        }
        else{
            j = 0;
            k++;
            arrayWords[k] = malloc (10 * howLetter * sizeof (char));
        }
    }
    *i1 = i; *j1 = j; *k1 = k; *countSymbol2 = countSymbol;
    return arrayWords;
}
char **functionIfSymbol3(char **arrayWords,char *word,int *i1,int *k1,int *j1,int howLetter){     //Symbol3 = ;
    int i,k,j;
    i = *(i1); j = *(j1); k = *(k1);
    
    if (j != 0){
        arrayWords[k][j] = '\n';
        j = 0;
        k++;
        arrayWords[k] = malloc(10);
    }
    arrayWords[k][j] = ';';
    j++;
    arrayWords[k][j] = '\n';
    j = 0;
    k++;
    arrayWords[k] = malloc(10 * howLetter * sizeof (char));
    i++;
    
    *i1 = i; *j1 = j; *k1 = k;
    return arrayWords;
}

int correctValue(char *word,int *i1){
    int i;
    i = *(i1);
    if((word[i] != '\n') && (word[i] != '"')&&(word[i] != '|')&&(word[i] != '&')&&(word[i] != '>')&&(word[i] != '<')&&(word[i] != '\0')&& (word[i] != ';')){
        return 1;
    }
    return 0;
}



char *readWord(int *how){
    char *word = NULL;
    char letter;
    int howLetter = 0, howLetterForAlloc = 100,countSymbol = 0;
    
    letter = getchar();
    word = malloc (100 * sizeof (char));
    
    letterNull(&letter);
    while((letter != '\n')&&(letter != '\0')){
        if (howLetterForAlloc > howLetter - 5){
            howLetterForAlloc = 3*howLetterForAlloc;
            word = realloc (word,howLetterForAlloc * sizeof(char));
        }
        if (letter == '"'){
            countSymbol++;
        }
        if (countSymbol == 2){
            countSymbol = 0;
        }
        word[howLetter] = letter;
        letter = getchar();
        if((word[0] == 'c')&&(word[1] == 'd')&&(letter == ' ')&&(howLetter == 1)){
            howLetter++;
            word[howLetter] = letter;
        }
        if((word[0] == 'l')&&(word[1] == 's')&&(letter == ' ')&&(howLetter == 1)){
            howLetter++;
            word[howLetter] = letter;
        }
        if((word[0] == 'c')&&(word[1] == 'a')&&(word[2] == 't')&&(letter == ' ')&&(howLetter == 2)){
            howLetter++;
            word[howLetter] = letter;
        }
        if((word[0] == 's')&&(word[1] == 'a')&&(word[2] == 'y')&&(letter == ' ')&&(howLetter == 2)){
            howLetter++;
            word[howLetter] = letter;
        }
        
        while((countSymbol == 1)&&(letter == '\n' )){
            howLetter++;
            word[howLetter] = letter;
            letter = getchar();
        }
        if (countSymbol != 1){      ///убирает пробелы
            letterNull(&letter);
        }
        howLetter++;
    }
    if (letter == '\n'){
        word[howLetter] = '\n';
        howLetter++;
        word[howLetter] = '\0';
    }
    
    *how = howLetter;
    return word;
}

char **inputToArray(int howLetter,char *word,char **arrayWords,int *howWord){
    int j = 0,i = 0,k = 0,countSymbol = 0;
    countSymbol = howSymbol(word);
    arrayWords = malloc(10 * howLetter * sizeof(char));
    arrayWords[0] = malloc (10 * howLetter * sizeof (char));
    while(word[i] != '\n'){
        
        if(word[i] == ';'){
            arrayWords = functionIfSymbol3(arrayWords,word,&i,&k,&j,howLetter);
        }
        
        arrayWords = functionForCdAndCat(arrayWords,word,&i,&k,howLetter);                //для cd ls cat
        arrayWords = functionForPartingWord(arrayWords,word,&i,&k,&j,howLetter);          //для | & >
        arrayWords = functionIfSymbol1(arrayWords,word,&i,&k,&j,howLetter);               //для Symbol1 = <
        arrayWords = functionIfSymbol2(arrayWords,word,&i,&k,&j,&countSymbol,howLetter);  //для Symbol2 = "
        
         if ((word[i] == '"') &&((countSymbol == 1))){
            countSymbol--;
            i++;
        }
        while(correctValue(word,&i)){
            arrayWords[k][j] = word[i];
            i++;
            j++;
        }
        if((arrayWords[0][0] == 'c')&&(arrayWords[0][1] == 'd')&&(word[2] == '\n')){
            arrayWords[0][2] = '\n';
            arrayWords[1] = NULL;
        }
    }
    if (arrayWords[k][j-1] != '\n'){
        arrayWords[k][j] = '\n';}
    arrayWords[k][j+1] = '\0';
    arrayWords[k+1] = NULL;
    *howWord = k+1;
    return arrayWords;
}

char **wordsForShell(int howLetter,char **arrayWords,char** arrayWordsForShell ,int *howWord){
    int i = 0;
    arrayWordsForShell = malloc(10 * howLetter * sizeof (char));
    arrayWordsForShell[0] = malloc(10 * howLetter * sizeof (char));
    if((arrayWords[0][0] == 'l')&&(arrayWords[0][1] == 's')&&(arrayWords[0][2] == '\n')){
        arrayWordsForShell[0][0] = 'l';
        arrayWordsForShell[0][1] = 's';
        if(arrayWords[1] == NULL){
            arrayWordsForShell[1] = NULL;
        }
        else{
            arrayWordsForShell[1] = malloc(10 * howLetter * sizeof (char));
            if(arrayWords[1][i] == '&'){
                free(arrayWordsForShell[1]);
                arrayWordsForShell[1] = NULL;
            }
            else{
                while(arrayWords[1][i] != '\n'){
                    arrayWordsForShell[1][i] = arrayWords[1][i];
                    i++;
                }
            }
        }
        return arrayWordsForShell;
    }
    if((arrayWords[0][0] == 'c')&&(arrayWords[0][1] == 'd')&&(arrayWords[0][2] == '\n')){
        arrayWordsForShell[0][0] = 'c';
        arrayWordsForShell[0][1] = 'd';
        if(arrayWords[1] == NULL){
            arrayWordsForShell[1] = NULL;
        }
        else{
            arrayWordsForShell[1] = malloc(10 * howLetter * sizeof (char));
            while(arrayWords[1][i] != '\n'){
                arrayWordsForShell[1][i] = arrayWords[1][i];
                i++;
            }
        }
        return arrayWordsForShell;
    }
    if((arrayWords[0][0] == 'c')&&(arrayWords[0][1] == 'a')&&(arrayWords[0][2] == 't')&&(arrayWords[0][3] == '\n')){
        arrayWordsForShell[0] = malloc(10 * howLetter * sizeof (char));
        arrayWordsForShell[0][0] = 'c';
        arrayWordsForShell[0][1] = 'a';
        arrayWordsForShell[0][2] = 't';
        if(arrayWords[1] == NULL){
            arrayWordsForShell[1] = NULL;
        }
        else{
            arrayWordsForShell[1] = malloc(10 * howLetter * sizeof (char));
            while(arrayWords[1][i] != '\n'){
                arrayWordsForShell[1][i] = arrayWords[1][i];
                i++;
            }
        }
        return arrayWordsForShell;
    }
    if((arrayWords[0][0] == 's')&&(arrayWords[0][1] == 'a')&&(arrayWords[0][2] == 'y')&&(arrayWords[0][3] == '\n')){
        arrayWordsForShell[0] = malloc(10 * howLetter * sizeof (char));
        arrayWordsForShell[0][0] = 's';
        arrayWordsForShell[0][1] = 'a';
        arrayWordsForShell[0][2] = 'y';
        if(arrayWords[1] == NULL){
            arrayWordsForShell[1] = NULL;
        }
        else{
            arrayWordsForShell[1] = malloc(10 * howLetter * sizeof (char));
            while(arrayWords[1][i] != '\n'){
                arrayWordsForShell[1][i] = arrayWords[1][i];
                i++;
            }
        }
        return arrayWordsForShell;
    }
    free(arrayWordsForShell[0]);
    arrayWordsForShell[0] = NULL;
    return arrayWordsForShell;
}


void outputArrayWords(char **arrayWords,int howWord){
    int i;
    if((arrayWords[0][0] == '\n')&&(arrayWords[0][1] == '\0')){
        printf("Пустая строка\n");
    }
    else{
        printf("Result:\n");
        for (i = 0;i < howWord;i++){
            printf("%s",arrayWords[i]);
        }
    }
}

void allFree(char **arrayWords,char *word,int howWord){
    int i;
    free(word);
    for(i = 0;i<howWord;i++){
        free(arrayWords[i]);
    }
    free(arrayWords);
    word = NULL;
    
}

void printwelcome(){
   char PathName[PATH_MAX];
   char PN;
   PN = (char)getwd(PathName);
   if (PN == (char)NULL)
       printf ("error");
   else
       printf ("[%s] > ",PathName);
}

void cdShell (char **arrayWordsForShell){
    int f = 0;
    char *word = NULL;
    if(arrayWordsForShell[1] == NULL){
        word = getenv("HOME");
        f = chdir (word);
    }
    else{
        f = chdir (arrayWordsForShell[1]);  // смена текущего каталога
        if (f == -1){
            printf ("oshibka cd\n");
        }
        else{
            printf("Текущим стал каталог %s\n",arrayWordsForShell[1]);
        }
    }
}

void allFree2(char **arrayWords,int howWord){
    int i = 0;
    if (howWord != 0){
        for(i = 0;i<howWord;i++){
         free(arrayWords[i]);
        }
        free(arrayWords);
    }
    else{
        i = 1;
        while(arrayWords[i] != NULL){
            free(arrayWords[i]);
            i++;
        }
        free(arrayWords);
        arrayWords = NULL;
    }
}

void сleaningZombieProcesses(int i){
    if(i == 0){
        while (wait(NULL) != -1){};
    }
    if (i == 1){
        while(wait4(-1, NULL, WNOHANG, NULL) > 0){}
    }
}

int checkForShell(char **arrayWordsForShell,int *howWord){
    int Res;
    if(arrayWordsForShell[0] == NULL){
        return 0;
    }
    if((arrayWordsForShell[0][0] == 'c')&&(arrayWordsForShell[0][1] == 'd')){
        cdShell(arrayWordsForShell);
        allFree2(arrayWordsForShell,*howWord);
        return 1;
    }
    if((arrayWordsForShell[0][0] == 'c')&&(arrayWordsForShell[0][1] == 'a')&&(arrayWordsForShell[0][2] == 't')){
        switch((Res = fork())){
            case -1:
                printf("Error while creating new process\n");
                exit(1);
            case 0:
                execvp(arrayWordsForShell[0],arrayWordsForShell);
                perror(arrayWordsForShell[0]);
                printf("Error while executing process\n");
                exit(1);
        }
        сleaningZombieProcesses(0);
        allFree2(arrayWordsForShell,*howWord);
        return 1;
    }
    if((arrayWordsForShell[0][0] == 'l')&&(arrayWordsForShell[0][1] == 's')){
        switch((Res = fork())){
            case -1:
                printf("Error while creating new process\n");
                exit(1);
            case 0:
                execvp(arrayWordsForShell[0],arrayWordsForShell);
                perror(arrayWordsForShell[0]);
                printf("Error while executing process\n");
                exit(1);
        }
        сleaningZombieProcesses(0);
        allFree2(arrayWordsForShell,*howWord);
        return 1;
    }
    if((arrayWordsForShell[0][0] == 's')&&(arrayWordsForShell[0][1] == 'a')&&(arrayWordsForShell[0][2] == 'y')){
        switch((Res = fork())){
            case -1:
                printf("Error while creating new process\n");
                exit(1);
            case 0:
                execvp(arrayWordsForShell[0],arrayWordsForShell);
                perror(arrayWordsForShell[0]);
                printf("Error while executing process\n");
                exit(1);
        }
        сleaningZombieProcesses(0);
        allFree2(arrayWordsForShell,*howWord);
        return 1;
    }
    return 0;
}

int main(int argc,char **argv){
    int file;
    if (argc == 2){
        file = open(argv[1], O_RDONLY);
        if (file != -1){
            dup2(file,0);
            close(file);
        }
    }
    else if (argc > 2){
        printf ("Error in argc\n");
        return 1;
    }
    
    char *word = NULL;
    char **arrayWords = NULL;
    char **arrayWordsForShell = NULL;
    int howLetter,howWord;
    for(;;){
        printwelcome();
        сleaningZombieProcesses(1);
        word = readWord(&howLetter);
        arrayWords = inputToArray(howLetter,word,arrayWords,&howWord);
        arrayWordsForShell = wordsForShell(howLetter,arrayWords,arrayWordsForShell ,&howWord);
        
        if(checkForShell(arrayWordsForShell,&howWord) != 1){
            outputArrayWords(arrayWords,howWord);
        }
        allFree(arrayWords,word,howWord);
    }
    return 0;
}

