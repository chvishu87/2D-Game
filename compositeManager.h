#ifndef COMPOSITEMANAGER__H
#define COMPOSITEMANAGER__H 

class CompositeManager {
public:
	enum MODE {START, PAUSE, RESUME, HELP, EXIT};

	CompositeManager() {}
	virtual MODE play()=0;
	virtual ~CompositeManager() {}
	
private:
	CompositeManager(const CompositeManager&);
	CompositeManager& operator=(const CompositeManager&);
};

#endif
