#ifndef __UTIL__
#define __UTIL__

#define PATH_SEP "/"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <set>

// opencv include file
#include <opencv2/opencv.hpp>

// boost include file
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random.hpp>

#include "CDataset.h"
#include "CPatch.h"

extern boost::lagged_fibonacci1279 genPose;

void normarizationByDepth(CPatch &patch,const CConfig &conf);
void normarizationCenterPointP(CPosPatch &patch, const CConfig &config);
void normarizationCenterPointT(CTestPatch &patch, const CConfig &config);

class databaseNode{
public:
    databaseNode(std::string className,cv::Size size, uchar depth)
      : name(className), classSize(size),classDepth(depth), instances(1){}

    std::string name;
    cv::Size classSize;
    uchar classDepth;

    int instances;
};

class CClassDatabase{
public:
    CClassDatabase(){
        vNode.clear();
    }

    void add(std::string str, cv::Size size, uchar depth);
    void write(const char* str);
    void read(const char* str);

    int search(std::string str) const;

    void show() const;

    void clear(){
        vNode.clear();
    };

    std::vector<databaseNode> vNode;
};

class nCk{
public:
    std::set<int> generate(int n, int k){
        std::set<int> cmb;
        int j;
        //srand(time(NULL));
        boost::uniform_smallint<> dst(0,n);
        boost::variate_generator<
                boost::lagged_fibonacci1279&, boost::uniform_smallint<>
                > rand( gen, dst );

        for(int i = n - k; i < n; i++){
            j = rand()%i;
            if(cmb.find(j) == cmb.end())
                cmb.insert(j);
            else
                cmb.insert(i);
        }
        return cmb;
    }
private:
    static boost::lagged_fibonacci1279 gen;
};

void loadTrainObjFile(CConfig conf, std::vector<CPosDataset*> &posSet);
void loadTrainPosFile(CConfig conf, std::vector<CPosDataset*> &posSet);//, boost::mt19937 &gen);
void loadTrainNegFile(CConfig conf, std::vector<CNegDataset*> &negSet);
//void loadTestFile(CConfig conf, std::vector<CTestDataset> &testSet);

void extractPosPatches(std::vector<CPosDataset*> &posSet,
                       std::vector<CPosPatch> &posPatch,
                       CConfig conf,
                       const int treeNum,
                       const CClassDatabase &classDatabase);
void extractNegPatches(std::vector<CNegDataset*> &negSet,std::vector<CNegPatch> &negPatch,
                       CConfig conf);
void extractTestPatches(CTestDataset* testSet,std::vector<CTestPatch> &testPatch, CConfig conf);

void pBar(int p,int maxNum, int width);


#endif
