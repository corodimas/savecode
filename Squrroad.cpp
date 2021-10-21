#include <SFML/Graphics.hpp>
#include <iostream>


sf::RenderWindow mywindow(sf::VideoMode(850, 1000, 32), "Sqirroad");
sf::View view(sf::Vector2f(850.0f, 350.0f),sf::Vector2f(850.0f, 1000.0f));
sf::Event ev;

int tilesize = 50;
float y = 850;
float x = 350;
float movespeed = 5.0;

bool move[4];
bool walking;
int nextspot;
enum MOVE { UP, DOWN, LEFT, RIGHT };
sf::Sprite character;
sf::Texture pytexture;
int spriteSizex = pytexture.getSize().x / 3;
int spriteSizey = pytexture.getSize().y / 4;
int animationFrame = 0;



void keymove()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)&&y>=0)
    {
        if (walking == false)
        {
            nextspot = y - tilesize;
            move[UP] = true;
            walking = true;

        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S )&& y<=850)
    {
        if (walking == false)
        {
            nextspot = y + tilesize;
            move[DOWN] = true;
            walking = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)&&x>= 0)
    {
        if (walking == false)
        {
            nextspot = x - tilesize;
            move[LEFT] = true;
            walking = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&&x <= 700)
    {
        if (walking == false)
        {
            nextspot = x + tilesize;
            move[RIGHT] = true;
            walking = true;
        }
    }
}

int main()
{
	if (!pytexture.loadFromFile("image/char/squrrial.png"))
	{
		std::cout << "Load fail" << std::endl;
	}
	character.setTexture(pytexture);
	character.setScale(sf::Vector2f(2.5, 2.5));
    int spriteSizex = pytexture.getSize().x / 3;
    int spriteSizey = pytexture.getSize().y / 4;
	character.setTextureRect(sf::IntRect(spriteSizex * animationFrame, spriteSizey * 3, spriteSizex, spriteSizey));
	
	for (int i = 0; i < 4; ++i)
		move[i] = false;
    walking = false;
    mywindow.setVerticalSyncEnabled(true);
	while (mywindow.isOpen())
	{
		while (mywindow.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)mywindow.close();
		}
        keymove();
        if (walking == true)
        {
            if (move[UP] == true)
            {
                y -= movespeed;
                if (y <= nextspot)
                {
                    y = nextspot;
                    walking = false;
                    move[UP] = false;
                }
                character.setTextureRect(sf::IntRect(spriteSizex * animationFrame, spriteSizey * 3, spriteSizex, spriteSizey));
            }

            if (move[DOWN] == true)
            {
                y += movespeed;
                if (y >= nextspot)
                {
                    y = nextspot;
                    walking = false;
                    move[DOWN] = false;
                }
                character.setTextureRect(sf::IntRect(spriteSizex * animationFrame, 0, spriteSizex, spriteSizey));
            }
            if (move[LEFT] == true)
            {
                x -= movespeed;
                if (x <= nextspot)
                {
                    x = nextspot;
                    walking = false;
                    move[LEFT] = false;
                }
                character.setTextureRect(sf::IntRect(spriteSizex * animationFrame, spriteSizey * 1, spriteSizex, spriteSizey));
            }
            if (move[RIGHT] == true)
            {
                x += movespeed;
                if (x >= nextspot)
                {
                    x = nextspot;
                    walking = false;
                    move[RIGHT] = false;
                }
                character.setTextureRect(sf::IntRect(spriteSizex * animationFrame, spriteSizey * 2, spriteSizex, spriteSizey));
            }
        }

        animationFrame++;
        if (animationFrame >= 3) {
            animationFrame = 0;
        }

        character.setPosition(x, y);
        mywindow.clear(sf::Color(0, 200, 0));
        mywindow.draw(character);
        mywindow.display();
	}
}
