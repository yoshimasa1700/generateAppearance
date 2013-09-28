#include <iostream>
#include "CConfig.h"
#include "globjloader.h"
#include "CDataset.h"

#define PATH_SEP "/"

using namespace std;

void pBar(int p,int maxNum, int width){
  int i;
  std::cout << "[";// << std::flush;
  for(i = 0;i < (int)((double)(p + 1)/(double)maxNum*(double)width);++i)
    std::cout << "*";

  for(int j = 0;j < width - i;++j)
    std::cout << " ";

  std::cout << "]" << (int)((double)(p + 1)/(double)maxNum*100) << "%"  << "\r" << std::flush;
}

int main(int argc, char *argv[]){
  CConfig conf;
  std::string inputPath, outputPath;
  int outputNum = 100;
  
  //read and check argument
  if(argc < 2) {
    cout << "Usage: ./generateAppearance [config.xml] [inputPath] [outputpath] [outputNum]"<< endl;
    conf.loadConfig("config.xml");
  } else
    conf.loadConfig(argv[1]);

  if(argc < 3)
    inputPath = "./models";
  else
    inputPath = argv[2];
  
  if(argc < 4)
    outputPath = "./dataset";
  else
    outputPath = argv[3];

  if(argc > 5)
    outputNum = atoi(argv[4]);

  //init gl
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(640, 480);	/*  Window Size If We Start In Windowed Mode */
  glutCreateWindow("Wavefront Obj File Viewer");

  //create appearance
  std::vector<std::vector<CPosDataset*> > posSet;
  std::vector<std::string> instName(0);

  std::vector<std::string> modelPath(0);
  std::vector<std::string> modelName(0);
  std::string trainModelListPath = conf.modelListFolder + PATH_SEP + conf.modelListName;

  boost::lagged_fibonacci1279 genPose;
  boost::uniform_real<> dst(0, 360);
  boost::variate_generator<boost::lagged_fibonacci1279&,
			   boost::uniform_real<> > rand(genPose, dst);

  std::ifstream modelList(trainModelListPath.c_str());
  if(!modelList.is_open()){
    std::cout << "train model list is not found!" << std::endl;
    exit(-1);
  }

  //std::cout << trainModelListPath << std::endl;

  int modelNum = 0;
  modelList >> modelNum;
  modelPath.resize(modelNum);
  modelName.resize(modelNum);

  posSet.resize(modelNum);

  for(int i = 0; i < modelNum; ++i){
    std::string tempName;
    modelList >> tempName;
    modelPath[i] = conf.modelListFolder +PATH_SEP + tempName;
    std::string tempClass;
    modelList >> tempClass;
    modelName[i] = tempClass;
    modelList >> tempClass;
    instName.push_back(tempClass);
  }

  string execstr = "mkdir -p ";
  for(unsigned int i = 0; i < modelName.size() ; ++i){
    system((execstr + outputPath + PATH_SEP + modelName[i]).c_str());
  }
  
  for(int j = 0; j < modelNum; ++j){
    posSet[j].resize(outputNum);
    
    for(int i = 0; i < outputNum; ++i){
      CPosDataset* posTemp = new CPosDataset();
      posTemp->setModelPath(modelPath.at(j));
      posTemp->setClassName(modelName.at(j));
      double tempAngle[3];
      for(int k = 0; k < 3; ++k)
	tempAngle[k] = rand();
      posTemp->setAngle(tempAngle);
      posTemp->setCenterPoint(cv::Point(320,240));

      posSet[j][i] = posTemp;
    }
  }
  //  std::cout << std::endl;
  modelList.close();

  std::cout << "loading image" << std::endl;

  std::ofstream filelist((outputPath + PATH_SEP + conf.traindatafile).c_str());
  filelist << modelNum << std::endl;
  for(unsigned int i = 0; i < posSet.size(); ++i){
    filelist << modelName[i] << std::endl;
    std::ofstream ofs((outputPath + PATH_SEP + modelName[i] + PATH_SEP + conf.traindatalist).c_str());
    std::ofstream ofs2((outputPath + PATH_SEP + modelName[i] + PATH_SEP + "dataListInst2.0.txt").c_str());

    ofs << outputNum << std::endl;
    ofs2 << outputNum << std::endl;

    for(unsigned int j = 0; j < posSet[i].size(); ++j){
      std::stringstream imageName;
      imageName << modelName[i] << "_" << j;
      ofs << imageName.str() + "_crop.png ";
      ofs << imageName.str() + "_depthcrop.png ";
      ofs << " nodata ";
      ofs << modelName[i] << " ";

      ofs2 << imageName.str() + "_crop.png ";
      ofs2 << imageName.str() + "_depthcrop.png ";
      ofs2 << " nodata ";
      ofs2 << instName[i] << " ";

      for(int k = 0; k < 3; ++k){
	ofs << posSet[i][j]->getParam()->getAngle()[k] << " ";
	ofs2 << posSet[i][j]->getParam()->getAngle()[k] << " ";
      }
      ofs << std::endl;
      ofs2 << std::endl;
      
      //      std::cout << posSet[i][j]->getModelPath() << std::endl;
      posSet[i][j]->loadImage(conf, posSet[i][j]->getModelPath(), posSet[i][j]->getParam());

      cv::Mat showDepth;
      showDepth = cv::Mat(posSet[i][j]->img[1]->rows,posSet[i][j]->img[1]->cols,CV_8U );

      posSet[i][j]->img[1]->convertTo(showDepth, CV_8U, 255.0 / 1000);

      //cv::namedWindow("test");
      //cv::imshow("test", showDepth);
      //cv::waitKey(0);
      //cv::destroyWindow("test");

      cv::Mat geta = cv::Mat::ones(posSet[i][j]->img[1]->rows, posSet[i][j]->img[1]->cols,CV_16UC1) * 350;

      std::cout << "kokoka?" << std::endl;
      *posSet[i][j]->img[1] += geta;
      std::cout << "kokoya!" << std::endl;

      cv::imwrite(outputPath + PATH_SEP + modelName[i] + PATH_SEP + imageName.str() + "_crop.png", *posSet[i][j]->img[0]);
      cv::imwrite(outputPath + PATH_SEP + modelName[i] + PATH_SEP + imageName.str() + "_depthcrop.png", *posSet[i][j]->img[1]);

      delete posSet[i][j];
      
      pBar(i*outputNum + j, modelNum*outputNum, 50);
    }
    ofs.close();
    ofs2.close();
  }
  std::cout << std::endl;
  // save appearance


  
  return 0;
}
