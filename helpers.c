#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int pixel_sum;
    // cicling the rows
    for(int i = 0; i<height; i++)
    {
        // cicling the coloums
        for(int i = 0; i<width; i++)
        {
            pixel_sum = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3 ;
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
