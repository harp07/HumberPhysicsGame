#include "propulsion.h"
#include "stdlib.h"

#define PTM_RATIO 32.0

using namespace cocos2d;

propulsion::propulsion(b2Vec2 c){
	center = c;
}
propulsion::~propulsion(){
}

void propulsion::addForce(b2Body *b,b2Vec2 f){

	b->ApplyForce(f,center);

}