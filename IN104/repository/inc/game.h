#ifndef INC_GameLOGIC_H
#define INC_GameLOGIC_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <vector>
#include <cmath>
#include "checkpoint.h"
#include "pod.h"

const unsigned int NUMBER_OF_LAPS = 3;
const float FRICTION_COEFF = 0.85;
const float ROTA_MAX = M_PI/10.;
const sf::Time PHYSICS_TIME_STEP = sf::milliseconds(100);
const std::string IMAGES_PATH = "../repository/Images/";
const std::string FONT_PATH = "../repository/";

struct GameInfos
{
    std::vector<Pod> pods;
    std::vector<sf::Vector2f> cpPositions_;
};

class Game : public sf::Drawable
{
    public :
    Game(); //create a Game with 2 to 8 checkpoints at random positions (they shouldn't overlap)
    Game(std::string fond,std::vector<sf::Vector2f> checkpointsPositions); //create a Game with predefined checkpoints positions

    void addPod(int choix, int nb_joueur, int choix2, int adversaire); //can add various arguments here to chose the apparence or the decision making type of the pod
    void updatePhysics();
    void updateGraphics(sf::Time frameTime); //change pods sprites positions and rotations depending on the frame time

    // private :
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;

    std::vector<Pod> pods_;
    std::vector<sf::Texture> podsTextures_;
    std::vector<sf::Sprite> podsSprites_;
    std::vector<sf::Vector2f> cpPositions_;
    FinalCheckPoint finalCP_;
    std::vector<CheckPoint> otherCPs_;

    sf::Time lastFrameTime;
    sf::Time physicsTime;   
};

#endif