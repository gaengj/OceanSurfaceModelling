/** Création d"un espace de nom dédié à l'affichage :
 *    - traitement les évènements clavier et souris
 *    - affichage de la houle et du framerate.
 */

#ifndef WINDOWHPP
#define WINDOWHPP

#define WIDTH  640
#define HEIGHT 480

#include "Ocean.h"
#include <GL/glut.h>

extern Ocean *ocean;
extern int    mainwindow;

namespace Window {

  /** Fonction principale d'affichage */
  void draw();

  /** Affichage du framerate */
  void draw_fps();

  /** Afficahe de l'océan */
  void draw_ocean();

  /** Impose/limite la fréquence d'affichage
   * @param[in] fps fréquence d'affichage
   */
  void setFPS(int);

  /** Calcul d'un temps de pause nécessaire dans l'affichage
   *  pour respecter les FPS
   */
  void fps_action();

  /** Initialialisation de la fenêtre d'affichage
   * @param[in] width     largeur de la fenêtre
   * @param[in] height    hauteur de la fenêtre
   * @param[in] title     titre de la fenêtre
   * @param[in] argc      nombre d'arguments d'entrée
   * @param[in] argv      tableau des arguments d'entrée
   * @param[in] keyboard  type du clavier
   * @param[in] p_fps     fréquence d'affichage cible
   * @param[in] translation_speed
   */
  void init(int, int, std::string, int, char**, std::string keyboard,
      int FPS, float translation_speed);

  /** Gestion des évenments claviers (appui)
   *  @param[in] key touche appuyée
   *  @param[in] x   position horizontale de la souris
   *  @param[in] y   position verticale de la souris
   */
  void keyboard(unsigned char, int, int);

  /** Gestion des évenments claviers (relachement)
   *  @param[in] key touche appuyée
   *  @param[in] x   position horizontale de la souris
   *  @param[in] y   position verticale de la souris
   */
  void keyboardUp(unsigned char, int, int);

  /** Gestion des évenments souris
   *  @param[in] x   position horizontale de la souris
   *  @param[in] y   position verticale de la souris
   */
  void mouseMove(int, int);

  /** Execute l'affichage :
   *   - intialise les variables
   *   - écoute les évènements claviers et souris
   *   - initialise l'affichage
   */
  void launch();

  /** Arrête l'affichage
  */
  void quit();

  /** Modifie la perspective */
  void reshape(int, int);

  /** Effectue la boucle temporelle de rendu */
  void rendering();
}

#endif
