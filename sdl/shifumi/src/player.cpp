#include <iostream>
#include <player.hpp>

Player::Player(std::string name, PlayerType type) {
    this->type = type; 
    this->name = name;
    this->score = 0;
    this->winner = 0;
}

//Player::~Player() {}
