#ifndef SELECT_LISTENER_H_
#define SELECT_LISTENER_H_


class SelectListener {

public:
	virtual ~SelectListener() {};

	virtual void handleSelectEvent() = 0;
	virtual void handleSelectEvent(int pointIndex) = 0;
	virtual void handleDeselectEvent() = 0;
};


#endif
