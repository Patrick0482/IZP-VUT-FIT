#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LENGTH 100
#define MAX_CHARACTERS 128

int string_length(char array[]){
    int size=0;
    for(int i=0; array[i] != '\0';i++){ 
        size++;
    }
    return size;
}

bool too_long_passw(char array[]){       
    for(int i=0; array[i] != '\0';i++){
        if(array[i]=='\n'){
            return false;
        }
    }
    return true;
}
bool is_string_same(char str1[], char str2[]){
    if(string_length(str1) != string_length(str2)){
        return false;
    }
    for(int i = 0; i<string_length(str1); i++){
        if(str1[i]!=str2[i]){
            return false;
        }
    }
    return true;
}

bool if_lowercase(char array[],int length){
    int i=0;
    while(i<length){
        if(array[i]>='a' && array[i]<='z'){
            return true;
        }
        i++;
    }
    return false;
}

bool if_uppercase(char array[],int length){
    int i=0;
    while(i<length){
        if(array[i]>='A' && array[i]<='Z'){
            return true; 
        }
        i++;
    }
    return false;
}

bool if_numbers(char array[],int length){
    int i=0;
    while(i<length){
        if(array[i]>='0' && array[i]<='9'){
            return true;
        }
        i++;
    }
    return false;
}

bool if_special(char array[],int length){
    int i=0;
    while(i<length){
        if((array[i]>=' ' && array[i]<'0') || (array[i]>'9' && array[i]<'A') || (array[i]>'Z' && array[i]<'a') || (array[i]>'z' && array[i]<='~')){  //interval of all characters without numbers and letters in ASCII
            return true;
        }
        i++;
    }
    return false;
}

bool level_one(char array[], int length){
    if((if_lowercase(array,length)) && (if_uppercase(array,length))){
        return true;
    }
    return false;
}


bool level_two(char array[], int length,int parameter){
    int x=0;

    if(if_uppercase(array,length)){
        x++;
    }
    if(if_lowercase(array,length)){
        x++;
    }
    if(if_numbers(array,length)){
        x++;
    }
    if(if_special(array,length)){
        x++;
    }
    
    if(x >= parameter || parameter >4){
        return true;
    }
    return false;
}

bool level_three(char array[],int length, int parameter){
    int i = 1;
    int sub_len = 1; //starting at second character and comparing it with one before
    int max_sub_len = 0;
    while(i<length){
        if(array[i]==array[i-1]){  
            sub_len++;
        }
        else {
            if(sub_len > max_sub_len){
                max_sub_len = sub_len;
                sub_len = 1;
            }
        }
        i++;
    }
    if(max_sub_len < parameter){
        return true;
    }
    return false;
}

bool level_four(char array[],int string_length,int parameterx){
    int max=0;
    int length=0;

    for(int i=0; i<string_length-1; i++){     //"catching" the first letter
        for(int j=i+1; j<string_length; j++){ //comparing the first letter with next one 
            for(int k=0; k<parameterx; k++){  //"k" is for reseting the for(j) and coming back to for(i)
                if(array[i+k]==array[j+k]){
                    length++;
                }
                else{
                    if(length>max){
                        max=length;     //saving the highest number of same substrings
                    }
                    k=parameterx; //if substrings are not the same this will go back to the for(i)
                    length = 0;
                }
            }
        }
    }

    if(max<parameterx){
        return true;
    }
    return false;
}

int is_shortest_passw(char array[],int shortest_pw){
    
    if(string_length(array) < (shortest_pw)){
        return string_length(array)-1;
    } 
      
    return shortest_pw;
}

int is_characters_count(int characters[]){
    int aux = 0;
    for(int i=0; i<MAX_CHARACTERS; i++){ //MAX_CHARACTERS --> amount of usable characters from ASCII in our passwords
        if(characters[i]>0){
            aux++;
        }
    }
    return aux;
}

int main(int argc, char *argv[]){

    bool stats_exist = false; 
    int shortest_passw = MAX_LENGTH; //MAX_LENGTH --> maximum count of characters in our password
    int character_count = 0;
    double passw_count = 0.0;
    int characters[MAX_CHARACTERS] = {0}; //array of different characters used in passwords

    if((argc != 4) && (argc != 3))
    {
        fprintf(stderr,"Wrong amount of arguments.\n");  //maximum length of argc should be 4 (with "--stats") or 3 without it
        return -1;
    }

    if(atoi(argv[1]) < 1 || atoi(argv[1]) > 4)
    {
        fprintf(stderr,"Input argument [LEVEL] only from interval <1,4>\n"); //we have only 4 levels and it should not be higher nor lower number 
        return -1;
    }

    if(atoi(argv[2]) <= 0)
    {
        fprintf(stderr,"Input argument [PARAM] only as positive number\n"); //PARAMETER can be any number that is not below zero
        return -1;
    }

    

    if(argc == 4)
    {
        if(!(is_string_same(argv[3],"--stats"))) //if "--stats" was written correctly
        {
            fprintf(stderr,"Format of [--stats] is incorrect.\n");
            return -1;
        }
        stats_exist = true;
    }

    int fine_param; //contains only numbers from argument PARAM
    int fine_level; // -||- from argument LEVEL

    char *string_part_p; //contains only the string part of argument PARAMETER -> later used for ERROR
    char *string_part_l; // -||- of argument LEVEL

    fine_param = strtol(argv[2],&string_part_p,10); //taking just the integer part and putting the string part in "string_part_p"
    fine_level = strtol(argv[1],&string_part_l,10); // -||- in "string_part_l"
    
    int parameter = fine_param; //for easier reading I guess
    int level = fine_level;

    if(string_part_p[0] != '\0' && string_part_l[0] != '\0'){     //controlling if LEVEL and PARAMETER are correctly written
        fprintf(stderr,"Argument LEVEL and PARAMETER may contain only numbers and CAN NOT be empty!\n"); 
        return -1;
    }
    if(string_part_l[0] != '\0'){
        fprintf(stderr,"Argument LEVEL may contain only numbers and CAN NOT be empty!\n");
        return -1;
    }

    if(string_part_p[0] != '\0'){
        fprintf(stderr,"Argument PARAMETER may contain only numbers and CAN NOT be empty!\n");
        return -1;
    }
    
    char password[MAX_LENGTH + 2];
    
    while (fgets(password,MAX_LENGTH + 2,stdin) != NULL){            //inputting passwords from stdin of max length "102" and checking if they are not NULL
        shortest_passw = is_shortest_passw(password,shortest_passw); 
        character_count += string_length(password); //total amount of characters
        passw_count += 1; //amount of passwords

        for(int j = 0; password[j] != '\0' && password[j] != '\n'; j++){
            int aux1 = password[j];
            characters[aux1] += 1; //different characters used
        }

        if(too_long_passw(password)){
            fprintf(stderr,"The password is too long!\n"); //if password is longer than MAX_LENGTH
            return -1;
        };

        int passw_length = string_length(password); //for better reading again
        int finished_levels = 0; //amount of levels done

        switch(level) //controlling the highest level possible if not done --> "falling through" to level underneath
        {
            case 4:
                if(level_four(password,passw_length,parameter)){ 
                    finished_levels++;
                }
                //fall through
            case 3:
                if(level_three(password,passw_length,parameter)){
                    finished_levels++;
                }
                //fall through
            case 2:
                if(level_two(password,passw_length,parameter)){
                    finished_levels++;
                }
                //fall through
            case 1:
                if(level_one(password,passw_length)){
                    finished_levels++;
                }
        }
        if(finished_levels == level){
            printf("%s",password);
        }
    }
    printf("\n");

    if(stats_exist){
    printf("Statistics: \n");
    printf("-------------------------\n");
    printf("Different characters count:  %d\n",is_characters_count(characters));
    printf("The shortest password: %d\n",is_shortest_passw(password,shortest_passw));
    printf("Average length of passwords: %.1f\n",(character_count/passw_count)-1);

    }
    return 0;
}