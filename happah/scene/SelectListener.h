#ifndef SELECT_LISTENER_H_
#define SELECT_LISTENER_H_


class SelectListener {

public:
	virtual void handleSelectEvent() = 0;
	virtual void handleDeselectEvent() = 0;


};


#endif
