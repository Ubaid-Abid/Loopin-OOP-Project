
#pragma once

#include<string>
#include"date.h"
#include"comment.h"
class user;
class page;
using namespace std;
class post {
private:
	string description;
	string owner_name;
	string activity;
	int id, no_of_likes_by_user, no_of_likes_by_pages;
	user** people_liked;
	page** page_liked;
	Date d;
	comment** total_comment;
	int comment_count;
public:
	post();
	void view_post();
	post(string& description, string owner_name, Date& date, int post_count, string activity);
	post(const string& t, user* u, const Date& date, int post_count, const string& owner, string);
	int get_id() const { return id; }
	void like_increase(user*);
	void like_increase(page*);
	int get_no_of_likes() { return no_of_likes_by_user; }
	int get_no_of_likes_by_pages() { return no_of_likes_by_pages; }
	string get_description() { return description; }
	string get_owner() { return owner_name; }
	void add_comment(string owner,string);
	user** get_likers() { return people_liked; }
	Date getDate() { return d; }
	page** get_page_liked() { return page_liked; }
	int get_comment_count() { return comment_count; }
	comment* get_comments(int i) { return total_comment[i]; }
	string get_activity() { return activity; }
	~post();
};
