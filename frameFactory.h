#ifndef FRAMEFACTORY__H
#define FRAMEFACTORY__H

#include <iostream>
#include <map>
#include <vector>
#include <SDL.h>

#include "frame.h"
#include "ioManager.h"
#include "gamedata.h"
#include "surfaceFactory.h"

class FrameFactory {
public:
	virtual ~FrameFactory() {
		//std::cout<< "Reacing frame factory destructor 1"<<std::endl;
		std::map<int, Frame *>::iterator itr= frameContainer.begin();
		while(itr != frameContainer.end()) {
			delete itr->second;
			//frameContainer.erase(itr);	
			itr++;
		}
		frameContainer.clear();
		//std::cout<<"frame facotry destructor 2"<<std::endl;
	}

	static FrameFactory& getInstance();

	Frame* getFrame(int name);
private:
	std::map<int, Frame*> frameContainer;
	const IOManager& io;
	const Gamedata* gdata;
	SurfaceFactory& surfact;
	FrameFactory(const FrameFactory&);
	FrameFactory& operator=(const FrameFactory&);
	FrameFactory ();
};
#endif
