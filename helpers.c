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
    RGBTRIPLE temp[height][width];
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
            temp[i][j].rgbtBlue = (int) round(sum_blue / number_m);
            temp[i][j].rgbtGreen = (int) round(sum_green / number_m);
            temp[i][j].rgbtRed = (int) round(sum_red / number_m);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // declare the temp
    RGBTRIPLE temp[height][width];
    // cicling rows
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // restart the sum every element
            float blue1 = 0, green1 = 0, red1 = 0;
            float blue2 = 0, green2 = 0, red2 = 0;
            // do the gx first
            // do the 3x3 matriz surrounding the pixel
            for (int k = i - 1; k <= i + 1; k++)
            {
                if (k < 0 || k > height - 1)
                {
                    continue;
                }
                int x;
                // cicle the coloums of the 3x3: Gx
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (l < 0 || l > width - 1)
                    {
                        continue;
                    }

                    blue1 += image[k][l].rgbtBlue * Gx[(k - i) + 1][(l - j) + 1];
                    green1 += image[k][l].rgbtGreen * Gx[(k - i) + 1][(l - j) + 1];
                    red1 += image[k][l].rgbtRed * Gx[(k - i) + 1][(l - j) + 1];
                }
            }

            // do the gy
            // do the 3x3 matriz surrounding the pixel
            for (int k = i - 1; k <= i + 1; k++)
            {
                if (k < 0 || k > height - 1)
                {
                    continue;
                }
                int y;

                // cicle the coloums of the 3x3: Gx
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (l < 0 || l > width - 1)
                    {
                        continue;
                    }

                    blue2 += image[k][l].rgbtBlue * Gy[(k - i) + 1][(l - j) + 1];
                    green2 += image[k][l].rgbtGreen * Gy[(k - i) + 1][(l - j) + 1];
                    red2 += image[k][l].rgbtRed * Gy[(k - i) + 1][(l - j) + 1];
                }
            }
            //red
            temp[i][j].rgbtBlue = (int) round(sqrt((blue1 * blue1) + (blue2 * blue2)));
            if (temp[i][j].rgbtBlue > 255)
            {
                temp[i][j].rgbtBlue = 255;
            }
            // Green
            temp[i][j].rgbtGreen = (int) round(sqrt((green1 * green1) + (green2 * green2)));
            if (temp[i][j].rgbtGreen > 255)
            {
                temp[i][j].rgbtGreen = 255;
            }

            // Red
            temp[i][j].rgbtRed = (int) round(sqrt((red1 * red1) + (red2 * red2)));
            if (temp[i][j].rgbtRed > 255)
            {
                temp[i][j].rgbtRed = 255;
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
