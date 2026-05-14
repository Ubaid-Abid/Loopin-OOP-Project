#pragma once
#include"user.h"
#include"post.h"
class page {
private:
	string id;
	user* owner;
	string title;
	post** post_shared;
	int numberofposts;
	post** post_owned;
	int owned_posts;
public:
	page();

	string get_id() { return id; }
	void set_page(string id, string title, user*);
	string get_title() { return title; }
	
	void append_post_shared();
	int get_numberofpost() { return numberofposts; }
	post* get_specific_post(int i) { return post_shared[i]; }
	post* get_owned_post(int i) {
		if (i < 0 || i >= owned_posts) return nullptr;
		return post_owned[i];
	}
	post* find_shared_post_by_id(int id) {
		for (int i = 0; i < numberofposts; ++i) {
			if (post_shared[i]->get_id() == id)
				return post_shared[i];
		}
		return nullptr;
	}
	int getpostcount() { return owned_posts; }
	bool add_comment_to_post(int id, string owner, string msg);
	~page();
};