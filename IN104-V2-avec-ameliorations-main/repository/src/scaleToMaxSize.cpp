#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef INC_TAILLE_H
#define INC_TAILLE_H


void scaleToMaxSize( sf::Sprite &object, sf::Sprite &cible)
{

auto sizeObject = object.getGlobalBounds(); // type auto si on sait pas ce qui arrive en sortie
// on veut hauteur ou largeur cible 
// get global bounds se refere à la longueur actuelle du sprite
// get local bounds se refere à la position initiale, sans toutes les transformations qui ont été subies par l'objet. 
const int w = sizeObject.width;
const int h = sizeObject.height;

auto sizeCible = cible.getGlobalBounds();
const int W = sizeCible.width;
const int H = sizeCible.height;


object.setScale( sf::Vector2f(std::max(H/h,W/w)*w, std::max(H/h,W/w)*h) );

}

#endif