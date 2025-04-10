#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double pixel_sum;
    int x;
    // cicling the rows
    for (int i = 0; i < height; i++)
    {
        // cicling the coloums
        for (int j = 0; j < width; j++)
        {
            pixel_sum = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
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
    for (int i = 0; i < height; i++)
    {
        // cicling the coloums
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = image[i][j];
            image[i][j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // cicling the rows
    for (int i = 0; i < height; i++)
    {
        // cicling the coloums
        for (int j = 0; j < width; j++)
        {
            float sum_blue = 0;
            float sum_green = 0;
            float sum_red = 0;
            float number_m = 0;

            // cicling the row of the 3x3 cube
            for (int k = i - 1; k <= i + 1; k++)
            {
                // verify if k is valid
                if (k < 0 || k > height - 1)
                {
                    continue;
                }

                // cicling the coloums of the 3x3
                for (int l = j - 1; l <= j + 1; l++)
                {
                    // verify l is valid
                    if (l < 0 || l > width - 1)
                    {
                        continue;
                    }
                    // update the sum to do the average
                    sum_blue += image[k][l].rgbtBlue;
                    sum_green += image[k][l].rgbtGreen;
                    sum_red += image[k][l].rgbtRed;
                    number_m++;
                }
            }
            image[i][j].rgbtBlue = sum_blue / number_m;
            image[i][j].rgbtGreen = sum_green / number_m;
            image[i][j].rgbtRed = sum_red / number_m;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
