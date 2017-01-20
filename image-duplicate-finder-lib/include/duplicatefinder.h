#ifndef DUPLICATEFINDER_H
#define DUPLICATEFINDER_H

#include <string>
#include <list>
#include <iostream>
#include "directoryexplorer.h"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv_modules.hpp"

struct Duplicate {
    std::string original;
    std::string duplicate;
};

class DuplicateFinder {
public :
    DuplicateFinder(const std::string&);

    std::list<Duplicate> find_duplicates();
private:
    cv::Mat load_mat(const std::string&);
    bool detect_matches(const cv::Mat&, const cv::Mat&);

    std::string root_directory;
	
	FlannBasedMatcher matcher;
};


#endif // DUPLICATEFINDER_H
