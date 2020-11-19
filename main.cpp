#include<iostream>
#include<vector>
#include <iterator>
#include<set>
#include<map>
//#include "event.h"
#include "user.h"
using namespace std;

int main(){
	set<user*> userList;
	map<string,string> m;
	int i=1;
	while(1){
		cout<<"Enter you choice"<<endl;
	    cout<<" '1' If you are an existing user"<<endl;
	    cout<<" '2' If you want to sign up"<<endl;
	    cout<<" Any other number to exit the application"<<endl;
	    int choice;
	    cin>>choice;
	    if(choice==1){
	    	string username,password;
	    	cout<<"Enter your username"<<endl;
	    	cin>>username;
	    	cout<<"Enter your password"<<endl;
	    	cin>>password;
	    	string testPass=m[username];
	    	if(password==testPass){
	    		cout<<"Welcome "<<username<<endl;
	    	}
	    	else{
	    		cout<<"Sorry, the details that you have entered do not match with any user in our record"<<endl;
	    	}
	    }
	    else if(choice==2){
	    	cout<<"Enter your username"<<endl;
	    	string username,password;
	    	cin>>username;
	    	cout<<"Enter your password"<<endl;
	    	cin>>password;
	    	user *newUser=new user(username,password,i);
	    	if(userList.find(newUser)==userList.end()){
	    		cout<<"The new user is created"<<endl;
	    		cout<<"Your unique userId is "<<i<<endl;
	    		userList.insert(newUser);
	    		m[username]=password;
	    		i++;
	    	}
	    	else{
	    		delete newUser;
	    		cout<<"Select a different username and password"<<endl;
	    	}
	    }
	    else{
	    	return 0;
	    }
	}
}