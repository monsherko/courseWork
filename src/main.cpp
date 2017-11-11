/*******************************************************************************
*                                                                              *
*                           created by Alisher Khodzhahanov                    *                                                   *
*                                                                              *
*                           ICQ: 649946128                                     *
*                           mail: monsherko@yahoo.com                          *
*                           telegram: monsherko                                *
*                                                                              *
*                                                                              *
********************************************************************************/






//  g++ main.cpp -o output `pkg-config --cflags --libs opencv` -std=c++11

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>




#include "matrix.hpp"
#include "toningalgorithm.hpp"




int main(int argc, char** argv) {

        if(argc > 3) {
                std::cout << "Usage: ./dithering [algorithm || --help] [path_to_image]\n" <<std::endl;
                std::cout << "Run with --help for more information.\n\n " << std::endl;
                std::cout << "created by sher" <<std::endl;

                return 0 ;
         }

         if(strcmp(argv[1], "--help") == 0) {
             std::cout << "algoritm: -halftoning\n          -halftoningWithThreshold\n          -halfFloydStreinberg\n" <<std::endl;

             return 0;
         }

        cv::Mat source_image = cv::imread( argv[argc - 1]);
        cv::Mat target_image;

        if(strcmp(argv[1], "-halftoning") == 0)  {
                uint8_t** tmp = initMatrix<uint8_t>(1, 4, tmp);
                target_image = halftoning<uint8_t>(source_image, tmp, 1<<4);
        } else if (strcmp(argv[1], "-halftoningWithThreshold") == 0) {
                target_image = halftoning(source_image);
        } else if (strcmp(argv[1], "-halfFloydStreinberg") == 0) {
          cv::Mat dithImg;

                target_image = halftoningFloydStreinberg<uint8_t>(source_image);
        } else {
                std::cout << "bad options"  << std::endl;
                return 0;
        }



        cv::imshow("target image", target_image);
        cv::waitKey();
        return 0;
}
