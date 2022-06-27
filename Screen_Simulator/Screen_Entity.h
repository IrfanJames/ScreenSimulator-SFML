#pragma once

#include "Screen_Gloabal.h"
#include "SFML/Graphics.hpp";
using sf::Sprite; using sf::RenderWindow;

class Entity {
public:
	int serial;
	float x, y, dx, dy, radius, angle, life;
	Sprite sprite;

	Entity() { life = 20.0f; x = W / 2; y = H / 2; dx = 0.0f; dy = 0.0f; angle = 0.0f; radius = 1.0f; serial = 0; }

	void setAll(Sprite s, float X, float Y, float Angle = 0.0f, float Radius = 1.0f) {
		x = X; y = Y; angle = Angle; radius = Radius;
		sprite = s;
	}

	virtual void update() {};
	//virtual void hit() {};

	void draw(RenderWindow& app) {
		sprite.setPosition(x, y);
		sprite.setRotation(angle);
		app.draw(sprite);
	}
	~Entity() {
		;
	}

};