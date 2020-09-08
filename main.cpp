#include <opencv2/core.hpp>
#include <cstdlib>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "CommandLineParser.h"

struct position {
    std::vector<int> bestRow {};
    std::vector<int> bestCol {};
    std::vector<double> bestSAD {};
};

int main(int argc, char** argv) {
    templateMatching::CommandLineParser commandLineParser{};
    commandLineParser.parseCommandLine(argc, argv);

    cv::Mat greyImage;
    cv::Mat greyTemplate;

    cv::cvtColor(commandLineParser.image, greyImage, cv::COLOR_BGR2GRAY);
    cv::cvtColor(commandLineParser.templateImage, greyTemplate, cv::COLOR_BGR2GRAY);

    position position{};
    float minSAD = INFINITY;

    for (int x = 0; x < commandLineParser.image.cols - commandLineParser.templateImage.cols; ++x) {
        for (int y = 0; y < commandLineParser.image.rows - commandLineParser.templateImage.rows; ++y) {
            float SAD = 0.0f;

            for (int j = 0; j < commandLineParser.templateImage.cols; ++j) {
                for (int i = 0; i < commandLineParser.templateImage.rows; ++i) {
                    int pImage = greyImage.at<uchar>(y+i, x+j);
                    int pTemplate = greyTemplate.at<uchar>(i, j);

                    SAD += abs(pImage - pTemplate);
                }
            }

            if ( minSAD > SAD ) {
                minSAD = SAD;
                position.bestRow.push_back(y);
                position.bestCol.push_back(x);
                position.bestSAD.push_back(SAD);
            }
        }
    }

    for (int i = 0; i < position.bestSAD.size(); ++i) {
        cv::Rect rect = cv::Rect(position.bestCol[i], position.bestRow[i], greyTemplate.cols, greyTemplate.rows);
        cv::rectangle(commandLineParser.image, rect, cv::Scalar(255,0,0),1,8,0);
    }

    cv::imshow( "Image", commandLineParser.image);
    cv::waitKey(0);

    return 0;
}
