#include "globjloader.h"

CGlObjLoader::CGlObjLoader(){
    _left = 0.0;		/* ortho view volume params */
  _right = 0.0;
  _bottom = 0.0;
  _top = 0.0;
  _zNear = 0.1;
  _zFar = 10.0;
  fovy = 45.0;
  prev_z = 0;

  mode = 0;		/* viewing mode */

  pmodel = NULL;

  light_ambient[0] = 0.0;
  light_ambient[1] = 0.0;
  light_ambient[2] = 0.0;
  light_ambient[3] = 1.0;

  for(int i = 0; i<4; ++i){
    light_diffuse[i] = 1.0;
    light_specular[i] = 1.0;
    light_position[i] = 1.0;
    
    mat_ambient[i] = 0.7;
    mat_diffuse[i] = 0.8;
    mat_specular[i] = 1.0;
  }
    light_position[3] = 0.0;
    mat_ambient[3] = 1.0;
    mat_diffuse[3] = 1.0;
    high_shininess[0] = 100.0;
  
  

  //     light_ambient[4] = { 1.0, 1.0, 1.0, 1.0 };
  //     light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
  //     light_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
  //     light_position[4] = { 1.0, 1.0, 1.0, 0.0 };

  //     mat_ambient[4] = { 0.7, 0.7, 0.7, 0.0 };
  //     mat_diffuse[4] = { 0.8, 0.8, 0.8, 1.0 };
  //     mat_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
  //     high_shininess[1] = { 100.0 };

  //#pragma omp critical
  getMatrix();
  glClearColor(0.0, 0.0, 0.0, 0.0);   // glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
  //glutMainLoop();
  glClearAccum(0.0, 0.0, 0.0, 0.0);

  // if (lighting)
  glEnable(GL_LIGHTING);
  /// if (lighting)
  glEnable(GL_LIGHT0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_TEXTURE_2D);

}
CGlObjLoader::CGlObjLoader(const char* fname)
{
  _left = 0.0;		/* ortho view volume params */
  _right = 0.0;
  _bottom = 0.0;
  _top = 0.0;
  _zNear = 0.1;
  _zFar = 10.0;
  fovy = 45.0;
  prev_z = 0;

  mode = 0;		/* viewing mode */

  pmodel = NULL;

  light_ambient[0] = 0.0;
  light_ambient[1] = 0.0;
  light_ambient[2] = 0.0;
  light_ambient[3] = 1.0;

  for(int i = 0; i<4; ++i){
    light_diffuse[i] = 1.0;
    light_specular[i] = 1.0;
    light_position[i] = 1.0;
    
    mat_ambient[i] = 0.7;
    mat_diffuse[i] = 0.8;
    mat_specular[i] = 1.0;
  }

  light_position[3] = 0.0;
  mat_ambient[3] = 1.0;
  mat_diffuse[3] = 1.0;
  high_shininess[0] = 100.0;
  
  

  //     light_ambient[4] = { 1.0, 1.0, 1.0, 1.0 };
  //     light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
  //     light_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
  //     light_position[4] = { 1.0, 1.0, 1.0, 0.0 };

  //     mat_ambient[4] = { 0.7, 0.7, 0.7, 0.0 };
  //     mat_diffuse[4] = { 0.8, 0.8, 0.8, 1.0 };
  //     mat_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
  //     high_shininess[1] = { 100.0 };

  //#pragma omp critical
  getMatrix();
  glClearColor(0.0, 0.0, 0.0, 0.0);   // glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
  //glutMainLoop();
  glClearAccum(0.0, 0.0, 0.0, 0.0);

  // if (lighting)
  glEnable(GL_LIGHTING);
  /// if (lighting)
  glEnable(GL_LIGHT0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_TEXTURE_2D);

  strncpy(filename, fname ,sizeof(filename));	/* get the last arg as the file always */

 
  if (!pmodel) {		/* load up the model */
    //      std::cout << filename << std::endl;
    //#pragma omp critical
    pmodel = glmReadOBJ(filename);
    if (!pmodel) {
      printf("\nUsage: objviewV2 <-s> <obj filename>\n");
      exit(0);
    }

    //std::cout << "load shita yo" << std::endl;
    //#pragma omp critical
    glmUnitize(pmodel);
    //#pragma omp critical
    glmVertexNormals(pmodel, 90.0, GL_TRUE);
  }

}

CGlObjLoader::~CGlObjLoader(){
  glmDelete(pmodel);
}

int CGlObjLoader::setModel(const char* fname){
  strncpy(filename, fname ,sizeof(filename));	/* get the last arg as the file always */
  if(pmodel){
    glmDelete(pmodel);
    pmodel = NULL;
  }
  if (!pmodel) {		/* load up the model */
    //      std::cout << filename << std::endl;
    //#pragma omp critical
    pmodel = glmReadOBJ(filename);
    if (!pmodel) {
      printf("can't load model %s", fname);
      exit(0);
    }
  }


  glmUnitize(pmodel);
  glmVertexNormals(pmodel, 90.0, GL_TRUE);
  std::cout << "kokomade kitayo" << std::endl;
  return 0;
}

void CGlObjLoader::Reshape(int w, int h){
  glViewport(0, 0, w, h);

  ww = w;
  wh = h;

  _top = 1.0;
  _bottom = -1.0;
  _left = -(double) w / (double) h;
  _right = -_left;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  /* glOrtho(_left,_right,_bottom,_top,_zNear,_zFar);  Ortho */
  gluPerspective(fovy, (double) w / (double) h, _zNear, _zFar);	/* PErspective for stereo */

  glMatrixMode(GL_MODELVIEW);
}

double CGlObjLoader::vlen(double x, double y, double z)
{
  return sqrt(x * x + y * y + z * z);
}

void CGlObjLoader::pos(double *px, double *py, double *pz, const int x, const int y,
		       const int *viewport)
{
  /*
    Use the ortho projection and viewport information
    to map from mouse co-ordinates back into world
    co-ordinates
  */

  *px = (double) (x - viewport[0]) / (double) (viewport[2]);
  *py = (double) (y - viewport[1]) / (double) (viewport[3]);

  *px = _left + (*px) * (_right - _left);
  *py = _top + (*py) * (_bottom - _top);
  *pz = _zNear;
}

void CGlObjLoader::getMatrix()
{
  //#pragma omp critical
  glGetDoublev(GL_MODELVIEW_MATRIX, _matrix);
  invertMatrix(_matrix, _matrixI);
}

void CGlObjLoader::setMatrix(double matrixI[16]){
  for(int i = 0; i < 16; ++i)
    _matrixI[i] = matrixI[i];
}

void CGlObjLoader::invertMatrix(const GLdouble * m, GLdouble * out)
{

  /* NB. OpenGL Matrices are COLUMN major. */
#define MAT(m,r,c) (m)[(c)*4+(r)]

  /* Here's some shorthand converting standard (row,column) to index. */
#define m11 MAT(m,0,0)
#define m12 MAT(m,0,1)
#define m13 MAT(m,0,2)
#define m14 MAT(m,0,3)
#define m21 MAT(m,1,0)
#define m22 MAT(m,1,1)
#define m23 MAT(m,1,2)
#define m24 MAT(m,1,3)
#define m31 MAT(m,2,0)
#define m32 MAT(m,2,1)
#define m33 MAT(m,2,2)
#define m34 MAT(m,2,3)
#define m41 MAT(m,3,0)
#define m42 MAT(m,3,1)
#define m43 MAT(m,3,2)
#define m44 MAT(m,3,3)

  GLdouble det;
  GLdouble d12, d13, d23, d24, d34, d41;
  GLdouble tmp[16];		/* Allow out == in. */

  /* Inverse = adjoint / det. (See linear algebra texts.) */

  /* pre-compute 2x2 dets for last two rows when computing */
  /* cofactors of first two rows. */
  d12 = (m31 * m42 - m41 * m32);
  d13 = (m31 * m43 - m41 * m33);
  d23 = (m32 * m43 - m42 * m33);
  d24 = (m32 * m44 - m42 * m34);
  d34 = (m33 * m44 - m43 * m34);
  d41 = (m34 * m41 - m44 * m31);

  tmp[0] = (m22 * d34 - m23 * d24 + m24 * d23);
  tmp[1] = -(m21 * d34 + m23 * d41 + m24 * d13);
  tmp[2] = (m21 * d24 + m22 * d41 + m24 * d12);
  tmp[3] = -(m21 * d23 - m22 * d13 + m23 * d12);

  /* Compute determinant as early as possible using these cofactors. */
  det = m11 * tmp[0] + m12 * tmp[1] + m13 * tmp[2] + m14 * tmp[3];

  /* Run singularity test. */
  if (det == 0.0) {
    /* printf("invert_matrix: Warning: Singular matrix.\n"); */
    /* 	  memcpy(out,_identity,16*sizeof(double)); */
  } else {
    GLdouble invDet = 1.0 / det;
    /* Compute rest of inverse. */
    tmp[0] *= invDet;
    tmp[1] *= invDet;
    tmp[2] *= invDet;
    tmp[3] *= invDet;

    tmp[4] = -(m12 * d34 - m13 * d24 + m14 * d23) * invDet;
    tmp[5] = (m11 * d34 + m13 * d41 + m14 * d13) * invDet;
    tmp[6] = -(m11 * d24 + m12 * d41 + m14 * d12) * invDet;
    tmp[7] = (m11 * d23 - m12 * d13 + m13 * d12) * invDet;

    /* Pre-compute 2x2 dets for first two rows when computing */
    /* cofactors of last two rows. */
    d12 = m11 * m22 - m21 * m12;
    d13 = m11 * m23 - m21 * m13;
    d23 = m12 * m23 - m22 * m13;
    d24 = m12 * m24 - m22 * m14;
    d34 = m13 * m24 - m23 * m14;
    d41 = m14 * m21 - m24 * m11;

    tmp[8] = (m42 * d34 - m43 * d24 + m44 * d23) * invDet;
    tmp[9] = -(m41 * d34 + m43 * d41 + m44 * d13) * invDet;
    tmp[10] = (m41 * d24 + m42 * d41 + m44 * d12) * invDet;
    tmp[11] = -(m41 * d23 - m42 * d13 + m43 * d12) * invDet;
    tmp[12] = -(m32 * d34 - m33 * d24 + m34 * d23) * invDet;
    tmp[13] = (m31 * d34 + m33 * d41 + m34 * d13) * invDet;
    tmp[14] = -(m31 * d24 + m32 * d41 + m34 * d12) * invDet;
    tmp[15] = (m31 * d23 - m32 * d13 + m33 * d12) * invDet;

    memcpy(out, tmp, 16 * sizeof(GLdouble));
  }

#undef m11
#undef m12
#undef m13
#undef m14
#undef m21
#undef m22
#undef m23
#undef m24
#undef m31
#undef m32
#undef m33
#undef m34
#undef m41
#undef m42
#undef m43
#undef m44
#undef MAT
}

void CGlObjLoader::DrawModel(void)
{

  mode = GLM_NONE;		/* reset mode */

  //if (smooth)
  mode = mode | GLM_SMOOTH;
  //    else
  //        mode = mode | GLM_FLAT;

  //  if (two_sided)
  mode = mode | GLM_2_SIDED;

  //if (material)
  mode = mode | GLM_MATERIAL;
  //    else
  //        mode = mode | GLM_COLOR;

  // if (textured && material)
  mode = mode | GLM_TEXTURE;

  glPushMatrix();
  if (pmodel)
    glmDraw(pmodel, mode);
  glPopMatrix();
}

void CGlObjLoader::Display(void)
{


  /*    GLint viewport[4]; */
  /*255
    int jitter;

    glGetIntegerv (GL_VIEWPORT, viewport);

    glClear(GL_ACCUM_BUFFER_BIT);
    for (jitter = 0; jitter < ACSIZE; jitter++) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    accPerspective (50.0,
    (GLdouble) viewport[2]/(GLdouble) viewport[3],
    1.0, 15.0, j8[jitter].x, j8[jitter].y, 0.0, 0.0, 1.0);
    DrawModel();
    glAccum(GL_ACCUM, 2551.0/ACSIZE);
    }
    glAccum (GL_RETURN, 1.0);
    glFlush();
  */

  //if (lighting) {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //    } else {
  //        glDisable(GL_LIGHTING);
  //        glDisable(GL_LIGHT0);
  //    }


  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();

  glLoadIdentity();
  glTranslatef(0, 0, -0.6);	/* to center object down Z */



  glRotatef(roll, 0.0f, 0.0f , 1.0f);
  glRotatef(yaw, 0.0f, 1.0f, 0.0f);
  glRotatef(pitch, 1.0f, 0.0f, 0.0f);

  glMultMatrixd(_matrix);

  //	if (show_axis)
  //	    DrawAxis(1.0f);
  //	if (wireframe)		/* if Wireframe is checked */
  //	    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	/* draw wireframe */
  //	else			/* else */
  //	    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	/* draw filled polygons */

  DrawModel();
  //glTranslatef(0, 0, 0.3);	/* to center object down Z */
  glPopMatrix();

  //glFlush();
  glutSwapBuffers();


  frontBuffer =  cv::Mat(480,640,CV_8UC3);
  depthBuffer =  cv::Mat(480,640,CV_32F);

  //    cv::Mat tempFront(480,640,CV_8UC3);
  //    cv::Mat depthFront(480,640,CV_32F);

  glReadPixels(0,0,frontBuffer.cols, frontBuffer.rows, GL_BGR, GL_UNSIGNED_BYTE , frontBuffer.data);
  glReadPixels(0,0,depthBuffer.cols, depthBuffer.rows, GL_DEPTH_COMPONENT , GL_FLOAT,depthBuffer.data);

  //    tempFront.copyTo(*frontBuffer);
  //    depthFront.copyTo(*depthBuffer);


  cv::flip(frontBuffer, frontBuffer, 0);
  cv::flip(depthBuffer, depthBuffer, 0);

  depthBuffer = depthBuffer * 1050;

  depthBuffer.convertTo(depthBuffer, CV_16U);

  //one = cv::Mat(480,640, CV_8U);
  cv::Mat one = cv::Mat::ones(480,640, CV_16U) * 1050;

  depthBuffer = one  - depthBuffer;

  cv::imwrite("test.png",frontBuffer);
  cv::imwrite("depth.png",depthBuffer);
  //std::cout << depthBuffer << std::endl;
}

cv::vector<cv::Mat*> CGlObjLoader::getAppearance(double r, double p, double y){
  roll = r;
  pitch = p;
  yaw = y;

  Reshape(640, 480);
  Display();

  cv::Mat* app = new cv::Mat(frontBuffer);
  cv::Mat* depth = new cv::Mat(depthBuffer);

  cv::vector<cv::Mat*> appearance(0);
  appearance.push_back(app);
  appearance.push_back(depth);

  glmDelete(pmodel);

  pmodel = NULL;
  
  return appearance;
}

cv::vector<cv::Mat*> CGlObjLoader::getAppearance(const double* angle){
  roll = angle[0];
  pitch = angle[1];
  yaw = angle[2];

  Reshape(640, 480);
  //for(int i = 0; i < 20; ++i)
  Display();

  cv::Mat* app = new cv::Mat(frontBuffer);
  cv::Mat* depth = new cv::Mat(depthBuffer);

  cv::vector<cv::Mat*> appearance(0);
  appearance.push_back(app);
  appearance.push_back(depth);

  return appearance;
}
