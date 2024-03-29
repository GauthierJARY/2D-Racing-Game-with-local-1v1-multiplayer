#include "pod.h"
#include <SFML/System/Vector2.hpp>
#include "game.h"
#include "utils.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <string>


Decision::Decision(sf::Vector2f target, float power) : target_(target), power_(power) 
{
};

Pod::Pod(sf::Vector2f pos, float angle, sf::Vector2f vel) : pos_(pos), vel_(vel), angle_(angle)
{
};

/////////////////// fonction décision /////////////////////////////:
bool initialisation=true;
int vitesse=50;
Decision Pod::getDecision(GameInfos gamesInfos ) const
{
// choix commandes, il faudra le donner en argumment de la fonction Pod
sf::Vector2f position;
if (mode==0){
    position=gamesInfos.cpPositions_[nextCP_];
    // on prend en argument le prochain checkpoint comme cible de la décision
    // nextcp est le prochain cp a atteindre 
    return Decision(position,100); // position du prochaine checkpoint et a quelle puissance on y va
    }

bool left=false;
bool right=false;
bool up=false;
bool down=false; 
// on récupère les choix du joueurs (pour le moments pour tous les vaisseaux)
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){left=true;}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){right=true;}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){up=true;}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){down=true;}
// on ppourra inclure une condition ou le choix des commandes n'impacte qu'un seul vaisseau, 
// puis intégrer une 2c2 avec touches ZQSD. 
if(mode==1){
    position.x=pos_.x;
    position.y=pos_.y;
// les pods sont positionnés sur la ligne de départ
    if(left ||right || up || down){
        if(left){
            if(pos_.x-100>0){position.x=pos_.x-100;}
            else{position.x=0;}
        }
        if(right){
            if(pos_.x+100<16000){position.x=pos_.x+100;}
            else{position.x=16000;}
        }
        if(up){
            if(pos_.y-100>0){position.y=pos_.y-100;}
            else{position.y=0;}
        }
        if(down){
            if(pos_.y+100<9000){position.y=pos_.y+100;}
            else{position.y=9000;}
        }
        vitesse=vitesse+1;
        vitesse=std::min(vitesse,100);
    }
    else{
        vitesse=vitesse-0.8*vitesse; // rajouter un coefficient de frottement air / neige / eau / espace
        vitesse=std::max(vitesse,0);
        position.x=pos_.x;
        position.y=pos_.y;
        }
    printf("vitesse = %d\n", vitesse);
    printf("position en x:%f et en y:%f\n",position.x,position.y);
    return Decision(position,vitesse); // position du prochaine checkpoint et a quelle puissance on y va
    }


bool q=false;
bool d=false;
bool z=false;
bool s=false; 
// on récupère les choix du joueurs (pour le moments pour tous les vaisseaux)
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){q=true;}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){d=true;}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){z=true;}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){s=true;}
// on ppourra inclure une condition ou le choix des commandes n'impacte qu'un seul vaisseau, 
// puis intégrer une 2c2 avec touches ZQSD. 
if(mode==2){
    position.x=pos_.x;
    position.y=pos_.y;
// les pods sont positionnés sur la ligne de départ
    if(q || d || z || s){
        if(q){
            if(pos_.x-100>0){position.x=pos_.x-100;}
            else{position.x=0;}
        }
        if(d){
            if(pos_.x+100<16000){position.x=pos_.x+100;}
            else{position.x=16000;}
        }
        if(z){
            if(pos_.y-100>0){position.y=pos_.y-100;}
            else{position.y=0;}
        }
        if(s){
            if(pos_.y+100<9000){position.y=pos_.y+100;}
            else{position.y=9000;}
        }
        vitesse=vitesse+1;
        vitesse=std::min(vitesse,100);
    }
    else{
        vitesse=vitesse-0.8*vitesse; // rajouter un coefficient de frottement air / neige / eau / espace
        vitesse=std::max(vitesse,0);
        position.x=pos_.x;
        position.y=pos_.y;
        }
    printf("vitesse = %d\n", vitesse);
    printf("position en x:%f et en y:%f\n",position.x,position.y);
    return Decision(position,vitesse); // position du prochaine checkpoint et a quelle puissance on y va
    }
};



