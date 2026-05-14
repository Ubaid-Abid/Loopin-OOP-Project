#pragma once
#pragma once
#include<string>
#include"date.h"
class post;
class page;
using namespace std;
class user {
private:
	string name;
	int id;
	user** friends;
	int friendcount;
	post** user_posts;//posts made by user
	int post_count;
	page** liked_pages;
	int like_count;//this contain number of pages which user has liked
	page** own_pages;
	int owner_count;//this contain number of pages my user has
	post** shareposts;
	int sharecount;

public:
	static user** user_record;
	static int total_users;
	user();
	int get_friendcount() { return friendcount; }
	void set_person(std::string name, int id);
	bool add_friend(int);
	int get_id() const { return id; }
	int get_ownercount() const { return owner_count; }
	string get_name() { return name; }
	page* get_pages_own(int i) { return own_pages[i]; }
	post* get_specific_post(int i) {
		return user_posts[i];
	}
	user* get_specificfriend(int i) { return friends[i]; }
	void create_post_with_info(const char* activity, const char* text, Date date);
	int get_post_count() { return post_count; }
	bool match_specific_post(int& id);
	void appendOwnedPage(page* newPage);
	void append_like_page_array(page* a);
	int get_like_posts() { return like_count; }
	bool share_post(int);
	~user();
};