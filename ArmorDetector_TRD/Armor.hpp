/**************************************************************
                    MIT License
        Copyright (c) 2021 HNU-YueLuRM-Vision
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

        Authors: Zeng QingCheng, <neozng1@hnu.edu.cn>
**************************************************************/

#pragma once
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <math.h>

using namespace cv;
using namespace std;

namespace hnurm
{

    class Armor
    {
    public:

        Armor(){}


        Armor(Point2f* armor_arr)
        {
            for(int i=0;i<4;i++)
            {
                vertexes[i]=armor_arr[i];
            }
            core.x=(armor_arr[2].x+armor_arr[3].x)/2-(armor_arr[0].x+armor_arr[1].x)/2;
            core.y=(armor_arr[0].y+armor_arr[1].y+armor_arr[2].y+armor_arr[3].y)/4;
        }

        Armor operator=(const Armor& _armor)
        {
            Armor temp_armor;
            for(int i=0;i<4;i++)
            {
                temp_armor.vertexes[i]=_armor.vertexes[i];
            }
            temp_armor.core=_armor.core;
            return temp_armor;
        }

    public:

        void DrawArmor(Mat& canvas)
        {
            for (int i = 0; i < 4; i++)
            {
                line(canvas, vertexes[i], vertexes[(i + 1) % 4], Scalar(0,255,0), 2);
            }
        }

        void GetSVMImg(Mat& cut_remap)
        {
            //do some project transformation and cut here.
            //how to tell the bigger one and the small one?
            //maybe we have to do this after redress ROI,but it cost too much ,cause we have to redress twice
            
        }

    public:

        Point2f vertexes[4];
        Point2f core;

    };//Armor

}//hnurm
