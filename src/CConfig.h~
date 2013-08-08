#ifndef __CCONFIG__
#define __CCONFIG__


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>

// boost include file
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random.hpp>

class CConfig
{
public:
    CConfig(){
        demoMode = 0;
    };
    ~CConfig(){};

    double widthScale,heightScale;

    int loadConfig(const char* filename);

    // Path to trees
    std::string	treepath;
    // Number of trees
    int		ntrees;
    // Patch width
    int		p_width;
    // Patch height
    int		p_height;
    // Path to images
    std::string	impath;
    // File with names of images
    std::string	imfiles;
    // Extract features
    bool		xtrFeature;
    // Scales
    std::vector<float>	scales;
    // Ratio
    std::vector<float>	ratios;
    // Output path
    std::string	outpath;
    // scale factor for output image (default: 128)
    int		out_scale;
    // Path to training image folder 12/12/14 MasahikoToyoshi
    std::string	trainpath;
    // training data file name
    std::string	traindatafile;
    // Path to positive examples
    std::string	trainpospath;
    // File with postive examples
    std::string	trainposfiles;
    // Subset of positive images -1: all images
    int		subsamples_pos;
    // Sample patches from pos. examples
    unsigned int	samples_pos;
    // Path to positive examples
    std::string	trainnegpath;
    // File with postive examples
    std::string	trainnegfiles;
    // Subset of neg images -1: all images
    int		subsamples_neg;
    // Samples from pos. examples
    unsigned int	samples_neg;
    // offset for saving tree number
    int	off_tree;
    // train image per tree
    int	imagePerTree;
    // sample number per leaf
    int	min_sample;
    // max depth of tree
    int	max_depth;
    // feature channel number
    int	featureChannel;
    // extract patch ratio
    double	patchRatio;
    // stride of getting patch
    int stride;
    // test data path
    std::string testPath;
    // test data file
    std::string testData;
    // test mode
    int testMode;
    double detectThreshold;

    std::string negDataPath,negDataList;

    int showGT;

    std::string classDatabaseName;

    int learningMode;

    std::string traindatalist;
    std::string testdatalist;
    int negMode;

    double pnRatio;

    double acPatchRatio;
    double mindist;
    double maxdist;

    int nOfTrials;

    int crossVMode;

    std::string negFolderList;
    int demoMode;
    int clusterNumLimit;

    // haar-like : 0, hog : 1, rotated haar-like : 2
    int rgbFeature;
    int depthFeature;

    int paramRadius;

    std::string modelListFolder;
    std::string modelListName;

    int modelLearningMode;
private:
    boost::property_tree::ptree pt;

};

#endif
