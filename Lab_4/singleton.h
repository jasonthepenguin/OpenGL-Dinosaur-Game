#pragma once

// Topic 8 lecture notes, Singleton class

template<class T>
class singleton
{
public:
	static T& Instance() {
		static T _instance;
		return _instance;
	}


private:
	singleton();
	~singleton();
	singleton(singleton const&);
	singleton& operator=(singleton const&);
};