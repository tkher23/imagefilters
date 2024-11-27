#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
        {
            float red_float = image[h][w].rgbtRed;
            float green_float = image[h][w].rgbtGreen;
            float blue_float = image[h][w].rgbtBlue;

            avg = round((red_float + green_float + blue_float) / 3);
            image[h][w].rgbtRed = avg;
            image[h][w].rgbtGreen = avg;
            image[h][w].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    int swapped_number;
    int swapped_red = 0;
    int swapped_green = 0;
    int swapped_blue = 0;
    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width / 2; w++)
        {
             // swapped_number = (width) - w;
            RGBTRIPLE image_new = image[h][w];
            image[h][w] = image[h][width - (w + 1)];
            image[h][width - (w + 1)] = image_new;

         //   image_new[h][swapped_number].rgbtRed = image[h][w].rgbtRed;
          //  image_new[h][swapped_number].rgbtGreen = image[h][w].rgbtGreen;
          //  image_new[h][swapped_number].rgbtBlue = image[h][w].rgbtBlue;

         //   swapped_red = image[h][w].rgbtRed;
       //     swapped_blue = image[h][w].rgbtBlue;
        //    swapped_green = image[h][w].rgbtGreen;

         //   image[h][w].rgbtRed = image[h][swapped_number].rgbtRed;
         //   image[h][w].rgbtGreen = image[h][swapped_number].rgbtGreen;
         //   image[h][w].rgbtBlue = image[h][swapped_number].rgbtBlue;

         //   image[h][swapped_number].rgbtRed = swapped_red;
         //   image[h][swapped_number].rgbtGreen = swapped_green;
          //  image[h][swapped_number].rgbtBlue = swapped_blue;
        }
    }

    return;
}

// Blur image

void blur(int height, int width, RGBTRIPLE image[height][width])
{
RGBTRIPLE image_new[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            float total_pixels = 0.00;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = h + x;
                    int currentY = w + y;

                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        continue;
                    }
                    totalRed += image[currentX][currentY].rgbtRed;
                    totalGreen += image[currentX][currentY].rgbtGreen;
                    totalBlue += image[currentX][currentY].rgbtBlue;

                    total_pixels++;
                }

            }

            image_new[h][w].rgbtRed = round(totalRed / total_pixels);
            image_new[h][w].rgbtGreen = round(totalGreen / total_pixels);
            image_new[h][w]. rgbtBlue = round(totalBlue / total_pixels);
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = image_new[h][w];
        }
    }

    /*
    typedef struct
{
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
} __attribute__((__packed__))
image_new;

RGBTRIPLE(*image_new)[width] = malloc(height, width * sizeof(RGBTRIPLE));

for (int h = 0; h < height - 1; h++)
{
    for (int w = 0; w < width - 1; w++)
    {
        if (h == 0)
        {
            if (w == 0)
            {
                image_new[h][w].rgbtBlue = (image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w + 1].rgbtBlue) / 4;
                image_new[h][w].rgbtRed = (image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w + 1].rgbtRed) / 4;
                image_new[h][w].rgbtGreen = (image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen) / 4;
            }
            else
            {
                image_new[h][w].rgbtBlue =  (image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w - 1].rgbtBlue + image[h + 1][w + 1].rgbtBlue) / 6;
                image_new[h][w].rgbtRed =  (image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w - 1].rgbtRed + image[h + 1][w + 1].rgbtRed) / 6;
                image_new[h][w].rgbtGreen =  (image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w - 1].rgbtGreen + image[h + 1][w + 1].rgbtGreen) / 6;
            }
        }
        else if (w == 0)
        {
            if (h == height - 2)
            {
                image_new[h][w].rgbtBlue =  (image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h - 1][w].rgbtBlue + image[h - 1][w + 1].rgbtBlue) / 4;
                image_new[h][w].rgbtRed =  (image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h - 1][w].rgbtRed + image[h - 1][w + 1].rgbtRed) / 4;
                image_new[h][w].rgbtGreen =  (image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen) / 4;
            }
            else
            {
                image_new[h][w].rgbtBlue = (image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w + 1].rgbtBlue + image[h - 1][w].rgbtBlue + image[h - 1][w + 1].rgbtBlue) / 6;
                image_new[h][w].rgbtRed = (image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w + 1].rgbtRed + image[h - 1][w].rgbtRed + image[h - 1][w + 1].rgbtRed) / 6;
                image_new[h][w].rgbtGreen = (image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen + image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen) / 6;
            }
        }
        else
        {
            image_new[h][w].rgbtBlue =  (image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w - 1].rgbtBlue + image[h + 1][w + 1].rgbtBlue) / 9;
            image_new[h][w].rgbtRed =  (image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w - 1].rgbtRed + image[h + 1][w + 1].rgbtRed) / 9;
            image_new[h][w].rgbtGreen =  (image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w - 1].rgbtGreen + image[h + 1][w + 1].rgbtGreen) / 9;
        }
    }
}


    for (int h = 0; h < height - 1; h++)
    {
        for (int w = 0; w < width - 1; w++)
        {
            while (fread(&image[h][w], sizeof(int), 1, input))
            {
                image[h][w] = (image[h - 1][w] + image[h - 1][w + 1] + image[h - 1][w - 1] + image[h][w - 1] + image[h][w] + image[h][w + 1] + image[h + 1][w] + image[h + 1][w - 1] + image[h + 1][w + 1]) / 9;
                fwrite(&image[h][w], sizeof(int), 1, output);
            }
        }
    }
    */
    return;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE image_new[height][width];
    int h;
    int w;

    int image_gx_Red = 0;
    int image_gx_Green = 0;
    int image_gx_Blue = 0;
    int image_gy_Red = 0;
    int image_gy_Green = 0;
    int image_gy_Blue = 0;

  //  int gx_multiplier = 1;
  //  int gy_multiplier = 1;

    int gx_total_red = 0;
    int gx_total_green = 0;
    int gx_total_blue = 0;

    int gy_total_red = 0;
    int gy_total_green = 0;
    int gy_total_blue = 0;

    int gx_multipliers[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_multipliers[3][3] =  {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (h = 0; h < height; h++)
    {
        for (w = 0; w < width; w++)
        {
            gx_total_red = 0;
            gx_total_green = 0;
            gx_total_blue = 0;
            gy_total_red = 0;
            gy_total_green = 0;
            gy_total_blue = 0;
            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    if (h - 1 + y < 0 || h - 1 + y > height - 1)
                    {
                        continue;
                    }

                    if (w - 1 + x < 0 || w - 1 + x > width - 1)
                    {
                        continue;
                    }
                    else
                    {
                        gx_total_red = gx_total_red + (image[h - 1 + y][w - 1 + x].rgbtRed * gx_multipliers[y][x]);
                        gx_total_green = gx_total_green + (image[h - 1 + y][w - 1 + x].rgbtGreen * gx_multipliers[y][x]);
                        gx_total_blue = gx_total_blue + (image[h - 1 + y][w - 1 + x].rgbtBlue * gx_multipliers[y][x]);

                        gy_total_red = gy_total_red + (image[h - 1 + y][w - 1 + x].rgbtRed * gy_multipliers[y][x]);
                        gy_total_green = gy_total_green + (image[h - 1 + y][w - 1 + x].rgbtGreen * gy_multipliers[y][x]);
                        gy_total_blue = gy_total_blue + (image[h - 1 + y][w - 1 + x].rgbtBlue * gy_multipliers[y][x]);
                    }
                }
            }

            image_new[h][w].rgbtRed = round(sqrt((gx_total_red * gx_total_red) + (gy_total_red * gy_total_red)));
            if (image_new[h][w].rgbtRed > 255)
            {
                image_new[h][w].rgbtRed = 255;
            }
            image_new[h][w].rgbtGreen = round(sqrt((gx_total_green * gx_total_green) + (gy_total_green * gy_total_green)));
            if (image_new[h][w].rgbtGreen > 255)
            {
                image_new[h][w].rgbtGreen = 255;
            }
            image_new[h][w].rgbtBlue = round(sqrt((gx_total_blue * gx_total_blue) + (gy_total_blue * gy_total_blue)));
            if (image_new[h][w].rgbtBlue > 255)
            {
                image_new[h][w].rgbtBlue = 255;
            }
        }

    }

        for (h = 0; h < height; h++)
    {
        for (w = 0; w < width; w++)
        {
            image[h][w] = image_new[h][w];
        }
    }

    return;
}
/*REAL void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE(*image_new)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    int h;
    int w;
    int red_value;
    int blue_value;
    int green_value;

    int image_gx_Red = 0;
    int image_gx_Green = 0;
    int image_gx_Blue = 0;
    int image_gy_Red = 0;
    int image_gy_Green = 0;
    int image_gy_Blue = 0;

  //  int gx_multiplier = 1;
  //  int gy_multiplier = 1;

    int gx_total_red = 0;
    int gx_total_green = 0;
    int gx_total_blue = 0;

    int gy_total_red = 0;
    int gy_total_green = 0;
    int gy_total_blue = 0;

    int gx_multipliers[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_multipliers[3][3] =  {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (h = 0; h < height; h++)
    {
        for (w = 0; w < width; w++)
        {
            gx_total_red = 0;
            gx_total_green = 0;
            gx_total_blue = 0;
            gy_total_red = 0;
            gy_total_green = 0;
            gy_total_blue = 0;
            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    if (h + y < 0 || h + y > height - 1)
                    {
                        continue;
                    }

                    if (w + x < 0 || w + x > width - 1)
                    {
                        continue;
                    }


                    gx_total_red += (image[h + y][w + x].rgbtRed * gx_multipliers[y + 1][x + 1]);
                    gx_total_green += (image[h + y][w + x].rgbtGreen * gx_multipliers[y + 1][x + 1]);
                    gx_total_blue += (image[h + y][w + x].rgbtBlue * gx_multipliers[y + 1][x + 1]);

                    gy_total_red += (image[h + y][w + x].rgbtRed * gy_multipliers[y + 1][x + 1]);
                    gy_total_green += (image[h + y][w + x].rgbtGreen * gy_multipliers[y + 1][x + 1]);
                    gy_total_blue += (image[h + y][w + x].rgbtBlue * gy_multipliers[y + 1][x + 1]);
                }
            }

                red_value = round(sqrt((gx_total_red * gx_total_red) + (gy_total_red * gy_total_red)));
                if (red_value > 255)
                {
                    image_new[h][w].rgbtRed = 255;
                }
                image_new[h][w].rgbtRed = red_value;

                green_value = round(sqrt((gx_total_green * gx_total_green) + (gy_total_green * gy_total_green)));
                if (green_value > 255)
                {
                    image_new[h][w].rgbtGreen = 255;
                }
                image_new[h][w].rgbtGreen = green_value;

                blue_value = round(sqrt((gx_total_blue * gx_total_blue) + (gy_total_blue * gy_total_blue)));
                if (blue_value > 255)
                {
                    image_new[h][w].rgbtBlue = 255;
                }
                image_new[h][w].rgbtBlue = blue_value;

            }
        }


    for (h = 0; h < height; h++)
    {
        for (w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = image_new[h][w].rgbtRed;
            image[h][w].rgbtGreen = image_new[h][w].rgbtGreen;
            image[h][w].rgbtBlue = image_new[h][w].rgbtBlue;
        }
    }

    return;

}
*/

/*void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE image_new[height][width];
    int h;
    int w;

    int image_gx_Red = 0;
    int image_gx_Green = 0;
    int image_gx_Blue = 0;
    int image_gy_Red = 0;
    int image_gy_Green = 0;
    int image_gy_Blue = 0;

    int gx_multiplier = 1;
    int gy_multiplier = 1;

    int gx_total_red = 0;
    int gx_total_green = 0;
    int gx_total_blue = 0;

    int gy_total_red = 0;
    int gy_total_green = 0;
    int gy_total_blue = 0;

    int gx_multipliers[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_multipliers[3][3] =  {{-1, 2, -1}, {0, 0, 0}, {1, 2, 1}};

    printf("height: %i, width: %i\n", height, width);
    for (h = 0; h < height; h++)
    {
        for (w = 0; w < width; w++)
        {
            gx_total_red = 0;
            gx_total_green = 0;
            gx_total_blue = 0;
            gy_total_red = 0;
            gy_total_green = 0;
            gy_total_blue = 0;


            // Compute gx_total_red
            if(h-1 >= 0 && w-1 >= 0)
            {
                gx_total_red += image[h-1][w-1].rgbtRed * gx_multipliers[0][0];
                gx_total_green += image[h-1][w-1].rgbtGreen * gx_multipliers[0][0];
                gx_total_blue += image[h-1][w-1].rgbtBlue * gx_multipliers[0][0];
            }


            if(h-1 >= 0)
            {
                gx_total_red += image[h-1][w].rgbtRed   * gx_multipliers[0][1];
                gx_total_green += image[h-1][w].rgbtGreen   * gx_multipliers[0][1];
                gx_total_blue += image[h-1][w].rgbtBlue   * gx_multipliers[0][1];
            }



            if(h-1 >= 0 && w+1 < width)
            {
                gx_total_red += image[h-1][w+1].rgbtRed * gx_multipliers[0][2];
                gx_total_green += image[h-1][w+1].rgbtGreen * gx_multipliers[0][2];
                gx_total_blue += image[h-1][w+1].rgbtBlue * gx_multipliers[0][2];

            }



            if(w-1 >= 0)
            {
                    gx_total_red += image[h][w-1].rgbtRed * gx_multipliers[1][0];
                    gx_total_red += image[h][w].rgbtRed   * gx_multipliers[1][1];
                    gx_total_green += image[h][w-1].rgbtGreen * gx_multipliers[1][0];
                    gx_total_green += image[h][w].rgbtGreen   * gx_multipliers[1][1];
                    gx_total_blue += image[h][w-1].rgbtBlue * gx_multipliers[1][0];
                    gx_total_blue += image[h][w].rgbtBlue   * gx_multipliers[1][1];
            }



            if(w+1 < width)
            {
                    gx_total_red += image[h][w+1].rgbtRed * gx_multipliers[1][2];
                    gx_total_green += image[h][w+1].rgbtGreen * gx_multipliers[1][2];
                    gx_total_blue += image[h][w+1].rgbtBlue * gx_multipliers[1][2];

            }

            if(h+1 < height && w-1 >= 0)
            {
                        gx_total_red += image[h+1][w-1].rgbtRed * gx_multipliers[2][0];
                        gx_total_green += image[h+1][w-1].rgbtGreen * gx_multipliers[2][0];
                        gx_total_blue += image[h+1][w-1].rgbtBlue * gx_multipliers[2][0];

            }
            if(h+1 < height)
            {
                        gx_total_red += image[h+1][w].rgbtRed   * gx_multipliers[2][1];
                        gx_total_green += image[h+1][w].rgbtGreen   * gx_multipliers[2][1];
                        gx_total_blue += image[h+1][w].rgbtBlue   * gx_multipliers[2][1];

            }
            if(h+1 < height && w+1 < width)
            {
                        gx_total_red += image[h+1][w+1].rgbtRed * gx_multipliers[2][2];
                        gx_total_green += image[h+1][w+1].rgbtGreen * gx_multipliers[2][2];
                        gx_total_blue += image[h+1][w+1].rgbtBlue * gx_multipliers[2][2];

            }

            // Compute gy_total_red
            if(h-1 >= 0 && w-1 >= 0)
            {
                gy_total_red += image[h-1][w-1].rgbtRed * gy_multipliers[0][0];
                gy_total_green += image[h-1][w-1].rgbtGreen * gy_multipliers[0][0];
                gy_total_blue += image[h-1][w-1].rgbtBlue * gy_multipliers[0][0];

            }

            if(h-1 >= 0)
            {
                gy_total_red += image[h-1][w].rgbtRed   * gy_multipliers[0][1];
                gy_total_green += image[h-1][w].rgbtGreen   * gy_multipliers[0][1];
                gy_total_blue += image[h-1][w].rgbtBlue   * gy_multipliers[0][1];

            }


            if(h-1 >= 0 && w+1 < width)
            {
                gy_total_red += image[h-1][w+1].rgbtRed * gy_multipliers[0][2];
                gy_total_green += image[h-1][w+1].rgbtGreen * gy_multipliers[0][2];
                gy_total_blue += image[h-1][w+1].rgbtBlue * gy_multipliers[0][2];

            }


            if(w-1 >= 0)
            {
                    gy_total_red += image[h][w-1].rgbtRed * gy_multipliers[1][0];
                    gy_total_red += image[h][w].rgbtRed   * gy_multipliers[1][1];
                    gy_total_green += image[h][w-1].rgbtGreen * gy_multipliers[1][0];
                    gy_total_green += image[h][w].rgbtGreen   * gy_multipliers[1][1];
                    gy_total_blue += image[h][w-1].rgbtBlue * gy_multipliers[1][0];
                    gy_total_blue += image[h][w].rgbtBlue   * gy_multipliers[1][1];

            }


            if(w+1 < width)
            {
                    gy_total_red += image[h][w+1].rgbtRed * gy_multipliers[1][2];
                    gy_total_green += image[h][w+1].rgbtGreen * gy_multipliers[1][2];
                    gy_total_blue += image[h][w+1].rgbtBlue * gy_multipliers[1][2];

            }

            if(h+1 < height && w-1 >= 0)
            {
                        gy_total_red += image[h+1][w-1].rgbtRed * gy_multipliers[2][0];
                        gy_total_green += image[h+1][w-1].rgbtGreen * gy_multipliers[2][0];
                        gy_total_blue += image[h+1][w-1].rgbtBlue * gy_multipliers[2][0];

            }

            if(h+1 < height)
            {
                        gy_total_red += image[h+1][w].rgbtRed   * gy_multipliers[2][1];
                        gy_total_green += image[h+1][w].rgbtGreen   * gy_multipliers[2][1];
                        gy_total_blue += image[h+1][w].rgbtBlue   * gy_multipliers[2][1];
            }

            if(h+1 < height && w+1 < width)
            {
                        gy_total_red += image[h+1][w+1].rgbtRed * gy_multipliers[2][2];
                        gy_total_green += image[h+1][w+1].rgbtGreen * gy_multipliers[2][2];
                        gy_total_blue += image[h+1][w+1].rgbtBlue * gy_multipliers[2][2];
            }

            image_new[h][w].rgbtRed = sqrt((gx_total_red * gx_total_red) + (gy_total_red * gy_total_red));
            if (image_new[h][w].rgbtRed > 255)
                image_new[h][w].rgbtRed = 255;

            image_new[h][w].rgbtGreen = sqrt((gx_total_green * gx_total_green) + (gy_total_green * gy_total_green));
            if (image_new[h][w].rgbtGreen > 255)
                image_new[h][w].rgbtGreen = 255;

            image_new[h][w].rgbtBlue = sqrt((gx_total_blue * gx_total_blue) + (gy_total_blue * gy_total_blue));
            if (image_new[h][w].rgbtBlue > 255)
                image_new[h][w].rgbtBlue = 255;

        }
    }

    for (h = 0; h < height; h++)
    {
        for (w = 0; w < width; w++)
        {
            image[h][w] = image_new[h][w];
        }
    }

    return;
}
///////////////////////
gx_total_red =
                image[h-1][w-1].rgbtRed * gx_multipliers[0][0] +
                image[h-1][w].rgbtRed   * gx_multipliers[0][1] +
                image[h-1][w+1].rgbtRed * gx_multipliers[0][2] +
                    image[h][w-1].rgbtRed * gx_multipliers[1][0] +
                    image[h][w].rgbtRed   * gx_multipliers[1][1] +
                    image[h][w+1].rgbtRed * gx_multipliers[1][2] +
                        image[h+1][w-1].rgbtRed * gx_multipliers[2][0] +
                        image[h+1][w].rgbtRed   * gx_multipliers[2][1] +
                        image[h+1][w+1].rgbtRed * gx_multipliers[2][2];

            gx_total_green =
                image[h-1][w-1].rgbtGreen * gx_multipliers[0][0] +
                image[h-1][w].rgbtGreen   * gx_multipliers[0][1] +
                image[h-1][w+1].rgbtGreen * gx_multipliers[0][2] +
                    image[h][w-1].rgbtGreen * gx_multipliers[1][0] +
                    image[h][w].rgbtGreen   * gx_multipliers[1][1] +
                    image[h][w+1].rgbtGreen * gx_multipliers[1][2] +
                        image[h+1][w-1].rgbtGreen * gx_multipliers[2][0] +
                        image[h+1][w].rgbtGreen   * gx_multipliers[2][1] +
                        image[h+1][w+1].rgbtGreen * gx_multipliers[2][2];

            gx_total_blue =
                image[h-1][w-1].rgbtBlue * gx_multipliers[0][0] +
                image[h-1][w].rgbtBlue   * gx_multipliers[0][1] +
                image[h-1][w+1].rgbtBlue * gx_multipliers[0][2] +
                    image[h][w-1].rgbtBlue * gx_multipliers[1][0] +
                    image[h][w].rgbtBlue   * gx_multipliers[1][1] +
                    image[h][w+1].rgbtBlue * gx_multipliers[1][2] +
                        image[h+1][w-1].rgbtBlue * gx_multipliers[2][0] +
                        image[h+1][w].rgbtBlue   * gx_multipliers[2][1] +
                        image[h+1][w+1].rgbtBlue * gx_multipliers[2][2];

            gy_total_red =
                image[h-1][w-1].rgbtRed * gy_multipliers[0][0] +
                image[h-1][w].rgbtRed   * gy_multipliers[0][1] +
                image[h-1][w+1].rgbtRed * gy_multipliers[0][2] +
                    image[h][w-1].rgbtRed * gy_multipliers[1][0] +
                    image[h][w].rgbtRed   * gy_multipliers[1][1] +
                    image[h][w+1].rgbtRed * gy_multipliers[1][2] +
                        image[h+1][w-1].rgbtRed * gy_multipliers[2][0] +
                        image[h+1][w].rgbtRed   * gy_multipliers[2][1] +
                        image[h+1][w+1].rgbtRed * gy_multipliers[2][2];

            gy_total_green =
                image[h-1][w-1].rgbtGreen * gy_multipliers[0][0] +
                image[h-1][w].rgbtGreen   * gy_multipliers[0][1] +
                image[h-1][w+1].rgbtGreen * gy_multipliers[0][2] +
                    image[h][w-1].rgbtGreen * gy_multipliers[1][0] +
                    image[h][w].rgbtGreen   * gy_multipliers[1][1] +
                    image[h][w+1].rgbtGreen * gy_multipliers[1][2] +
                        image[h+1][w-1].rgbtGreen * gy_multipliers[2][0] +
                        image[h+1][w].rgbtGreen   * gy_multipliers[2][1] +
                        image[h+1][w+1].rgbtGreen * gy_multipliers[2][2];

            gy_total_blue =
                image[h-1][w-1].rgbtBlue * gy_multipliers[0][0] +
                image[h-1][w].rgbtBlue   * gy_multipliers[0][1] +
                image[h-1][w+1].rgbtBlue * gy_multipliers[0][2] +
                    image[h][w-1].rgbtBlue * gy_multipliers[1][0] +
                    image[h][w].rgbtBlue   * gy_multipliers[1][1] +
                    image[h][w+1].rgbtBlue * gy_multipliers[1][2] +
                        image[h+1][w-1].rgbtBlue * gy_multipliers[2][0] +
                        image[h+1][w].rgbtBlue   * gy_multipliers[2][1] +
                        image[h+1][w+1].rgbtBlue * gy_multipliers[2][2];


            image_new[h][w].rgbtRed = sqrt((gx_total_red * gx_total_red) + (gy_total_red * gy_total_red));
            if (image_new[h][w].rgbtRed > 255)
                image_new[h][w].rgbtRed = 255;

            image_new[h][w].rgbtGreen = sqrt((gx_total_green * gx_total_green) + (gy_total_green * gy_total_green));
            if (image_new[h][w].rgbtGreen > 255)
                image_new[h][w].rgbtGreen = 255;

            image_new[h][w].rgbtBlue = sqrt((gx_total_blue * gx_total_blue) + (gy_total_blue * gy_total_blue));
            if (image_new[h][w].rgbtBlue > 255)
                image_new[h][w].rgbtBlue = 255;



/////////////////

            for (int y = -1; y < 2; y++)
            {

                for (int x = -1; x < 2; x++)
                {
                    int width_adjusted = w + x;
                    int height_adjusted = h + y;

                    if (width_adjusted < 0 || height_adjusted < 0 || h + x > width || w + y > height)
                    {
                        printf("1.. Continuing for adjusted width %i and height %i \n", width_adjusted, height_adjusted);
                        continue;
                    }

                    image_gx_Red = x * gx_multiplier * image[width_adjusted][height_adjusted].rgbtRed;
                    image_gx_Green = x * gx_multiplier * image[width_adjusted][height_adjusted].rgbtGreen;
                    image_gx_Blue = x * gx_multiplier * image[width_adjusted][height_adjusted].rgbtBlue;

                    gx_total_red = gx_total_red + image_gx_Red;
                    gx_total_green = gx_total_green + image_gx_Green;
                    gx_total_blue = gx_total_blue + image_gx_Blue;

                }
                if (y == -1)
                {
                    gx_multiplier = 2;
                }
                if (y == 0)
                {
                    gx_multiplier = 1;
                }

            }

            for (int x = -1; x < 2; x++)
            {

                for (int y = -1; y < 2; y++)
                {
                    int width_adjusted = w + x;
                    int height_adjusted = h + y;

                    if (width_adjusted < 0 || height_adjusted < 0 || h + x > width || w + y > height)
                    {
                      //  printf("2.. Continuing for adjusted width %i and height %i \n", width_adjusted, height_adjusted);
                        continue;
                    }

                    image_gy_Red = y * gy_multiplier * image[width_adjusted][height_adjusted].rgbtRed;
                    image_gy_Green = y * gy_multiplier * image[width_adjusted][height_adjusted].rgbtGreen;
                    image_gy_Blue = y * gy_multiplier * image[width_adjusted][height_adjusted].rgbtBlue;

                    gy_total_red = gy_total_red + image_gy_Red;
                    gy_total_green = gy_total_green + image_gy_Green;
                    gy_total_blue = gy_total_blue + image_gy_Blue;

                    if (y == -1)
                    {
                        gy_multiplier = 2;
                    }
                    if (y == 0)
                    {
                        gy_multiplier = 1;
                    }
                }
            }

            image_new[h][w].rgbtRed = sqrt((gx_total_red * gx_total_red) + (gy_total_red * gy_total_red));
            if (image_new[h][w].rgbtRed > 255)
            {
                image_new[h][w].rgbtRed = 255;
            }
            if (image_new[h][w].rgbtRed < 0)
            {
                image_new[h][w].rgbtRed = 0;
            }
            image_new[h][w].rgbtGreen = sqrt((gx_total_green * gx_total_green) + (gy_total_green * gy_total_green));
            if (image_new[h][w].rgbtGreen > 255)
            {
                image_new[h][w].rgbtGreen = 255;
            }
            if (image_new[h][w].rgbtGreen < 0)
            {
                image_new[h][w].rgbtGreen = 0;
            }
            image_new[h][w].rgbtBlue = sqrt((gx_total_blue * gx_total_blue) + (gy_total_blue * gy_total_blue));
            if (image_new[h][w].rgbtBlue > 255)
            {
                image_new[h][w].rgbtBlue = 255;
            }
            if (image_new[h][w].rgbtBlue < 0)
            {
                image_new[h][w].rgbtBlue = 0;
            }

        }
    }
    printf("h: %i, w: %i\n", h, w);

    for (h = 0; h < height; h++)
    {
        for (w = 0; w < width; w++)
        {
            image[h][w] = image_new[h][w];
        }
    }
    printf("FINAL h: %i, w: %i\n", h, w);

    return;
*/


// Detect edges
