#include <getopt.h>
#include<math.h>
#include <stdlib.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int H = 0;

    for (int i = 0; i <= width; i++)
    {
    int average = (image[H][i].rgbtRed + image[H][i].rgbtGreen + image[H][i].rgbtBlue) /3;
    image[H][i].rgbtRed = average;
    image[H][i].rgbtGreen = average;
    image[H][i].rgbtBlue = average;

    if (i == width)
    {
        i = 0;
        H++;
        if(H == height)
        {
            return;
        }
    }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            buffer = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][width - j] = buffer;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int green;
    int blue;
    int red;

    for(int x=1; x < height - 1; x++){
        green = image[x][0].rgbtGreen + image[x-1][0].rgbtGreen + image[x+1][0].rgbtGreen;
        image[x][0].rgbtGreen = green/3;
        red = image[x][0].rgbtRed + image[x-1][0].rgbtRed + image[x+1][0].rgbtRed;
        image[x][0].rgbtRed = red/3;
        blue = image[x][0].rgbtBlue + image[x-1][0].rgbtBlue + image[x+1][0].rgbtBlue;
        image[x][0].rgbtBlue = blue/3;
        green = image[x][width-1].rgbtGreen + image[x-1][width-1].rgbtGreen + image[x+1][width-1].rgbtGreen;
        image[x][width-1].rgbtGreen = green/3;
        red = image[x][width-1].rgbtRed + image[x-1][width-1].rgbtRed + image[x+1][width-1].rgbtRed;
        image[x][width-1].rgbtRed = red/3;
        blue = image[x][width-1].rgbtBlue + image[x-1][width-1].rgbtBlue + image[x+1][width-1].rgbtBlue;
        image[x][width-1].rgbtBlue = blue/3;
    }

    for(int y=1; y < height - 1; y++){
        green = image[0][y].rgbtGreen + image[0][y-1].rgbtGreen + image[0][y+1].rgbtGreen;
        image[0][y].rgbtGreen = green/3;
        red = image[0][y].rgbtRed + image[0][y-1].rgbtRed + image[0][y+1].rgbtRed;
        image[0][y].rgbtRed = red/3;
        blue = image[0][y].rgbtBlue + image[0][y-1].rgbtBlue + image[0][y+1].rgbtBlue;
        image[0][y].rgbtBlue = blue/3;
        green = image[height-1][y].rgbtGreen + image[height-1][y-1].rgbtGreen + image[height-1][y+1].rgbtGreen;
        image[height-1][y].rgbtGreen = green/3;
        red = image[height-1][y].rgbtRed + image[height-1][y-1].rgbtRed + image[height-1][y+1].rgbtRed;
        image[height-1][y].rgbtRed = red/3;
        blue = image[height-1][y].rgbtBlue + image[height-1][y-1].rgbtBlue + image[height-1][y+1].rgbtBlue;
        image[height-1][y].rgbtBlue = blue/3;
    }

    for(int x=1; x < height - 1; x++){
        for(int y=1; y < width - 1; y++){
            green = image[x][y].rgbtGreen + image[x-1][y].rgbtGreen + image[x+1][y].rgbtGreen + image[x][y-1].rgbtGreen + image[x][y+1].rgbtGreen;
            image[x][y].rgbtGreen = green/5;
            red = image[x][y].rgbtRed + image[x-1][y].rgbtRed + image[x+1][y].rgbtRed + image[x][y-1].rgbtRed + image[x][y+1].rgbtRed;
            image[x][y].rgbtRed = red/5;
            blue = image[x][y].rgbtBlue + image[x-1][y].rgbtBlue + image[x+1][y].rgbtBlue + image[x][y-1].rgbtBlue + image[x][y+1].rgbtBlue;
            image[x][y].rgbtBlue = blue/5;
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*image_edge)[width] = calloc(height, width * sizeof(RGBTRIPLE));
        int gx[3][3];
        int gy[3][3];

    gx[0][0] = -1;
    gx[0][1] = 0;
    gx[0][2] = 1;

    gx[1][0] = -2;
    gx[1][1] = 0;
    gx[1][2] = 2;

    gx[2][0] = -1;
    gx[2][1] = 0;
    gx[2][2] = 1;


    gy[0][0] = -1;
    gy[0][1] = -2;
    gy[0][2] = -1;

    gy[1][0] = 0;
    gy[1][1] = 0;
    gy[1][2] = 0;

    gy[2][0] = 1;
    gy[2][1] = 2;
    gy[2][2] = 1;

    int gxValBlue;
    int gyValBlue;

    int gxValGreen;
    int gyValGreen;

    int gxValRed;
    int gyValRed;

    int squaredBlue;
    int squaredGreen;
    int squaredRed;





       for (int lin = 0; lin < height; ++lin)
    {

      for (int col = 0; col < width; ++col)
      {



        if (lin !=0 && lin != height && col != 0 && col != width)// all the neighboring pixels
        {




          gxValBlue = (image[lin-1][col-1].rgbtBlue * gx[0][0] + image[lin-1][col].rgbtBlue * gx[0][1] + image[lin-1][col+1].rgbtBlue * gx[0][2] + image[lin][col-1].rgbtBlue * gx[1][0] + image[lin][col].rgbtBlue * gx[1][1] + image[lin][col+1].rgbtBlue * gx[1][2] + image[lin-1][col-1].rgbtBlue * gx[2][0] + image[lin+1][col].rgbtBlue * gx[2][1] + image[lin+1][col+1].rgbtBlue * gx[2][2]);
          gyValBlue = (image[lin-1][col-1].rgbtBlue * gy[0][0] + image[lin-1][col].rgbtBlue * gy[0][1] + image[lin-1][col+1].rgbtBlue * gy[0][2] + image[lin][col-1].rgbtBlue * gy[1][0] + image[lin][col].rgbtBlue * gy[1][1] + image[lin][col+1].rgbtBlue * gy[1][2] + image[lin-1][col-1].rgbtBlue * gy[2][0] + image[lin+1][col].rgbtBlue * gy[2][1] + image[lin+1][col+1].rgbtBlue * gy[2][2]);

          squaredBlue = (int)sqrt(gxValBlue*gxValBlue + gyValBlue*gyValBlue);

          gxValGreen = (image[lin-1][col-1].rgbtGreen * gx[0][0] + image[lin-1][col].rgbtGreen * gx[0][1] + image[lin-1][col+1].rgbtGreen * gx[0][2] + image[lin][col-1].rgbtGreen * gx[1][0] + image[lin][col].rgbtGreen * gx[1][1] + image[lin][col+1].rgbtGreen * gx[1][2] + image[lin-1][col-1].rgbtGreen * gx[2][0] + image[lin+1][col].rgbtGreen * gx[2][1] + image[lin+1][col+1].rgbtGreen * gx[2][2]);
          gyValGreen = (image[lin-1][col-1].rgbtGreen * gy[0][0] + image[lin-1][col].rgbtGreen * gy[0][1] + image[lin-1][col+1].rgbtGreen * gy[0][2] + image[lin][col-1].rgbtGreen * gy[1][0] + image[lin][col].rgbtGreen * gy[1][1] + image[lin][col+1].rgbtGreen * gy[1][2] + image[lin-1][col-1].rgbtGreen * gy[2][0] + image[lin+1][col].rgbtGreen * gy[2][1] + image[lin+1][col+1].rgbtGreen * gy[2][2]);

          squaredGreen = (int)sqrt(gxValGreen*gxValGreen + gyValGreen*gyValGreen);

          gxValRed = (image[lin-1][col-1].rgbtRed * gx[0][0] + image[lin-1][col].rgbtRed * gx[0][1] + image[lin-1][col+1].rgbtRed * gx[0][2] + image[lin][col-1].rgbtRed * gx[1][0] + image[lin][col].rgbtRed * gx[1][1] + image[lin][col+1].rgbtRed * gx[1][2] + image[lin-1][col-1].rgbtRed * gx[2][0] + image[lin+1][col].rgbtRed * gx[2][1] + image[lin+1][col+1].rgbtRed * gx[2][2]);
          gyValRed = (image[lin-1][col-1].rgbtRed * gy[0][0] + image[lin-1][col].rgbtRed * gy[0][1] + image[lin-1][col+1].rgbtRed * gy[0][2] + image[lin][col-1].rgbtRed * gy[1][0] + image[lin][col].rgbtRed * gy[1][1] + image[lin][col+1].rgbtRed * gy[1][2] + image[lin-1][col-1].rgbtRed * gy[2][0] + image[lin+1][col].rgbtRed * gy[2][1] + image[lin+1][col+1].rgbtRed * gy[2][2]);

          squaredRed = (int)sqrt(gxValRed*gxValRed + gyValRed*gyValRed);



          if (squaredBlue > 255)
          {
            image_edge[lin][col].rgbtBlue = 255;
          }
          else
          {
            image_edge[lin][col].rgbtBlue = squaredBlue;
          }



          if (squaredGreen > 255)
          {
           image_edge[lin][col].rgbtGreen = 255;
          }
          else
          {
            image_edge[lin][col].rgbtGreen = squaredGreen;
          }


          if (squaredRed > 255)
          {
            image_edge[lin][col].rgbtRed = 255;
          }
          else
          {
            image_edge[lin][col].rgbtRed = squaredRed;
          }
        }

          else
          { // bottom
          image_edge[lin][col].rgbtBlue = 0;
          image_edge[lin][col].rgbtGreen = 0;
          image_edge[lin][col].rgbtRed = 0;
          }
      }
    }


    int H = 0;
    for (int i = 0; i <= width; i++)
    {
    image[H][i].rgbtBlue = image_edge[H][i].rgbtBlue;
    image[H][i].rgbtGreen = image_edge[H][i].rgbtGreen;
    image[H][i].rgbtRed = image_edge[H][i].rgbtRed;

    if (i == width)
    {
        i = 0;
        H++;
        if(H == height)
        {
            free(image_edge);
            return;
        }
    }
    }
    free(image_edge);
    return;
}
