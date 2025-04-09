#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double pixel_sum;
    int x;
    // cicling the rows
    for(int i = 0; i<height; i++)
    {
        // cicling the coloums
        for(int j = 0; j<width; j++)
        {
            pixel_sum = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0 ;
            x = round(pixel_sum);
            image[i][j].rgbtBlue = x;
            image[i][j].rgbtGreen = x;
            image[i][j].rgbtRed = x;
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
        for(int j = 0; j<width/2 ; j++)
        {
            temp = image[i][width - (j+1)];
            image[i][width - (j+1)] = image[i][j];
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
