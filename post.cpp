#include"post.h"
#include"user.h"

void post::like_increase(user* a) {
	no_of_likes_by_user++;
	user** temp = new user * [no_of_likes_by_user];
	for (int i = 0; i < no_of_likes_by_user - 1; i++)
		temp[i] = people_liked[i];
	if (people_liked != nullptr) {
		delete[] people_liked;
	}
	people_liked = temp;
	people_liked[no_of_likes_by_user - 1] = a;
}
void post::like_increase(page* b) {
	no_of_likes_by_pages++;
	page** temp = new page * [no_of_likes_by_pages];
	for (int i = 0; i < no_of_likes_by_pages - 1; i++)
		temp[i] = page_liked[i];
	if (page_liked != nullptr) {
		delete[] page_liked;
	}
	page_liked = temp;
	page_liked[no_of_likes_by_pages - 1] = b;
}
post::post() {
	people_liked = nullptr;
	no_of_likes_by_user = 0;
	no_of_likes_by_pages = 0;
	total_comment = nullptr;
	comment_count = 0;
	
	page_liked = nullptr;
}
post::post(const string& t, user* u, const Date& date, int post_count, const string& owner, string activity)
{
	this->activity = activity;
	owner_name = owner;
	description = t;
	id = (u->get_id() * 100) + post_count;
	d = date;
	no_of_likes_by_user = 0;
	no_of_likes_by_pages = 0;
	people_liked = nullptr;
	page_liked = nullptr;
	total_comment = nullptr;
	comment_count = 0;
}
post::post(string& description, string owner_name, Date& date, int post_count, string activity) {
	this->activity = activity;
	d = date;
	this->owner_name = owner_name;
	this->description = description;
	id = post_count * 10;
	no_of_likes_by_user = 0;
	no_of_likes_by_pages = 0;
	people_liked = nullptr;
	page_liked = nullptr;
	total_comment = nullptr;
	comment_count = 0;
}
void post::add_comment(string owner,string buff) {
	
	comment_count++;
	comment** t = new comment * [comment_count];
	for (int i = 0; i < comment_count - 1; i++) {
		t[i] = total_comment[i];
	}
	if (total_comment != nullptr) 
		delete[] total_comment;
	total_comment = t;
	total_comment[comment_count - 1] = new comment(buff, owner);
}
post::~post() {
	
	for (int i = 0; i < comment_count; ++i) {
		delete total_comment[i];
	}
	
	delete[] total_comment;

	
	delete[] people_liked;
	delete[] page_liked;

	
}




