#include<stdio.h>
#include<stdlib.h>
#include "stringutil.h"
#include <time.h>
char** words = NULL;
unsigned long nwords = 0;
char** verses = NULL;
unsigned long nverses = 0;
char* text = NULL;
long* chapterlengths = NULL;
long nchapters = 0;
unsigned long textlen;
long verseProgress = 0;

long n_sameletters=0;
long n_samevc=0;

unsigned long addword(char* text, unsigned long len){
    nwords++;
    words = realloc(words, nwords * sizeof(char*));
    words[nwords-1] = str_null_terminated_alloc(text, len);
    return nwords-1;
}

void makeVerse(){
    char* versetext = strdup("");
    long q = (((long)rand())%100); //how many words should be in the verse?
    q += 2;
    if((long)verseProgress + q >= (long)nwords)
    {
        q = nwords - verseProgress;
    }
    if(q <= 0){
        puts("\n<<ERROR>> A negative-word verse???");
        return;
    }
    long i;
    for(i = 0; i < q; i++){
        versetext = strcataf1(versetext, words[verseProgress+i]);
        if(i + 1 != q)
            versetext = strcataf1(versetext, " ");
    }
    verseProgress += q;
    nverses++;
    verses = realloc(verses, nverses * sizeof(char*));
    verses[nverses-1] = versetext;
}

void lettercount_verse(long vn, long* letters, long* vowels, long* consonants){
    *consonants = 0;
    *vowels = 0;
    *letters = 0;
    unsigned long verselen = strlen(verses[vn]);
    unsigned long i;
    for(i = 0; i < verselen; i++){
        switch(verses[vn][i]){
            default: //numbers and space go to default...
            break;
            case 'a':case 'A':
            case 'e':case 'E':
            case 'i':case 'I':
            case 'o':case 'O':
            case 'u':case 'U':
            (*vowels)++;
            break;
            
            case 'b':case 'B':
            case 'c':case 'C':
            case 'd':case 'D':
            
            case 'f':case 'F':
            case 'g':case 'G':
            case 'h':case 'H':
            
            case 'j':case 'J':
            case 'k':case 'K':
            case 'l':case 'L':
            case 'm':case 'M':
            case 'n':case 'N':
            
            case 'p':case 'P':
            case 'q':case 'Q':
            case 'r':case 'R':
            case 's':case 'S':
            case 't':case 'T':
            
            case 'v':case 'V':
            case 'w':case 'W':
            case 'x':case 'X':
            case 'y':case 'Y':
            case 'z':case 'Z':
            (*consonants)++; break;
            
        }
    }
    *letters = *vowels + *consonants; //notably, this does not include numbers...
}

void lettercount_verses(long v1, long v2, char* has_same_letters, char* matches_vowels_consonants){
    long letters_v1;
    long letters_v2;
    long consonants_v1;
    long consonants_v2;
    long vowels_v1;
    long vowels_v2;
    
    lettercount_verse(v1, &letters_v1, &vowels_v1, &consonants_v1);
    lettercount_verse(v2, &letters_v2, &vowels_v2, &consonants_v2);
    
    *has_same_letters = 0;
    *matches_vowels_consonants = 0;
    if(letters_v1 == letters_v2)
    *has_same_letters = 1;
    if(consonants_v1 == consonants_v2)
    if(vowels_v1 == vowels_v2)
    *matches_vowels_consonants = 1;
}

void compare_verses(long v1, long v2){
        printf("\n~~\nComparing verse %ld with %ld\n~~\n", v1,v2);
        char data[2];
        lettercount_verses(v1, v2, data+0, data+1);
        if(data[0]){
            printf("\n~~The verses have the same number of letters!~~\n");
            n_sameletters++;
        }
        if(data[1]){
            printf("\n~~The verses have the same number of vowels and consonants!~~\n");
            n_samevc++;
        }
        if(data[0] == 0 && data[1] == 0){
            puts("\nNo pattern found in verse letter counts.\n");
        }
        {
            printf("~~VERSE %ld~~\n%s\n~~", v1, verses[0]);
            printf("~~VERSE %ld~~\n%s\n~~", v2, verses[nverses-1]);
        }
}

int main(int argc, char** argv){
    srand(time(NULL));
    if(argc < 2){
        puts("usage: versegen /path/to/file_to_turn_into_verses.txt");
        exit(1);
    }
    FILE* q = fopen(argv[1], "r");
    {
        unsigned long len;
        text = read_file_into_alloced_buffer(q, &len);
    }
    //remove all non-alphanumeric characters.
    {
        unsigned long i;
        unsigned long l;
        l = strlen(text);
        textlen = l;
        for(i = 0; i < l; i++)
            if(!isalnum(text[i]))
                text[i] = ' ';
    }
    {unsigned long i;
    unsigned long wordlength;
    wordlength = 0;
        for(i = 0; i < textlen; i++){
            if(isalnum(text[i])) wordlength++;
            else if(wordlength != 0){
                addword(text+i-wordlength, wordlength);
                wordlength = 0;
            }
        }
        if(wordlength != 0){
                addword(text+i-wordlength, wordlength);
                wordlength = 0;
        }
    }
    verseProgress = 0;
    nverses = 0;
    //Print important things...
    printf("%lu words\n", nwords);
    if(nwords > 776)
    printf("%s is the 777th word\n", words[776]);
    if(nwords > 1610)
    printf("%s is the 1611th word\n", words[1610]);
    while(verseProgress < (long)nwords) makeVerse();
    printf("%lu verses\n", nverses);
    if(nverses > 776)
        printf("\n~~~~\n%s\n~~~~\n is the 777th verse\n", verses[776]);
    if(nverses > 1610)
        printf("\n~~~~\n%s\n~~~~\n is the 1611th verse\n", verses[1610]);
        
    //Take the resulting text and search for patterns...
    {
        char data[2];
        lettercount_verses(0, 1, data+0, data+1);
        if(data[0])
            printf("\n~~The first and last verses have the same number of letters!~~\n");
        if(data[1])
            printf("\n~~The first and last verses have the same number of vowels and consonants!~~\n");
            
        if(data[0] == 0 && data[1] == 0){
            puts("\nNo pattern found in first and last verse letter counts.\n");
        }
        {
            printf("~~FIRST VERSE~~\n%s\n~~", verses[0]);
            printf("~~LAST VERSE~~\n%s\n~~", verses[nverses-1]);
        }
    }
    puts("\n~~\nFIRST AND LAST VERSES\n~~\n");
    compare_verses(0, nverses-1);
    if(nverses > 1609)
    compare_verses(776, 1610);
    
    n_samevc = 0;
    n_sameletters = 0;
    for(int i = 0; i < 100000; i++){
        long q = rand();
        long q2 = rand();
        q %= nverses;
        q2 %= nverses;
        if(q == q2){
            i--;
            continue;
        }
        compare_verses(q,q2);
    }
    puts("\n~~SUMMARY OF FINDINGS~~\n");
    printf("\n%ld had the same number of letters, and \n%ld had the same number of vowels and consonants.\n", n_sameletters, n_samevc);
}
