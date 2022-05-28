#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <checkpoint.h>
#include "game.h"
#include "utils.h"

int main()
{   
///////// affichage et initialisation ///////////
sf::ContextSettings settings;
settings.antialiasingLevel = 32;
sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!"); // on définit les paramètre de la fenêtre
sf::View myView(sf::Rect(0.f,0.f,16000.f,9000.f));
window.setView(myView);
///////// gestion du temps ////////////////
float FPS = 60; // Nombre d'images par seconde
Game myGame("../repository/Images/background.png",{{5000,5600},{1000,100},{12000,5300},{300,5300}}); // on initialise le jeu avec la liste de check point souhaitée
sf::Time refreshTime = sf::microseconds(1e6/FPS);
window.setFramerateLimit(FPS);
//horloge depuis le début du jeu
sf::Clock globalClock;
//horloge réinitialisée à chaque frame
sf::Clock refreshClock;
//temps de la physique du jeu
sf::Time physicsTime = sf::Time::Zero;
/////////////////////////////////////////////
int nombre_joueur; // arguments de la fonction addPod()
int nombre_adversaire;
int choix1; // apparence des vaisseaux des joueurs
int choix2;
/////////initilisation du jeu ////////////
int interface=0; // interface 0 correspond au menu

while (window.isOpen())
{
    sf::Event event;
    if(interface==0){
        while(interface==0){
            // on charge la fenêtre du menu
            sf::Texture fondTexture;
            fondTexture.loadFromFile("../repository/Images/map3.png");  
            sf::Sprite fondSprite;
            fondSprite.setTexture(fondTexture);
            auto rec = fondSprite.getGlobalBounds();
            fondSprite.scale(sf::Vector2f(16000/rec.width, 9000/rec.height));
            // on charge les apparences supplémentaires
            sf::Texture droide_;
            droide_.loadFromFile("../repository/Images/droide.png");
            sf::Sprite droide;
            droide.setTexture(droide_);
            setOriginToCenter(droide);
            scaleToMaxSize(droide,10,10);
            droide.setPosition(1000,6500);
            int dro=0; // interrupteurs pour laisser les images en places
            sf::Text text1;
            sf::Font police_affichage;
            police_affichage.loadFromFile("../repository/Fredoka-Bold.ttf");
            text1.setFont(police_affichage);
            text1.setCharacterSize(500);
            setTextCenterPosition(text1, 5000,4000);
            text1.setString("Choisir votre mode ? \nA=1vs5\nB=1vs1\nC= DEMO"); 
            sf::Text text2;
            text2.setFont(police_affichage);
            text2.setCharacterSize(500);
            setTextCenterPosition(text2, 5000,8000);
            text2.setString("Then press SPACE"); // on distingue 2 textes pour pouvoir en mettre certains en surbrillance de manière indépendante

            while (window.pollEvent(event))
            {
                // le joueur sélection son mode de jeu
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    nombre_joueur=1;
                    nombre_adversaire=6;
                    choix1=0; // apparence des vaisseaux des joueurs
                    choix2=1;
                    text2.setFillColor(sf::Color(255,0,0,255));
                    dro=1;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
                {
                    nombre_joueur=2;
                    nombre_adversaire=2;
                    choix1=0; // apparence des vaisseaux des joueurs
                    choix2=1;
                    text2.setFillColor(sf::Color(255,0,0,255));
                    dro=1;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
                    // C = demo avec tous les vaisseaux
                    nombre_joueur=0;
                    nombre_adversaire=6;
                    choix1=0; // apparence des vaisseaux des joueurs
                    choix2=1;
                    text2.setFillColor(sf::Color(255,0,0,255));
                    dro=1;
                } 
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    interface=1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    interface=1; 
                    // interface 1 correspond à notre jeu 
                }
            }
            if(dro==1) // c'est à dire que le joueur a sélectionné son mode de jeu
            {
                scaleByRadius(droide,300000); 
            }
            window.clear();
            ////////////////////////////////////////////////////////////////////////:
            window.setVerticalSyncEnabled(false);
            window.clear();
            window.draw(fondSprite);
            window.draw(text1);
            window.draw(text2); 
            window.draw(droide);  
            window.display(); // on supprime tout ce qui est affiché 
            // display est essentiel lors du passage d'un menu à l'autre
        }
        // WARNING il faut bien se placer en dehors de la boule d'affichage autrements les informations ne sont pas prises en compte
        myGame.addPod(choix1,nombre_joueur,choix2,nombre_adversaire); // on mets à jour la fonction selon le mode de jeu choisi par le joueur
    }
    if(interface==1) // on affiche le jeu 
    {
        while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape ))
                    {
                        window.close();
                    }
                }
            //si on a dépassé le refreshTime depuis la dernière frame
        if (refreshClock.getElapsedTime() >= refreshTime)
            {
                //réinitialise l'horloge qui mesure le temps entre les frames
                refreshClock.restart();
                //récupère le temps écoulé depuis le début du jeu
                sf::Time frameTime = globalClock.getElapsedTime();
                //si on a dépassé le temps de la physique
                if (frameTime > physicsTime)
                {
                    //met à jour les sprite au temps de la physique
                    myGame.updateGraphics(physicsTime);
                    //fait avancer la physique d'un pas de temps
                    myGame.updatePhysics();
                    physicsTime += PHYSICS_TIME_STEP;
                    //reprend le temps écoulé depuis le début pour rester précis
                    frameTime = globalClock.getElapsedTime();
                }
                //met à jour les sprites au temps actuel
                myGame.updateGraphics(frameTime);
                window.clear();
                // on affiche tous les arguments définis comme drawable dans le fichier game
                window.draw(myGame);
                window.display(); // on supprime tout ce qui est affiché
            }
    }
} 
return 0;
}
