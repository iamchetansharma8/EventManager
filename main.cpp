#include<iostream>
#include<vector>
#include <iterator>
#include<set>
#include<map>
#include <cstring>
#include <unistd.h>
//#include "event.h"
#include "user.h"
#define pb push_back
using namespace std;
class date{
	int day,month,year;
public:
	date(int day,int month,int year){
		this->day=day;
		this->month=month;
		this->year=year;
	}
};
class event:public date{
	string name;
	set<string> invitedPeeps;
	vector<string> chat;
	string host;
	int strength;
	int total;
public:
	event(string name,int day,int month,int year,int strength,string host):date(day,month,year){
		this->name=name;
		this->strength=strength;
		this->host=host;
		invitedPeeps.insert(host);
		chat.pb(host+" created this group");
		total=1;
	}
	void addMsg(string userName){
		if(invitedPeeps.find(userName)!=invitedPeeps.end()){
			while(1){
			cout<<"Enter your message"<<endl;
			string msg;
			cin.ignore();
			getline(cin,msg);
			msg=userName+" : "+msg;
			chat.pb(msg);
			int choice;
			cout<<"Press '1' to enter a new message"<<endl;
			cout<<"Press '2' to go exit the chat section"<<endl;
			cin>>choice;
			if(choice==1){
				continue;
			}
			break;
		}
			for(int i=0;i<chat.size();i++){
				cout<<chat[i]<<endl;
			}
		}
		else{
			cout<<"Sorry you are not invited to any such event"<<endl;
		}
	}
	void addUser(string userName){
		if(total<strength){
			invitedPeeps.insert(userName);
			total++;
		}
		else{
			cout<<"Sorry, no more people can be invited, seats are full "<<endl;
		}
	}
	void showChat(){
		for(int i=0;i<chat.size();i++){
			cout<<chat[i]<<endl;
		}
	}
};
int WriteFile(string fname, map<string,string> *m)
{
	int count =1;
	if (m->empty())
        return 0;

    FILE *fp = fopen(fname.c_str(), "w");
    if (!fp)
        return -errno;

    for(std::map<std::string, std::string>::iterator it = m->begin(); it != m->end(); it++) {
        fprintf(fp, "%s=%s\n", it->first.c_str(), it->second.c_str());
    }

    fclose(fp);
	return count;
}
int ReadFile(string fname, map<string, string> *m) {
        int count = 0;
        if (access(fname.c_str(), R_OK) < 0)
                return -errno;

        FILE *fp = fopen(fname.c_str(), "r");
        if (!fp)
                return -errno;

        m->clear();

        char *buf = 0;
        size_t buflen = 0;

        while(getline(&buf, &buflen, fp) > 0) {
                char *nl = strchr(buf, '\n');
                if (nl == NULL)
                        continue;
                *nl = 0;

                char *sep = strchr(buf, '=');
                if (sep == NULL)
                        continue;
                *sep = 0;
                sep++;

                std::string s1 = buf;
                std::string s2 = sep;

                (*m)[s1] = s2;

                count++;
        }

        if (buf)
                free(buf);

        fclose(fp);
        return count;
}
/*void chatFunction(string eventName,string userName,map<string,vector<string>> &eventsInvitedTo,map<string,vector<string>> &chat){
	for(int i=0;i<eventsInvitedTo[userName].size();i++){
		if(eventsInvitedTo[userName][i]==eventName){
			while(1){
			cout<<"Enter your message"<<endl;
			string curChat;
			cin.ignore();
			getline(cin,curChat);
			curChat=userName+" : "+curChat;
			chat[eventName].pb(curChat);
			for(int i=0;i<chat[eventName].size();i++){
				cout<<chat[eventName][i]<<endl;
			}
			cout<<"Enter '1' to enter a new message"<<endl;
			cout<<"Enter '2' to exit the chat section"<<endl;
			int opt;
			cin>>opt;
			if(opt==1){
				continue;
			}
			break;
		}
		}
	}
	cout<<"Sorry the event name you have entered doesn't match with any event in our list"<<endl;
}
*/
int main(){
	//map<string,vector<string>> chat;
	set<user*> userList;
	map<string,event*> eventList;
	map<string,string> m;    //username,password
	string fname ="username list";
	int d = ReadFile(fname, &m);	
	map<string,vector<string>> eventsInvitedTo;
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
	    		cout<<"What'd you wish to do"<<endl;
	    		cout<<"Enter '1' to see all the events in which you are invited"<<endl;
	    		cout<<"Enter '2' to create a new event"<<endl;
	    		int choice;
	    		cin>>choice;
	    		if(choice==1){
	    			for(int i=0;i<eventsInvitedTo[username].size();i++){
	    				cout<<eventsInvitedTo[username][i]<<","<<" ";
	    			}
	    			cout<<endl;
	    			cout<<"Enter your choice"<<endl;
	    			cout<<"Enter 1, if you want to enter the chat section of an event"<<endl;
	    			cout<<"Enter 2, to exit"<<endl;
	    			int option;
	    			cin>>option;
	    			if(option==1){
	    				cout<<"Enter the name of the event whose chat section you want to enter"<<endl;
	    				string curName;
	    				cin>>curName;
	    				for(int i=0;i<eventsInvitedTo[username].size();i++){
	    					if(eventsInvitedTo[username][i]==curName){
	    						eventList[curName]->addMsg(username);
	    					}
	    					else{
	    						cout<<"You are not invited to any such event"<<endl;
	    					}
	    				}
	    			}
	    			else{
	    				break;
	    			}
	    		}
	    		else if(choice==2){
	    			cout<<"Enter the name of the event"<<endl;
	    			string eventName;
	    			cin>>eventName;
	    			cout<<"Enter the date month and year on which the event is to be held"<<endl;
	    			int d,m,y;
	    			cin>>d>>m>>y;
	    			cout<<"Enter the number of people you wish to invite to the event"<<endl;
	    			int strength;
	    			cin>>strength;
	    			event *e=new event(eventName,d,m,y,strength,username);
	    			eventsInvitedTo[username].pb(eventName);
	    			eventList[eventName]=e;
	    			while(1){
	    				cout<<"Enter '1' to send invitation to someone"<<endl;
	    				cout<<"Enter '2' to go back"<<endl;
	    				int choice;
	    				cin>>choice;
	    				if(choice==1){
	    					cout<<"Enter the name of the person whom you want to invite"<<endl;
	    					string name;
	    					cin>>name;
	    					if(m.find(name)!=m.end()){
	    						e->addUser(name);
	    						eventsInvitedTo[name].pb(eventName);
	    						cout<<"User Invited"<<endl;
	    					}
	    					else{
	    						cout<<"Enter valid name"<<endl;
	    					}
	    					continue;
	    				}
	    				break;
	    			}
	    		}
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
	    	if(1){
	    		user *newUser=new user(username,password,i);
	    		i++;
	    		userList.insert(newUser);
	    		m[username]=password;
	    		cout<<"The new user is created"<<endl;
				int c = WriteFile(fname, &m);
	    	}
	    	else{
	    		cout<<"Select a different username and password"<<endl;
	    	}
	    }
	    else{
	    	return 0;
	    }
	}
	return 0;
}