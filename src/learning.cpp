#pragma GCC diagnostic ignored "-fpermissive"

#include <HFMD_core/CRForest.h>
//#include "util.h"

using namespace std;

int main(int argc, char* argv[]){

    //config file
    CConfig		conf;	 // setting

    // init glut (for learn from obj file)
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);	/*  Window Size If We Start In Windowed Mode */
    glutCreateWindow("Wavefront Obj File Viewer");

    //read and check argument
    if(argc < 2) {
        cout << "Usage: ./learning [config.xml] [off_tree] [learningMode]"<< endl;
        conf.loadConfig("config.xml");
    } else
        conf.loadConfig(argv[1]);

    if(argc < 3)
        conf.off_tree = 0;
    else
        conf.off_tree = atoi(argv[2]);

    if(argc > 4)
        conf.learningMode = atoi(argv[3]);

    //create tree directory
    string tpath(conf.treepath);
    tpath.erase(tpath.find_last_of(PATH_SEP));
    string execstr = "mkdir ";
    execstr += tpath;
    system( execstr.c_str() );

    // create random forest class
    CRForest forest(conf);

    // learning
    forest.learning();

    return 0;
}
