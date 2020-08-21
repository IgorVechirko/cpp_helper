#ifndef ValotileRegisterKeyWords_H
#define ValotileRegisterKeyWords_H

#include "CommonInclude.h"

namespace ValotileRegisterKeyWords
{

	class DoorController
	{
		volatile  bool _isOpenButtonPressed{false};


		void openDoor()
		{
		}

		void checkInteruptedStates()
		{
			if ( _isOpenButtonPressed ) //compile may optimize this code if volatile  not used
			{
				openDoor();
			}
		}
	};

	void registerKeyWordUsingFunc()
	{
		register char registerVariable = 3;//hit for compiler that variable using very ofter an can be placed in to register or can be granted wiht higher priority

		for( int i = 0; i < 1000000; i++)
		{
			registerVariable += i;
		}
	}
}


#endif