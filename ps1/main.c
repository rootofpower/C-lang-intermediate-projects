#include <stdio.h>
#include "bmp.h"
#include <stdlib.h>
#include <string.h>
#include "playfair.h"

int main(int argc, char *argv[])
{   
     
    char *encrypted, *decrypted;
    unsigned char *encrypted_bmp;
    //reverse func usage
    char* reversed;
    reversed = reverse("Hello World!");
    printf("%s\n", reversed);
    free(reversed);
    //end
   
    //encrypt func usage    
   
    encrypted = playfair_encrypt(NULL, "");
    if(encrypted == NULL) printf("encrypted playfair is NULL\n");

    decrypted = playfair_decrypt(NULL, encrypted);
    if(decrypted == NULL) printf("decrypted playfair is NULL\n");

    free(encrypted);
    free(decrypted);

    encrypted = playfair_encrypt("unswerving", "XXOVNING");
    printf("Encrypted playfair -> %s>\n", encrypted);
    char* text = "SS YA ID SI";
    char* key = "unswerving";
    decrypted = playfair_decrypt(key, text);
    printf("Decrypted pl -> %s>\n", decrypted);
    free(encrypted);
    free(decrypted);
    //vigenere encrypt/decrypt func usage 
    //with null statement 
    encrypted = vigenere_encrypt(NULL, "Hello world!");
    if(encrypted == NULL)
        printf("vigener encr is null\n");
    decrypted = vigenere_decrypt("CoMPuTeR", encrypted);
    if(decrypted == NULL)
        printf("vig dec is null\n");
    free(encrypted);
    free(decrypted);
    //key is string 
    
    encrypted = vigenere_encrypt("abcag fes freg", "Hello World!");
    if(encrypted == NULL)
        printf("vigenere_encrypt = NULL\n");
    decrypted = vigenere_decrypt("abdfs gtgs wrg", encrypted);
    if(decrypted == NULL)
        printf("vigenere_decrypt = NULL\n");
    free(encrypted);
    free(decrypted);

    //with empty str
    encrypted = vigenere_encrypt("", "fagrf");
    if(strcmp(encrypted, "") == 0)
        printf("vig encr empt str\n");
    decrypted = vigenere_decrypt("CoMPuTeR", encrypted);
    if(strcmp(decrypted, "") == 0)
        printf("vig dec empt str\n");
    free(encrypted);
    free(decrypted);
    //default use
    encrypted = vigenere_encrypt("COMPUTER", "HELLO WORLD!");
    printf("!vigenere encrypted -> %s\n", encrypted); 
    decrypted = vigenere_decrypt("CoMPuTeR", encrypted);
    printf("vigenere decrypted -> %s\n", decrypted);
    free(encrypted);
    free(decrypted);

    //end  
    
    //bit encrypt/decrypt func usage 
    //default use 
    encrypted_bmp = bit_encrypt("Hello world!");
    printf("!!!bit encrypted -> \n");
    for(int i=0; i < 12;i++) {
        printf("%x ", encrypted_bmp[i]);
    }

    decrypted = bit_decrypt(encrypted_bmp);
    printf("bit decrypted -> %s\n", decrypted);
    free(encrypted_bmp);
    free(decrypted);

    //with null
    encrypted_bmp = bit_encrypt(NULL);
    if(encrypted_bmp == NULL)
        printf("bit encr is null\n");

    decrypted = bit_decrypt(encrypted_bmp);
    if(decrypted == NULL)
        printf("bit decrypt is null\n");
    free(encrypted_bmp);
    free(decrypted);

    //with emty str
    
    encrypted_bmp = bit_encrypt("");
    if(strcmp((char*)encrypted_bmp, "") == 0)
        printf("bit encrypt empty str\n");
    decrypted = bit_decrypt(encrypted_bmp);
    if(strcmp(decrypted, "") == 0)
        printf("bit decrypt empty str\n");
    free(encrypted_bmp);
    free(decrypted);

    //end

    //bmp encrypt/decrypt func usage
    //default usage
    encrypted_bmp = bmp_encrypt("Secret", "Hello");
    printf("bmp encrypted -> %s\n", encrypted_bmp);
    decrypted = bmp_decrypt("Secret", encrypted_bmp);
    printf("bnp decrypted -> %s\n", decrypted);
    free(encrypted_bmp);
    free(decrypted);

    //with null 
    //
    encrypted_bmp = bmp_encrypt(NULL, "abc");
    if(encrypted_bmp == NULL)
        printf("bmp encrypt is null\n");
    decrypted = bmp_decrypt(NULL, encrypted_bmp);
    if(decrypted == NULL)
        printf("bmp decrypt is null\n");
    free(encrypted_bmp);
    free(decrypted);

    // //with empty str
    // 

    encrypted_bmp = bmp_encrypt("", "abc");
    if(strcmp((char*)encrypted_bmp, "") == 0)
        printf("bmp encrypt is empty string\n");
    decrypted = bmp_decrypt ("", encrypted_bmp);
    if(strcmp(decrypted, "") == 0)
        printf("bmp decrypt is empty string\n");
    free(encrypted_bmp);
    free(decrypted);


    //end

    return 0;

}
