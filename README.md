# easy_time
 #### Header Only C++ Timings & Benchmark Library.
easy_time is a wrapper around the `<chrono>` library, designed to make the entire interface easier to use, hence `easy_time`. 

`easy_time` is a header only library, so it can be compiled (using the premake files), or it can be directly put into any project without any linking issues. `easy_time` was made in C++14 and has not been verified to work on any other standard, though more modern standards should compile fine.

# Example:
```cpp

#include "et_time_point_m"

int main()
{

	// This will record the exact time it was created.
	// It is equivilant to std::chrono::high_resolution_clock::now().
	et::time_point_m example_point_now = {};

	// This will convert 1000ms or 1 second to a time_point.
	// This is equivilant to:
	// std::chrono::time_point<hrc>(std::chrono::milliseconds(1 * SECOND))
	// as you can see... it is much simplier.
	et::time_point_m example_point_custom_ms = {1 * SECOND};

	// This will convert the time point to nano seconds as a 64bit integer.
	// This can be used for any of the et types.
	/*
	et::nanoseconds 
	et::microseconds
	et::milliseconds
	et::seconds
	et::minutes
	et::hours
	*/
	// This is equivilant to:
	//long long time_in_ns = std::chrono::time_point_cast<et::nanoseconds>(now).time_since_epoch().count()
	long long time_in_ns = example_point_custom_ms.to<et::nanoseconds>();

}
```

This library will be expanding over an iterative design. If you wish to contribute. Submit a pull-request.