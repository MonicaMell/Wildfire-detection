#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"


void resize_image(const uint8_t* original_image, int original_width, int original_height,
                         uint8_t* resized_image, int adjusted_width, int adjusted_height) {

    for (int y = 0; y < adjusted_height; y++) {
        for (int x = 0; x < adjusted_width; x++) {
            // calculating the coordinates in the original image
            float original_x = (float)x / adjusted_width * original_width;
            float original_y = (float)y / adjusted_height * original_height;

            // calculating mean color of 3x3 neighborhood in the original image
            int color_mean[3] = {0};
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    int original_current_x = (int)original_x + i;
                    int original_current_y = (int)original_y + j;

                    // staying within the image bounds
                    original_current_x = fmin(fmax(original_current_x, 0), original_width - 1);
                    original_current_y = fmin(fmax(original_current_y, 0), original_height - 1);

                    for (int k = 0; k < 3; k++) {
                        color_mean[k] += original_image[(original_current_y * original_width +
                                                         original_current_x) * 3 + k];
                    }
                }
            }
            for (int i = 0; i < 3; i++) {
                color_mean[i] /= 9;
            }
            resized_image[(y * adjusted_width + x) * 3] = color_mean[0];
            resized_image[(y * adjusted_width + x) * 3 + 1] = color_mean[1];
            resized_image[(y * adjusted_width + x) * 3 + 2] = color_mean[2];
        }
    }
}


int count_red_pixels(const uint8_t* image, int width, int height) {
    int count = 0;
    for (int i = 0; i < width * height; i++) {
        if (image[i * 3] > 125 && image[i * 3 + 1] < 100 && image[i * 3 + 2] < 100) {
            count++;
        }
    }
    return count;
}


int count_orange_pixels(const uint8_t* image, int width, int height) {
    int count = 0;
    for (int i = 0; i < width * height; i++) {
        if (image[i * 3] > 200 && image[i * 3 + 1] > 100 && image[i * 3 + 2] < 100) {
            count++;
        }
    }
    return count;
}


void ascii_representation(const uint8_t* image, int width, int height) {
    char ascii_chars[] = "@%#*+=-:. ";

    // converting RGB to grayscale
    int* grayscale_image = malloc(width * height * sizeof(int));
    for (int i = 0; i < width * height; i++) {
        grayscale_image[i] = (int)(0.299 * image[i * 3] +
                                   0.587 * image[i * 3 + 1] +
                                   0.114 * image[i * 3 + 2]);
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // checking if the pixel is red or orange
            if (((image[(y * width + x) * 3] > 125 && image[(y * width + x) * 3 + 1] < 100) ||
                (image[(y * width + x) * 3] > 200 && image[(y * width + x) * 3 + 1] > 100)) &&
                image[(y * width + x) * 3 + 2] < 100) {

                // ANSI escape code for red text
                printf("\033[1;31m");  
            }
            // mapping grayscale value to ASCII character
            int index = (int)(grayscale_image[y * width + x] / 255.0 * (sizeof(ascii_chars) - 1));
            printf("%c", ascii_chars[index]);

            // resetting text color to default
            printf("\033[0m");
        }
        printf("\n");
    }
    free(grayscale_image);
}


int main() {

    int original_width, original_height, channels;
    uint8_t* original_image = stbi_load("/home/monika/Downloads/test_image6.jpg",
                                         &original_width, &original_height, &channels, 3);
    
    if (NULL == original_image) {
        perror("Error loading the image");
        return errno;
    }

    int adjusted_width = 140;
    int adjusted_height = 40;

    uint8_t* resized_image = malloc(adjusted_width * adjusted_height * 3);
    resize_image(original_image, original_width, original_height,
                 resized_image, adjusted_width, adjusted_height);

    int red_count = count_red_pixels(resized_image, adjusted_width, adjusted_height);
    int orange_count = count_orange_pixels(resized_image, adjusted_width, adjusted_height);

    printf("Red Pixels: %d\n", red_count);
    printf("Orange Pixels: %d\n", orange_count);

    double fire_pixel_proportion = ((double)red_count / (adjusted_width * adjusted_height)+
                                    (double)orange_count / (adjusted_width * adjusted_height));

    // a threshold for claiming fire
    double fire_threshold = 0.009;

    // compareing proportion with the threshold to detect fire
    if (fire_pixel_proportion > fire_threshold) {
        printf("Fire detected!\n");
    } else {
        printf("No fire detected.\n");
    }

    ascii_representation(resized_image, adjusted_width, adjusted_height);

    stbi_image_free(original_image);
    free(resized_image);

    return 0;
}