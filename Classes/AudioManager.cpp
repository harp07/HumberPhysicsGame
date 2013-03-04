/* AudioManager.cpp
** Manages all the sound effects and music for the game.
** use .wav files since they are supported by all platforms
*/

#include "AudioManager.h"



//Constructor initializes all the sound and music paths for use with the engine.
AudioManager::AudioManager(){

	
	shoot = "effect1.wav";
	splash = "splash.wav";
	hit = "hit.wav";
	song1 = "music.mid";
	song2 = "song2.wav";
	song3 = "song3.wav";
	//etc etc
	
	//Could also preload sounds and music here if desired, with 
	//preloadEffect() and preloadBackgroundMusic()
	
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(song1.c_str());
		SimpleAudioEngine::sharedEngine()->preloadEffect(shoot.c_str());
	
	
	
}

//Have to release the engine to avoid memory leaks.
AudioManager::~AudioManager(){
	SimpleAudioEngine::sharedEngine()->end();
}



void AudioManager::playSound(int audioID){
	switch (audioID){
	case shootEffect:
		  SimpleAudioEngine::sharedEngine()->playEffect(shoot.c_str());
		  break;
		case waterEffect:
			SimpleAudioEngine::sharedEngine()->playEffect(splash.c_str());
	 	  break;
	 
		
	}

	
}

void AudioManager::playMusic(int audioID, bool loop){
	switch (audioID){
		case titleSong:
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(song1.c_str(),loop);
		  break;
		case gameSong:
		  SimpleAudioEngine::sharedEngine()->playBackgroundMusic(song2.c_str(),loop);
		  break;
	//etc etc
		
	}
		  
	
}

//Probably won't use this one because of the id. -just use stopAll
void AudioManager::stopSound(unsigned int id){
	SimpleAudioEngine::sharedEngine()->stopEffect(id);
}

void AudioManager::stopAllSounds(){
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

void AudioManager::pauseMusic(){
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AudioManager::resumeMusic(){
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AudioManager::stopMusic(){
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

//value must be in 0.0~1.0	The engine takes care of range-checking I think.
void AudioManager::setSoundVolume(float value){
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(value);
}

void AudioManager::setMusicVolume(float value){
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(value);
}
