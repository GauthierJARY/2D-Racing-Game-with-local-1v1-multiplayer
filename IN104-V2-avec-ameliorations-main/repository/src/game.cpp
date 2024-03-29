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
    cpPositions_=checkpointsPositions;
    int i=0;
    int taille= checkpointsPositions.size();
    otherCPs_.reserve(taille-1);

    for (i=1;i<taille;i++){
        otherCPs_.emplace_back(checkpointsPositions[i],i);
    }
    backgroundTexture_.loadFromFile(fond);
    backgroundSprite_.setTexture(backgroundTexture_);
    auto rec=backgroundSprite_.getLocalBounds();
    backgroundSprite_.scale(sf::Vector2f(16000/rec.width,9000/rec.height));
}

void Game::addPod(int choix1, int nb_joueur, int choix2, int adversaire)
{
    int nombre_j=nb_joueur;
    int choix_user_vaisseaux=choix1;
    int choix_user_vaisseaux2=choix2;
    int nb_pods = adversaire;
    
    podsSprites_.reserve(nb_pods);
    pods_.reserve(nb_pods);
    podsTextures_.reserve(nb_pods);
 
        Pod pod1 = Pod({3000,5600}, 0.f);
    // gestion directe sans copie et donc sans changement d'adresse
    pods_.emplace_back(pod1);
    podsTextures_.emplace_back();
    podsTextures_[0].loadFromFile("/home/ensta/in104/repository/Images/BSGCylon.png");
        Pod pod2 = Pod({5000,6000}, 0.f);
    pods_.emplace_back(pod2);
    podsTextures_.emplace_back();
    podsTextures_[1].loadFromFile("/home/ensta/in104/repository/Images/BSGViper.png");
        Pod pod3 = Pod({2000,5620}, 0.f);
    pods_.emplace_back(pod3);
    podsTextures_.emplace_back();
    podsTextures_[2].loadFromFile("/home/ensta/in104/repository/Images/NMSFighterG.png");
        Pod pod4 = Pod({1000,5630}, 0.f);
    pods_.emplace_back(pod4);
    podsTextures_.emplace_back();
    podsTextures_[3].loadFromFile("/home/ensta/in104/repository/Images/NMSFighterY.png");
        Pod pod5 = Pod({4000,5640}, 0.f);
    pods_.emplace_back(pod5);
    podsTextures_.emplace_back();
    podsTextures_[4].loadFromFile("/home/ensta/in104/repository/Images/SWAnakinsPod.png");
        Pod pod6 = Pod({5000,5650}, 0.f);
    pods_.emplace_back(pod6);
    podsTextures_.emplace_back();
    podsTextures_[5].loadFromFile("/home/ensta/in104/repository/Images/SWMilleniumFalcon.png");

    for (int i=0; i<nb_pods; i++){podsSprites_.emplace_back(podsTextures_[i]);}

    for (int i=0; i<nb_pods; i++)
    {
        podsSprites_[i].setTexture(podsTextures_[i]);
        setOriginToCenter(podsSprites_[i]);
        scaleToMaxSize(podsSprites_[i], 800,800);
        pods_[i].nextCP_ = 1;
        pods_[i].lapCount_ = 0;
        pods_[i].mode=0;
        pods_[i].fin=false;
    }

    if(nombre_j==1){
        pods_[choix_user_vaisseaux].mode=1;}
    if(nombre_j==2){
        pods_[choix_user_vaisseaux].mode=1;
        pods_[choix_user_vaisseaux2].mode=2;
    }

    //podsSprites_[1].setColor(sf::Color(255,0,0));
    //podsSprites_[0].setColor(sf::Color(0,255,0));
}

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

            float norm_ = norme(diff);
            if(norm_ != 0)
            {
                pod.vel_.x = FRICTION_COEFF*(pod.vel_.x + power*   ( (target.x - pod.pos_.x)/norme(diff)));
                pod.vel_.y = FRICTION_COEFF*(pod.vel_.y + power*((target.y - pod.pos_.y)/norme(diff)));
            }
            else{pod.vel_ = FRICTION_COEFF*pod.vel_;}

            if(pod.vel_.x != 0)
            {
                if (pod.vel_.x < 0) {pod.angle_ = M_PI + std::atan(pod.vel_.y/pod.vel_.x);}
                else {pod.angle_ = std::atan(pod.vel_.y/pod.vel_.x);}
            }
            pod.pos_ = pod.pos_ + pod.vel_;


            if(distance_point(pod.pos_,cpPositions_[pod.nextCP_])<500) // taille du checkpoint
            {
                pod.nextCP_+=1;
                if(pod.nextCP_==cpPositions_.size()){
                    pod.nextCP_=0;
                }
                if(pod.nextCP_==1){pod.lapCount_+=1;}
                if(pod.lapCount_==NUMBER_OF_LAPS){pod.fin=true;}
            }
        } 
    }   
}
physicsTime += PHYSICS_TIME_STEP;
}

void Game::updateGraphics(sf::Time frameTime)
{
    float k = (physicsTime - frameTime)/(frameTime - lastFrameTime);
    float sec1  = physicsTime.asSeconds();
    float sec2 = frameTime.asSeconds();
    float sec3 = lastFrameTime.asSeconds();
    printf("k = %f\n", k);
    printf("physicsTime = %f, frameTime = %f, lastFrameTime = %f\n", sec1, sec2, sec3);
    
    int nb_pods = podsSprites_.size();
    for (int i=0; i<nb_pods; i++){
        sf::Vector2f pos_sprite = podsSprites_[i].getPosition();
        if (k>1)  podsSprites_[i].setPosition( pos_sprite + (pods_[i].pos_ - pos_sprite)/k );
        else{ podsSprites_[i].setPosition(pods_[i].pos_); }
       /* float angle_max=M_PI/10;
        if(pods_[i].angle_==angle_max){
            podsSprites_[i].setRotation((pods_[i].angle_+angle_max)*180.f/M_PI);}
        else{
            podsSprites_[i].setRotation((pods_[i].angle_)*180.f/M_PI);}*/
        podsSprites_[i].setRotation((pods_[i].angle_)*180.f/M_PI);
    }
    lastFrameTime = frameTime;
}


void Game::draw( sf::RenderTarget& target, sf::RenderStates states) const
{
// on draw tous les Sprites : pods et CP (dans leurs listes)
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
//// démarrage
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

sf::Text Titre_jeu;
sf::Font police_affichage;
police_affichage.loadFromFile("../repository/Fredoka-Bold.ttf");
Titre_jeu = sf::Text("Jeu de course 2D",police_affichage, 400);
Titre_jeu.setOutlineThickness(50);
setTextCenterPosition(Titre_jeu,2000,1000);
target.draw(Titre_jeu);

for (int i=0; i<size(pods_);i++)
{
    std::string tempo;
    if(pods_[i].mode==1 || pods_[i].mode==2)
    {
        int Tour_joueur1=pods_[i].lapCount_; // le compteur de tour est réalise pour le pod du joueur, ici le 1er pod
        std::string TourJ1 = std::to_string(Tour_joueur1);
        std::string I=std::to_string(i);
        sf::Font police_tours;
        sf::Text compteur;
        compteur.setFont(police_affichage);
        compteur.setOutlineThickness(50);
        compteur.setString("Tours " + TourJ1 +"/3 pour J"+ I);
        compteur.setCharacterSize(400);
        compteur.setFillColor(sf::Color(255,255,255,200));
        compteur.setOutlineThickness(50);
        setTextCenterPosition(compteur, 14000, 300+500*std::min(i,1));

        int temps=physicsTime.asSeconds();
        std::string chrono=std::to_string(temps);
        sf::Text montre;
        tempo==std::to_string(temps);
        montre.setString("Victoire J"+I+"en:"+chrono+"s"); 
        montre.setFont(police_affichage);
        montre.setCharacterSize(400);
        montre.setFillColor(sf::Color(255,255,255,200));
        setTextCenterPosition(montre, 10000,200+500*std::min(i,1));
        if(!pods_[i].fin)
            {
            ////// compteur de tour 
                target.draw(compteur);
            ///// chronomètre
                target.draw(montre);
            }
        else
            {
                sf::Text montre;
                montre.setString("Victoire J1 en:"+tempo+"s"); 
                montre.setFont(police_affichage);
                montre.setCharacterSize(400);
                montre.setFillColor(sf::Color(255,255,255,200));
                setTextCenterPosition(montre, 10000,20+500*std::max(i,1));
                target.draw(montre);
            }
    }
}




}
