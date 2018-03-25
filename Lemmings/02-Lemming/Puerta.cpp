#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Puerta.h"
#include "Game.h"


enum PuertaAnims
{
	OPENING, OPENED
};


void Puerta::init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram)
{
	state = OPENING;
	spritesheet.loadFromFile("images/puertas2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(33, 20), glm::vec2(1.f, 1.f/10.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(OPENING, 10);

	for (int i = 0; i<10; i++)
		sprite->addKeyframe(OPENING, glm::vec2(0.f, float(i) / 10.f));
	sprite->setAnimationSpeed(OPENED, 0);
	sprite->addKeyframe(OPENED, glm::vec2(0.0f , 9.f / 10.f));
	sprite->changeAnimation(OPENING);
	sprite->setPosition(initialPosition);

}

void Puerta::update(int deltaTime)
{
	if (sprite->update(deltaTime) == 0)
		return;

	switch (state)
	{
	case OPENING:
		if(sprite->currentKeyFrame() == sprite->sizeCurrentAnimation()-1)
			sprite->changeAnimation(OPENED);
		break;
	
	}
}

void Puerta::render()
{
	sprite->render();
}