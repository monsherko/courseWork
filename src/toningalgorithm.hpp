std::pair<cv::Mat, int> copySourceImg(cv::Mat sourceImg) {

      int maxThresh = 0;
      cv::Mat targetImg(sourceImg.rows, sourceImg.cols, CV_8UC1);

      for(int i=0; i < sourceImg.rows; i++)
      {
              for(int j=0; j < sourceImg.cols; j++)
              {
                       targetImg.at<int8_t>(i,j) = sourceImg.at<int8_t>(i,j);
                       if (maxThresh < targetImg.at<int8_t>(i,j))
                       {
                                maxThresh = targetImg.at<int8_t>(i,j);
                       }
              }
      }

        return std::pair<cv::Mat, int>(targetImg, maxThresh);
}


template<typename T>
cv::Mat halftoning(cv::Mat sourceImg, T** matrix, int sizeMatrix)
{
       cv::Mat dithImg;
       cv::cvtColor(sourceImg, dithImg, CV_BGR2GRAY);
       std::pair<cv::Mat, int> res = copySourceImg(dithImg);


        for ( int i = 0; i < dithImg.rows ; i++)
        {
               for ( int j = 0; j < dithImg.cols ; j++)
               {
                         if(res.first.at<uint8_t>(i,j) > matrix[i % sizeMatrix][j % sizeMatrix]){
                                  res.first.at<uint8_t>(i,j) = 255;
                         } else {
                                  res.first.at<uint8_t>(i,j) = 0;
                         }
                }
         }

         return res.first;
}

cv::Mat halftoning(cv::Mat sourceImg)
{
        cv::Mat dithImg;
        cv::cvtColor(sourceImg, dithImg, CV_BGR2GRAY);
        std::pair<cv::Mat, int> res = copySourceImg(dithImg);

        for ( int i = 0; i < dithImg.rows; i++)
        {
                for ( int j = 0; j < dithImg.cols; j++)
                {
                        if(res.first.at<uint8_t>(i,j) > res.second/2){
                                res.first.at<uint8_t>(i,j) = 255;
                        } else {
                                res.first.at<uint8_t>(i,j) = 0;
                        }
                }
        }

        return res.first;
}


uint8_t saturated_add(uint8_t val1, int8_t val2)
{
        int16_t val1_int = val1;
        int16_t val2_int = val2;


        return val1+val2 > 255 ? 255 : ((val1+val2) < 0? 0 : (val1+val2));

}
// Floyd-Steinberg algorithm ...
template<typename Type>
cv::Mat halftoningFloydStreinberg(cv::Mat sourceImg) {

        int error;


        cv::Mat dithImg;
        cv::cvtColor(sourceImg, dithImg, CV_BGR2GRAY);

        for(int i=0; i < dithImg.rows; i++)
        {
                for(int j=0; j < dithImg.cols; j++)
                {
                        if(dithImg.at<Type>(i,j) < 127) {
                                error = dithImg.at<Type>(i,j) - 0;
                                dithImg.at<Type>(i,j) = 0;

                        } else {
                                error = dithImg.at<Type>(i,j) - 255;
                                dithImg.at<Type>(i,j) = 255;
                        }



                        if( (j != 0) && (i != (dithImg.rows-1)) && (j != (dithImg.cols - 1))) {
                                dithImg.at<Type>(i+0,j+1) = saturated_add(dithImg.at<Type>(i+0,j+1),(error * 7) / 16);
                                dithImg.at<Type>(i+1,j+1) = saturated_add(dithImg.at<Type>(i+1,j+1),(error * 1) / 16);
                                dithImg.at<Type>(i+1,j+0) = saturated_add(dithImg.at<Type>(i+1,j+0),(error * 5) / 16);
                                dithImg.at<Type>(i+1,j-1) = saturated_add(dithImg.at<Type>(i+1,j-1),(error * 3) / 16);
                         }
                }
        }

        return dithImg;
}
