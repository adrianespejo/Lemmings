#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>

void Game::init()
{
	actualScene = 0;
	bPlay = true;
	paused = false;
	doubleSpeed = false;
	bLeftMouse = bRightMouse = false;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	mciSendString(TEXT("open sound/MAIN_THEME.mp3 alias main"), NULL, 0, NULL);
	mciSendString(TEXT("play main repeat"), NULL, 0, NULL);
	home.init();
}

bool Game::update(int deltaTime)
{
	switch (actualScene) {

	case 0:
		home.update(deltaTime);
		break;
	case 1:
		if (!paused) {
			pair<bool, bool> cont;
			if (!doubleSpeed) cont = scene.update(deltaTime);
			else cont = scene.update(deltaTime * 2);
			if (!cont.first) {
				if (!cont.second) {
					mciSendString(TEXT("close scene1"), NULL, 0, NULL);
					mciSendString(TEXT("open sound/MAIN_THEME.mp3 alias main"), NULL, 0, NULL);
					mciSendString(TEXT("play main repeat"), NULL, 0, NULL);
					paused = false;
					doubleSpeed = false;
					home.init();
					actualScene = 0;
				}
				else {
					mciSendString(TEXT("close scene1"), NULL, 0, NULL);
					paused = false;
					doubleSpeed = false;
					simpleScene.init(3);
					actualScene = 7;
				}
			}
		}
		break;
	case 2:
		if (!paused) {
			pair<bool, bool> cont;
			if (!doubleSpeed) cont = scene2.update(deltaTime);
			else cont = scene2.update(deltaTime * 2);
			if (!cont.first) {
				if (!cont.second) {
					mciSendString(TEXT("close scene2"), NULL, 0, NULL);
					mciSendString(TEXT("open sound/MAIN_THEME.mp3 alias main"), NULL, 0, NULL);
					mciSendString(TEXT("play main repeat"), NULL, 0, NULL);
					paused = false;
					doubleSpeed = false;
					home.init();
					actualScene = 0;
				}
				else {
					mciSendString(TEXT("close scene2"), NULL, 0, NULL);
					paused = false;
					doubleSpeed = false;
					simpleScene.init(4);
					actualScene = 8;
				}
			}
		}
		break;
	case 3:
		if (!paused) {
			pair<bool, bool> cont;
			if (!doubleSpeed) cont = scene3.update(deltaTime);
			else cont = scene3.update(deltaTime * 2);
			if (!cont.first) {
				if (!cont.second) {
					mciSendString(TEXT("close scene3"), NULL, 0, NULL);
					mciSendString(TEXT("open sound/MAIN_THEME.mp3 alias main"), NULL, 0, NULL);
					mciSendString(TEXT("play main repeat"), NULL, 0, NULL);
					paused = false;
					doubleSpeed = false;
					home.init();
					actualScene = 0;
				}
				else {
					mciSendString(TEXT("close scene3"), NULL, 0, NULL);
					paused = false;
					doubleSpeed = false;
					simpleScene.init(0);
					actualScene = 4;
				}
			}
		}
		break;
	case 4:
		simpleScene.update(deltaTime);
		break;
	case 5:
		simpleScene.update(deltaTime);
		break;
	case 6:
		simpleScene.update(deltaTime);
		break;
	case 7:
		simpleScene.update(deltaTime);
		break;
	case 8:
		simpleScene.update(deltaTime);
		break;
	}
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (actualScene) {
	case 0:
		home.render();
		break;
	case 1:
		scene.render();
		break;
	case 2:
		scene2.render();
		break;
	case 3:
		scene3.render();
		break;
	case 4:
		simpleScene.render();
		break;
	case 5:
		sceneInstruccions.render();
		break;
	case 6:
		simpleScene.render();
		break;
	case 7:
		simpleScene.render();
		break;
	case 8:
		simpleScene.render();
		break;
	}
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;

	if (key == 8) {
		if (actualScene == 4 || actualScene == 5) actualScene = 0;
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	if (actualScene == 0 && key == GLUT_KEY_F1) {
		mciSendString(TEXT("close main"), NULL, 0, NULL);
		simpleScene.init(2);
		actualScene = 6;
	}
	else if (actualScene == 0 && key == GLUT_KEY_F2) {
		mciSendString(TEXT("close main"), NULL, 0, NULL);
		simpleScene.init(3);
		actualScene = 7;
	}
	else if (actualScene == 0 && key == GLUT_KEY_F3) {
		mciSendString(TEXT("close main"), NULL, 0, NULL);
		simpleScene.init(4);
		actualScene = 8;
	}
	else if (actualScene == 0 && key == GLUT_KEY_F4) {
		simpleScene.init(0);
		actualScene = 4;
	}
	else if (actualScene == 0 && key == GLUT_KEY_F5) {
		sceneInstruccions.init();
		actualScene = 5;
	}
	else if (actualScene == 5 && (key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT)) {
		sceneInstruccions.keyPressed(key);
	}
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	mouseX = x;
	mouseY = y;
	switch (actualScene) {
	case 1:
		scene.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse, paused);
		break;
	case 2:
		scene2.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse, paused);
		break;
	case 3:
		scene3.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse, paused);
		break;
	}
}

void Game::mousePress(int button)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		bLeftMouse = true;
		pair<bool, bool> speedOrPause;
		speedOrPause.first = false;
		speedOrPause.second = false;
		switch (actualScene) {
		case 1:
			speedOrPause = scene.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse, paused);
			if (speedOrPause.second) {
				if (paused) mciSendString(TEXT("play scene1 repeat"), NULL, 0, NULL);
				else mciSendString(TEXT("pause scene1"), NULL, 0, NULL);
				paused = !paused;
			}
			if (speedOrPause.first) {
				doubleSpeed = !doubleSpeed;
				if (doubleSpeed) mciSendString(TEXT("set scene1 speed 1500"), NULL, 0, NULL);
				else mciSendString(TEXT("set scene1 speed 1000"), NULL, 0, NULL);
			}
			break;
		case 2:
			speedOrPause = scene2.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse, paused);
			if (speedOrPause.second) {
				if (paused) mciSendString(TEXT("play scene2 repeat"), NULL, 0, NULL);
				else mciSendString(TEXT("pause scene2"), NULL, 0, NULL);
				paused = !paused;
			}
			if (speedOrPause.first) {
				doubleSpeed = !doubleSpeed;
				if (doubleSpeed) mciSendString(TEXT("set scene2 speed 1500"), NULL, 0, NULL);
				else mciSendString(TEXT("set scene2 speed 1000"), NULL, 0, NULL);
			}
			break;
		case 3:
			speedOrPause = scene3.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse, paused);
			if (speedOrPause.second) {
				if (paused) mciSendString(TEXT("play scene3 repeat"), NULL, 0, NULL);
				else mciSendString(TEXT("pause scene3"), NULL, 0, NULL);
				paused = !paused;
			}
			if (speedOrPause.first) {
				doubleSpeed = !doubleSpeed;
				if (doubleSpeed) mciSendString(TEXT("set scene3 speed 1500"), NULL, 0, NULL);
				else mciSendString(TEXT("set scene3 speed 1000"), NULL, 0, NULL);
			}
			break;
		case 6:
			if (bLeftMouse) {
				mciSendString(TEXT("open sound/BACKGROUND-1.mp3 alias scene1"), NULL, 0, NULL);
				mciSendString(TEXT("play scene1 repeat"), NULL, 0, NULL);
				scene.init();
				actualScene = 1;
			}
			break;
		case 7:
			if (bLeftMouse) {
				mciSendString(TEXT("open sound/BACKGROUND-2.mp3 alias scene2"), NULL, 0, NULL);
				mciSendString(TEXT("play scene2 repeat"), NULL, 0, NULL);
				scene2.init();
				actualScene = 2;
			}
			break;
		case 8:
			if (bLeftMouse) {
				mciSendString(TEXT("open sound/BACKGROUND-3.mp3 alias scene3"), NULL, 0, NULL);
				mciSendString(TEXT("play scene3 repeat"), NULL, 0, NULL);
				scene3.init();
				actualScene = 3;
			}
			break;
		}
	}
	else if(button == GLUT_RIGHT_BUTTON)
	{
		bRightMouse = true;
		switch (actualScene) {
		case 1:
			scene.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse, paused);
			break;
		case 2:
			scene2.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse, paused);
			break;
		case 3:
			scene3.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse, paused);
			break;
		}
	}
}

void Game::mouseRelease(int button)
{
	if(button == GLUT_LEFT_BUTTON)
		bLeftMouse = false;
	else if(button == GLUT_RIGHT_BUTTON)
		bRightMouse = false;
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





