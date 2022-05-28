#include "game.h"
#include "checkpoint.h"
#include "utils.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "utils.h"


// version Gauthier
Game::Game() : finalCP_({0,0})
{}

Game::Game(std::string fond,std::vector<sf::Vector2f> checkpointsPositions) : finalCP_(checkpointsPositions[0])
{
    cpPositions_=checkpointsPositions; // on récupère l'argument donné à la fonction dans le main
    int i=0;
    int taille= checkpointsPositions.size();
    otherCPs_.reserve(taille-1); // IMPORTANT: on réserve de l'espace mémoire pour ne pas avoir des erreurs de segmentation core dumped. 
    // les variables ne doivent pas être locales car sont utilisées dans plusieurs fonctions 

    for (i=1;i<taille;i++){
        otherCPs_.emplace_back(checkpointsPositions[i],i);
    }
    // affichage du fond de la partie
    backgroundTexture_.loadFromFile(fond); // affichage selon la carte choisie par le joueur, en arguments dans le main.cpp
    backgroundSprite_.setTexture(backgroundTexture_);
    auto rec=backgroundSprite_.getLocalBounds();
    backgroundSprite_.scale(sf::Vector2f(16000/rec.width,9000/rec.height)); // mise à l'échelle de l'image sur notre fenêtre ouverte dans le main.cpp
}

void Game::addPod(int choix1, int nb_joueur, int choix2, int adversaire)
{
    // on réccupère les arguments = éléments choisis par le joueur
    int nombre_j=nb_joueur;
    int choix_user_vaisseaux=choix1;
    int choix_user_vaisseaux2=choix2;
    int nb_pods = adversaire;
    // on réserve de la mémoire IMPORTANT: permet d'éviter les définitions locales et de copier les éléments sans lien avec leurs cases mémoires.
    // Cela permet d'éviter les erreurs de segmentation core dumped.   
    podsSprites_.reserve(nb_pods);
    pods_.reserve(nb_pods);
    podsTextures_.reserve(nb_pods);
    // on importe les textures des vaisseaux = pod
        Pod pod1 = Pod({3000,5600}, 0.f);
    // gestion directe sans copie et donc sans changement d'adresse
    pods_.emplace_back(pod1);
    podsTextures_.emplace_back();
    podsTextures_[0].loadFromFile("/home/ensta/IN104/repository/Images/BSGCylon.png");
        Pod pod2 = Pod({5000,6000}, 0.f);
    pods_.emplace_back(pod2);
    podsTextures_.emplace_back();
    podsTextures_[1].loadFromFile("/home/ensta/IN104/repository/Images/BSGViper.png");
        Pod pod3 = Pod({2000,5620}, 0.f);
    pods_.emplace_back(pod3);
    podsTextures_.emplace_back();
    podsTextures_[2].loadFromFile("/home/ensta/IN104/repository/Images/NMSFighterG.png");
        Pod pod4 = Pod({1000,5630}, 0.f);
    pods_.emplace_back(pod4);
    podsTextures_.emplace_back();
    podsTextures_[3].loadFromFile("/home/ensta/IN104/repository/Images/NMSFighterY.png");
        Pod pod5 = Pod({4000,5640}, 0.f);
    pods_.emplace_back(pod5);
    podsTextures_.emplace_back();
    podsTextures_[4].loadFromFile("/home/ensta/IN104/repository/Images/SWAnakinsPod.png");
        Pod pod6 = Pod({5000,5650}, 0.f);
    pods_.emplace_back(pod6);
    podsTextures_.emplace_back();
    podsTextures_[5].loadFromFile("/home/ensta/IN104/repository/Images/SWMilleniumFalcon.png");
    // les textures = "vaisseaux graphique" et les vaisseaux "physiques" sont rangés dans des listes pour être invoqués ensuite dans d'autres fonctions. 
    // ici il s'agit seulement d'importer les ressources graphiques et initialiser les éléments
    for (int i=0; i<nb_pods; i++){podsSprites_.emplace_back(podsTextures_[i]);}

    for (int i=0; i<nb_pods; i++)
    {
        // on initialise les pods, selon le mode de jeu choisi
        podsSprites_[i].setTexture(podsTextures_[i]);
        setOriginToCenter(podsSprites_[i]);
        scaleToMaxSize(podsSprites_[i], 800,800);
        pods_[i].nextCP_ = 1;
        pods_[i].lapCount_ = 0;
        pods_[i].mode=0; // indique si le controle sera manuel ou non 
        pods_[i].fin=false; // interrupteur pour l'affichage des chronos
    }

    if(nombre_j==1){ 
        // l'initialisation est différentes selon le mode choisi
        pods_[choix_user_vaisseaux].mode=1;}
    if(nombre_j==2){
        pods_[choix_user_vaisseaux].mode=1;
        pods_[choix_user_vaisseaux2].mode=2;
    }
    // affichage coloré pour le débug. 
    //podsSprites_[1].setColor(sf::Color(255,0,0));
    //podsSprites_[0].setColor(sf::Color(0,255,0));
}

// mets à jour les vaisseaux "physiques"
void Game::updatePhysics()
{
if(physicsTime.asSeconds()>1){
    std::vector<Pod> PodsSnapshot = pods_;
    for (Pod &pod : pods_)
    { 
        if(pod.lapCount_<NUMBER_OF_LAPS)
        {
            Decision d = pod.getDecision({pods_, cpPositions_}); // = struct gameInfos qui contient les infos pods et cpPsoitions
            sf::Vector2f target = d.target_;
            float power = d.power_;
            sf::Vector2f diff;
            diff.x = target.x - pod.pos_.x;
            diff.y = target.y - pod.pos_.y;
            // on doit mettre à jour l'angle avant de mettre à jour la target.
            // si jamais la target nest pas réaliste il faut la rédéfinir. 
            float norm_ = norme(diff);
            if(norm_ != 0)
            {
                pod.vel_.x = FRICTION_COEFF*(pod.vel_.x + power*( (target.x - pod.pos_.x) / norme(diff) ) ); 
                // on pourra considérer une FRICTION COEFF différent selon la carte choisie, il faudra simplement le mettre en arguments dans le main
                pod.vel_.y = FRICTION_COEFF*(pod.vel_.y + power*( (target.y - pod.pos_.y) / norme(diff) ) );
            }
            else{pod.vel_ = FRICTION_COEFF*pod.vel_;}

            if(pod.vel_.x != 0)
            {
                if (pod.vel_.x < 0) {pod.angle_ = M_PI + std::atan(pod.vel_.y/pod.vel_.x);}
                else {pod.angle_ = std::atan(pod.vel_.y/pod.vel_.x);}
            }
            pod.pos_ = pod.pos_ + pod.vel_; // incrément de position. La vitesse n'a pas vraiment la dimension d'une vitesse et est seulement une itération

            // on mets à jour les attributs des vaisseaux s'ils passent les checkpoints. 
            // ces informations sont essentielles pour le mode IA car permet de définir quel est le prochain checkpoint à target. 
            if(distance_point(pod.pos_,cpPositions_[pod.nextCP_])<500) // taille du checkpoint, où on considère qu'il vient de valider le passage
            {
                pod.nextCP_+=1;
                if(pod.nextCP_==cpPositions_.size()){
                    pod.nextCP_=0;
                }
                if(pod.nextCP_==1){pod.lapCount_+=1;}
                if(pod.lapCount_==NUMBER_OF_LAPS){pod.fin=true; }// interrupteur pour savoir si la course est finie
            }
        } 
    }   
}
physicsTime += PHYSICS_TIME_STEP;
}

// mets à jour les vaisseaux "graphiques" sur les positions physique calculées précedemment dans la partie UpdatePhysics
void Game::updateGraphics(sf::Time frameTime)
{
    // facteur pour lisser les images 
    // en effet les incréments de rafraichissement des positions physique se fait à temps fixe et il ne faut pas avoir l'impression d'une téléportation
    float k = (physicsTime - frameTime)/(frameTime - lastFrameTime);
    float sec1  = physicsTime.asSeconds();
    float sec2 = frameTime.asSeconds();
    float sec3 = lastFrameTime.asSeconds();
    printf("k = %f\n", k);
    printf("physicsTime = %f, frameTime = %f, lastFrameTime = %f\n", sec1, sec2, sec3);
    
    int nb_pods = podsSprites_.size();
    for (int i=0; i<nb_pods; i++){
        sf::Vector2f pos_sprite = podsSprites_[i].getPosition(); // on récupère l'ancienne position
        if (k>1)  podsSprites_[i].setPosition( pos_sprite + (pods_[i].pos_ - pos_sprite)/k );
        else{ podsSprites_[i].setPosition(pods_[i].pos_); }
        // erreur ! la condition sur l'angle max doit se faire dans la partie update physics
       /* float angle_max=M_PI/10;
        if(pods_[i].angle_==angle_max){
            podsSprites_[i].setRotation((pods_[i].angle_+angle_max)*180.f/M_PI);}
        else{
            podsSprites_[i].setRotation((pods_[i].angle_)*180.f/M_PI);}*/
        // la partie update graphics fait juste correspondre l'aspect graphique à ce qui  a été défini. 
        podsSprites_[i].setRotation((pods_[i].angle_)*180.f/M_PI);
    }
    lastFrameTime = frameTime;
}

std::string chrono="0";
std::string chrono2="0";
void Game::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
// on draw tous les Sprites : pods et CP (dans leurs listes), tout ce qui a été mis en liste et définit comme drawable
// s'appuie sur la définition des classes faites précédemment. 
    target.draw(backgroundSprite_, states);
    target.draw(finalCP_, states);

    for (const auto &cp : otherCPs_)
    {
        target.draw(cp, states);
    }

    for (const auto &podSprite : podsSprites_)
    {
        target.draw(podSprite, states);
    }
//////////////// affichage bonus
/// compteur au démarrage
if(physicsTime.asMilliseconds()<1000){
    if(physicsTime.asMilliseconds()<500){
        sf::Text START;
        sf::Font police_affichage;
        police_affichage.loadFromFile("../repository/Fredoka-Bold.ttf");
        START = sf::Text("WAIT",police_affichage, 1000);
        START.setOutlineThickness(50);
        setTextCenterPosition(START,8000,4500);
        target.draw(START);
    }
}
if(physicsTime.asMilliseconds()<1000){
    if(physicsTime.asMilliseconds()>500){
        sf::Text Départ;
        sf::Font police_affichage;
        police_affichage.loadFromFile("../repository/Fredoka-Bold.ttf");
        Départ = sf::Text("GO",police_affichage, 2000);
        Départ.setOutlineThickness(50);
        setTextCenterPosition(Départ,8000,4500);
        target.draw(Départ);
    }
}
/// affichage du titre du jeu
sf::Text Titre_jeu;
sf::Font police_affichage;
police_affichage.loadFromFile("../repository/Fredoka-Bold.ttf");
Titre_jeu = sf::Text("Jeu de course 2D",police_affichage, 400);
Titre_jeu.setOutlineThickness(50);
setTextCenterPosition(Titre_jeu,2000,1000);
target.draw(Titre_jeu);

/// affichage du compteur de tour et du chrono pour chaque vaisseau contrôlé par un joueur
// dans la fonction telle que rendue, les vaisseaux contrôles sont toujours les mêmes, 
// dans une version améliorée, on pourrait considérer que le joueurs puisse choisir son vaisseau
// en ce cas le programme reste robuste il suffit de donner en arguements choix1 et choix2 du main dans les pods_[0] et pods_[1]

if(pods_[0].mode==1){
    sf::Text montre;
    sf::Text compteur;
    int Tour_joueur1=pods_[0].lapCount_; // le compteur de tour est réalise pour le pod du joueur, ici le 1er pod
    std::string TourJ1 = std::to_string(Tour_joueur1); // on convertit le type
    std::string I=std::to_string(1);
    sf::Font police_tours;
    compteur.setFont(police_affichage);
    compteur.setOutlineThickness(50);
    compteur.setString("Tours " + TourJ1 +"/3 pour J"+ I); // on concatène les string pour l'affichage
    compteur.setCharacterSize(400);
    compteur.setFillColor(sf::Color(255,255,255,200));
    compteur.setOutlineThickness(50);
    setTextCenterPosition(compteur, 14000, 300);
    montre.setString("Victoire J"+I+"en:"+chrono+"s"); 
    montre.setFont(police_affichage);
    montre.setCharacterSize(400);
    montre.setFillColor(sf::Color(255,255,255,200));
    setTextCenterPosition(montre, 10000,200);
    int temps;
    if(!pods_[0].fin) // permet de figer le compteur
    {
        temps=physicsTime.asSeconds();
        chrono=std::to_string(temps);
    }
    ////// compteur de tour 
    target.draw(compteur);
    ///// chronomètre
    target.draw(montre);
}


if(pods_[1].mode==2){
    sf::Text montre2;
    sf::Text compteur2;
    int Tour_joueur2=pods_[1].lapCount_; // le compteur de tour est réalise pour le pod du joueur, ici le 1er pod
    std::string TourJ2 = std::to_string(Tour_joueur2); // on convertit le type
    std::string I2=std::to_string(2);
    compteur2.setFont(police_affichage);
    compteur2.setOutlineThickness(50);
    compteur2.setString("Tours " + TourJ2 +"/3 pour J"+ I2); // on concatène les string pour l'affichage
    compteur2.setCharacterSize(400);
    compteur2.setFillColor(sf::Color(255,255,255,200));
    compteur2.setOutlineThickness(50);
    setTextCenterPosition(compteur2, 14000, 300+500);
    montre2.setString("Victoire J"+I2+"en:"+chrono2+"s"); 
    montre2.setFont(police_affichage);
    montre2.setCharacterSize(400);
    montre2.setFillColor(sf::Color(255,255,255,200));
    setTextCenterPosition(montre2, 10000,200+500);
    int temps2;
    if(!pods_[1].fin) // permet de figer le compteur
        {
        temps2=physicsTime.asSeconds();
            chrono2=std::to_string(temps2);
        }
    ////// compteur de tour 
    target.draw(compteur2);
    ///// chronomètre
    target.draw(montre2);
}
}
