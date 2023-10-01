#include<stdio.h>
#include<string.h>
#include<assert.h>

#define LEN 200
#define NUMLEN 10
#define CUTPART 10
#define CUTLEN 80
#define CUT "$"
#define START 1
#define END 13
#define DIGITOLD 2
#define DIGITNEW 2
// #define DEBUG
// #define DEBUG2

int digit(int i);
void makeNum(char Num[], int i, int maxDigit);
int cutSource(char Part[][CUTLEN], char Source[]);
void makeFileName(int n, char Part[][CUTLEN], char Num[], char Result[]);

int main(){

    char SourceOld[LEN] = "[Nekomoe kissaten] Irozuku Sekai no Ashita kara $ [WebRip 1080p HEVC-yuv420p10 AAC].JPSC.ass";
    char SourceNew[LEN] = "[DMG&MakariHoshiyume&VCB-Studio] Irozuku Sekai no Ashita kara [$][Ma10p_1080p][x265_flac_aac].JPSC.ass";

    char PartOld[CUTPART][CUTLEN];
    char PartNew[CUTPART][CUTLEN];
    int nP_Old = cutSource(PartOld, SourceOld);
    int nP_New = cutSource(PartNew, SourceNew);
    
    for (int i = START; i <= END; i++){
        char Old[LEN] = "", New[LEN] = "";
        char NumOld[NUMLEN] = "";
        char NumNew[NUMLEN] = "";
        makeNum(NumOld, i, DIGITOLD);
        makeNum(NumNew, i, DIGITNEW);
        makeFileName(nP_Old, PartOld, NumOld, Old);
        makeFileName(nP_New, PartNew, NumNew, New);
        int success = rename(Old, New);
        if (success == 0)
            continue;
        printf("failed: %d\n", i);
    }


    return 0;
}

void makeFileName(int n, char Part[][CUTLEN], char Num[], char Result[]){
    for (int i = 0; i < n-1; i++){
        strcat(Result, Part[i]);
        strcat(Result, Num);
    }
    strcat(Result, Part[n-1]);
    #ifdef DEBUG
        printf("%s\n", Result);
    #endif
}

int cutSource(char Part[][CUTLEN], char Source[]){
    int n = 0;
    char *head = strtok(Source, CUT);
    while (head != NULL){
        strcpy(Part[n], head);
        n++;
        head = strtok(NULL, CUT);
    }
    return n;
}

void makeNum(char Num[], int i, int maxDigit){
    int d = digit(i);
    while (d < maxDigit){
        strcat(Num, "0");
        d++;
    }
    char Temp[NUMLEN];
    sprintf(Temp, "%d\0", i);
    strcat(Num, Temp);
    #ifdef DEBUG
        printf("%d, Num: %s\n", i, Num);
    #endif
}

int digit(int i){
    #ifdef DEBUG2
        printf("%d: ", i);
    #endif
    int re = 0;
    while (i > 0){
        i /= 10;
        re++;
    }
    #ifdef DEBUG2
        printf("%d digits\n", re);
    #endif
    return re;
}