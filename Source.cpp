#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<string>
#include<utility>
#include<stdio.h>

#include<SFML\System.hpp>
#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Network.hpp>

#include"Player.h"

#include"Platform.h"
#include"Enemy.h"
#include"Collider.h"
#include"Menu.h"
#include"Bullet.h"
#include"bulletEnemy.h"
#include"EnemyShooter.h"
#include"PauseButton.h"
#include"Boss1.h"
#include"Textbox.h"
#include"Princessxi.h"

static const float VIEW_WIDTH = 1080.0f;
static const float VIEW_HEIGHT = 720.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

using namespace std;

void showHighScore(int x, int y, string word, sf::RenderWindow& window, sf::Font* font);

int main()
{
	srand(time(NULL));
	
	sf::RenderWindow window(sf::VideoMode(1080, 720),"MY FIRST GAME",sf::Style::Close | sf::Style::Resize );
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

	//HP*************************************************************************
	//sf::Clock plusHpClock;
	sf::Clock hpclock;
	sf::RectangleShape hpOutline;
	hpOutline.setOutlineThickness(1);
	hpOutline.setFillColor(sf::Color::Transparent);
	hpOutline.setOutlineColor(sf::Color::Black); 
	hpOutline.setPosition(20, 20); //กำหนดตำเเหน่งของกรอบหลอดเลือด
	hpOutline.setSize(sf::Vector2f(500, 20)); //กำหนดขนาดของกรอบหลอดเลือด
	sf::RectangleShape hpBar;
	hpBar.setSize(sf::Vector2f(500, 20)); // กำหนดความกว้างเเละความยาวของหลอดเลือด
	hpBar.setFillColor(sf::Color::Red); // กำหนดสีหลอดเลือด
	hpBar.setPosition(20, 20); //กำหนดตำเเหน่งหลอดเลือด

	//Item blood*****************************************************************
	sf::Texture bloodTexture;
	bloodTexture.loadFromFile("blood.png");
	sf::Sprite blood;
	blood.setTexture(bloodTexture);
	blood.setScale(1.0f, 1.0f);
	int random_x;
	int random_y;
	random_x = rand() % 800;
	random_y = rand() % 200;
	//blood.setPosition(random_x, random_y);

	//item
	sf::Texture itemTexture;
	itemTexture.loadFromFile("fireBullet2.png");
	sf::Sprite item;
	item.setTexture(itemTexture);
	item.setScale(1.5, 1.5);
	item.setPosition(10000, 100000);

	//เสียงตอนฟัน*********************************************************************
	sf::SoundBuffer soundEffect;
	soundEffect.loadFromFile("mixkit-light-saber-sword-1708.wav");
	sf::Sound swordEffect;
	swordEffect.setBuffer(soundEffect);

	sf::SoundBuffer soundEffect2;
	soundEffect2.loadFromFile("mixkit-falling-hit-757.wav");
	sf::Sound shootEffect;
	shootEffect.setBuffer(soundEffect2);

	sf::SoundBuffer soundBackground;
	soundBackground.loadFromFile("10493107_MotionElements_warmhearted-short-version_preview.wav");
	sf::Sound backgroundmusic;
	backgroundmusic.setBuffer(soundBackground);

	backgroundmusic.setLoop(true);

	int gorn = 1;

	//Background**********************************************************************
	sf::Texture bg;
	bg.loadFromFile("2longBG.png");
	//Box for Background
	sf::RectangleShape box_bg(sf::Vector2f(13632, 720));
	box_bg.setTexture(&bg);
	box_bg.setPosition(-540, -360);

	sf::Texture bgCredit;
	bgCredit.loadFromFile("CreditNAPAT.png");
	//Box for Background
	sf::RectangleShape box_bgCredit(sf::Vector2f(1136, 720));
	box_bgCredit.setTexture(&bgCredit);
	//box_bgCredit.setPosition(-540, -360);

	sf::Texture bgHow;
	bgHow.loadFromFile("How to play xxx.png");
	//Box for Background
	sf::RectangleShape box_bgHow(sf::Vector2f(1136, 720));
	box_bgHow.setTexture(&bgHow);
	//box_bgCredit.setPosition(-540, -360);

	sf::Texture firstPage;
	firstPage.loadFromFile("ohmlim.png");
	sf::RectangleShape boxFirstPage(sf::Vector2f(1136, 720));
	boxFirstPage.setTexture(&firstPage);

	//load picture to sprite**********************************************************
	sf::Texture playerTexture;
	playerTexture.loadFromFile("heroyedtood.png");
	//setting sprite EX.speedAnimation,speedWalk
	Player player(&playerTexture, sf::Vector2u(5, 4), 0.1f, 200.0f);

	sf::Texture princessTexture;
	princessTexture.loadFromFile("pri.png");
	Princessxi princess(&princessTexture, sf::Vector2u(5, 4), 0.1f, 0.0f);

	sf::Texture boss1Texture2;
	boss1Texture2.loadFromFile("Bossrobotxxx.png");
	
	//load picture to Enemy********************************************************
	sf::Texture enemyTexture;
	enemyTexture.loadFromFile("BOSS.png");
	//setting sprite EX.speedAnimation,speedWalk
	//Enemy enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f,100,100);

	sf::Texture orcTexture;
	orcTexture.loadFromFile("orcva.png");
	
	//load picture to Boss 1*********************************************************
	sf::Texture boss1Texture;
	boss1Texture.loadFromFile("EnemyBigboss.png");

	//load picture to Shooter*********************************************************
	sf::Texture shooterTexture;
	shooterTexture.loadFromFile("SHOOTERJINGs.png");
	
	//เรียก Enemy เเบบ vector ***********************************************************
	std::vector<EnemyShooter*> enemiesShooter;
	//enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, -100, 200));

	std::vector<Enemy*> enemies;
	//enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f,-200,-100));
	//enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, 200, 100));
	//enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, 0, 500));

	std::vector<Boss1*> bossOne;
	//bossOne.push_back(new Boss1(&boss1Texture, sf::Vector2u(5, 4), 0.1f, 0.0f, -100, 0));
	//bossOne.push_back(new Boss1(&boss1Texture2, sf::Vector2u(4, 4), 0.1f, 0.0f, abs(player.GetPosition().x) + 300, 100));

	//*******************************************************************************************
	//Platform
	//Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f));
	//Platform platform2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 600.0f));
	//Platform platform3(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(856.0f, 600.0f));

	float deltaTime = 0.0f;

	sf::Clock clock;
	sf::Clock K_clock;
	sf::Clock itemClock;
	sf::Clock enemyAttackClock;

	sf::Clock missionClock;

	//ส่วนของScore**************************************************
	sf::Font font;
	if (!font.loadFromFile("font/FC Friday Medium Italic.otf"))
	{
		std::cout << "Failed" << std::endl;
	}
	int scoreCount = 0;
	sf::Text scoreText;
	//scoreText.setPosition(340, -300);
	scoreText.setFont(font);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setScale(1, 1);

	sf::Font font3;
	if (!font3.loadFromFile("font/FC Friday Medium Italic.otf"))
	{
		std::cout << "Failed" << std::endl;
	}
	sf::Text fontScore;
	fontScore.setFont(font3);
	fontScore.setFillColor(sf::Color::Black);
	fontScore.setScale(1, 1);
	fontScore.setString("KILLS");

	sf::Font font8;
	if (!font8.loadFromFile("font/FC Friday Medium Italic.otf"))
	{
		std::cout << "Failed" << std::endl;
	}
	sf::Text fontCredit;
	fontCredit.setFont(font8);
	fontCredit.setFillColor(sf::Color::Black);
	fontCredit.setScale(2, 2);
	fontCredit.setString("Game by");

	//Enemy left text************************************************
	sf::Font font1;
	if (!font1.loadFromFile("font/FC Friday Medium Italic.otf"))
	{
		std::cout << "Failed" << std::endl;
	}
	int enemyLeftCount = 10;
	sf::Text enemyLeftText;
	enemyLeftText.setFont(font1);
	enemyLeftText.setFillColor(sf::Color::Black);
	enemyLeftText.setScale(1,1);

	sf::Font font2;
	if (!font2.loadFromFile("font/FC Friday Medium Italic.otf"))
	{
		std::cout << "Failed" << std::endl;
	}
	sf::Text enemyleft;
	enemyleft.setFont(font2);
	enemyleft.setFillColor(sf::Color::Black);
	enemyleft.setScale(1, 1);
	enemyleft.setString("Enemy Left");

	//Congreat put up text !!!
	sf::Font font4;
	if (!font4.loadFromFile("font/FC Friday Medium Italic.otf"))
	{
		std::cout << "Failed" << std::endl;
	}
	sf::Text congreat;
	congreat.setFont(font4);
	congreat.setFillColor(sf::Color::Black);
	congreat.setScale(1, 1);
	congreat.setString("Please 4 To Continue...");

	//!!!STAGE1!!!
	sf::Font font7;
	if (!font7.loadFromFile("font/FC Friday Medium Italic.otf"))
	{
		std::cout << "Failed" << std::endl;
	}
	sf::Text stage1;
	stage1.setFont(font7);
	stage1.setFillColor(sf::Color::Red);
	stage1.setScale(2, 2);
	stage1.setString("Stage1!!!");

	sf::Font font9;
	if (!font9.loadFromFile("font/FC Friday Medium Italic.otf"))
	{
		std::cout << "Failed" << std::endl;
	}
	sf::Text stagewin;
	stagewin.setFont(font9);
	stagewin.setFillColor(sf::Color::Red);
	stagewin.setScale(2, 2);
	stagewin.setString("WINnn!!!");

	sf::Font font10;
	if (!font10.loadFromFile("font/FC Friday Medium Italic.otf"))
	{
		std::cout << "Failed" << std::endl;
	}
	sf::Text stagewon;
	stagewon.setFont(font10);
	stagewon.setFillColor(sf::Color::Black);
	stagewon.setScale(2, 2);
	stagewon.setString("please Numpad 0!!!");


	sf::Clock fontStage1Clock;
	
	//!!!STAGE2!!!
	sf::Font font5;
	if (!font5.loadFromFile("font/FC Friday Medium Italic.otf"))
	{
		std::cout << "Failed" << std::endl;
	}
	sf::Text stage2;
	stage2.setFont(font5);
	stage2.setFillColor(sf::Color::Red);
	stage2.setScale(2, 2);
	stage2.setString("Stage2!!!");

	sf::Clock fontStage2Clock;

	//!!!STAGE3!!!
	sf::Font font6;
	if (!font6.loadFromFile("font/FC Friday Medium Italic.otf"))
	{
		std::cout << "Failed" << std::endl;
	}
	sf::Text stage3;
	stage3.setFont(font6);
	stage3.setFillColor(sf::Color::Red);
	stage3.setScale(2, 2);
	stage3.setString("Stage3!!!");

	sf::Clock fontStage3Clock;

	sf::Text BossStage;
	BossStage.setFont(font6);
	BossStage.setFillColor(sf::Color::Red);
	BossStage.setScale(2, 2);
	BossStage.setString("Boss  Stage!!!");

	sf::Clock fontBossStageClock;

	//***************************************************************
	int game = 0; // เอาไว้เข้าเมนู
	int napat = 0;// เอาไว้เรียกBoss
	
	//ประกาศเมนูมาจากคลาส***********************************************
	Menu menu(window.getSize().x, window.getSize().y);
	
	PauseButton pause(window.getSize().x, window.getSize().y);

	sf::Texture bulletTexture;
	bulletTexture.loadFromFile("fireBullet2.png");

	Bullet bulletprojectile;
	std::vector <Bullet> ::const_iterator iter;
	std::vector <Bullet> bulletArray;
	int counter;
	int bulletCooldown = 0;

	bulletEnemy bulletprojectile2;
	std::vector <bulletEnemy> ::const_iterator iter2;
	std::vector <bulletEnemy> bulletArray2;
	int counter2;
	int bulletCooldown2 = 0;

	int test1 = 0;
	int test2 = 0;
	int test3 = 0;
	int test4 = 0;

	int permissionOfShoot = 0;

	int dropItem = 0;

	int intoStage = 0;

	Textbox textbox1(24, sf::Color(120, 120, 120, 80), false, font, sf::Vector2f(600.0f, 340.0f));
	
	sf::Font fontForHighScore;
	fontForHighScore.loadFromFile("font/FC Friday Medium Italic.otf");
	
	//try to do High score
	FILE* fp;
	char Temp[255];
	int score[6];
	string name[6];
	vector <pair<int, string>> userScore;
	fp = fopen("./HighScore.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &Temp);
		name[i] = Temp;
		fscanf(fp, "%d", &score[i]);
		userScore.push_back(make_pair(score[i], name[i]));
		//std::cout << Temp << " " << score;
	}
	//name[5] = "BIG";
	//score[5] ;
	userScore.push_back(make_pair(score[5], name[5]));
	sort(userScore.begin(), userScore.end());
	fclose(fp);
	fopen("./HighScore.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		strcpy(Temp, userScore[i].second.c_str());
		fprintf(fp, "%s %d\n", Temp, userScore[i].first);
		//std::cout << userScore[i].second << " " << userScore[i].first << endl;
	}
	fclose(fp);

	int end = 1;

	//เข้าสู่ส่วนของลูป********************************************************************************************************************
	while (window.isOpen())
	{
		while (game == 1)
		{
			//อันนี้เอาไว้ทำไรวะลืม*************************************************************
			deltaTime = clock.restart().asSeconds();

			//GO To stage2 ยังไม่เสร็จ***************************************************************
			if (enemyLeftCount == 0)
			{
				test1 = 1; //เอาไว้วาด please 4 to continue
			}
			if (enemyLeftCount == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && intoStage == 0)
			{
				test1 = 2;  // please 4 to ... จะหายไป
				test2 = 1; // เอาไว้วาด stage2!!!
				enemyLeftCount = 10;
				intoStage = 1;
			}
			if (enemyLeftCount == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && intoStage == 1)
			{
				test1 = 2;  // please 4 to ... จะหายไป
				test3 = 1; // เอาไว้วาด stage3!!!
				enemyLeftCount = 20;
				intoStage = 2;
			}
			if (enemyLeftCount == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && intoStage == 2)
			{
				test1 = 2;  // please 4 to ... จะหายไป
				test4 = 1; // เอาไว้วาด stage3!!!
				enemyLeftCount = 10;
				intoStage = 3;
			}


			//pauseButton*****************************************************************
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				game = 2;
			}

			//เซ็ตตำเเหน่งตัวโชว์score**********************************************************
			scoreText.setPosition(hpBar.getPosition().x + 800, -350);
			fontScore.setPosition(hpBar.getPosition().x + 640, -350);

			enemyLeftText.setPosition(hpBar.getPosition().x + 810, -250);
			enemyleft.setPosition(hpBar.getPosition().x + 640, -250);

			congreat.setPosition(hpBar.getPosition().x + 550, 300);

			stage1.setPosition(hpBar.getPosition().x + 300, -300);
			stage2.setPosition(hpBar.getPosition().x + 300, -300);
			stage3.setPosition(hpBar.getPosition().x + 300, -300);
			BossStage.setPosition(hpBar.getPosition().x + 95, -300);
			stagewin.setPosition(hpBar.getPosition().x + 300, -300);
			stagewon.setPosition(hpBar.getPosition().x + 300, 100);

			//สุ่มตำเเหน่งการเกิดไอเทมเพิ่มเลือด****************************************************

			if (itemClock.getElapsedTime().asSeconds() >= 10)
			{
				random_x = rand() % window.getSize().x + view.getCenter().x - window.getSize().x / 2;
				random_y = rand() % 200;
				blood.setPosition(random_x, random_y);
				itemClock.restart();
			}
			
			//เก็บเลือดเเล้วหลอดเลือดเพิ่ม**********************************************************

			if (player.hitboxplayer2->getGobalBounds().intersects(blood.getGlobalBounds()))
			{
				if (player.returnHP() + 100 <= 500)
				{
					blood.setPosition(100000, 100000);
					player.plusHP();
					hpBar.setSize(sf::Vector2f(player.returnHP() * 1, 20));
				}
			}

			//Set player อยู่ตรงกลางตลอด*****************************************************
			
			if (player.GetPosition().x >= 8 && player.GetPosition().x <= 13000)
			{
				//if (enemies.size() == 0)
				//{
					view.setCenter(player.GetPosition().x, 0);
				//}
			}
			//view.setCenter(player.GetPosition().x, player.GetPosition().y);
			
			//เรียกบอสออกมา*****************************************************************************************

			while (napat == 0)
			{
				if (player.GetPosition().x >= 0)
				{
					enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, -100, 0));
					napat = 1;
				}
				break;
			}
			

			while (napat == 1)
			{
				if (player.GetPosition().x >= 800)
				{
					enemies.push_back(new Enemy(&orcTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 300, 0));
					enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, abs(player.GetPosition().x) - 300, 0));
					enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) - 300, 0));
					napat = 2;
				}
				break;
			}


			while (napat == 2)
			{
				if (player.GetPosition().x >= 1600)
				{
					enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) - 450, 0));
					enemies.push_back(new Enemy(&orcTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, abs(player.GetPosition().x) + 600, 100));
					enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) - 450, 500));
					napat = 3;
				}
				break;
			}
			while (napat == 3)
			{
				if (player.GetPosition().x >= 2400)
				{
					enemies.push_back(new Enemy(&orcTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) - 450, 0));
					enemies.push_back(new Enemy(&orcTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, abs(player.GetPosition().x) + 600, 100));
					enemies.push_back(new Enemy(&orcTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) - 450, 500));
					napat = 4;
				}
				break;
			}

			while (test1 == 2 )
			{
				if (napat == 4)
				{
					enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) - 450, 0));
					enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, abs(player.GetPosition().x) + 600, 100));
					enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) - 450, 500));
					napat = 5;
				}
				break;
			}

			if (napat == 5)
			{
				enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 2000, 0));
				enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, abs(player.GetPosition().x) + 1500, 100));
				enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 1500, 500));
				napat = 6;
			}

			if (napat == 6)
			{
				enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 1200, 0));
				enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, abs(player.GetPosition().x) + 600, 100));
				enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 900, 500));
				enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 1200, 300));
				napat = 7;
			}

			while (test3 == 2)
			{
				if (napat == 7)
				{
					enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 1000, 0));
					enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 900, 0));
					enemies.push_back(new Enemy(&orcTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 900, 500));
					enemies.push_back(new Enemy(&orcTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, abs(player.GetPosition().x) + 900, 100));
					napat = 8;
				}
				break;
			}

			if (napat == 8 && enemyLeftCount == 16)
			{
				enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 1000, 0));
				enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 900, 0));
				enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 900, 500));
				enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, abs(player.GetPosition().x) + 900, 100));
				napat = 9;
			}

			if (napat == 9 && enemyLeftCount == 12)
			{
				enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 1000, 0));
				enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 900, 0));
				enemies.push_back(new Enemy(&orcTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 900, 500));
				enemies.push_back(new Enemy(&orcTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, abs(player.GetPosition().x) + 900, 100));
				napat = 10;
			}

			if (napat == 10 && enemyLeftCount == 8)
			{
				enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 1000, 0));
				enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 900, 0));
				enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 900, 500));
				enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, abs(player.GetPosition().x) + 900, 100));
				napat = 11;
			}

			if (napat == 11 && enemyLeftCount == 4)
			{
				enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 1000, 0));
				enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 900, 0));
				enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 900, 500));
				enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, abs(player.GetPosition().x) + 900, 100));
				napat = 12;
			}

			while (test4 == 2)
			{
				if (napat == 12)
				{
					backgroundmusic.stop();
					bossOne.push_back(new Boss1(&boss1Texture2, sf::Vector2u(4, 4), 0.1f, 0.0f, abs(player.GetPosition().x) + 900, 100));
					enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 1000, 0));
					enemiesShooter.push_back(new EnemyShooter(&shooterTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 900, 0));
					enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 100.0f, abs(player.GetPosition().x) + 900, 500));
					enemies.push_back(new Enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, 0.0f, abs(player.GetPosition().x) + 900, 100));
					napat = 13;
				}
				break;
			}

			//ปริ้นท์ตำเเหน่งของเพลเยอเเละenemy*****************************************************

			//printf("x = %.f y = %.f\n", player.GetPosition().x, player.GetPosition().y);
			/*for (auto* i : enemies) {
				printf("x = %.f y = %.f\n", i->GetPosition().x, i->GetPosition().y);
			}*/
			//printf("x = %.f y = %.f\n", box_bg.getPosition().x, box_bg.getPosition().y);

			//*******************************************************************************
			sf::Event evnt;
			while (window.pollEvent(evnt))
			{
				switch (evnt.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case  sf::Event::Resized:
					printf("New window width: %i New eindow height: %i\n", evnt.size.width, evnt.size.height);
					ResizeView(window, view);
					break;
				/*case sf::Event::TextEntered:
					if (evnt.text.unicode < 128)
					{
						printf("%c", evnt.text.unicode);
					}*/
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
				}
				
			}

			//WINDOW COLLISION*****************************************************
			//Lef window collision
			if (player.GetPosition().x <= -433)
			{
				player.setPosition(-433, player.GetPosition().y);
			}
			//Top window collision
			if (player.GetPosition().y <= -121)
			{
				player.setPosition(player.GetPosition().x, -121);
			}
			//Low window Collision
			if (player.GetPosition().y >= 200)
			{
				player.setPosition(player.GetPosition().x, 200);
			}

			//WINDOW COLLISION of Enemy*********************************************
			for (auto* i : enemies)
			{
				//Lef window collision
				if (i->GetPosition().x <= -433)
				{
					i->setPosition(-433, i->GetPosition().y);
				}
				//Top window collision
				if (i->GetPosition().y <= -17)
				{
					i->setPosition(i->GetPosition().x, -17);
				}
				//Low window Collision
				if (i->GetPosition().y >= 150)
				{
					i->setPosition(i->GetPosition().x, 150);
				}
			}

			for (auto* i : enemiesShooter)
			{
				//Lef window collision
				if (i->GetPosition().x <= -433)
				{
					i->setPosition(-433, i->GetPosition().y);
				}
				//Top window collision
				if (i->GetPosition().y <= -17)
				{
					i->setPosition(i->GetPosition().x, -17);
				}
				//Low window Collision
				if (i->GetPosition().y >= 150)
				{
					i->setPosition(i->GetPosition().x, 150);
				}
			}

			//Attack Sound Effect***********************************************************
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
			{
				swordEffect.play();
			}

			//Enemy Collision****************************************************************
			for (auto* i : enemies)
			{
				for (auto* j : enemies)
				{
					if (i != j)
					{
						(j->GetCollider().checkCollision(i->GetCollider(), 1.0f));
					}
				}
			}

			for (auto* i : enemiesShooter)
			{
				for (auto* j : enemiesShooter)
				{
					if (i != j)
					{
						(j->GetCollider().checkCollision(i->GetCollider(), 1.0f));
					}
				}
			}

			//Enemy Attack*******************************************************************
			for (auto* i : enemies)
			{
				for (auto* j : enemies)
				{
					if (i->hitboxEnemy->getGobalBounds().intersects(player.hitboxplayer2->getGobalBounds()))
			        {
				        i->row = 2;
				        if (hpclock.getElapsedTime().asSeconds() >= 1.0f)
				        {
					        hpclock.restart();
					        player.decreaseHp();
					        hpBar.setSize(sf::Vector2f(player.returnHP() * 1, 20));
				        }

			        }
			        else if (j->hitboxEnemy->getGobalBounds().intersects(player.hitboxplayer2->getGobalBounds()))
			        {
				        j->row = 2;
				        if (hpclock.getElapsedTime().asSeconds() >= 1.0f)
				        {
					        hpclock.restart();
					        player.decreaseHp();
					        hpBar.setSize(sf::Vector2f(player.returnHP() * 1, 20));
				        }
			        }
				}
			}
			hpBar.setPosition(view.getCenter().x - window.getSize().x / 2, view.getCenter().y - window.getSize().y / 2);
			//std::cout << window.getSize().x << std::endl;
			hpOutline.setPosition(view.getCenter().x - window.getSize().x / 2, view.getCenter().y - window.getSize().y / 2);

			
			for (auto* i : bossOne)
			{
				for (auto* j : bossOne)
				{
					if (i->hitboxbossOne->getGobalBounds().intersects(player.hitboxplayer2->getGobalBounds()))
					{
						i->row = 1;
						if (hpclock.getElapsedTime().asSeconds() >= 2.0f)
						{
							hpclock.restart();
							player.decreaseHpByBoss();
							hpBar.setSize(sf::Vector2f(player.returnHP() * 1, 20));
						}

					}
					else if (j->hitboxbossOne->getGobalBounds().intersects(player.hitboxplayer2->getGobalBounds()))
					{
						j->row = 1;
						if (hpclock.getElapsedTime().asSeconds() >= 2.0f)
						{
							hpclock.restart();
							player.decreaseHpByBoss();
							hpBar.setSize(sf::Vector2f(player.returnHP() * 1, 20));
						}
					}
				}
			}
			hpBar.setSize(sf::Vector2f(player.returnHP() * 1, 20));
			hpBar.setPosition(view.getCenter().x - window.getSize().x / 2, view.getCenter().y - window.getSize().y / 2);
			//std::cout << window.getSize().x << std::endl;
			hpOutline.setPosition(view.getCenter().x - window.getSize().x / 2, view.getCenter().y - window.getSize().y / 2);


			//Attack Enemy*************************************************************
			int temp = 0;
			for (auto* i : enemies)
			{
				if (player.hitbox->getGobalBounds().intersects(i->hitboxEnemy2->getGobalBounds()))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
					{
						if (i->returnHP() == 0)
						{
							delete enemies.at(temp);
							scoreCount += 1;
							enemyLeftCount -= 1;
							enemies.erase(enemies.begin() + temp);
							temp--;
						}
						else
						{
							i->decreaseHP();
							i->setColor();
						}
					}
				}
				temp++;
			}

			temp = 0;
			for (auto* i : enemiesShooter)
			{
				if (player.hitbox->getGobalBounds().intersects(i->hitboxEnemy2->getGobalBounds()))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
					{
						if (i->returnHP() == 0)
						{
							delete enemiesShooter.at(temp);
							scoreCount += 1;
							enemyLeftCount -= 1;
							enemiesShooter.erase(enemiesShooter.begin() + temp);
							temp--;
						}
						else
						{
							i->decreaseHP();
							i->setColor();
						}
					}
				}
				temp++;
			}

			temp = 0;
			for (auto* i : bossOne)
			{
				if (player.hitbox->getGobalBounds().intersects(i->hitboxbossOne2->getGobalBounds()))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
					{
						if (i->returnHP() == 0)
						{
							delete bossOne.at(temp);
							scoreCount += 1;
							enemyLeftCount -= 1;
							bossOne.erase(bossOne.begin() + temp);
							temp--;
						}
						else
						{
							i->decreaseHP();
							i->setColor();
							i->row = 2;
						}
					}
				}
				temp++;
			}
			
			//if shoot enemy*************************************************************************************
			temp = 0;
			for (auto* i : enemies)
			{
				counter = 0;
				for (iter = bulletArray.begin(); iter != bulletArray.end(); iter++)
				{
					if (bulletArray[counter].rect.getGlobalBounds().intersects(i->hitboxEnemy2->getGobalBounds()) && i->returnHP() > 0)
					{
						i->decreaseHpbyBullet();
						i->setColor();
						if(i->returnHP() <= 0)
						{
							delete enemies.at(temp);
							scoreCount += 1;
							enemyLeftCount -= 1;
							enemies.erase(enemies.begin() + temp);
							temp--;
							break;
						}
						bulletArray[counter].bulletin = false;
					}
					counter++;
				}
				temp++;
			}

			temp = 0;
			for (auto* i : enemiesShooter)
			{
				counter = 0;
				for (iter = bulletArray.begin(); iter != bulletArray.end(); iter++)
				{
					if (bulletArray[counter].rect.getGlobalBounds().intersects(i->hitboxEnemy2->getGobalBounds()) && i->returnHP() > 0)
					{
						
						i->decreaseHpbyBullet();
						i->setColor();
						
						if(i->returnHP() <= 0)
						{
							scoreCount += 1;
							enemyLeftCount -= 1;
							delete enemiesShooter.at(temp);
							enemiesShooter.erase(enemiesShooter.begin() + temp);
							temp--;
							break;
						}
						bulletArray[counter].bulletin = false;
					}
					counter++;
				}
				temp++;
			}

			
			for (auto* i : enemiesShooter)
			{
				if (i->returnHP() <= 1)
				{
					item.setPosition(i->GetPosition().x, i->GetPosition().y);
					dropItem = 1;
					//printf("\n napat   ");
				}
			}

			if (player.hitboxplayer2->getGobalBounds().intersects(item.getGlobalBounds()))
			{
				permissionOfShoot = 1;
				item.setPosition(14000, 14000);
			}

			//printf("\n %d   ", dropItem);

			temp = 0;
			for (auto* i : bossOne)
			{
				counter = 0;
				for (iter = bulletArray.begin(); iter != bulletArray.end(); iter++)
				{
					if (bulletArray[counter].rect.getGlobalBounds().intersects(i->hitboxbossOne2->getGobalBounds()) && i->returnHP() > 0)
					{

						i->decreaseHpbyBullet();
						i->setColor();

						if (i->returnHP() <= 0)
						{
							scoreCount += 1;
							enemyLeftCount -= 1;
							delete bossOne.at(temp);
							bossOne.erase(bossOne.begin() + temp);
							temp--;
							break;
						}
						bulletArray[counter].bulletin = false;
					}
					counter++;
				}
				temp++;
			}

			//Shoot Enemy
			if (permissionOfShoot == 1)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					shootEffect.play();
					if (bulletCooldown == 0)
					{
						if (bulletprojectile.direction == 2)
						{
							bulletprojectile.rect.setPosition(player.body.getPosition().x + 30, player.body.getPosition().y);
							//bulletprojectile.rect.setPosition(100, 100);
						}
						else if (bulletprojectile.direction == 1)
						{
							bulletprojectile.rect.setPosition(player.body.getPosition().x - 30, player.body.getPosition().y);
						}
						bulletprojectile.direction = player.playerDirection;
						bulletprojectile.bulletRange = player.body.getPosition().x;
						bulletArray.push_back(bulletprojectile);
					}
				}
			}
			
			bulletCooldown++;
			if (bulletCooldown >= 100)
			{
				bulletCooldown = 0;
			}

			//Enemy Shoot

			for (auto* i : enemiesShooter)
			{
				for (auto* j : enemiesShooter)
				{
					if (i->hitboxAttackEnemyShooter->getGobalBounds().intersects(player.hitboxplayer2->getGobalBounds()))
					{
						i->row = 2;
					}
					else if (j->hitboxAttackEnemyShooter->getGobalBounds().intersects(player.hitboxplayer2->getGobalBounds()))
					{
						j->row = 2;
					}
				}
			}

			for (auto* i : enemiesShooter)
			{
				if (player.hitboxplayer2->getGobalBounds().intersects(i->hitboxAttackEnemyShooter->getGobalBounds()))
				{
					if (bulletCooldown2 == 0)
					{
						if (bulletprojectile2.direction == 2)
						{
							bulletprojectile2.rect.setPosition(i->GetPosition().x + 30, i->GetPosition().y);
							//bulletprojectile.rect.setPosition(100, 100);
						}
						else if (bulletprojectile2.direction == 1)
						{
							bulletprojectile2.rect.setPosition(i->GetPosition().x - 30, i->GetPosition().y);
						}
						bulletprojectile2.direction = i->enemyShootDirection;
						bulletprojectile2.bulletRange = i->GetPosition().x;
						bulletArray2.push_back(bulletprojectile2);
					}
				}
			}
			bulletCooldown2++;
			if (bulletCooldown2 >= 500)
			{
				bulletCooldown2 = 0;
			}

			//ศัตรูยิงเราเเล้วเลือด ลด **********************************************************************************************
			temp = 0;
			counter2 = 0;
			for (iter2 = bulletArray2.begin(); iter2 != bulletArray2.end(); iter2++)
			{
				if (bulletArray2[counter2].rect.getGlobalBounds().intersects(player.hitboxplayer2->getGobalBounds()))
				{
					player.decreaseHp();
					hpBar.setSize(sf::Vector2f(player.returnHP() * 1, 20));
					bulletArray2[counter2].bulletin = false;
				}
				counter2++;
			}
			temp++;
			hpBar.setPosition(view.getCenter().x - window.getSize().x / 2, view.getCenter().y - window.getSize().y / 2);
			//std::cout << window.getSize().x << std::endl;
			hpOutline.setPosition(view.getCenter().x - window.getSize().x / 2, view.getCenter().y - window.getSize().y / 2);

			//ผลักศัตรู (!!!ยังบัคอยู่!!!)****************************************************
			for (auto* i : enemies)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
				{
					if (player.hitbox->getGobalBounds().intersects(i->getGobalBounds()))
					{
						/*if (K_clock.getElapsedTime().asSeconds() >= 3)
						{*/
							if (i->GetPosition().x < player.GetPosition().x)
							{
								i->setPosition(player.GetPosition().x - 300.0f , i->GetPosition().y);
								//K_clock.restart();
							}
							else if (i->GetPosition().x > player.GetPosition().x)
							{
								i->setPosition(player.GetPosition().x + 300.0f, i->GetPosition().y);
								//K_clock.restart();
							}
							//K_clock.restart();
						//}
					}
				}
			}

			for (auto* i : enemiesShooter)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
				{
					if (player.hitbox->getGobalBounds().intersects(i->getGobalBounds()))
					{
						/*if (K_clock.getElapsedTime().asSeconds() >= 3)
						{*/
						if (i->GetPosition().x < player.GetPosition().x)
						{
							i->setPosition(player.GetPosition().x - 300.0f, i->GetPosition().y);
							//K_clock.restart();
						}
						else if (i->GetPosition().x > player.GetPosition().x)
						{
							i->setPosition(player.GetPosition().x + 300.0f, i->GetPosition().y);
							//K_clock.restart();
						}
						//K_clock.restart();
					//}
					}
				}
			}

			//ปริ้นท์มาเช็คเฉยๆ
			//printf("%d", enemy.returnHP());

			//HitBox********************************************************
			if (player.faceRight == true)
			{
				player.hitbox->update(player.body.getPosition(), -80, 10);
			}
			else if (player.faceRight == false)
			{
				player.hitbox->update(player.body.getPosition(), 80, 10);
			}

			player.hitboxplayer2->update(player.body.getPosition(), -5, 3);

			for (auto* i : enemies)
			{
				if (i->faceRight == true)
				{
					i->hitboxEnemy->update(i->GetPosition(), -80, 10);
				}
				else if (i->faceRight == false)
				{
					i->hitboxEnemy->update(i->GetPosition(), 80, 10);
				}
			}

			for (auto* i : enemies)
			{
				i->hitboxEnemy2->update(i->GetPosition(), -5, 10);
			}

			for (auto* i : bossOne)
			{
				if (i->faceRight == true)
				{
					i->hitboxbossOne->update(i->GetPosition(), -80, 10);
				}
				else if (i->faceRight == false)
				{
					i->hitboxbossOne->update(i->GetPosition(), 80, 10);
				}
			}

			for (auto* i : bossOne)
			{
				i->hitboxbossOne2->update(i->GetPosition(), -5, 10);
			}

			for (auto* i : enemiesShooter)
			{
				if (i->faceRight == true)
				{
					i->hitboxAttackEnemyShooter->update(i->GetPosition(), -200, 10);
				}
				else if (i->faceRight == false)
				{
					i->hitboxAttackEnemyShooter->update(i->GetPosition(), 200, 10);
				}
			}

			for (auto* i : enemiesShooter)
			{
				i->hitboxEnemy2->update(i->GetPosition(), -5, 10);
			}

			//Update Functions********************************************************************************************

			player.update(deltaTime);
			princess.update(deltaTime);
			//enemy.update(deltaTime,&player);

			for (auto* i : enemies)
			{
				i->update(deltaTime, &player);
			}
			for (auto* i : enemiesShooter)
			{
				i->update(deltaTime, &player);
			}
			for (auto* i : bossOne)
			{
				i->update(deltaTime, &player);
			}

			//Check ชนกล่อง
			//platform1.GetCollider().checkCollision(player.GetCollider(), 1.0f); // 1คือเลื่อนไม่ได้
			//platform2.GetCollider().checkCollision(player.GetCollider(), 1.0f);
			//platform3.GetCollider().checkCollision(player.GetCollider(), 1.0f);
			//***********************************************************************************************************
			
			//Clear Old Frame
			window.clear();
			//Setview
			window.setView(view);

			//Draw ********************************************************************************************************

			window.draw(box_bg); // Draw background

			//Update Bullet
			counter = 0;
			for (iter = bulletArray.begin(); iter != bulletArray.end(); iter++)
			{
				//std::cout << "run" << std::endl;
				bulletArray[counter].update();
				window.draw(bulletArray[counter].rect);
				counter++;
			}
			counter = 0;
			for (iter = bulletArray.begin(); iter != bulletArray.end(); iter++)
			{
				if (bulletArray[counter].bulletin == false)
				{
					bulletArray.erase(iter);
					break;
				}
				counter++;
			}
			counter2 = 0;
			for (iter2 = bulletArray2.begin(); iter2 != bulletArray2.end(); iter2++)
			{
				//std::cout << "run" << std::endl;
				bulletArray2[counter2].update();
				window.draw(bulletArray2[counter2].rect);
				counter2++;
			}
			counter2 = 0;
			for (iter2 = bulletArray2.begin(); iter2 != bulletArray2.end(); iter2++)
			{
				if (bulletArray2[counter2].bulletin == false)
				{
					bulletArray2.erase(iter2);
					break;
				}
				counter2++;
			}

			player.draw(window); // Draw player
			princess.draw(window);
			//enemy.draw(window);
			for (auto* i : enemies)
			{
				i->draw(window);
			}
			for (auto* i : enemiesShooter)
			{
				i->draw(window);
			}
			for (auto* i : bossOne)
			{
				i->draw(window);
			}
			//platform1.Draw(window);
			//platform2.Draw(window);
			player.render(&window); // draw hitbox
			for (auto* i : enemies)
			{
				i->render(&window);
			}
			for (auto* i : enemiesShooter)
			{
				i->render(&window);
			}
			for (auto* i : bossOne)
			{
				i->render(&window);
			}
			
			if (/*fontStage2Clock.getElapsedTime().asSeconds() > 1.0f &&*/ test1 == 0)
			{
				fontStage1Clock.restart();
				test1 = 3;
			}
			else if (fontStage2Clock.getElapsedTime().asSeconds() <= 4.0f && test1 == 3)
			{
				window.draw(stage1);
			}
			
			if (/*fontStage2Clock.getElapsedTime().asSeconds() > 1.0f &&*/ test2 == 1)
			{
				fontStage2Clock.restart();
				test2 = 2;
			}
			else if (fontStage2Clock.getElapsedTime().asSeconds() <= 4.0f && test2 == 2)
			{
				window.draw(stage2);
			}

			if (/*fontStage2Clock.getElapsedTime().asSeconds() > 1.0f &&*/ test3 == 1)
			{
				fontStage3Clock.restart();
				test3 = 2;
			}
			else if (fontStage3Clock.getElapsedTime().asSeconds() <= 4.0f && test3 == 2)
			{
				//printf("Hello");
				window.draw(stage3);
			}

			if (/*fontStage2Clock.getElapsedTime().asSeconds() > 1.0f &&*/ test4 == 1)
			{
				fontBossStageClock.restart();
				test4 = 2;
			}
			else if (fontBossStageClock.getElapsedTime().asSeconds() <= 4.0f && test4 == 2)
			{
				window.draw(BossStage);
			}
			
			scoreText.setString(std::to_string(scoreCount));
			window.draw(enemyLeftText);
			enemyLeftText.setString(std::to_string(enemyLeftCount));
			window.draw(scoreText);
			window.draw(enemyleft);
			window.draw(fontScore);

			if (test1 == 1)
			{
				window.draw(congreat);
			}

			if (dropItem == 1)
			{
				window.draw(item);
			}
			
			if (player.returnHP() <= 0)
			{
				game = 0;
				userScore.erase(userScore.begin(), userScore.end());
				std::cout << "F";
				fp = fopen("./HighScore.txt", "r");
				for (int i = 0; i < 5; i++)
				{
					fscanf(fp, "%s", &Temp);
					name[i] = Temp;
					fscanf(fp, "%d", &score[i]);
					userScore.push_back(make_pair(score[i], name[i]));
					//std::cout << Temp << " " << score;
				}
				name[5] = textbox1.getName();
				score[5] = scoreCount;
				userScore.push_back(make_pair(score[5], name[5]));
				sort(userScore.begin(), userScore.end());
				fclose(fp);
				fopen("./HighScore.txt", "w");
				for (int i = 5; i >= 1; i--)
				{
					strcpy(Temp, userScore[i].second.c_str());
					fprintf(fp, "%s %d\n", Temp, userScore[i].first);
					//std::cout << userScore[i].second << " " << userScore[i].first << endl;
				}
				fclose(fp);
				textbox1.resetString();

				//window.close();
				while (!enemies.empty())
				{
					enemies.clear();
					//delete enemies.at(0);
				}
				while (!enemiesShooter.empty())
				{
					enemiesShooter.clear();
				}
				while (!bossOne.empty())
				{
					bossOne.clear();
				}

				player.hp = 500;
				/*for (auto* i : enemies)
				{
					i.cla
				}*/
				//break;
				//window.clear();
			}

			/*for (auto* i : bossOne)
			{
				if (i->returnHP() <= 0)
				{
					if (player.getGobalBounds().intersects(princess.getGobalBounds()))
					{
						window.draw(stagewin);
						printf("fg");
					}
				}
			}*/

			if (player.getGobalBounds().intersects(princess.getGobalBounds()) && bossOne.size() <= 0)
			{
				window.draw(stagewin);
				window.draw(stagewon);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
				{
					game = 0;
					userScore.erase(userScore.begin(), userScore.end());
					std::cout << "F";
					fp = fopen("./HighScore.txt", "r");
					for (int i = 0; i < 5; i++)
					{
						fscanf(fp, "%s", &Temp);
						name[i] = Temp;
						fscanf(fp, "%d", &score[i]);
						userScore.push_back(make_pair(score[i], name[i]));
						//std::cout << Temp << " " << score;
					}
					name[5] = textbox1.getName();
					score[5] = scoreCount;
					userScore.push_back(make_pair(score[5], name[5]));
					sort(userScore.begin(), userScore.end());
					fclose(fp);
					fopen("./HighScore.txt", "w");
					for (int i = 5; i >= 1; i--)
					{
						strcpy(Temp, userScore[i].second.c_str());
						fprintf(fp, "%s %d\n", Temp, userScore[i].first);
						//std::cout << userScore[i].second << " " << userScore[i].first << endl;
					}
					fclose(fp);
					textbox1.resetString();

					//window.close();
					while (!enemies.empty())
					{
						enemies.clear();
						//delete enemies.at(0);
					}
					while (!enemiesShooter.empty())
					{
						enemiesShooter.clear();
					}
					while (!bossOne.empty())
					{
						bossOne.clear();
					}

					player.hp = 500;
				}

			}

				/*game = 0;
					userScore.erase(userScore.begin(), userScore.end());
					std::cout << "F";
					fp = fopen("./HighScore.txt", "r");
					for (int i = 0; i < 5; i++)
					{
						fscanf(fp, "%s", &Temp);
						name[i] = Temp;
						fscanf(fp, "%d", &score[i]);
						userScore.push_back(make_pair(score[i], name[i]));
						//std::cout << Temp << " " << score;
					}
					name[5] = textbox1.getName();
					score[5] = scoreCount;
					userScore.push_back(make_pair(score[5], name[5]));
					sort(userScore.begin(), userScore.end());
					fclose(fp);
					fopen("./HighScore.txt", "w");
					for (int i = 5; i >= 1; i--)
					{
						strcpy(Temp, userScore[i].second.c_str());
						fprintf(fp, "%s %d\n", Temp, userScore[i].first);
						//std::cout << userScore[i].second << " " << userScore[i].first << endl;
					}
					fclose(fp);
					textbox1.resetString();

					//window.close();
					while (!enemies.empty())
					{
						enemies.clear();
						//delete enemies.at(0);
					}
					while (!enemiesShooter.empty())
					{
						enemiesShooter.clear();
					}
					while (!bossOne.empty())
					{
						bossOne.clear();
					}

					player.hp = 500;*/
			

			//Key ลัด จบเกม
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
			{
				enemies.clear();
				enemiesShooter.clear();
				test4 = 2;
				napat = 12;
				permissionOfShoot = 1;
				
			}*/

			window.draw(blood);
			window.draw(hpBar);       // วาด หลอดเลือดสีเเดง 
			window.draw(hpOutline);  // วาดกรอบหลอดเลือด
			window.display();
		}
		//******************************************************************************************************************

		//Menu
		while (game == 0)
		{
			view.setCenter(540, 360);
			boxFirstPage.setPosition(0, 0);
			player.hp = 500;
			sf::Event evnt;
			while (window.pollEvent(evnt))
			{
				if (gorn == 1)
				{
					backgroundmusic.play();
					gorn = 2;
				}
				switch (evnt.type)
				{
				case sf::Event::KeyReleased:
					switch (evnt.key.code)
					{
					case sf::Keyboard::Up:
						menu.moveUp();
						break;
					case sf::Keyboard::Down:
						menu.moveDown();
						break;
					case sf::Keyboard::Return:
						switch (menu.GetPressedItem())
						{
						case 0:
							std::cout << "Play has been pressed" << std::endl;
							 game = 4;
							 player.hp = 500;
							 player.setPosition(0.0f, -100.0f);

							 napat = 0;

							 test1 = 0;
							 test2 = 0;
							 test3 = 0;
							 test4 = 0;

							 permissionOfShoot = 0;

							 dropItem = 0;

							 intoStage = 0;

							 scoreCount = 0;

							 enemyLeftCount = 10;

							item.setPosition(10000, 100000);

							view.setCenter(player.GetPosition().x, 0);
							
							break;
						case 1:
							std::cout << "LeaderBoard has been pressed" << std::endl;
							game = 3;
							break;
						case 2:
							std::cout << "Exit has been pressed" << std::endl;
							window.close();
							break;
						case 3:
							std::cout << "Credit has been pressed" << std::endl;
							game = 5;
							break;
						case 4:
							std::cout << "How to play has been pressed" << std::endl;
							game = 6;
							break;
						}
						break;
					}
					break;
				case evnt.TextEntered:
					textbox1.typedOn(evnt);
					break;
				case sf::Event::Closed:
					window.close();
					break;
				}
			}
			window.clear();
			window.draw(boxFirstPage);
			//textbox1.Update(sf::Mouse::getPosition(window));
			window.setView(view);
			menu.draw(window);
			//textbox1.Draw(window);
			window.display();
		}

		//Puase***********************************************************************
		while (game == 2)
		{
			view.setCenter(540, 360);
			sf::Event evnt;
			while (window.pollEvent(evnt))
			{
				switch (evnt.type)
				{
				case sf::Event::KeyReleased:
					switch (evnt.key.code)
					{
					case sf::Keyboard::Up:
						pause.moveUp();
						break;
					case sf::Keyboard::Down:
						pause.moveDown();
						break;
					case sf::Keyboard::Return:
						switch (pause.GetPressedItem())
						{
						case 0:
							std::cout << "Play has been pressed" << std::endl;
							game = 1;
							view.setCenter(player.GetPosition().x, 0);
							break;
						case 1:
							std::cout << "Exit has been pressed" << std::endl;
							window.close();
							break;
						}
						break;
					}
					break;

				case sf::Event::Closed:
					window.close();
					break;
				}
			}
			window.clear();
			window.setView(view);
			pause.draw(window);
			window.display();
		}

		while (game == 3)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
					game = 0;
			}

			window.clear();
			showHighScore(10, 10, "HIGHSCORE", window, &font);
			showHighScore(10, 600, "<<BACKSPACE", window, &font);
			
			showHighScore(10, 100, userScore[5].second, window, &font);
			showHighScore(400, 100, to_string(userScore[5].first), window, &font);

			showHighScore(10, 140, userScore[4].second, window, &font);
			showHighScore(400, 140, to_string(userScore[4].first), window, &font);

			showHighScore(10, 180, userScore[3].second, window, &font);
			showHighScore(400, 180, to_string(userScore[3].first), window, &font);

			showHighScore(10, 220, userScore[2].second, window, &font);
			showHighScore(400, 220, to_string(userScore[2].first), window, &font);

			showHighScore(10, 260, userScore[1].second, window, &font);
			showHighScore(400, 260, to_string(userScore[1].first), window, &font);
			
			window.display();
		}

		while (game == 4)
		{
			view.setCenter(540, 360);
			sf::Event evnt;
			while (window.pollEvent(evnt))
			{
				switch (evnt.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case evnt.TextEntered:
					textbox1.typedOn(evnt);
					break;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					game = 1;
					view.setCenter(player.GetPosition().x, 0);
				}
			}
			window.clear();
			window.setView(view);
			textbox1.Update(sf::Mouse::getPosition(window));
			textbox1.Draw(window);
			window.display();
		}

		while (game == 5)
		{
			view.setCenter(540, 360);
			box_bgCredit.setPosition(0, 0);
			//fontCredit.setPosition(10, 10);
			sf::Event evnt;
			while (window.pollEvent(evnt))
			{
				switch (evnt.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					game = 0;
					//view.setCenter(player.GetPosition().x, 0);
				}
			}
			window.clear();
			window.setView(view);
			window.draw(box_bgCredit);
			showHighScore(10, 5, "<<<BACKSPACE", window, &font);
			//window.draw(fontCredit);
			window.display();
		}

		while (game == 6)
		{
			view.setCenter(540, 360);
			box_bgHow.setPosition(0, 0);
			//fontCredit.setPosition(10, 10);
			sf::Event evnt;
			while (window.pollEvent(evnt))
			{
				switch (evnt.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					game = 0;
					//view.setCenter(player.GetPosition().x, 0);
				}
			}
			window.clear();
			window.setView(view);
			window.draw(box_bgHow);
			showHighScore(10, 5, "<<<BACKSPACE", window, &font);
			//window.draw(fontCredit);
			window.display();
		}
	}
	return 0;
}

void showHighScore(int x, int y, string word, sf::RenderWindow& window, sf::Font* font)
{
	sf::Text text;
	text.setFont(*font);
	text.setPosition(x, y);
	text.setString(word);
	text.setCharacterSize(32);
	window.draw(text);
}