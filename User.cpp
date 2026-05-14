#include"user.h"
#include"post.h"
#include<iostream>
#include"page.h"
#include<fstream>
#include<raylib.h>

user::user() {
	friends = nullptr;
	liked_pages = nullptr;
	user_posts = nullptr;
	own_pages = nullptr;
	shareposts = nullptr;
	id = 0;
	friendcount = 0;
	post_count = 0;
	owner_count = 0;
	like_count = 0;
	sharecount = 0;
}
void user::set_person(string name, int id) {
	this->name = name;
	this->id = id;
}
bool user::add_friend(int inputId) {
	if (inputId == this->get_id()) return false;

	
	for (int i = 0; i < friendcount; i++) {
		if (inputId == friends[i]->get_id()) return false;
	}

	
	for (int i = 0; i < total_users; i++) {
		if (inputId == user_record[i]->get_id()) {
			
			user** temp = new user * [friendcount + 1];
			for (int j = 0; j < friendcount; j++)
				temp[j] = friends[j];
			temp[friendcount] = user_record[i];
			friendcount++;
			delete[] friends;
			friends = temp;
			return true;
		}
	}
	return false;
}
bool user::match_specific_post(int& id) {//this function matches id and then return true also it assigns id to current index of post to whom our users id has matched

	for (int i = 0; i < this->post_count; i++) {
		if (id == this->user_posts[i]->get_id())
		{
			id = i;
			return true;
		}
	}
	return false;
}

void user::create_post_with_info(const char* activity, const char* text,Date date) {
	post_count++;

	if (user_posts != nullptr) {
		post** temp = new post * [post_count];
		for (int i = 0; i < post_count - 1; i++)
			temp[i] = user_posts[i];
		delete[] user_posts;
		user_posts = temp;
	}
	else if (user_posts == nullptr)
		user_posts = new post * [post_count];

	user_posts[post_count - 1] = new post(text, this, date, post_count, this->get_name(), activity);
	for (int i = 0; i < post_count - 1; ++i) {
		for (int j = i + 1; j < post_count; ++j) {
			Date A = user_posts[i]->getDate();
			Date B = user_posts[j]->getDate();


			bool shouldSwap = (B.get_y() > A.get_y()) || (B.get_y() == A.get_y() && B.get_m() > A.get_m())
				|| (B.get_y() == A.get_y() && B.get_m() == A.get_m() && B.get_d() > A.get_d());

			if (shouldSwap) {
				post* tmp = user_posts[i];
				user_posts[i] = user_posts[j];
				user_posts[j] = tmp;
			}
		}
	}
}
void user::appendOwnedPage(page* newPage) {

	page** temp = new page * [owner_count + 1];

	for (int k = 0; k < owner_count; ++k)
		temp[k] = own_pages[k];

	temp[owner_count] = newPage;

	delete[] own_pages;
	own_pages = temp;
	owner_count++;
}
void user::append_like_page_array(page* a)
{
	page** temp = new page * [like_count + 1];
	for (int i = 0; i < like_count; i++)
		temp[i] = liked_pages[i];
	temp[like_count] = a;
	like_count++;
	delete[] liked_pages;
	liked_pages = temp;
}
bool user::share_post(int pid) {
	bool c = false;
	for (int i = 0; i < total_users; i++)
	{
		user* temp = user_record[i];
		for (int j = 0; j < temp->post_count; j++)
		{
			if (pid == temp->get_specific_post(j)->get_id()) {
				post** t = new post * [sharecount + 1];
				for (int k = 0; k < sharecount; k++)
					t[k] = shareposts[k];
				t[sharecount] = temp->get_specific_post(j);
				delete[] shareposts;
				shareposts = t;
				sharecount++;
				return true;

			}
		}
	}
	if (!c)
	{
		for (int i = 0; i < total_users; i++)
		{
			for (int j = 0; j < user_record[i]->owner_count; j++)
			{
				page* te = user_record[i]->get_pages_own(j);
				for (int k = 0; k < te->getpostcount(); k++)
				{
					if (pid == te->get_specific_post(k)->get_id()) {
						post** t = new post * [sharecount + 1];
						for (int k = 0; k < sharecount; k++)
							t[k] = shareposts[k];
						t[sharecount] = te->get_specific_post(k);
						delete[] shareposts;
						shareposts = t;
						sharecount++;
						return true;
						
					}
				}


			}
		}
	}
	return false;
}
user::~user(){
	for (int i = 0; i < post_count; ++i) 
		delete user_posts[i];  
	
	delete[] user_posts;

	
	for (int i = 0; i < owner_count; ++i) 
		delete own_pages[i]; 
	
	delete[] own_pages;	
	delete[] friends;
	delete[] liked_pages;
	delete[] shareposts;

}