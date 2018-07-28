# TimeoutCallback
The TimeoutCallback library makes it easy to handle events that need to occur after a specific time. For example debouncing a button.

```c
#include <TimeoutCallback.h>

// instantiate the class
TimeoutCallback tc;

// this function will be called once the timeout has expired
void callMe(int value) // must have an int param!
{
	Serial.println("called me");
	// restart the event
	tc.Start(5000);
}

void setup()
{
	Serial.begin(115200);
	// start the callback event: it will call callMe after 3seconds
	tc.Start(&callMe, 3000);
	// you can specify an int parameter to pass to the callback function
	//tc.Start(&callMe, 99, 3000);
}

void loop()
{
	// we need to periodically call the update function, so the library knows the elapsed time
	tc.Update();
}
```


[![Analytics](https://ga-beacon.appspot.com/UA-122950438-1/TimeoutCallback)](https://github.com/igrigorik/ga-beacon)
