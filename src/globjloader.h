#ifndef GLOBJLOADER_H
#define GLOBJLOADER_H

# ifdef _WIN32
#   include <windows.h>
# endif
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <glm.h>

#include <opencv2/opencv.hpp>

#define bool int
#define true 1
#define false 0


class CGlObjLoader
{
public:
  CGlObjLoader(const char* fname);
  CGlObjLoader();

  virtual ~CGlObjLoader();

  int setModel(const char* fname);

    cv::vector<cv::Mat*> getAppearance(double r, double p, double y);
    cv::vector<cv::Mat*> getAppearance(const double* angle);
    
    void invertMatrix(const GLdouble * m, GLdouble * out);
    void setMatrix(double * matrixI);
private:
    cv::Mat frontBuffer;
    cv::Mat depthBuffer;

    double roll, pitch, yaw;

    /* Ortho (if used) */
    double _left;		/* ortho view volume params */
    double _right;
    double _bottom;
    double _top;
    double _zNear;
    double _zFar;
    double fovy;
    double prev_z;

    //    double _left = 0.0;		/* ortho view volume params */
    //    double _right = 0.0;
    //double _bottom = 0.0;
    //double _top = 0.0;
    //double _zNear = 0.1;
    //double _zFar = 10.0;
    //double fovy = 45.0;
    //double prev_z = 0;


    /* Modelview Matrix */
    double _matrix[16];		/* model matrix and supporting linear algebra functions */
    double _matrixI[16];
    double vlen(double x, double y, double z);
    void pos(double *px, double *py, double *pz, const int x, const int y,
             const int *viewport);
    void getMatrix();


    /* Global Variables for this app */
    GLMmodel *pmodel;	/* the loaded model */
    char filename[256];
    GLuint mode;		/* viewing mode */

    int ww, wh;			/* window width and height */
//    //int wireframe = 0;		/* Draw modes */
//    //int show_axis = 1;
//    int smooth = 1;
//    int material = 1;
//    int textured = 1;
//    int two_sided = 1;
//    int show_help = 0;		/* help toggle */
//    int stereo = 0;			/* stereo init variable */
//    int benchmark = 0;
//    int centerZ = -1;
//    float auto_rotate = 0;
//    int xrotate = 0;
//    int yrotate = 1;
//    int zrotate = 0;

//    int lighting = 1;

    /* Lighting Variables */
    GLfloat light_ambient[4];// = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[4];// = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[4];// = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[4];// = { 1.0, 1.0, 1.0, 0.0 };

    GLfloat mat_ambient[4];// = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_diffuse[4];// = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[4];// = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[1];//= { 100.0 };

    /* Standard Glut interface functions                                     */
    void Reshape(int w, int h);
    void Display(void);

    /* Model and help display functoins */
    void DrawModel(void);
};

#endif // GLOBJLOADER_H
