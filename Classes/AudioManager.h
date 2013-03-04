/* AudioManager.h
** Manages all the sound effects and music for the game.
** use .wav files since they are supported by all platforms
*/



#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <string>
#include <iostream>
using namespace CocosDenshion;
using namespace std;

using namespace cocos2d;



enum
{
	explosionEffect = 1,
	waterEffect,
	shootEffect,
	hitEffect,
	titleSong,
	gameSong

};

class AudioManager {
	private:
		//The Audio Engine
			
		
	
		//Sounds. These will all be strings of the filepath to the sound.

		string shoot;
		string splash;
		string hit;
		// etc ...  
		//Music
		string song1;
		string song2;
		string song3;
		// etc ...
		
	public:
		AudioManager();
		void playSound(int audioID);
		void playMusic(int audioID, bool loop);
		void stopSound(unsigned int id);
		void stopAllSounds();
		void pauseMusic();
		void resumeMusic();
		void stopMusic();
		void setSoundVolume(float val);
		void setMusicVolume(float val);
		~AudioManager();
		

};




