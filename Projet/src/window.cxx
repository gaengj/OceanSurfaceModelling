#include <cmath>
#include <cstring>
#include <ctime>

#include <iostream>
#include <sstream>
#include <vector>

#include "gl_defs.hxx"

#include "camera.hxx"
#include "window.hxx"

Ocean *ocean;
int    mainwindow;

namespace Window {

  /** Permet le déplacement dans la scène 3D */
  Camera* camera;

  /** Permet de gérer la fréquence d'affichage */
  int             frames(-1);
  int             fps;
  int             fps_goal;
  std::string     fps_str;
  time_t          sleep_avant(0);
  int             t;
  struct timespec tim1, tim2;

  /** Nombres d'éléments de la scène et coordonées du maillage  */
  int                  nxOcean;
  int                  nyOcean;
  std::vector<double*> vertexOceanX;
  std::vector<double*> vertexOceanY;

  void draw() {
    if(glutGet(GLUT_ELAPSED_TIME) - t >= 1000) fps_action();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera->translation();

    gluLookAt(camera->getX(), camera->getY(), camera->getZ(),
        camera->getSightX(), camera->getSightY(), camera->getSightZ(),
        0, 1, 0);

    draw_ocean();
    draw_fps();

    glutSwapBuffers();
    glutPostRedisplay();

    nanosleep(&tim1, &tim2);

    frames++;
  }

  void draw_fps() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2f(550, 460);
    char        buf[15] = "FPS : ";
    const char* p(buf);
    strcat(buf, fps_str.c_str());
    do glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *p); while(*(++p));
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
  }

  void draw_ocean() {
    // Réalise effectivement l'étape de calcul
    ocean->compute();

    // Impose la couleur d'affichage de la grille
    glColor3ub(82, 184, 255);

    // Parcours la scène dans la direction x afin de récupérer
    // les colonnes à afficher
    for(int x = 0 ; x < nxOcean ; x++) {
      // Récupère les données depuis la classe Ocean
      ocean->gl_VertexArrayY(x, vertexOceanY[x]);
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3, GL_DOUBLE, 0, vertexOceanY[x]);
      glDrawArrays(GL_LINE_STRIP, 0, nyOcean+1);
      glDisableClientState(GL_VERTEX_ARRAY);
    }

    // Parcours la scène dans la direction y afin de récupérer
    // les lignes à afficher
    for(int y = 0 ; y < nyOcean ; y++) {
      // Récupère les données depuis la classe Ocean
      ocean->gl_VertexArrayX(y, vertexOceanX[y]);
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3, GL_DOUBLE, 0, vertexOceanX[y]);
      glDrawArrays(GL_LINE_STRIP, 0, nxOcean+1);
      glDisableClientState(GL_VERTEX_ARRAY);
    }
    glColor3ub(0, 0, 0);
  }

  void fps_action() {
    t      = glutGet(GLUT_ELAPSED_TIME);
    fps    = frames;
    frames = 0;
    std::ostringstream oss;
    oss << fps;
    fps_str = oss.str();
    sleep_avant  = tim1.tv_nsec;
    tim1.tv_nsec = (int)(((double)(1.0/fps_goal) - (double)(1.0/fps))*pow(10, 9) + sleep_avant) % 1000000000;
  }

  void init(int width, int height, std::string titre, int argc, char** argv, std::string keyboard, int p_fps, float translation_speed) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(width, height);
    mainwindow = glutCreateWindow(titre.c_str());
    glEnable(GL_MULTISAMPLE);
    Camera::KEYBOARD mode = keyboard=="azerty" ? Camera::AZERTY : Camera::QWERTY;
    camera = new Camera(mode, -100, 100, -100, 4*M_PI/7, M_PI/4, 0.01, translation_speed, WIDTH, HEIGHT);
    fps_goal = p_fps;
  }

  void keyboard(unsigned char key, int x, int y) {
    camera->setKeyboard(key, true);
  }

  void keyboardUp(unsigned char key, int x, int y) {
    camera->setKeyboard(key, false);
  }

  void launch() {
    tim1.tv_sec  = 0;
    tim1.tv_nsec = 0;
    t = glutGet(GLUT_ELAPSED_TIME);

    // Initialise le tableau de données à afficher
    nxOcean = ocean->getNx();
    nyOcean = ocean->getNy();
    for(int i=0 ; i<nyOcean ; i++) {
      vertexOceanX.push_back(new double[3*(nxOcean+1)]);
    }
    for(int i=0 ; i<nxOcean ; i++) {
      vertexOceanY.push_back(new double[3*(nyOcean+1)]);
    }

    // Initialise les tableaux nécessaires aux tranferts de données
    for(int x=0 ; x<nxOcean ; x++) {
      ocean->init_gl_VertexArrayY(x, vertexOceanY[x]);
    }
    for(int y=0 ; y<nyOcean ; y++) {
      ocean->init_gl_VertexArrayX(y, vertexOceanX[y]);
    }

    // Réalise l'affichage
    glClearColor(1, 1, 1, 1);
    glutReshapeFunc(reshape);
    // La fonction draw permet de définir les procédures d'affichage
    glutDisplayFunc(draw);
    glutPassiveMotionFunc(mouseMove);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutWarpPointer(WIDTH/2, HEIGHT/2);
    glutIdleFunc(rendering);
    glutMainLoop();
  }

  void mouseMove(int x, int y) {
    camera->rotation(x, y);
    if(x>=WIDTH || x<=0 || y>=HEIGHT || y<=0) {
      glutWarpPointer(WIDTH/2, HEIGHT/2);
      camera->setMouse(WIDTH/2, HEIGHT/2);
    }
  }

  void quit() {
    for(int i=0 ; i<nyOcean ; i++) delete[] vertexOceanX[i];
    for(int i=0 ; i<nxOcean ; i++) delete[] vertexOceanY[i];
  }

  void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, float(width)/float(height), 1, 10*sqrt(pow(ocean->getLy(), 2) + pow(ocean->getLx(), 2)));
  }

  void rendering(){
     /* Boucle Temporelle */
    ocean->compute();
    ocean->t_increment();
  }

}


