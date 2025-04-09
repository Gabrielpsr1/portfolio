#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double pixel_sum;
    // cicling the rows
    for(int i = 0; i<height; i++)
    {
        // cicling the coloums
        for(int j = 0; j<width; j++)
        {
            pixel_sum = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3 ;
            pixel_sum = round(pixel_sum);
            image[i][j].rgbtBlue = pixel_sum;
            image[i][j].rgbtGreen = pixel_sum;
            image[i][j].rgbtRed = pixel_sum;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    // cicling the rows
    for(int i = 0; i<height; i++)
    {
        // cicling the coloums
        for(int j = 0; j<width; j++)
        {
            temp = image[i][width - 1 - i];
            image[i][width - 1 - i] = image[i][j];
            image[i][j] = temp;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
