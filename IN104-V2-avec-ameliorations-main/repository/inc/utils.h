#ifndef INC_UTILS_H
#define INC_UTILS_H

#include <SFML/Graphics.hpp>

///////// moi  ////////////// 
// void setOriginToCenter(sf::Sprite &object);
// void setOriginToCenter(sf::Shape &object);

// void scaleToMinSize( sf::Sprite &object, double x, double y);
// void scaleToMaxSize( sf::Sprite &object, double x, double y);

// si on veut faire initialisation avec une classe quelquconque dans pour dire ou ca va marcher
// template<class T>
// void setOriginToCenter( T &object)
/////// fin de moi ////////////


void setOriginToCenter(sf::Sprite &object);
void setOriginToCenter(sf::Shape &object);

void scaleToMinSize(sf::Sprite &sp, double size_x, double size_y);
void scaleToMaxSize(sf::Sprite &sp, double size_x, double size_y);
void scaleByRadius(sf::Sprite &sp, int radius);

void setTextCenterPosition(sf::Text &txt, sf::Vector2f center);

float distance_point(sf::Vector2f A, sf::Vector2f B);

void setTextCenterPosition(sf::Text &Sprite, float x, float y);
float norme(sf::Vector2f v);

#endif