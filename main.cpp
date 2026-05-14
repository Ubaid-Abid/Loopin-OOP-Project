#include"SocialNetworkApp.h"
user** user::user_record = nullptr;
int   user::total_users = 0;

int main() {
	SocialNetworkApp s;
	s.Run();
}