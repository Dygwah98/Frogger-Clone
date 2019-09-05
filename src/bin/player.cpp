#include"../include/player.h"

Player::Player(): 
    GameObject(), position(0), speed(0.0f), isMoving(false), dir(Keys::nd), lifes(3) {

    cout << "Player::Player() " << this << endl;
}

Player::Player(const int& i, const float& f): 
    GameObject(f), position(0), speed(0.0f), isMoving(false), dir(Keys::nd), lifes(3) {}

Player::~Player() {

    cout << "Player::~Player() " << this << endl;
}

int Player::get_position() const {

    return position;
}

bool Player::is_moving() const {

    return isMoving;
}

bool Player::is_dead() const {

    return lifes == 0;
}

void Player::lose_life() {

    if(lifes > 0) --lifes;
}

void Player::reposition(const int& i, const float& f) {

    position = i;
    set_coord(f);
}

void Player::set_dir(Keys key) {
    
    if(!isMoving) {
    
        isMoving = true;
        dir = key;
    }
}

void Player::move() {
    
    reposition( position + dpos.at(dir), get_coord() + dcord.at(dir)*speed );
}