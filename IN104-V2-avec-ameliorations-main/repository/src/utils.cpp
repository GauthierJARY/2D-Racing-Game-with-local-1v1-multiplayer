#include "utils.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>

void setOriginToCenter(sf::Sprite &object)
{
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2., rect.height/2.);
}

void setOriginToCenter(sf::Shape &object)
{
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2., rect.height/2.);
}

void scaleToMinSize(sf::Sprite &sp, double size_x, double size_y)
{
    double scalingFactor = std::max(size_x/sp.getTextureRect().width, size_y/sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void scaleToMaxSize(sf::Sprite &sp, double size_x, double size_y)
{
    double scalingFactor = std::min(size_x/sp.getTextureRect().width, size_y/sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void scaleByRadius(sf::Sprite &sp, int radius)
{
    double scalingFactor = 2*radius/std::sqrt(sp.getTextureRect().width*sp.getTextureRect().width + sp.getTextureRect().height*sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void setTextCenterPosition(sf::Text &txt, sf::Vector2f center)
{
    sf::Vector2f offset;
    offset.x = txt.getPosition().x - txt.getGlobalBounds().left - txt.getGlobalBounds().width/2.;
    offset.y = txt.getPosition().y - txt.getGlobalBounds().top - txt.getGlobalBounds().height/2.;

    txt.setPosition(center + offset);
}

float distance_point(sf::Vector2f A, sf::Vector2f B){
    return std::sqrt(pow(A.x-B.x,2)+pow(A.y-B.y,2));
}

float norme(sf::Vector2f v){
    return sqrt(v.x*v.x+v.y*v.y);
}


void setTextCenterPosition(sf::Text &Sprite, float x, float y){
    sf::FloatRect textRect = Sprite.getLocalBounds();
    Sprite.setOrigin(textRect.left + textRect.width/2.0f,
    textRect.top  + textRect.height/2.0f);
    Sprite.setPosition(x,y);
}

////////////// code 1ere version ////////////////////////////////////////////////////////////////////

/*
#include <SFML/Graphics.hpp>
#include "utils.h"

void setOriginToCenter(sf::Sprite &object)
{
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2, rect.height/2);
}

void setOriginToCenter(sf::Shape &object)
{
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2, rect.height/2);
}


void scaleToMaxSize(sf::Sprite &object, double x, double y)
{
auto sizeObject = object.getGlobalBounds(); // type auto si on sait pas ce qui arrive en sortie
// on veut hauteur ou largeur cible 
// get global bounds se refere à la longueur actuelle du sprite
// get local bounds se refere à la position initiale, sans toutes les transformations qui ont été subies par l'objet. 
double w = sizeObject.width;
double h = sizeObject.height;
double max_largeur=x/w;
double max_longueur=y/h;
if (max_largeur > max_longueur){
    object.setScale(max_largeur, max_largeur);
}
else{
    object.setScale(max_longueur, max_longueur);
}
}

void scaleToMinSize(sf::Sprite &object, double x, double y)
{
auto sizeObject = object.getGlobalBounds(); // type auto si on sait pas ce qui arrive en sortie
// on veut hauteur ou largeur cible 
// get global bounds se refere à la longueur actuelle du sprite
// get local bounds se refere à la position initiale, sans toutes les transformations qui ont été subies par l'objet. 
double w = sizeObject.width;
double h = sizeObject.height;
double max_largeur=x/w;
double max_longueur=y/h;
if (max_largeur < max_longueur){
    object.setScale(max_largeur, max_largeur);
}
else{
    object.setScale(max_longueur, max_longueur);
}
}

*/

///////////////////////////////////////////////////////////////////////////////////