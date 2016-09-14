#include "..\..\include\math\Vector2f.h"

Vector2f::Vector2f(float x, float y) {

}

Vector2f::~Vector2f() {

}

void Vector2f::get(float &x, float &y) {
	x = this->x;
	y = this->y;
}

float Vector2f::getX() {
	return this->x;
}

float Vector2f::getY() {
	return this->y;
}

void Vector2f::set(float x, float y) {
	this->x = x;
	this->y = y;
}

void Vector2f::setX(float x) {
	this->x = x;
}

void Vector2f::setY(float y) {
	this->y = y;
}