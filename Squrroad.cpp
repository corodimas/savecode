#include <SFML/Graphics.hpp>
#include<iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setPosition(200.f, 200.f);
	//texture
	sf::Texture pytexture;
	if (!pytexture.loadFromFile("image/char/squrrial.png"))
	{
		std::cout << "Load fail" << std::endl;
	}
	sf::Texture cartexture;
	if (!cartexture.loadFromFile("image/enimie/ca3.png"))
	{
		std::cout << "Load car fail" << std::endl;
	}

	//spirte char
	sf::Sprite character;
	character.setTexture(pytexture);
	character.setScale(sf::Vector2f(4, 4));
	
	int spriteSizex = pytexture.getSize().x / 3;
	int spriteSizey = pytexture.getSize().y / 4;

	character.setTextureRect(sf::IntRect(0, 0, spriteSizex, spriteSizey));
	sf::Vector2f spawPoint = {0.f, 0.f};
	character.setPosition(spawPoint);
	int animationFrame = 0;

	//sprite car
	sf::Sprite car1;
	car1.setTexture(cartexture);


	
	
	shape.setFillColor(sf::Color::Green);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			character.move(1.f,0.f);
			character.setTextureRect(sf::IntRect(spriteSizex * animationFrame, spriteSizey * 2, spriteSizex, spriteSizey));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			character.move(-.1f, 0.f);
			character.setTextureRect(sf::IntRect(spriteSizex * animationFrame, spriteSizey * 1, spriteSizex, spriteSizey));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			character.move(0.f, -.1f);
			character.setTextureRect(sf::IntRect(spriteSizex * animationFrame, spriteSizey * 3, spriteSizex, spriteSizey));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			character.move(0.f, .1f);
			character.setTextureRect(sf::IntRect(spriteSizex * animationFrame, 0, spriteSizex, spriteSizey));
		}
		animationFrame++;
		car1.move(0.01f, 0.01f);

		if (animationFrame >= 3) {
			animationFrame = 0;
		}

		window.clear();
		window.draw(character);
		window.draw(car1);
		window.display();
	}
	return 0;
}
