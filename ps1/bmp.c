#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char* reverse(const char* text){ 
    if(text == NULL) {
        return NULL;
    }
    char* reversed = (char*) calloc(10000, sizeof(char));
    if(strcmp(text, "") == 0){
        strcpy(reversed, text);
    return reversed;
    }
    int size = strlen(text);
    for(int i = 0, j = size - 1; text[i]; i++, j--){
        reversed[i] = text[j];
        if(islower(reversed[i])) reversed[i] = toupper(reversed[i]);
    }
    reversed[size] = '\0';
    return reversed;
}

char* vigenere_encrypt(const char* key, const char* text){
    if(key == NULL || text == NULL || strchr(key, ' ') != 0) return NULL;

    char *encrypted;
    encrypted = (char*) calloc(10000, sizeof(char));

    if(strcmp(key, "") == 0 || strcmp(text, "") == 0){
        strcpy(encrypted, "");
        return encrypted;
    } 

    int count = 0, keyLength = strlen(key) - 1;
    for(int i = 0; text[i]; i++){
        if(isalpha(text[i])){
            char ch = toupper(text[i]) + (toupper(key[count]) - 'A');
            encrypted[i] = ch;
            if(encrypted[i] > 'Z'){
                encrypted[i] -= 26;
            }
            if(count == keyLength){
                count = 0;
                continue;
            }
            count++;
        }
        else{
            encrypted[i] = text[i];
        }
    }
    encrypted[strlen(text)] = '\0';
    return encrypted;
}


char* vigenere_decrypt(const char* key, const char* text){

    if(key == NULL || text == NULL || strchr(key, ' ') != 0) return NULL;
    
    char *decrypted;
    decrypted = (char*) calloc(10000, sizeof(char));

    if(strcmp(key, "") == 0 || strcmp(text, "") == 0){
        strcpy(decrypted, "");
        return decrypted;
    }
    int count = 0, keyLength = strlen(key) - 1;
    for(int i = 0; text[i]; i++){
        if(isalpha(text[i])){
            char ch = toupper(text[i]) - (toupper(key[count]) - 'A');
            decrypted[i] = ch;
            if(decrypted[i] < 'A'){
                decrypted[i] += 26;
            }
            if(count == keyLength){
                count = 0;
                continue;
            }
            count++;
        }
        else{
            decrypted[i] = text[i];
        }
    }
    decrypted[strlen(text)] = '\0';

    return decrypted;
}



unsigned char* bit_encrypt(const char* text){

    if(text == NULL) return NULL;

    unsigned char *encrypted;
    encrypted = (unsigned char*) calloc(10000, sizeof(unsigned char));

    if(strcmp(text, "") == 0){
        strcpy((char*)encrypted, "");
        return encrypted;
    } 
    bool bits[8]; 
    
    for(int i = 0; text[i]; i++){
        unsigned char mask = 128;
        for(int j = 0; j < 8; j++){
            bits[j] = ((mask & text[i]) ? 1:0);
            mask >>= 1;
        }
        int flag = bits[0];
        bits[0] = bits[1];
        bits[1] = flag;

        flag = bits[2];
        bits[2] = bits[3];
        bits[3] = flag;
       
        
        for(int j = 4; j < 8; j++){
            bits[j] = bits[j-4] ^ bits[j];
        }

        mask = 128; 
        for(int j = 0; j < 8; j++){
            encrypted[i] |= (bits[j] ? mask : 0);
            mask >>= 1;
        }
    }

    return encrypted;

}


char* bit_decrypt(const unsigned char* text){

    if((char*)text == NULL) return NULL;

    char *decrypted;
    decrypted = (char*) calloc(10000, sizeof(char));

    if(strcmp((char*)text, "") == 0){
        strcpy(decrypted, "");
        return decrypted;
    }

    for(int i = 0; text[i]; i++) {
        bool bits[8]; 
        unsigned char mask = 128; 
        for(int j = 0; j < 8; j++) {
            bits[j] = ((mask & text[i]) ? 1 : 0);
            mask >>= 1;
        }
        for(int j = 7; j >= 4; j--) {
            bits[j] = bits[j-4] ^ bits[j];
        }
        
        int flag = bits[0];
        bits[0] = bits[1];
        bits[1] = flag;

        flag = bits[2];
        bits[2] = bits[3];
        bits[3] = flag;
                
        mask = 128;
        for(int j = 0; j < 8; j++) {
            decrypted[i] |= (bits[j] ? mask : 0);
            mask >>= 1;
        }
    }

    return decrypted;

}

unsigned char* bmp_encrypt(const char* key, const char* text){


    if(key == NULL || text == NULL || strchr(key, ' ') != 0) return NULL;

    unsigned char *encrypted;
    encrypted = (unsigned char*) calloc(10000, sizeof(unsigned char));

    if(strcmp(key, "") == 0 || strcmp(text, "") == 0){
        strcpy((char*)encrypted, "");
        return encrypted;
    }
    char* reversed;
    char* vigenere_encrypted;
    
    reversed = reverse(text);
    printf("reversed encr %s\n", reversed);
    vigenere_encrypted = vigenere_encrypt(key, reversed);
    printf("vigenere_encrypted %s\n", vigenere_encrypted);
    free(encrypted);
    encrypted = bit_encrypt(vigenere_encrypted);
    free(reversed);
    free(vigenere_encrypted);

    return encrypted;

}


char* bmp_decrypt(const char* key, const unsigned char* text){

    if(key == NULL || text == NULL || strchr(key, ' ') != 0) return NULL;

    char *decrypted;
    decrypted = (char*) calloc(10000, sizeof(char));

    if(strcmp(key, "") == 0 || strcmp((char*)text, "") == 0){
        strcpy(decrypted, "");
        return decrypted;
    }
    
    char *vigenere_decrypted;
    char *reversed;
    vigenere_decrypted = bit_decrypt(text);
    printf("bit decr %s\n", vigenere_decrypted);
    reversed = vigenere_decrypt(key, vigenere_decrypted);
    printf("vig decr %s\n", reversed);
    free(decrypted);
    decrypted = reverse(reversed);
    free(reversed);
    free(vigenere_decrypted);
    return decrypted;
}










