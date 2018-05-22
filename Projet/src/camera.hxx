#ifndef CAMERAHPP
#define CAMERAHPP

#include <cmath>
#include <map>


/** Défini le comportement de la caméra en fonction des actions
 * de la souris ou du clavier
 */
class Camera {

  public:
    /** Précise les claviers utilisables */
    enum KEYBOARD {AZERTY, QWERTY};

    /** Unique constructeur possible
     * @param[in]
     */
    Camera(KEYBOARD,
        float, float, float,
        float, float, float, float, int, int);
    ~Camera() {}

    int   getMouseX() { return mouse_x; }
    int   getMouseY() { return mouse_y; }
    float getSightX() { return X + sin(theta)*sin(psi); }
    float getSightY() { return Y + cos(psi); }
    float getSightZ() { return Z + cos(theta)*sin(psi); }
    float getX()      { return X; }
    float getY()      { return Y; }
    float getZ()      { return Z; }

    void setKeyboard(int i, bool state) { keys[i] = state; }
    void setMouse(int x, int y)         { mouse_x = x; mouse_y = y; }
    void setX(float p_X)                { X = p_X; }
    void setY(float p_Y)                { Y = p_Y; }
    void setZ(float p_Z)                { Z = p_Z; }

    void rotation(int, int);
    void translation();

  private:
    /** Créer un mapping entre les touches et
     * les directions de déplacements
     */
    enum    DIR {FORWARD, BACKWARD, LEFT, RIGHT};
    typedef std::map<DIR, int> k_map;

    k_map    key_map;
    /** Type de clavier */
    KEYBOARD keyboard;
    /** Identifie les touches appuyées */
    bool     keys[255];

    /** Centre x de la sphère de visualisation */
    float    X;
    /** Centre y de la sphère de visualisation */
    float    Y;
    /** Centre z de la sphère de visualisation */
    float    Z;
    /** Orientation psi dans le repère de la sphère */
    float    psi;
    /** Orientation theta dans le repère de la sphère */
    float    theta;
    /** Abscisse de la souris */
    int      mouse_x;
    /** Ordonnée de la souris */
    int      mouse_y;
    /** Sensibilité de la souris  */
    float    rotation_speed;
    /** Sensibilite du clavier */
    float    translation_speed;
    /** Mesure le temps enre 2 interactions */
    int      time;

};

#endif
