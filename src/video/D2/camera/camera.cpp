#include <ngengine/video/D2/camera/camera.h>

using namespace nge;
using namespace nge::camera;

Camera::Camera()
{
	_x = 0;
	_y = 0;
	_width = 0;
	_height = 0;
	_xspeed = 0;
	_yspeed = 0;
}

Camera::~Camera()
{

}

/* ----------- */

void Camera::setFrameSize(Sint32 w, Sint32 h)
{
	_frameW = w;
	_frameH = h;
	this->updateSpeed();
}

void Camera::setFrameWidth(Sint32 w)
{
	_frameW = w;
	this->updateSpeed();
}

void Camera::setFrameHeight(Sint32 h)
{
	_frameH = h;
	this->updateSpeed();
}

/* ------------ */

void Camera::setPos(Sint32 x, Sint32 y)
{
	_x = x;
	_y = y;
}

void Camera::setX(Sint32 x)
{
	_x = x;
}

void Camera::setY(Sint32 y)
{
	_y = y;
}

void Camera::moveX(Sint32 x)
{
	_x += x;
}

void Camera::moveY(Sint32 y)
{
	_y += y;
}

void Camera::setSize(Sint32 width, Sint32 height)
{
	_width = width;
	_height = height;
}

void Camera::setWidth(Sint32 width)
{
	_width = width;
}

void Camera::setHeight(Sint32 height)
{
	_height = height;
}

void Camera::increaseWidth(Sint32 width)
{
	_width += width;
}

void Camera::increaseHeight(Sint32 height)
{
	_height += height;
}

/* Gestion du zoom */

void Camera::zoom(Sint32 value)
{
	if(_xspeed && _yspeed) {

		if(value > 0) { 
			this->moveX(-_xspeed * value);
			this->increaseWidth(2 * _xspeed * value);
			this->moveY(-_yspeed * value);
			this->increaseHeight(2 * _yspeed * value);
		}
		else if(value < 0) {
			if(((_width + 2 * _xspeed * value) >= _frameW) && 
				((_height + 2 * _yspeed * value) >= _frameH)) {
				this->moveX(-_xspeed * value);
				this->increaseWidth(2 * _xspeed * value);
				this->moveY(-_yspeed * value);
				this->increaseHeight(2 * _yspeed * value);
			}
			else { // on bloque
			}
		}
		else;
	}
	else;

	return;
}

Sint32 Camera::getZoomCoeff()
{
	return (_width * 1000) / _frameW; // doit être = ) à : (_height * 1000) / _frameH
}

Sint32 Camera::getZoomXSpeed()
{
	return _xspeed;
}

Sint32 Camera::getZoomYSpeed()
{
	return _yspeed;
}

void Camera::convertPixelToCoordinate(Sint32 pxX, Sint32 pxY, Sint32 *x, Sint32 *y)
{
	if(x && y) {
		*x = (pxX * this->getZoomCoeff()) / 1000 + _x;
		*y = (pxY * this->getZoomCoeff()) / 1000 + _y;
	}
	else;
}

/* -------- */

Sint32 Camera::getX()
{
	return _x;
}

Sint32 Camera::getY()
{
	return _y;
}

Sint32 Camera::getWidth()
{
	return _width;
}

Sint32 Camera::getHeight()
{
	return _height;
}

/* --------- */

void Camera::updateSpeed()
{
	Sint32 pgcd;

	if(_frameW == _frameH) {
		_xspeed = 1;
		_yspeed = 1;
	}

	else {
		pgcd = this->getPGCD(_frameW, _frameH);

		_xspeed = _frameW / pgcd;
		_yspeed = _frameH / pgcd;
	}
}

Uint32 Camera::getPGCD(nge::Uint32 a, nge::Uint32 b)
{
	nge::Uint32 c;

	if(a < b) {
		c = b;
		b = a;
		a = c;
	}
	else;

	do {
		c = a % b;
		if(!c)
			;
		else {
			a = b;
			b = c;
		}
	} while(c);

	return b;
}


