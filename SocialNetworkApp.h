
#pragma once
#pragma once
#include"user.h"
#include"post.h"
#include"date.h"
#include"page.h"
#include"Comment.h"
#include<iostream>
#include<fstream>
#include<string>
#include<limits>
using namespace std;

class SocialNetworkApp {
protected:
	
	Date date;
	page* owner;
	user* person;
public:
	SocialNetworkApp() :person(nullptr), owner(nullptr) {};
	bool Run();
	void set_date();
	
	void welcome();
	Date get_date() { return date; }
    void login();
	void loadfromfile();
	void point_to_owner(page* p);
	void general();
	user* get_user() { return person; }
	~SocialNetworkApp() {};
};

