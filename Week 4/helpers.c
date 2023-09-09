#include "helpers.h"
#include <stdio.h>
#include "stdio.h"
#include <math.h>
#include "math.h"

void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
}

int average(int input, int divided_by);
int rgbvalue(RGBTRIPLE rgbt, int color);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Take average first
            float float_average = (double)(image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3;
            float_average = (round(float_average));
            int average = float_average;
            //Replace value with average
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //a pixel in index x is moved to (width - x)
    //e.g. a pixel in index 0 is moved to 10
    //e.g. a pixel in index 3 is moved to 7

    if (width == 2)
    {
        for (int row = 0; row < height; row++)
        {
            swap(&image[row][0], &image[row][1]);
        }
    }

    //case 1 for odd width
    else if (width % 2 == 1) {
        //find the coordinate of the pixel in the middle
        int middle = width / 2;

        for (int row = 0; row < height; row++)
        {
            for (int column = 0; column < middle; column++)
            {
                swap(&image[row][column], &image[row][width - 1 - column]);
            }
        }
    }



    //case 2 for even width
    else if (width % 2 == 0) {
        //find the coordinate of the pixel in the middle
        int middle = width / 2;

        for (int row = 0; row < height; row++)
        {
            for (int column = 0; column < middle; column++)
            {
                swap(&image[row][column], &image[row][width - 1 - column]);
            }
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int h = height;
    int w = width;
    
    //Create a new data structure that stores RGB values
    typedef struct temprgb
    {
        int tred;
        int tgreen;
        int tblue;
    }
    temprgb;
    //Access by e.g. temp.tred

    //Create a new array containing all pixels of the image
    temprgb image_copy[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {

            /*--- image[row][column] ---*/

            int pixel_set = 0;

            //Corners

            //Top left corner
            if (row == 0 && column == 0)
            {
                //Calculate blur average
                int blur_red = image[0][0].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed + image[0][1].rgbtRed;
                int blur_green = image[0][0].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen + image[0][1].rgbtGreen;
                int blur_blue = image[0][0].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue + image[0][1].rgbtBlue;

                //Replace corner with new value
                image_copy[0][0].tred = average(blur_red,4);
                image_copy[0][0].tgreen = average(blur_green,4);
                image_copy[0][0].tblue = average(blur_blue,4);

                pixel_set = 1;
            }

            //Top right corner
            if (row == 0 && column == width - 1)
            {
                //Calculate blur average
                int blur_red = image[0][width - 1].rgbtRed + image[0][width-2].rgbtRed + image[1][width-2].rgbtRed + image[1][width-1].rgbtRed;
                int blur_green = image[0][width - 1].rgbtGreen + image[0][width-2].rgbtGreen + image[1][width-2].rgbtGreen + image[1][width-1].rgbtGreen;
                int blur_blue = image[0][width - 1].rgbtBlue + image[0][width-2].rgbtBlue + image[1][width-2].rgbtBlue + image[1][width-1].rgbtBlue;

                //Replace corner with new value
                image_copy[0][width-1].tred = average(blur_red,4);
                image_copy[0][width-1].tgreen = average(blur_green,4);
                image_copy[0][width-1].tblue = average(blur_blue,4);

                pixel_set = 1;

            }

            //Bottom left corner
            if (row == height - 1 && column == 0)
            {
                //Calculate blur average
                int blur_red = image[height-1][0].rgbtRed + image[height-2][0].rgbtRed + image[height-2][1].rgbtRed + image[height-1][1].rgbtRed;
                int blur_green = image[height-1][0].rgbtGreen + image[height-2][0].rgbtGreen + image[height-2][1].rgbtGreen + image[height-1][1].rgbtGreen;
                int blur_blue = image[height-1][0].rgbtBlue + image[height-2][0].rgbtBlue + image[height-2][1].rgbtBlue + image[height-1][1].rgbtBlue;

                //Replace corner with new value
                image_copy[height-1][0].tred = average(blur_red,4);
                image_copy[height-1][0].tgreen = average(blur_green,4);
                image_copy[height-1][0].tblue = average(blur_blue,4);

                pixel_set = 1;

            }

            //Bottom right corner
            if (row == height-1 && column == width-1)
            {
                //Calculate blur average
                int blur_red = image[height-1][width-1].rgbtRed + image[height-2][width-1].rgbtRed + image[height-1][width-2].rgbtRed + image[height-2][width-2].rgbtRed;
                int blur_green = image[height-1][width-1].rgbtGreen + image[height-2][width-1].rgbtGreen + image[height-1][width-2].rgbtGreen + image[height-2][width-2].rgbtGreen;
                int blur_blue = image[height-1][width-1].rgbtBlue + image[height-2][width-1].rgbtBlue + image[height-1][width-2].rgbtBlue + image[height-2][width-2].rgbtBlue;

                //Replace corner with new value
                image_copy[height-1][width-1].tred = average(blur_red,4);
                image_copy[height-1][width-1].tgreen = average(blur_green,4);
                image_copy[height-1][width-1].tblue = average(blur_blue,4);

                pixel_set = 1;

            }

            //Edges: else if, image[row][0], image[row][width]

            //Left (column = 0)
            if (pixel_set == 0 && column == 0)
            {
                //Calculate blur average
                int blur_red = image[row-1][0].rgbtRed + image[row-1][1].rgbtRed + image[row][0].rgbtRed + image[row][1].rgbtRed + image[row+1][0].rgbtRed + image[row+1][1].rgbtRed;
                int blur_green = image[row-1][0].rgbtGreen + image[row-1][1].rgbtGreen + image[row][0].rgbtGreen + image[row][1].rgbtGreen + image[row+1][0].rgbtGreen + image[row+1][1].rgbtGreen;
                int blur_blue = image[row-1][0].rgbtBlue + image[row-1][1].rgbtBlue + image[row][0].rgbtBlue + image[row][1].rgbtBlue + image[row+1][0].rgbtBlue + image[row+1][1].rgbtBlue;


                //Replace edge with new value
                image_copy[row][0].tred = average(blur_red,6);
                image_copy[row][0].tgreen = average(blur_green,6);
                image_copy[row][0].tblue = average(blur_blue,6);

                pixel_set = 1;


            }

            //Right (column = width)
            if (pixel_set == 0 && column == width - 1)
            {
                //Calculate blur average
                int blur_red = image[row-1][width-1].rgbtRed + image[row-1][width-2].rgbtRed + image[row][width-1].rgbtRed + image[row][width-2].rgbtRed + image[row+1][width-2].rgbtRed + image[row+1][width-1].rgbtRed;
                int blur_green = image[row-1][width-1].rgbtGreen + image[row-1][width-2].rgbtGreen + image[row][width-1].rgbtGreen + image[row][width-2].rgbtGreen + image[row+1][width-2].rgbtGreen + image[row+1][width-1].rgbtGreen;
                int blur_blue = image[row-1][width-1].rgbtBlue + image[row-1][width-2].rgbtBlue + image[row][width-1].rgbtBlue + image[row][width-2].rgbtBlue + image[row+1][width-2].rgbtBlue + image[row+1][width-1].rgbtBlue;


                //Replace edge with new value
                image_copy[row][width-1].tred = average(blur_red,6);
                image_copy[row][width-1].tgreen = average(blur_green,6);
                image_copy[row][width-1].tblue = average(blur_blue,6);

                pixel_set = 1;

            }

            //Top (row = 0)
            if (pixel_set == 0 && row == 0)
            {
                //Calculate blur average
                int blur_red = image[0][column-1].rgbtRed + image[0][column+1].rgbtRed + image[0][column].rgbtRed + image[1][column+1].rgbtRed + image[1][column-1].rgbtRed + image[1][column].rgbtRed;
                int blur_green = image[0][column-1].rgbtGreen + image[0][column+1].rgbtGreen + image[0][column].rgbtGreen + image[1][column+1].rgbtGreen + image[1][column-1].rgbtGreen + image[1][column].rgbtGreen;
                int blur_blue = image[0][column-1].rgbtBlue + image[0][column+1].rgbtBlue + image[0][column].rgbtBlue + image[1][column+1].rgbtBlue + image[1][column-1].rgbtBlue + image[1][column].rgbtBlue;


                //Replace edge with new value
                image_copy[0][column].tred = average(blur_red,6);
                image_copy[0][column].tgreen = average(blur_green,6);
                image_copy[0][column].tblue = average(blur_blue,6);

                pixel_set = 1;

            }

            //Bottom (row = height)
            if (pixel_set == 0 && row == height-1)
            {
                //Calculate blur average
                int blur_red = image[height-1][column-1].rgbtRed + image[height-1][column+1].rgbtRed + image[height-1][column].rgbtRed + image[height-2][column+1].rgbtRed + image[height-2][column].rgbtRed + image[height-2][column-1].rgbtRed;
                int blur_green = image[height-1][column-1].rgbtGreen + image[height-1][column+1].rgbtGreen + image[height-1][column].rgbtGreen + image[height-2][column+1].rgbtGreen + image[height-2][column].rgbtGreen + image[height-2][column-1].rgbtGreen;
                int blur_blue = image[height-1][column-1].rgbtBlue + image[height-1][column+1].rgbtBlue + image[height-1][column].rgbtBlue + image[height-2][column+1].rgbtBlue + image[height-2][column].rgbtBlue + image[height-2][column-1].rgbtBlue;


                //Replace edge with new value
                image_copy[height-1][column].tred = average(blur_red,6);
                image_copy[height-1][column].tgreen = average(blur_green,6);
                image_copy[height-1][column].tblue = average(blur_blue,6);

                pixel_set = 1;

            }

            //Everything else in the middle


            if (pixel_set == 0)
            {
                //Calculate blur average
                int blur_red = image[row-1][column-1].rgbtRed + image[row-1][column].rgbtRed + image[row-1][column+1].rgbtRed + image[row][column-1].rgbtRed + image[row][column].rgbtRed + image[row][column+1].rgbtRed + image[row+1][column-1].rgbtRed + image[row+1][column].rgbtRed + image[row+1][column+1].rgbtRed;
                int blur_green = image[row-1][column-1].rgbtGreen + image[row-1][column].rgbtGreen + image[row-1][column+1].rgbtGreen + image[row][column-1].rgbtGreen + image[row][column].rgbtGreen + image[row][column+1].rgbtGreen + image[row+1][column-1].rgbtGreen + image[row+1][column].rgbtGreen + image[row+1][column+1].rgbtGreen;
                int blur_blue = image[row-1][column-1].rgbtBlue + image[row-1][column].rgbtBlue + image[row-1][column+1].rgbtBlue + image[row][column-1].rgbtBlue + image[row][column].rgbtBlue + image[row][column+1].rgbtBlue + image[row+1][column-1].rgbtBlue + image[row+1][column].rgbtBlue + image[row+1][column+1].rgbtBlue;

                //Replace edge with new value
                image_copy[row][column].tred = average(blur_red,9);
                image_copy[row][column].tgreen = average(blur_green,9);
                image_copy[row][column].tblue = average(blur_blue,9);

                pixel_set = 1;

            }
        }
    }

    //Replace all pixels with the new pixel
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            image[i][j].rgbtRed = image_copy[i][j].tred;
            image[i][j].rgbtGreen = image_copy[i][j].tgreen;
            image[i][j].rgbtBlue = image_copy[i][j].tblue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Initialize variables
    int h = height;
    int w = width;
    int gx_red, gx_green, gx_blue;
    int gy_red, gy_green, gy_blue;

    int tl_red, tl_green, tl_blue;
    int tc_red, tc_green, tc_blue;
    int tr_red, tr_green, tr_blue;
    int sl_red, sl_green, sl_blue;
    int m_red, m_green, m_blue;
    int sr_red, sr_green, sr_blue;
    int bl_red, bl_green, bl_blue;
    int bm_red, bm_green, bm_blue;
    int br_red, br_green, br_blue;

    //Create a new data structure that stores RGB values
    typedef struct temprgb
    {
        int tred;
        int tgreen;
        int tblue;
    }
    temprgb;
    //Access by e.g. temp.tred

    //Create a new array containing all pixels of the image
    temprgb image_copy[height][width];

    //Find gx, gy values and store it in image_copy
    for (int r = 0; r < h; r++)
    {
        for (int c = 0; c < w; c++)
        {
            int pixel_set = 0;

            //If true for any of these conditions it is either a corner or a side (edge)
            if (r == 0 || r == h-1 || c == 0 || c == w-1)
            {
                //Top left: [r-1][c-1]
                if (r-1 < 0 || c-1 < 0)
                {
                   tl_red = 0;
                   tl_green = 0;
                   tl_blue = 0;
                }
                else
                {
                    tl_red = rgbvalue(image[r-1][c-1],0);
                    tl_green = rgbvalue(image[r-1][c-1],1);
                    tl_blue = rgbvalue(image[r-1][c-1],2);
                }

                //Top center: [r-1][c]
                if (r-1 < 0)
                {
                    tc_red = 0;
                    tc_green = 0;
                    tc_blue = 0;
                }
                else
                {
                    tc_red = rgbvalue(image[r-1][c],0);
                    tc_green = rgbvalue(image[r-1][c],1);
                    tc_blue = rgbvalue(image[r-1][c],2);
                }

                //Top right: [r-1][c+1]
                if (r-1 < 0 || c+1 > w-1)
                {
                    tr_red = 0;
                    tr_green = 0;
                    tr_blue = 0;
                }
                else
                {
                    tr_red = rgbvalue(image[r-1][c+1],0);
                    tr_green = rgbvalue(image[r-1][c+1],1);
                    tr_blue = rgbvalue(image[r-1][c+1],2);
                }

                //Sandwich left: [r][c-1]
                if (c-1 < 0)
                {
                    sl_red = 0;
                    sl_green = 0;
                    sl_blue = 0;
                }
                else
                {
                    sl_red = rgbvalue(image[r][c-1],0);
                    sl_green = rgbvalue(image[r][c-1],1);
                    sl_blue = rgbvalue(image[r][c-1],2);
                }

                //Sandwich middle: [r][c] (no need if statement here)
                m_red = rgbvalue(image[r][c],0);
                m_green = rgbvalue(image[r][c],1);
                m_blue = rgbvalue(image[r][c],2);

                //Sandwich right: [r][c+1]
                if (c+1 > w-1)
                {
                    sr_red = 0;
                    sr_green = 0;
                    sr_blue = 0;
                }
                else
                {
                    sr_red = rgbvalue(image[r][c+1],0);
                    sr_green = rgbvalue(image[r][c+1],1);
                    sr_blue = rgbvalue(image[r][c+1],2);
                }

                //Bottom left: [r+1][c-1]
                if (r+1 > h-1 || c-1 < 0)
                {
                    bl_red = 0;
                    bl_green = 0;
                    bl_blue = 0;
                }
                else
                {
                    bl_red = rgbvalue(image[r+1][c-1],0);
                    bl_green = rgbvalue(image[r+1][c-1],1);
                    bl_blue = rgbvalue(image[r+1][c-1],2);
                }

                //Bottom middle: [r+1][c]
                if (r+1 > h-1)
                {
                    bm_red = 0;
                    bm_green = 0;
                    bm_blue = 0;
                }
                else
                {
                    bm_red = rgbvalue(image[r+1][c],0);
                    bm_green = rgbvalue(image[r+1][c],1);
                    bm_blue = rgbvalue(image[r+1][c],2);
                }

                //Bottom right: [r+1][c+1]
                if (r+1 > h-1 || c+1 > w-1)
                {
                    br_red = 0;
                    br_green = 0;
                    br_blue = 0;
                }
                else
                {
                    br_red = rgbvalue(image[r+1][c+1],0);
                    br_green = rgbvalue(image[r+1][c+1],1);
                    br_blue = rgbvalue(image[r+1][c+1],2);
                }

                //Calculate Gx
                gx_red = (-1)*tl_red + 0*tc_red + 1*tr_red +
                         (-2)*sl_red + 0*m_red + 2*sr_red +
                         (-1)*bl_red + 0*bm_red + 1*br_red;


                gx_green = (-1)*tl_green + 0*tc_green + 1*tr_green +
                           (-2)*sl_green + 0*m_green + 2*sr_green +
                           (-1)*bl_green + 0*bm_green + 1*br_green;


                gx_blue = (-1)*tl_blue + 0*tc_blue + 1*tr_blue +
                          (-2)*sl_blue + 0*m_blue + 2*sr_blue +
                          (-1)*bl_blue + 0*bm_blue + 1*br_blue;


                //Calculate Gy
                gy_red = (-1)*tl_red + (-2)*tc_red + (-1)*tr_red +
                         0*sl_red + 0*m_red + 0*sr_red +
                         1*bl_red + 2*bm_red + 1*br_red;


                gy_green = (-1)*tl_green + (-2)*tc_green + (-1)*tr_green +
                           0*sl_green + 0*m_green + 0*sr_green +
                           1*bl_green + 2*bm_green + 1*br_green;


                gy_blue = (-1)*tl_blue + (-2)*tc_blue + (-1)*tr_blue +
                          0*sl_blue + 0*m_blue + 0*sr_blue +
                          1*bl_blue + 2*bm_blue + 1*br_blue;

                int final_red;
                int final_green;
                int final_blue;

                final_red = round(sqrt((double)(gy_red*gy_red + gx_red*gx_red)));
                if (final_red >= 255)
                {
                    final_red = 255;
                }

                final_green = round(sqrt((double)(gy_green*gy_green + gx_green*gx_green)));
                if (final_green >= 255)
                {
                    final_green = 255;
                }

                final_blue = round(sqrt((double)(gy_blue*gy_blue + gx_blue*gx_blue)));
                if (final_blue >= 255)
                {
                    final_blue = 255;
                }

                image_copy[r][c].tred = final_red;
                image_copy[r][c].tgreen = final_green;
                image_copy[r][c].tblue = final_blue;

                


                pixel_set = 1;
            }


            if (pixel_set == 0)
            {
                //Calculate Gx
                gx_red = (-1)*image[r-1][c-1].rgbtRed + 0*image[r-1][c].rgbtRed + 1*image[r-1][c+1].rgbtRed +
                         (-2)*image[r][c-1].rgbtRed + 0*image[r][c].rgbtRed + 2*image[r][c+1].rgbtRed +
                         (-1)*image[r+1][c-1].rgbtRed + 0*image[r+1][c].rgbtRed + 1*image[r+1][c+1].rgbtRed;


                gx_green = (-1)*image[r-1][c-1].rgbtGreen + 0*image[r-1][c].rgbtGreen + 1*image[r-1][c+1].rgbtGreen +
                           (-2)*image[r][c-1].rgbtGreen + 0*image[r][c].rgbtGreen + 2*image[r][c+1].rgbtGreen +
                           (-1)*image[r+1][c-1].rgbtGreen + 0*image[r+1][c].rgbtGreen + 1*image[r+1][c+1].rgbtGreen;


                gx_blue = (-1)*image[r-1][c-1].rgbtBlue + 0*image[r-1][c].rgbtBlue + 1*image[r-1][c+1].rgbtBlue +
                          (-2)*image[r][c-1].rgbtBlue + 0*image[r][c].rgbtBlue + 2*image[r][c+1].rgbtBlue +
                          (-1)*image[r+1][c-1].rgbtBlue + 0*image[r+1][c].rgbtBlue + 1*image[r+1][c+1].rgbtBlue;


                //Calculate Gy
                gy_red = (-1)*image[r-1][c-1].rgbtRed + (-2)*image[r-1][c].rgbtRed + (-1)*image[r-1][c+1].rgbtRed +
                         0*image[r][c-1].rgbtRed + 0*image[r][c].rgbtRed + 0*image[r][c+1].rgbtRed +
                         1*image[r+1][c-1].rgbtRed + 2*image[r+1][c].rgbtRed + 1*image[r+1][c+1].rgbtRed;


                gy_green = (-1)*image[r-1][c-1].rgbtGreen + (-2)*image[r-1][c].rgbtGreen + (-1)*image[r-1][c+1].rgbtGreen +
                           0*image[r][c-1].rgbtGreen + 0*image[r][c].rgbtGreen + 0*image[r][c+1].rgbtGreen +
                           1*image[r+1][c-1].rgbtGreen + 2*image[r+1][c].rgbtGreen + 1*image[r+1][c+1].rgbtGreen;


                gy_blue = (-1)*image[r-1][c-1].rgbtBlue + (-2)*image[r-1][c].rgbtBlue + (-1)*image[r-1][c+1].rgbtBlue +
                          0*image[r][c-1].rgbtBlue + 0*image[r][c].rgbtBlue + 0*image[r][c+1].rgbtBlue +
                          1*image[r+1][c-1].rgbtBlue + 2*image[r+1][c].rgbtBlue + 1*image[r+1][c+1].rgbtBlue;


                int final_red;
                int final_green;
                int final_blue;

                final_red = round(sqrt((double)(gy_red*gy_red + gx_red*gx_red)));
                if (final_red >= 255)
                {
                    final_red = 255;
                }

                final_green = round(sqrt((double)(gy_green*gy_green + gx_green*gx_green)));
                if (final_green >= 255)
                {
                    final_green = 255;
                }

                final_blue = round(sqrt((double)(gy_blue*gy_blue + gx_blue*gx_blue)));
                if (final_blue >= 255)
                {
                    final_blue = 255;
                }

                image_copy[r][c].tred = final_red;
                image_copy[r][c].tgreen = final_green;
                image_copy[r][c].tblue = final_blue;

                pixel_set = 1;
            }
        }
    }

    //Replace all pixels with the new pixel
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            image[i][j].rgbtRed = image_copy[i][j].tred;
            image[i][j].rgbtGreen = image_copy[i][j].tgreen;
            image[i][j].rgbtBlue = image_copy[i][j].tblue;
        }
    }

    return;
}

int average(int input, int divided_by)
{
    float average_float = (double)input / divided_by;
    average_float = round(average_float);
    int result = (int)average_float;
    return result;
}

int rgbvalue(RGBTRIPLE rgbt, int color)
{
    //Red
    if (color == 0) 
    {
        return rgbt.rgbtRed;
    }

    //Green
    if (color == 1) 
    {
        return rgbt.rgbtGreen;
    }

    //Blue
    if (color == 2) 
    {
        return rgbt.rgbtBlue;
    }
    else 
    {
        return 0;
    }
       
}

