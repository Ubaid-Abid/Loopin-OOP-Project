#include"page.h"
#include<fstream>
#include<string>
using namespace std;
page::page() {
	owner = nullptr;
	post_shared = nullptr;
	post_owned = nullptr;
	numberofposts = 0;
	owned_posts = 0;
}


void page::set_page(string id, string name, user* owner) {
	this->id = id;
	this->title = name;
	this->owner = owner;

}

void page::append_post_shared() {
	post** temp = new post * [numberofposts + 1];
	for (int i = 0; i < numberofposts; i++)
		temp[i] = post_shared[i];
	temp[numberofposts] = new post;
	delete[] post_shared;
	post_shared = temp;
	numberofposts++;
}





bool page::add_comment_to_post(int id, string owner, string msg) {


	
	for (int i = 0; i < user::total_users; i++)
	{
		int temp = id;
		if (user::user_record[i]->match_specific_post(temp)) {
			
			user::user_record[i]->get_specific_post(temp)->add_comment(owner, msg);
			i = user::total_users + 1;
			return true;
			break;
		}
	}
	
	for (int i = 0; i < user::total_users; i++) {//in this loop i will go in each page of each user and check for posts
		user* u = user::user_record[i];
		for (int j = 0; j < u->get_ownercount(); j++) {
			page* p = u->get_pages_own(j);//this is specific page
			int count = p->get_numberofpost();//this contain total number of posts that page has
			for (int k = 0; k < count; k++) {
				post* pst = p->get_specific_post(k);//well this is that specific post with whom we are gonna compate
				if (pst->get_id() == id) {
					cout << "Id for post by page has matched!\n";

					pst->add_comment(owner, msg);
					return true;
					break;
				}
			}
		}
	}
	return false;
		
}
page::~page() {
	
	for (int i = 0; i < owned_posts; ++i) {
		delete post_owned[i];
	}
	
	delete[] post_owned;

	for(int i=0;i<numberofposts;i++)
	delete post_shared[i];
	delete[] post_shared;

	
}
