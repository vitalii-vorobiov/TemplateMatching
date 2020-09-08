//
// Created by Vitaliy Vorobyov on 08.09.2020.
//

#include <iostream>
#include <boost/program_options.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/stitching.hpp>

#include "CommandLineParser.h"

namespace po = boost::program_options;

int templateMatching::CommandLineParser::parseCommandLine(int argc, char **argv) {
    po::options_description desc("General options");
    desc.add_options()
            ("help,h", "Show help")
            ("image,i", po::value<std::string>(), "Input images for stitching")
            ("template,t", po::value<std::string>(), "Input images for stitching")
            ;

    po::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return EXIT_SUCCESS;
    }

    if (vm.count("image")) {
        std::string image_name = vm["image"].as<std::string>();
        image = cv::imread(cv::samples::findFile(image_name));
        if (image.empty()) {
            std::cout << "Can't read image '" << image_name << std::endl;
            return EXIT_FAILURE;
        }
    }

    if (vm.count("template")) {
        std::string template_name = vm["template"].as<std::string>();
        templateImage = cv::imread(cv::samples::findFile(template_name));
        if (templateImage.empty()) {
            std::cout << "Can't read image '" << template_name << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}