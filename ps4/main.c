#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "transformations.h"

int main(int argc, char *argv[])
{
    FILE* fp = fopen("./assets/lenna.bmp", "rb");
    FILE* testf = fopen("test.bmp", "wb");
    FILE* testf1 = fopen("test1.bmp", "wb");
    struct bmp_image* test = read_bmp(fp);
    struct bmp_image* test1 = read_bmp(fp);
    fclose(fp);
    struct bmp_image* horizontal = flip_horizontally(test);

    bool writing = write_bmp(testf, horizontal);
    if(writing){
        printf("Good horizontal\n");
    }
    else{
        printf("bad h\n");
    }
    struct bmp_image* vertical = flip_vertically(test);
    writing = write_bmp(testf, vertical);
    if(writing){
        printf("Good vertical\n");
    }
    else{
        printf("bad v\n");
    }
    struct bmp_image* right = rotate_right(test);
    writing = write_bmp(testf, right);
    if(writing){
        printf("Good right\n");
    }
    else{
        printf("bad right\n");
    }
    struct bmp_image* left = rotate_left(test1);
    writing = write_bmp(testf1, left);
    if(writing){
        printf("Good left\n");
    }
    else{
        printf("bad left\n");
    }
    struct bmp_image* cropped = crop(test, 2, 0, 1, 1);
    writing = write_bmp(testf, cropped);
    if(writing){
        printf("Good crop\n");
    }
    else{
        printf("bad crop\n");
    }
    struct bmp_image* scaled = scale(test, 2);
    writing = write_bmp(testf1, scaled);
    if(writing){
        printf("Good scale\n");
    }
    else{
        printf("bad scale\n");
    }
        struct bmp_image* extracted = extract(test, "r");
    writing = write_bmp(testf, extracted);
    if(writing){
        printf("Good extract\n");
    }
    else{
        printf("bad extract\n");
    }

    free_bmp_image(test);
    fclose(testf);
    fclose(testf1);
    free_bmp_image(horizontal);
    free_bmp_image(vertical);
    free_bmp_image(right);
    free_bmp_image(left);
    free_bmp_image(cropped);
    free_bmp_image(scaled);
    free_bmp_image(extracted);
    free_bmp_image(test1);
    return 0;
}
