#ifndef __CPATCH__
#define __CPATCH__

//#include "util.h"
#include "CDataset.h"

class CPatch
{
public:
 CPatch(cv::Rect r,CDataset *d) : roi(r), data(d){
        //cv::Mat* depthImage = d->img.at(1);
        //relativePosition.x = data->getDepthImagePath() - roi.x + roi.width / 2 + 1
    }
    CPatch(){}
    virtual ~CPatch(){}

    void setData(CDataset *d){data = d;}
    CDataset* getData()const{return data;}

    void setRoi(cv::Rect r){roi = r;}
    cv::Rect getRoi()const{return roi;}

    cv::Mat* getFeature(int featureNum) const{return data->feature.at(featureNum);}
    cv::Mat* getDepth() const{return data->img.at(1);}

//    int centerPointValue(){return data->img.at(1)->at<ushort>()}
private:
    cv::Rect roi;
    double scale;
    CDataset *data;
};

class CPosPatch : public CPatch{
public:
 CPosPatch(cv::Rect r,CPosDataset *pos) : CPatch(r, pos),pData(pos){
        relativePosition = pData->getParam()->getCenterPoint() - cv::Point(getRoi().x + getRoi().width / 2 + 1, getRoi().y + getRoi().height / 2 + 1);
        std::cout << relativePosition << std::endl;
    }
    CPosPatch(){

    }
    virtual ~CPosPatch(){}

    std::string getClassName()const{return pData->getParam()->getClassName();}
    cv::Point getCenterPoint()const{return pData->getParam()->getCenterPoint();}
    int getFeatureNum()const{return pData->feature.size();}
    CParamset getParam()const{return *(pData->getParam());}
    std::string getRgbImageFilePath(){return pData->getRgbImagePath();}
    cv::Mat* getDepth() const{return pData->img.at(1);}
    void setCenterPoint(cv::Point nCenter){pData->setCenterPoint(nCenter);}

    cv::Point getRelativePosition(){return relativePosition;}
    void setRelativePosition(const cv::Point p){relativePosition = p;}

private:
    CPosDataset *pData;
    cv::Point relativePosition;
};

class CNegPatch : public CPatch{
public:
 CNegPatch(cv::Rect r, CNegDataset *neg ) : CPatch(r, neg), nData(neg){}
    CNegPatch(){}
    int getFeatureNum()const{return nData->feature.size();}
    cv::Mat* getDepth() const{return nData->img.at(1);}
    virtual ~CNegPatch(){}

private:
    CNegDataset *nData;
};

class CTestPatch : public CPatch{
public:
 CTestPatch(cv::Rect r, CTestDataset *tes) : CPatch(r, tes),tData(tes){}
    CTestPatch(){}
    virtual ~CTestPatch(){}
    //cv::Rect getPatchRoi(){return this->getRoi(
    int getFeatureNum()const {return tData->feature.size();}
    cv::Mat* getDepth() const{return tData->img.at(1);}

private:
    CTestDataset *tData;
};

#endif
