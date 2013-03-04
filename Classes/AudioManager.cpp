/* AudioManager.cpp
** Manages all the sound effects and music for the game.
** use .wav files since they are supported by all platforms
*/

#include "AudioManager.h"
#include <iostream>
#include <string>

//Constructor initializes all the sound and music paths for use with the engine.
AudioManager::AudioManager(SimpleAudioEngine *audioEngine){

	shoot = "/assets/sounds/shoot.wav";
	splash = "/assets/sounds/splash.wav";
	hit = "/assets/sounds/hit.wav";
	song1 = "/assets/music/song1.wav";
	song2 = "/assets/music/song2.wav";
	song3 = "assets/music/song3.wav";
	//etc etc
	
	//Could also preload sounds and music here if desired, with 
	//preloadEffect() and preloadBackgroundMusic()

	this.audioEngine = audioEngine;
}

//Have to release the engine to avoid memory leaks.
AudioManager::~AudioManager(){
	audioEngine.end();
}



void AudioManager::playSound(string sound){
	switch (sound){
		case "shoot":
		  audioEngine.playEffect(shoot);
		  break;
		case "splash":
		  audioEngine.playEffect(splash);
	 	  break
	//etc etc
		default:
		  printf("Sound not found: " + sound); 
	}

	
}

void AudioManager::playMusic(string song, bool loop){
	switch (song){
		case "song1":
		  audioEngine.playBackgroundMusic(song1,loop);
		  break;
		case "song2":
		  audioEngine.playBackgroundMusic(song2,loop);
		  break;s
	//etc etc
		default:
		  printf("Song not found: " + song); 
	}
		  
	
}

//Probably won't use this one because of the id. -just use stopAll
void AudioManager::stopSound(unsigned int id){
	audioEngine.stopEffect(id);
}

void AudioManager::stopAllSounds(){
	audioEngine.stopAllEffects();
}

void AudioManager::pauseMusic(){
	audioEngine.pauseBackgroundMusic();
}

void AudioManager::resumeMusic(){
	audioEngine.resumeBackgroundMusic();
}

void AudioManager::stopMusic(){
	audioEngine.stopBackgroundMusic();
}

//value must be in 0.0~1.0	The engine takes care of range-checking I think.
void AudioManager::setSoundVolume(float value){
	audioEngine.setEffectsVolume(value);
}

void AudioManager::setMusicVolume(float value){
	audioEngine.setBackgroundMusicVolume(value);
}
