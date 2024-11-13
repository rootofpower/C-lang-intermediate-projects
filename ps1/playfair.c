#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "playfair.h"
#include <stdio.h>
#include <stdbool.h>

char* add_x(char* str){
    char* added = (char*) calloc(2 * strlen(str), sizeof(char));
    int j = 0, i = 0;
    bool flag = 0;
    for(i = 0, j = 0; i < strlen(str);i++){
        if(str[i] == str[i+1] && str[i] != 'X'){
            added[j++] = str[i];
            added[j++] = 'X';
            added[j++] = str[i+1];
            flag = 1;
            i++;
        }
        
        else{
        added[j++] = str[i];
        if(str[i] == 'X' && flag){
                flag = 0;
            }
        }
    }
    j = strlen(added);
    if(j % 2 != 0) added[j++] = 'X';
    added[j] = '\0';
    free(str);
    return added;
}

void search(char f_letter, char sec_letter, char matrix[5][5], int arr[]){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(f_letter == matrix[i][j]){
                arr[0] = i;
                arr[1] = j;
            }
        }
    }
    for(int i = 0; i < 5; i++){
        for (int j = 0;j < 5;j++) {
            if(sec_letter == matrix[i][j]){
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}
void fillMatrix(char matrix[5][5], char* key){
    
    char alphabet[26] = {0};
    int k = 0, i = 0, j = 0, flag = 0;
    strcpy(alphabet, ALPHA);
    for(i = 0; key[i]; i++){
        for(j = 0, k = 0; j < strlen(alphabet); j++){
            if(alphabet[j] != key[i]){
                alphabet[k++] = alphabet[j];
            }
            if(alphabet[k-1] == 'Z'){
                flag = 1;
                if(flag == 1) break;
            }


        }
    }
    alphabet[k] = '\0';
    k = 0;
    int index = 0;
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            if(k < strlen(key))
                matrix[i][j] = key[k++];
            else{
                matrix[i][j] = alphabet[index++];  
            }
        }
    }

}

void removeSpases(char* text){
    int i, j;
    for(i = 0, j = 0; i < strlen(text); i++)
        if(text[i] != ' ')
            text[j++] = text[i];
    text[j] = '\0';
}

void toUpperString(char* text,const char* str){
    int i;
    for(i = 0; str[i]; i++){
        text[i] = str[i];
        if(islower(text[i])) text[i] = toupper(text[i]);
    } 
}

void fromWToV(char* str){
    int i;
    for(i = 0; str[i]; i++){
        if(str[i] == 'W')
            str[i] = 'V';
    }
}
void remDublicates(char* str){
    int hash[256] = {0};
    int i, j;
    for(i = 0, j = 0; i < strlen(str); i++){
        if(hash[(int)str[i]] == 0){
            hash[(int)str[i]] = 1;
            str[j++] = str[i];
        }
    }
    str[j] = '\0';    
}
char* playfair_encrypt(const char* key, const char* text){
    if(key == NULL || text == NULL || strcmp(key, " ") == 0 || strcmp(text, " ") == 0) return NULL;
    for(int i = 0; key[i]; i++){
        if(!isalpha(key[i]) && !isspace(key[i])) return NULL;
    }
    char* encrypted, *key_reworked, *text_reworked;
    encrypted = (char*) calloc(10000, sizeof(char));
    int i = 0, j = 0;
    if(strcmp(key, "") == 0 || strcmp(text, "") == 0){
        strcpy(encrypted, "");
        return encrypted;
    } 
    key_reworked = (char*) calloc(2 * strlen(key), sizeof(char));
    text_reworked = (char*) calloc(2* strlen(text), sizeof(char));
    
    // to upper 
    
    toUpperString(key_reworked, key);
   
    //remove spase in key

    removeSpases(key_reworked);
    
    fromWToV(key_reworked); 
    //remove dublicates
    remDublicates(key_reworked); 
    //toupper text
    toUpperString(text_reworked, text);   

    removeSpases(text_reworked);

    //change W to V in text 

    fromWToV(text_reworked);
    //add X in text 
    text_reworked = add_x(text_reworked);
    //filling key in matrix
    char matrix[5][5];
    fillMatrix(matrix, key_reworked);

    //encrypting
    
    int arr[4] = {0};
    for(i = 0, j = 0; text_reworked[i]; i+=2, j+=3){
        search(text_reworked[i], text_reworked[i+1], matrix, arr);
        if(arr[0] == arr[2]){
                if(arr[1] == arr[3]){
                    encrypted[j] = matrix[(arr[0] + 1) % 5][arr[1]];
                    encrypted[j+1] = matrix[(arr[2] + 1) % 5][arr[3]];
                    encrypted[j+2] = ' ';
                }
                else{
                    encrypted[j] = matrix[arr[0]][(arr[1] +1) %5];
                    encrypted[j+1] = matrix[arr[2]][(arr[3] + 1)%5];
                    encrypted[j+2] = ' ';
                }
        }
        else if(arr[1] == arr[3]){
                encrypted[j] = matrix[(arr[0] + 1) % 5][arr[1]];
                encrypted[j+1] = matrix[(arr[2] + 1) % 5][arr[3]];
                encrypted[j+2] = ' ';
                
        }
        else{
                encrypted[j] = matrix[arr[0]][arr[3]];
                encrypted[j+1] = matrix[arr[2]][arr[1]];
                encrypted[j+2] = ' ';
                
            }
    }
    encrypted[j - 1] = '\0';
    free(key_reworked);
    free(text_reworked);

    return encrypted;
}

char* playfair_decrypt(const char* key, const char* text){
    if(key == NULL || text == NULL || strchr(text, 'W') != 0 || strcmp(key, " ") == 0 || strcmp(key, " ") == 0) return NULL;
    for(int i = 0; key[i]; i++){
        if(!isalpha(key[i]) && !isspace(key[i])) return NULL;
    }
    char *decrypted, *key_reworked, *text_reworked;
    decrypted = (char*) calloc(10000, sizeof(char));
    if(strcmp(key, "") == 0 || strcmp(text, "") == 0){
        strcpy(decrypted, "");
        return decrypted;
    } 
    int i;
    key_reworked = (char*) calloc(2 * strlen(key), sizeof(char));
    text_reworked = (char*) calloc(2* strlen(text), sizeof(char));
    

    toUpperString(key_reworked, key);
    removeSpases(key_reworked);
    fromWToV(key_reworked);
    remDublicates(key_reworked); 
    toUpperString(text_reworked, text);
    removeSpases(text_reworked);

    char matrix[5][5]; 
    fillMatrix(matrix, key_reworked);
    int arr[4] = {0};
    for(i = 0; text_reworked[i]; i+=2){
        search(text_reworked[i], text_reworked[i+1], matrix, arr);
        if(arr[0] == arr[2]){
            if(arr[1] == arr[3]&& arr[0] == 0){
                decrypted[i] = matrix[4][arr[1]];
                decrypted[i+1] = matrix[4][arr[3]];
            }
            else if(arr[1] == arr[3] && arr[0] != 0){
                decrypted[i] = matrix[(arr[0] - 1) % 5][arr[1]];
                decrypted[i+1] = matrix[(arr[2] - 1) % 5][arr[3]];
            }
            else if(arr[3] == 0){
                decrypted[i] = matrix[arr[0]][(arr[1] - 1) % 5];
                decrypted[i+1] = matrix[arr[2]][4];
            }
            else if(arr[1] == 0){
                decrypted[i] = matrix[arr[0]][4];
                decrypted[i+1] = matrix[arr[2]][(arr[3] - 1) % 5];                    
            }    
            else {
                decrypted[i] = matrix[arr[0]][(arr[1] - 1) % 5];
                decrypted[i + 1] = matrix[arr[2]][(arr[3] - 1) % 5];
            }
        }
        else if(arr[1] == arr[3]){
            if(arr[0] == 0){
                decrypted[i] = matrix[4][arr[1]];
                decrypted[i+1] = matrix[(arr[2] - 1) % 5][arr[3]];                    
            }
            else if(arr[2] == 0){
                decrypted[i] = matrix[(arr[0] - 1) % 5][arr[1]];
                decrypted[i+1] = matrix[4][arr[3]];
            }
            else {
                decrypted[i] = matrix[(arr[0] - 1) % 5][arr[1]];
                decrypted[i + 1] = matrix[(arr[2] - 1) % 5][arr[3]];
            }
        }
        else{
            decrypted[i] = matrix[arr[0]][arr[3]];
            decrypted[i+1] = matrix[arr[2]][arr[1]];
        }
    }
    free(text_reworked);
    free(key_reworked);
    return decrypted;
}

