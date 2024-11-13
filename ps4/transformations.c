#include "bmp.h"
#include "transformations.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct bmp_image* flip_horizontally(const struct bmp_image* image){
    if (!image || !image->data || !image->header) {
        return NULL;
    }

    struct bmp_image* flipped = (struct bmp_image*)calloc(1, sizeof(struct bmp_image));
    if (!flipped) {
        return NULL; 
    }
    flipped->header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    if (!flipped->header) {
        free(flipped);
        return NULL; 
    } 
    memcpy(flipped->header, image->header, sizeof(struct bmp_header));

    flipped->data = (struct pixel*)calloc(image->header->width * image->header->height, sizeof(struct pixel));
    if (!flipped->data) {
        free(flipped->header);
        free(flipped);
        return NULL; 
    }

    for (uint32_t height = 0; height < image->header->height; height++) {
        for (uint32_t width = 0; width < image->header->width; width++) {
            uint32_t src_index = height * image->header->width + width;
            uint32_t dest_index = height * image->header->width + (image->header->width - 1 - width);
            flipped->data[dest_index] = image->data[src_index];
        }
    }
    return flipped;
}


struct bmp_image* flip_vertically(const struct bmp_image* image) {
    if (!image || !image->data || !image->header) {
        return NULL;
    }

    struct bmp_image* flipped = (struct bmp_image*)calloc(1, sizeof(struct bmp_image));
    if (!flipped) {
        return NULL; 
    }

    flipped->header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    if (!flipped->header) {
        free(flipped);
        return NULL; 
    } 
    memcpy(flipped->header, image->header, sizeof(struct bmp_header));

    flipped->data = (struct pixel*)calloc(image->header->width * image->header->height, sizeof(struct pixel));
    if (!flipped->data) {
        free(flipped->header);
        free(flipped);
        return NULL; 
    }

    for (uint32_t height = 0; height < image->header->height; height++) {
        for (uint32_t width = 0; width < image->header->width; width++) {
            uint32_t index_src = height * image->header->width + width;
            uint32_t index_dest = (image->header->height - height - 1) * image->header->width + width;
            
            flipped->data[index_dest] = image->data[index_src];
        }
    }

    return flipped;
}



struct bmp_image* rotate_right(const struct bmp_image* image){
    if(!image || !image->data || !image->header) {
        return NULL;
    }
    struct bmp_image* rotated = (struct bmp_image*) calloc(1, sizeof(struct bmp_image));
    if(!rotated){
        return NULL;
    }
    rotated->header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    if(!rotated->header){
        free(rotated);
        return NULL;
    }
    memcpy(rotated->header, image->header, sizeof(struct bmp_header));
    
    rotated->data = (struct pixel*)calloc(rotated->header->width * rotated->header->height, sizeof(struct pixel));
    if(!rotated->data){
        free(rotated->header);
        free(rotated);
        return NULL;
    }
    memcpy(rotated->data, image->data, image->header->height * image->header->width * sizeof(struct pixel));
    for(int i = 0; i < 3; i++){
        struct bmp_image* temp = (struct bmp_image*) calloc(1, sizeof(struct bmp_image));
        if(!temp){
            free_bmp_image(rotated);
            return NULL;
        }
        temp->header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
        if(!temp->header){
            free(temp);
            free_bmp_image(rotated);
            return NULL;
        }
        memcpy(temp->header, rotated->header, sizeof(struct bmp_header));
    
        temp->data = (struct pixel*)calloc(rotated->header->width * rotated->header->height, sizeof(struct pixel));
        if(!temp->data){
            free(temp->header);
            free(temp);
            free_bmp_image(rotated);
            return NULL;
        }
        memcpy(temp->data, rotated->data, rotated->header->height * rotated->header->width * sizeof(struct pixel));
        free_bmp_image(rotated);
        rotated = rotate_left(temp);
        free_bmp_image(temp);
    }

        return rotated;
}

struct bmp_image* rotate_left(const struct bmp_image* image){
    if(!image || !image->data || !image->header) {
        return NULL;
    }
    struct bmp_image* rotated = (struct bmp_image*) calloc(1, sizeof(struct bmp_image));
    if(!rotated){
        return NULL;
    }
    rotated->header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    if(!rotated->header){
        free(rotated);
        return NULL;
    }
    
    memcpy(rotated->header, image->header, sizeof(struct bmp_header));
    // swapped height and width
    
    rotated->header->height = image->header->width;
    rotated->header->width = image->header->height;
    
    uint32_t padding = (4 - ((rotated->header->width * sizeof(struct pixel)) % 4)) % 4;
    uint32_t sizeofimage = (uint32_t)(rotated->header->width * sizeof(struct pixel) * rotated->header->height + padding * rotated->header->height); 

    rotated->header->image_size = sizeofimage;
    rotated->header->size = rotated->header->image_size + sizeof(struct bmp_header); // update file size
    
    rotated->data = (struct pixel*)calloc(rotated->header->width * rotated->header->height, sizeof(struct pixel));
    if(!rotated->data){
        free(rotated->header);
        free(rotated);
        return NULL;
    }

    for (uint32_t height = 0; height < rotated->header->height; height++) {
        for (uint32_t width = 0; width < rotated->header->width; width++) {
            uint32_t src_index = width * image->header->width + height;
            uint32_t dest_index = (height * rotated->header->width) + (rotated->header->width - 1 - width);
            rotated->data[dest_index] = image->data[src_index];
        }
    }

    return rotated;
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
    if(!image || !image->data || !image->header || height < 1 || width < 1 || start_y < 0 || start_x < 0 || start_x > image->header->width || start_y > image->header->height || height > image->header->height - start_y || width > image->header->width - start_x) {
        return NULL;
    }
    struct bmp_image* croped = (struct bmp_image*) calloc(1, sizeof(struct bmp_image));
    if(!croped){
        return NULL;
    }

    croped->header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    if(!croped->header){
        free(croped);
        return NULL;
    }

    memcpy(croped->header, image->header, sizeof(struct bmp_header));
    croped->header->height = height;
    croped->header->width = width;
    
    uint32_t padding = (4 - ((croped->header->width * sizeof(struct pixel)) % 4)) % 4;
    uint32_t sizeofimage = (uint32_t)(croped->header->width * sizeof(struct pixel) * croped->header->height + padding * croped->header->height); 

    croped->header->image_size = sizeofimage;
    croped->header->size = croped->header->image_size + sizeof(struct bmp_header); // update file size
    

    croped->data = (struct pixel*)calloc(image->header->width * image->header->height, sizeof(struct pixel));
    if (!croped->data) {
        free(croped->header);
        free(croped);
        return NULL; 
    }
    
    
    for (uint32_t i = 0 ; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            uint32_t src_index = (image->header->height - start_y - i - 1) * image->header->width + (start_x + j);
            uint32_t dest_index = (height - i - 1) * croped->header->width + j;
            croped->data[dest_index] = image->data[src_index];
        }
    }

    return croped;
}

struct bmp_image* scale(const struct bmp_image* image, float factor){
    if(!image || !image->data || !image->header || factor <= 0) {
        return NULL;
    }
    struct bmp_image* scaled = (struct bmp_image*) calloc(1, sizeof(struct bmp_image));
    if(!scaled){
        return NULL;
    }

    scaled->header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    if(!scaled->header){
        free(scaled);
        return NULL;
    }

    memcpy(scaled->header, image->header, sizeof(struct bmp_header));
    scaled->header->width = (uint32_t)(round((float)image->header->width * factor));
    scaled->header->height = (uint32_t)(round((float)image->header->height * factor));

    scaled->data = (struct pixel*)calloc(scaled->header->width * scaled->header->height, sizeof(struct pixel));
    if (!scaled->data) {
        free(scaled->header);
        free(scaled);
        return NULL; 
    }
    uint32_t padding = (4 - ((scaled->header->width * sizeof(struct pixel)) % 4)) % 4;
    uint32_t sizeofimage = (uint32_t)(scaled->header->width * sizeof(struct pixel) * scaled->header->height + padding * scaled->header->height); 

    scaled->header->image_size = sizeofimage;
    scaled->header->size = scaled->header->image_size + sizeof(struct bmp_header); // update file size
    

    for (uint32_t new_y = 0; new_y < scaled->header->height; new_y++) {
        for (uint32_t new_x = 0; new_x < scaled->header->width; new_x++) {
            float original_x = (float)new_x * (float)image->header->width / (float)scaled->header->width;
            float original_y = (float)new_y * (float)image->header->height / (float)scaled->header->height;
            
            uint32_t nearest_x = (uint32_t)floor(original_x);
            uint32_t nearest_y = (uint32_t)floor(original_y);
            
            if (nearest_x >= image->header->width) nearest_x = image->header->width - 1;
            if (nearest_y >= image->header->height) nearest_y = image->header->height - 1;
            
            scaled->data[new_y * scaled->header->width + new_x] = image->data[nearest_y * image->header->width + nearest_x];
        }
    }

    return scaled;
}


struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
    if(!image || !image->data || !image->header || !colors_to_keep) {
        return NULL;
    }
    const char rgb[] = {"rgb"};
    size_t len = strspn(colors_to_keep, rgb);
    if(len != strlen(colors_to_keep)){
        return NULL;
    }
    struct bmp_image* extracted = (struct bmp_image*) calloc(1, sizeof(struct bmp_image));
    if(!extracted){
        return NULL;
    }

    extracted->header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    if(!extracted->header){
        free(extracted);
        return NULL;
    }

    memcpy(extracted->header, image->header, sizeof(struct bmp_header));

    extracted->data = (struct pixel*)calloc(image->header->width * image->header->height, sizeof(struct pixel));
    if (!extracted->data) {
        free(extracted->header);
        free(extracted);
        return NULL; 
    }
    

    for (uint32_t i = 0; i < image->header->width * image->header->height; i++) {
        if (strchr(colors_to_keep, 'r')) {
            extracted->data[i].red = image->data[i].red;
        } else {
            extracted->data[i].red = 0;
        }
        if (strchr(colors_to_keep, 'g')) {
            extracted->data[i].green = image->data[i].green;
        } else {
            extracted->data[i].green = 0;
        }
        if (strchr(colors_to_keep, 'b')) {
            extracted->data[i].blue = image->data[i].blue;
        } else {
            extracted->data[i].blue = 0;
        }
    }

    return extracted;

}
