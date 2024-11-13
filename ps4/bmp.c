#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>


struct bmp_header* read_bmp_header(FILE* stream) {
    if (!stream) {
        return NULL;
    }

    fseek(stream, 0, SEEK_SET);
    
    struct bmp_header* header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    if (!header) {
        return NULL;
    }

    if (fread(header, sizeof(struct bmp_header), 1, stream) != 1) {
        free(header);
        return NULL;
    }

    if (header->type != 0x4d42) {
        free(header);
        return NULL;
    }

    return header;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header) {
    if (!stream || !header) {
        return NULL;
    }

    fseek(stream, header->offset, SEEK_SET);

    struct pixel* data = (struct pixel*)calloc(header->width * header->height, sizeof(struct pixel));
    if (!data) {
        return NULL;
    }

    int padding = (4 - ((int)(header->width * sizeof(struct pixel)) % 4)) % 4;

    for (int height = 0; height < header->height; height++) {
        for (int width = 0; width < header->width; width++) {
            fread(&data[(uint32_t)height * header->width + (uint32_t)width], sizeof(struct pixel), 1, stream);
        }
        fseek(stream, padding, SEEK_CUR);
    }
    return data;
}

struct bmp_image* read_bmp(FILE* stream){
    if(!stream){
        return NULL;
    }
    struct bmp_image* image = (struct bmp_image*) calloc(1, sizeof(struct bmp_image));
    image->header = read_bmp_header(stream);
    if(!image->header){
        fprintf(stderr, "Error: This is not a BMP file.\n");
        free_bmp_image(image);
        return NULL;
    }
    image->data = read_data(stream, image->header);
    if(!image->data){
        fprintf(stderr, "Error: Corrupted BMP file.\n");
        free_bmp_image(image);
        return NULL;
    }
    return image;
}



bool write_bmp(FILE* stream, const struct bmp_image* image) {
    if (!stream || !image || !image->header || !image->data) {
        printf("first if\n");
        return false;
    }

    fseek(stream, 0, SEEK_SET);
    if (fwrite(image->header, sizeof(struct bmp_header), 1, stream) != 1) {
        printf("second if\n");
        return false;
    }

    fseek(stream, image->header->offset, SEEK_SET);
    for (int row = 0; row < image->header->height; row++) {
        if (fwrite(&image->data[(uint32_t)row * image->header->width], sizeof(struct pixel), image->header->width, stream) != image->header->width) {
            printf("third if\n");
            return false;
        }
        int padding = (4 - (image->header->width * sizeof(struct pixel)) % 4) % 4;
        if (padding > 0) {
            unsigned char pad = 0;
            if (fwrite(&pad, sizeof(unsigned char), (uint32_t)padding, stream) != padding) {
                printf("fourth if\n");
                return false;
            }
        }
    }

    return true;
}

void free_bmp_image(struct bmp_image* image){
    if(image){
        free(image->header);
        free(image->data);
        free(image);
    }
}

