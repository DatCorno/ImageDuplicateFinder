#include "include/duplicatefinder.h"

using namespace std;
using namespace cv;

DuplicateFinder::DuplicateFinder(const std::string &root) : root_directory(root)
{

}

//Creates a  list of Duplicate objects, which is a convenient structure to
//keep two images together. The duplicates are images that share common features
//but are not the same files.
list<Duplicate> DuplicateFinder::find_duplicates()
{
    unordered_set<string> all_paths = get_all_images(root_directory);

    list<Duplicate> duplicates;

    auto orb = ORB::create();

    //Loop through all the paths to images found
    for(unordered_set<string>::iterator it = all_paths.begin(); it != all_paths.end(); ++it)
    {
        //If it is the last element no need to compare it to anything
        if(distance(it, all_paths.end()) == 1)
            break;

        Mat supposed_original = load_mat(*it); //Load the mat of the image
        Mat descriptor_original; //Descriptor for the matches

        vector<KeyPoint> original_keypoints;
		
		orb(supposed_original, nullptr, original_keypoints, descriptor_original);
		
        auto to_compare_it = it;

        //Starting from the next element following the current image, detect keypoints and set
        //descriptor for matches
        for(++to_compare_it; to_compare_it != all_paths.end(); ++to_compare_it)
        {
            Mat supposed_copy = load_mat(*to_compare_it); //The loaded copy's image
            Mat descriptor_copy; //Descriptor for the copy mat

            vector<KeyPoint> copy_keypoints; //Copy's points of interest

			orb(supposed_copy, nullptr, copy_keypoints, descriptor_copy);

            //Analyse if there are any matches between all keypoints
            if(detect_matches(descriptor_original, descriptor_copy))
                duplicates.push_back({*it, *to_compare_it}); //Add the paths to the original and duplicate to list
        }

    }

    return duplicates;
}

//Given two mats as descriptors return if they have any features in common using a
bool DuplicateFinder::detect_matches(const Mat &descriptor_original, const Mat &descriptor_copy)
{
    vector<DMatch> matches;

    matcher.match(descriptor_original, descriptor_copy, matches);

	double max_dist = 0; double min_dist = 100;
	
	for(size_t i = 0; i < descriptor_original.rows; ++i)
	{
		double dist = matches[i].distance;
		if(dist < min_dist) min_dist = dist;
		if(dist > max_dist) max_dist = dist;
	}
	
	vector<DMatch> good_matches;
	
	for(size_t i = 0; i < descriptor_original.rows; ++i)
		if(matches[i].distance <= max(2 * min_dist, 0.02))
			good_matches.push_back(matches[i]);
		
	return good_matches.size() > 0;
}

Mat DuplicateFinder::load_mat(const string &path)
{
    return imread(path, CV_LOAD_IMAGE_GRAYSCALE);
}
