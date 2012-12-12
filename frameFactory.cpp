#include "frameFactory.h"

FrameFactory::FrameFactory(): 
	frameContainer(),
	io(IOManager::getInstance()),
	gdata(Gamedata::getInstance()),
	surfact(SurfaceFactory::getInstance())
	{}

FrameFactory& FrameFactory::getInstance() {
	static FrameFactory fact;
	return fact;
}

Frame* FrameFactory::getFrame(int name) {
	Frame * frame = NULL;
	if(frameContainer.find(name) != frameContainer.end()) {
		frame = frameContainer[name];
	} else {
		std::vector<Frame*> vec;	
		switch(name) {
			case 1:
				frame = new Frame(surfact.getSurface(1),
													gdata->getXmlInt("redorbWidth"),
													gdata->getXmlInt("redorbHeight"), gdata->getXmlInt("redorbWidth")*0,0);
				
				break;
			case 2:
				frame = new Frame(surfact.getSurface(1),
													gdata->getXmlInt("redorbWidth"),
													gdata->getXmlInt("redorbHeight"), gdata->getXmlInt("redorbWidth")*1, 0);
				break;
			case 3:
				frame = new Frame(surfact.getSurface(1),
													gdata->getXmlInt("redorbWidth"),
													gdata->getXmlInt("redorbHeight"), gdata->getXmlInt("redorbWidth")*2, 0);
				break;
		case 4:				
				frame = new Frame(surfact.getSurface(1),
													gdata->getXmlInt("redorbWidth"),
													gdata->getXmlInt("redorbHeight"), gdata->getXmlInt("redorbWidth")*3, 0);
				break;
		case 5:
				frame = new Frame(surfact.getSurface(1),
													gdata->getXmlInt("redorbWidth"),
													gdata->getXmlInt("redorbHeight"), gdata->getXmlInt("redorbWidth")*4, 0);
				break;
		case 6:
				frame = new Frame(surfact.getSurface(1),
													gdata->getXmlInt("redorbWidth"),
													gdata->getXmlInt("redorbHeight"), gdata->getXmlInt("redorbWidth")*5, 0);
				break;
		case 7:
				frame = new Frame(surfact.getSurface(2),
													gdata->getXmlInt("bulletWidth"),
													gdata->getXmlInt("bulletHeight"), 0, 0);
				break;
	  default:
				throw("Frame not available");
		}
		frameContainer[name] = frame;
	}
	return frame;
}
