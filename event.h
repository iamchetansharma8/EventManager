#include<iostream>
#include<string>
#include<set>
using namespace std;
class event{
	string eventName;
	int capacity;
public:
	event(string eventName,int capacity){
		this->eventName=eventName;
		this->capacity=capacity;
	}
};