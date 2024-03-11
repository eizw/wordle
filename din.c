#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void getWordList(char** wordlist) {
    FILE *wordsfile = fopen("wordlist.txt", "r");
    char *word = malloc(6 * sizeof(char));
    int i = 0;
    while (fscanf(wordsfile, "%s", word) != EOF && i < 200) {
        wordlist[i] = word;
        i++;
        word = malloc(6 * sizeof(char));
    }
    fclose(wordsfile);
}

char *pickWord(char** wordlist) {
    srand(time(NULL));
    return wordlist[rand() % 200];
}

char* toCaps(char *g) {
    for (int i = 0; i < strlen(g); i++) {
        g[i] = toupper(g[i]);
    }
    return g;
}

int validCheck(char *g, char** wordlist) {
    int i = 0;
    int match = 0;
    while (i < 200) {
        if (strpbrk(g, wordlist[i])) match++;
        i++;
    }
    if (match==0) return 0;
    for (int i = 0; i < strlen(g); i++) {
        if (i==5) return 0;
        if (isalpha(g[i]) == 0) return 0;
        for (int j = 0; j < 5; j++) {
            if (g[i] == g[j] && i != j) return 0;
        }
    }
    return 1;
}

char *guessCheck(char *guess, char *word) {
        char *check;
        check = malloc(6 * sizeof(char));
        strcpy(check, "-----\0");
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (guess[i]==word[j]) {
                    if (i==j) check[i] = '*';
                    else check[i] = '#';
                    break;
                } 
            }
        }
        return check;
}

char *getGuess(char *g, int i) {
    printf("Please enter a guess\n");
    switch (i) {
        case 0: printf("First Guess: "); break;
        case 1: printf("Second Guess: "); break;
        case 2: printf("Third Guess: "); break;
        case 3: printf("Fourth Guess: "); break;
        case 4: printf("Fifth Guess: "); break;
        case 5: printf("Six (and last!) Guess: "); break;
    }
    // * INPUT: guess
    scanf("%s", g);
    return g;
}

int newGame() {
    char** wordlist = calloc(200, sizeof(char*));
    getWordList(wordlist);
    char g[6];
    char w[6];
    strcpy(w, pickWord(wordlist));
    for (int i = 0; i < 6; i++) {
        // ! make guess all caps
        strcpy(g, toCaps(getGuess(g, i)));
        // ! check validity of guess
        if(validCheck(g, wordlist) == 0) {
            printf("(Invalid guess, try again.)\n");
            i--;
            continue;
        }
        char *c = guessCheck(g, w);
        printf("%s\n", c);
        free(c);
        if (strcmp(c, "*****")==0) {
            printf("Good Job!, You've guessed in %d guesses.\n", i);
            return 0;
        }
    }
    printf("You've ran out of guesses!\nThe word was %s\n\n", w);
}

int main(int argc, char *argv) {
    while (1) {
        int input;
        printf("Welcome to Wordle!\n1 - Start a new game\n2 - How to play\n3 - Exit\n");
        // * INPUT: main menu selection
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            newGame();
            break;
        case 2:
            printf("Google 'how to play wordle'\n");
            break;
        case 3:
            return 0;
            break;
        default:
            printf("Invalid input, try again\n");
            break;
        }
    }
    return 0;
}