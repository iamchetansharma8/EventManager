#include<iostream>
#include<string>
#define pb push_back
using namespace std;
class user{
	string username,password;
	int id;
	//set<event> eventList;
public:
	user(string username,string password,int id){
		this->username=username;
		this->password=password;
		this->id=id;
	}
	bool operator<(const user& t) const{
		return this->id < t.id;
	}
};