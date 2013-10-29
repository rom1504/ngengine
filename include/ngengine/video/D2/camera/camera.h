#ifndef NATIV_GAMES_ENGINE_VIDEO_D2_CAMERA_CAMERA_H
#define NATIV_GAMES_ENGINE_VIDEO_D2_CAMERA_CAMERA_H

#include <ngengine/video/opengl/opengl.h>
#include <ngengine/video/texture/texture.h>
#include <glm/glm.hpp>

namespace nge {
  namespace video {
    namespace D2 {

  class Camera {
			public:
				Camera();
				~Camera();

				/* Taille de l'écran, nécessaire pour gérer le zoom correctement */
				void setFrameSize(Sint32 w, Sint32 h);
				void setFrameWidth(Sint32 w);
				void setFrameHeight(Sint32 h);

				/* Manipulation de ce qui est affiché */

				void setPos(Sint32 x, Sint32 y);
				void setX(Sint32 x);
				void setY(Sint32 y);
				void moveX(Sint32 x);
				void moveY(Sint32 y);

				void setSize(Sint32 width, Sint32 height); // width multiple de frameWidth, idem pour height et frameHeight
				void setWidth(Sint32 width);
				void setHeight(Sint32 height);

				void increaseWidth(Sint32 width);
				void increaseHeight(Sint32 height);

				/* Gestion du zoom */
				void zoom(Sint32 value); // augmente la taille de la vue de value * speedX/Y.
				
				Sint32 getZoomCoeff();
				/** coefficient du zoom:
				 *	1000 correspond à un dézoom x1 et c'est le minimum normalement
				 *	1100 correspond à un dézoom x1,1
				 * Permet de gérer la vitesse de la caméra: avancer vers la droite: 
				 *	(cam->getZoomCoeff() * facteurX) / 1000.  
				 */

				Sint32 getZoomXSpeed(); // si écran 800*400, vitesse de 2 selon x, et 1 selon y
				Sint32 getZoomYSpeed(); 

				void convertPixelToCoordinate(Sint32 pxX, Sint32 pxY, Sint32 *x, Sint32 *y);

				// ----

				Sint32 getFrameWidth();
				Sint32 getFrameHeight();

				Sint32 getX();
				Sint32 getY();
				Sint32 getWidth();
				Sint32 getHeight();
				
        

			private:
				void updateSpeed();
        Uint32 getPGCD(Uint32 a, Uint32 b);

				Sint32 _frameW, _frameH; // mêmes valeurs que dans la sous-scène
				Sint32 _xspeed, _yspeed;
				Sint32 _x, _y, _width, _height;
		};

    }
  }
}

#endif
