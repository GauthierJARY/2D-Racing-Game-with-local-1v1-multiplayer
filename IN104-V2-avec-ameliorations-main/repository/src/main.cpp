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
	sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");
	sf::View myView(sf::Rect(0.f, 0.f, 16000.f, 9000.f));
	window.setView(myView);
	/////////////////////////////////////////////////
	///////// gestion du temps ////////////////
	float FPS = 60; // Nombre d'images par seconde
	Game myGame("../repository/Images/background.png", {{5000, 5600}, {1000, 100}, {12000, 5300}, {300, 5300}});

	sf::Time refreshTime = sf::microseconds(1e6 / FPS);
	window.setFramerateLimit(FPS);
	// horloge depuis le début du jeu
	sf::Clock globalClock;
	// horloge réinitialisée à chaque frame
	sf::Clock refreshClock;
	// temps de la physique du jeu
	sf::Time physicsTime = sf::Time::Zero;
	/////////////////////////////////////////////

	/////////initilisation du jeu ////////////
	// Vous pouvez aussi initialiser myGame avec une liste de checkpoints prédéfinie

	////////////////////////////////////////////

	// On importe tous les sprites et textures en dehors de la boucle pour diminuer les opérations effectuées et rendre le menu plus fluide

	sf::Texture background;
	if (!background.loadFromFile("/home/ensta/in104/repository/Images/background.png")) // chemin à changer pour le background
	{
	}

	sf::Sprite BackgroundSp;
	BackgroundSp.setTexture(background);
	setOriginToCenter(BackgroundSp);
	BackgroundSp.setPosition(8000, 4500);
	scaleToMinSize(BackgroundSp, 16000, 9000);

	sf::Font fontmenu;
	if (!fontmenu.loadFromFile("/home/ensta/in104/repository/Fredoka-Bold.ttf")) // chemin pour la police à chnager aussi
	{
	}

	sf::Text text1;
	text1.setFont(fontmenu);
	text1.setString("Play");
	// setOriginToCenter(text1);
	text1.setPosition(5000, 6500);
	text1.setFillColor(sf::Color(255, 215, 0));
	text1.setCharacterSize(1200);

	sf::Text text2;
	text2.setFont(fontmenu);
	text2.setString("Quit");
	// setOriginToCenter(text2);
	text2.setPosition(9000, 6500);
	text2.setFillColor(sf::Color(255, 255, 255, 100));
	text2.setCharacterSize(1200);

	sf::Text text3;
	text3.setFont(fontmenu);
	text3.setString("Space Race");
	// setOriginToCenter(text3);
	text3.setPosition(5500, 0);
	text3.setFillColor(sf::Color(255, 255, 255));
	text3.setCharacterSize(1200);

	sf::Texture map1;
	if (!map1.loadFromFile("/home/ensta/in104/repository/Images/map1.png")) // Chemin de map1 à changer
	{
	}

	sf::Sprite Map1Sp;
	Map1Sp.setTexture(map1);
	setOriginToCenter(Map1Sp);
	Map1Sp.setPosition(5500, 5000);
	scaleToMinSize(Map1Sp, 1000, 1800);

	sf::Texture map2;
	if (!map2.loadFromFile("/home/ensta/in104/repository/Images/map2.png")) // Chemin de map2 à changer
	{
	}

	sf::Sprite Map2Sp;
	Map2Sp.setTexture(map2);
	setOriginToCenter(Map2Sp);
	Map2Sp.setPosition(10500, 5000);
	scaleToMinSize(Map2Sp, 1000, 1800);

	sf::Sprite Back1Sp;
	Back1Sp.setTexture(map1);
	setOriginToCenter(Back1Sp);
	Back1Sp.setPosition(8000, 4500);
	scaleToMinSize(Back1Sp, 16000, 9000);

	sf::Sprite Back2Sp;
	Back2Sp.setTexture(map2);
	setOriginToCenter(Back2Sp);
	Back2Sp.setPosition(8000, 4500);
	scaleToMinSize(Back2Sp, 16000, 9000);

	sf::Text text4;
	text4.setFont(fontmenu);
	text4.setString("Map 1");
	// setOriginToCenter(text4);
	text4.setPosition(5000, 6500);
	text4.setFillColor(sf::Color(255, 215, 0));
	text4.setCharacterSize(1200);

	sf::Text text5;
	text5.setFont(fontmenu);
	text5.setString("Map 2");
	// setOriginToCenter(text5);
	text5.setPosition(9000, 6500);
	text5.setFillColor(sf::Color(255, 255, 255, 100));
	text5.setCharacterSize(1200);

	sf::Text text6;
	text6.setFont(fontmenu);
	text6.setString("Choose Map");
	// setOriginToCenter(text6);
	text6.setPosition(5500, 0);
	text6.setFillColor(sf::Color(255, 255, 255));
	text6.setCharacterSize(1200);

	sf::Text text7;
	text7.setFont(fontmenu);
	text7.setString("Space Ship 1");
	// setOriginToCenter(text7);
	text7.setPosition(2000, 6500);
	text7.setFillColor(sf::Color(255, 215, 0));
	text7.setCharacterSize(900);

	sf::Text text8;
	text8.setFont(fontmenu);
	text8.setString("Space Ship 2");
	// setOriginToCenter(text8);
	text8.setPosition(9000, 6500);
	text8.setFillColor(sf::Color(255, 255, 255, 100));
	text8.setCharacterSize(900);

	sf::Text text9;
	text9.setFont(fontmenu);
	text9.setString("Choose Space Ship");
	// setOriginToCenter(text9);
	text9.setPosition(4000, 0);
	text9.setFillColor(sf::Color(255, 255, 255));
	text9.setCharacterSize(1200);

	// Passons aux vaisseaux

	sf::Texture Ship1;
	if (!Ship1.loadFromFile("/home/ensta/in104/repository/Images/Ship1.png")) // Chemin de Ship1 à changer
	{
	}

	sf::Sprite Ship1Sp;
	Ship1Sp.setTexture(Ship1);
	setOriginToCenter(Ship1Sp);
	Ship1Sp.setPosition(4000, 4000);
	scaleToMinSize(Ship1Sp, 1000, 1200);

	sf::Texture Ship2;
	if (!Ship2.loadFromFile("/home/ensta/in104/repository/Images/Ship2.png")) // Chemin de Ship2 à changer
	{
	}

	sf::Sprite Ship2Sp;
	Ship2Sp.setTexture(Ship2);
	setOriginToCenter(Ship2Sp);
	Ship2Sp.setPosition(11000, 4000);
	scaleToMinSize(Ship2Sp, 1000, 1200);

	sf::Texture fondTexture;
	fondTexture.loadFromFile("../repository/Images/map1.png");
	sf::Sprite fondSprite;
	fondSprite.setTexture(fondTexture);
	auto rec = fondSprite.getGlobalBounds();
	fondSprite.scale(sf::Vector2f(16000 / rec.width, 9000 / rec.height));

	sf::Texture droide_;
	droide_.loadFromFile("../repository/Images/droide.png");
	sf::Sprite droide;
	droide.setTexture(droide_);
	setOriginToCenter(droide);
	scaleByRadius(droide, 10);
	droide.setPosition(1000, 6500);

	sf::Text Text1;
	sf::Font police_affichage;
	police_affichage.loadFromFile("../repository/Fredoka-Bold.ttf");
	Text1.setFont(police_affichage);
	Text1.setCharacterSize(500);
	setTextCenterPosition(Text1, 5000, 4000);
	Text1.setString("Choisir votre mode ? \nA=1vs5\nB=1vs1\nC= DEMO");
	sf::Text Text2;
	Text2.setFont(police_affichage);
	Text2.setCharacterSize(500);
	setTextCenterPosition(Text2, 5000, 8000);
	Text2.setString("Then press SPACE");

	int Select = 0;			   // permet de switcher d'un item selectionné à l'autre 
	int MenuIndex = 0;		   // permet à l'algo de comprendre qu'il est passé d'un menu à l'autre
	int MapIndex = 0;		   // permet de garder l'information de la map selectionnée
	int ShipIndex = 0;		   // permet de savoir quel vaisseau a été selectionné
	int i = 0;				   // permet de faire clignoter le texte
	int cligne;				   // permet de rester dans l'interval 0-255
	int nombre_joueur = 0;	   // permet de récupérer le nombre de joueurs qu'a selectionné l'utilisateur
	int nombre_adversaire = 6; // permet de récupérer le nombre d'adversaires qu'a selectionné l'utilisateur
	int choix1 = 0;
	int choix2 = 1;
	int interface = 0;

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (MenuIndex == 0)
		{
			// Clignotement de texte permet aussi de rendre compte à quel point l'ordi ram

			if (i == 255)
				cligne = -1; //
			if (i == 0)
				cligne = 1;

			text3.setFillColor(sf::Color(255, 255, 255, i));
			i += cligne;

			// Switch de couleur suivant ce que le jooueur selectionne
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && Select != 1)
			{
				Select = 1;
				text1.setFillColor(sf::Color(255, 255, 255, 100));
				text2.setFillColor(sf::Color(255, 215, 0));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && Select != 0)
			{
				Select = 0;
				text2.setFillColor(sf::Color(255, 255, 255, 100));
				text1.setFillColor(sf::Color(255, 215, 0));
			}

			// Redirection vers les menus correspondants
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				if (Select == 0)
				{
					MenuIndex = 1;
				}

				if (Select == 1)
				{
					window.close();
				}
			}

			window.clear();
			window.draw(BackgroundSp);
			window.draw(text1);
			window.draw(text2);
			window.draw(text3);
			window.display();
		}

		// Si le joueur veut commncer à jouer passons au choix de la map

		if (MenuIndex == 1)
		{
			Select = 0;
			if (i == 255)
				cligne = -1;
			if (i == 0)
				cligne = 1;

			text6.setFillColor(sf::Color(255, 255, 255, i));
			i += cligne;

			// Switch de couleur suivant ce que le jooueur selectionne
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && Select != 1)
			{
				Select = 1;
				text4.setFillColor(sf::Color(255, 255, 255, 100));
				text5.setFillColor(sf::Color(255, 215, 0));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && Select != 0)
			{
				Select = 0;
				text4.setFillColor(sf::Color(255, 255, 255, 100));
				text5.setFillColor(sf::Color(255, 215, 0));
			}

			// Redirection vers les maps correspondantes
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				if (Select == 0)
				{
					MapIndex = 1;
					MenuIndex = 2;
				}

				if (Select == 1)
				{
					MapIndex = 2;
					MenuIndex = 2;
				}
			}			
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && Select == 0)
			{
				MapIndex = 1;
				MenuIndex = 2;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && Select == 1)
			{
				MapIndex = 2;
				MenuIndex = 2;
			}*/
			window.clear();
			window.draw(BackgroundSp);
			window.draw(Map1Sp);
			window.draw(Map2Sp);
			window.draw(text4);
			window.draw(text5);
			window.draw(text6);
			window.display();
		}

	// Choix de vaisseaux fonctionnel mais difficile de l'implémenter dans le game 

		/*if (MenuIndex == 2)
		{
			Select = 0;

			if (i == 255)
				cligne = -1;
			if (i == 0)
				cligne = 1;

			text9.setFillColor(sf::Color(255, 255, 255, i));
			i += cligne;


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && Select != 1)
			{
				Select = 1;
				text7.setFillColor(sf::Color(255, 255, 255, 100));
				text8.setFillColor(sf::Color(255, 215, 0));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && Select != 0)
			{
				Select = 0;
				text8.setFillColor(sf::Color(255, 255, 255, 100));
				text7.setFillColor(sf::Color(255, 215, 0));
			}

			//Redirection vers les vaisseaux correspondants
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				if (Select == 0)
				{
					ShipIndex = 1;
					MenuIndex = 3;
				}

				if (Select == 1)
				{
					ShipIndex = 2;
					MenuIndex = 3;
				}
			}

			window.clear();
			if (MapIndex == 1)
			{
				window.draw(Back1Sp);
			}

			else
			{
				window.draw(Back2Sp);
			}

			window.draw(Ship1Sp);
			window.draw(Ship2Sp);
			window.draw(text7);
			window.draw(text8);
			window.draw(text9);
			window.display();
		}*/
		if (MenuIndex == 2)
		{
			if (interface == 0)
			{
				while (interface == 0)
				{

					while (window.pollEvent(event))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
						{
							nombre_joueur = 1;
							nombre_adversaire = 6;
							text2.setFillColor(sf::Color(255, 0, 0, 255));
							scaleByRadius(droide, 10000);
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
						{
							nombre_joueur = 2;
							nombre_adversaire = 2;
							text2.setFillColor(sf::Color(255, 0, 0, 255));
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
						{
							nombre_joueur = 0;
							nombre_adversaire = 6;
							text2.setFillColor(sf::Color(255, 0, 0, 255));
						} // demo avec tous les vaisseaux
						if (event.type == sf::Event::Closed)
						{
							window.close();
							interface = 1;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							interface = 1;
						}
					}
					window.clear();
					////////////////////////////////////////////////////////////////////////:
					window.setVerticalSyncEnabled(false);
					window.clear();
					if (MapIndex == 1)
					{
						window.draw(Back1Sp);
					}

					else
					{
						window.draw(Back2Sp);
					}
					window.draw(Text1);
					window.draw(Text2);
					window.draw(droide);
					window.display();
				}
				myGame.addPod(choix1, nombre_joueur, choix2, nombre_adversaire);
			}
			if (interface == 1)
			{
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
					{
						window.close();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						window.close();
					}
				}
				// si on a dépassé le refreshTime depuis la dernière frame
				if (refreshClock.getElapsedTime() >= refreshTime)
				{
					// réinitialise l'horloge qui mesure le temps entre les frames
					refreshClock.restart();
					// récupère le temps écoulé depuis le début du jeu
					sf::Time frameTime = globalClock.getElapsedTime();
					// si on a dépassé le temps de la physique
					if (frameTime > physicsTime)
					{
						// met à jour les sprite au temps de la physique
						myGame.updateGraphics(physicsTime);
						// fait avancer la physique d'un pas de temps
						myGame.updatePhysics();
						physicsTime += PHYSICS_TIME_STEP;
						// reprend le temps écoulé depuis le début pour rester précis
						frameTime = globalClock.getElapsedTime();
					}
					// met à jour les sprites au temps actuel
					myGame.updateGraphics(frameTime);
					window.clear();
					window.draw(myGame);
					window.display();
				}
			}
		}

	}
	return 0;
}
