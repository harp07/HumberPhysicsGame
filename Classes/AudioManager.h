/* AudioManager.h
** Manages all the sound effects and music for the game.
** use .wav files since they are supported by all platforms
*/



#include <SimpleAudioEngine.h>
#include <string>

class AudioManager {
	private:
		//The Audio Engine
		SimpleAudioEngine *audioEngine;		

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
		AudioManager(SimpleAudioEngine);
		void playSound(string sound);
		void playMusic(string song, bool loop);
		void stopSound();
		void stopAllSounds();
		void pauseMusic();
		void resumeMusic();
		void stopMusic();
		void setSoundVolume(float);
		void setMusicVolume(float);
		~AudioManager();
		

}




