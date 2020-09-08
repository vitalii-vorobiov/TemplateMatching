//
// Created by Vitaliy Vorobyov on 08.09.2020.
//

#ifndef TEMPLATEMATCHING_COMMANDLINEPARSER_H
#define TEMPLATEMATCHING_COMMANDLINEPARSER_H

namespace templateMatching {
    class CommandLineParser {
    public:
        cv::Mat image;
        cv::Mat templateImage;
        int parseCommandLine(int argc, char** argv);
    };
}

#endif //TEMPLATEMATCHING_COMMANDLINEPARSER_H
