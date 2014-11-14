

/*
 * aTunes.ino
 */

#include "aTunes.h"

#if defined( ENERGIA )
#define buzzerPin PUSH2
#else
#define buzzerPin 1
#endif



void setup()
{
	pinMode( buzzerPin, OUTPUT );

	switch( 3 )
	{
		case 1:
			ImperialMarch( buzzerPin );
			break;
		case 2:
			ImperialMarchShort( buzzerPin );
			break;
		case 3:
			MarioBros( buzzerPin );
			break;
		default:
			break;
	}

}

void loop()
{

}
