#include"Comment.h"

comment::comment(string comnt, string owner) {
	this->comnt = comnt;
	this->owner = owner;
}
void comment::give_comment()const {
	cout << owner << " wrote:"; cout << comnt << endl;
}