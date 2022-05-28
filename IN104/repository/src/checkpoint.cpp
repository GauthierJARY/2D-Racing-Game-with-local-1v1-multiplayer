#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "checkpoint.h"
#include <vector>
#include <SFML/Window.hpp>
#include <iostream>
#include "utils.h"
#include "game.h"

// on définit une classe checkpoint, basée sur un cercle standardisé pour tous les checkpoints à venir
// l'idée est de manipuler uniquement l'outil checkpoint et ses fonctionnalités sans se soucier des fonctions et de l'apparence à chaque création.
CheckPoint::CheckPoint(sf::Vector2f center, unsigned int id) : circle_(500, 500)
{
    setOriginToCenter(circle_);
    circle_.setPosition(center);
    circle_.setFillColor(sf::Color(0,0,0,63));
    circle_.setOutlineColor(sf::Color(0,0,0));
    circle_.setOutlineThickness(50);

    font_.loadFromFile("../repository/Fredoka-Bold.ttf");
    fillingText_ = sf::Text(std::to_string(id),font_, 500);
    fillingText_.setOutlineThickness(50);

    setTextCenterPosition(fillingText_, center);

    // le checkpoint aura donc une apparence de cercle avec un numéro selon l'argument d'entrée
};

// on définit une fonction draw associée à cette classe
void CheckPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circle_, states);
    target.draw(fillingText_);
};

// on définit de nouveau une fonction pour cette classe. 
// On utilise les fonctions associées aux classes qui ont servi à créer le checkpoint, 
// mais cela va désormais être une fonction de cette classe précisemment. 
sf::Vector2f CheckPoint::getPosition()
{
    return circle_.getPosition();
}

// de manière analogue pour la calsse checkpoint final, différente car basée sur un import d'image Sprite
FinalCheckPoint::FinalCheckPoint(sf::Vector2f center) : circle_(500, 500)
{
    setOriginToCenter(circle_);
    circle_.setPosition(center);
    circle_.setFillColor(sf::Color(255,255,255,63));
    circle_.setOutlineColor(sf::Color(0,0,0));
    circle_.setOutlineThickness(50);
    fillingTexture_ = sf::Texture();
    fillingTexture_.loadFromFile("../repository/Images/checkeredFlag.png");  
    fillingSprite_ = sf::Sprite(fillingTexture_);
    fillingSprite_.setPosition(center);
    setOriginToCenter(fillingSprite_);
    scaleByRadius(fillingSprite_,500);
    
};

// idem que pour la classe Checkpoint
void FinalCheckPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circle_, states);
    target.draw(fillingSprite_, states);
};

sf::Vector2f FinalCheckPoint::getPosition()
{
    return circle_.getPosition();
}