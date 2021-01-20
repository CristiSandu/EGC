#include "Player.h"


Player::Player() {
	{
		player = new Mesh("sphere");
		player->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");

	}
}

Player::~Player() {
	delete player;
}

Mesh* Player::GetPlayer() {
	return player;
}
