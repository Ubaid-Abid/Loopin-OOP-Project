#pragma once
#include<iostream>
using namespace std;
class comment {
private:
	string comnt;
	string owner;
public:
	comment() {};
	comment(string commt, string owner);
	void give_comment() const;
	string get_owner() { return owner; }
	string get_text() { return comnt; }
	~comment() {};
};
