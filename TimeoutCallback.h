#ifndef TimeoutCallback_h
#define TimeoutCallback_h 
#endif

#include <Arduino.h>

// Type for the callback that has one int parameter and no return values
typedef void(*CallbackType)(int);

// It calls back a function, when the specified time has elapsed
class TimeoutCallback
{
public:
	TimeoutCallback();
	~TimeoutCallback();
	void Setup(CallbackType callbackFunction);
	void Setup(CallbackType callbackFunction, int param);
	void Update(void);
	void Start(unsigned int timeout);
	void Start(CallbackType callbackFunction, unsigned int timeout);
	void Start(CallbackType callbackFunction, int param, unsigned int timeout);
private:
	unsigned long _startTime;
	CallbackType _callbackFunction;
	int _param;
	unsigned int _timeout;
	bool _isRunning;
};

// Constructor - resets all the variables
TimeoutCallback::TimeoutCallback()
{
	_startTime = 0;
	_callbackFunction = NULL;
	_timeout = 0;
	_isRunning = false;
	_param = 0;
}

TimeoutCallback::~TimeoutCallback()
{
}

// Checks whether the timeout has elapsed. You need to call this method periodically
void TimeoutCallback::Update(void)
{
	if (!_isRunning)
	{ // must be running
		return;
	}
	if (NULL == _callbackFunction)
	{ // cannot do a thing without a callback function
		return;
	}

	if (millis() - _startTime >= _timeout)
	{
		_isRunning = false;
		_callbackFunction(_param);
	}
}

// Stores the name of the method to call back
void TimeoutCallback::Setup(CallbackType callbackFunction)
{
	Setup(callbackFunction, 0);
}

// Stores the name of the method to call back
void TimeoutCallback::Setup(CallbackType callbackFunction, int param)
{
	_isRunning = false;
	_callbackFunction = callbackFunction;
	_param = param;
}

// Starts the timer looking for timeout to expire
void TimeoutCallback::Start(unsigned int timeout)
{
	_isRunning = true;
	_startTime = millis();
	_timeout = timeout;
}

// Stores the name of the method to call back and starts the timer looking for timeout to expire
void TimeoutCallback::Start(CallbackType callbackFunction, unsigned int timeout)
{
	Start(callbackFunction, 0, timeout);
}

// Stores the name of the method to call back and starts the timer looking for timeout to expire
void TimeoutCallback::Start(CallbackType callbackFunction, int param, unsigned int timeout)
{
	Setup(callbackFunction, param);
	Start(timeout);
}
