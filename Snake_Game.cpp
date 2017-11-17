//snake game 
// press w a s d to controll
#include <iostream>
#include <vector>
#include <utility>
#include <conio.h>
#include <windows.h>
using namespace std;

#define height 25//height of board
#define width 25//width of board

int dir = 1;//to track direction in which snake is moving

struct snake {
	int size,x,y;
	vector <pair <int,int> > visit;//to keep track of current snake position 
} s;

struct fruit {
	int x,y;
} f;

void draw () {
	system("cls");
	for (int i=0;i<=width+2;i++) cout<<'$';
	cout<<"\n";
	for (int i=0;i<=height;i++) {
		cout<<'$';
		for (int j=0;j<=width;j++) {
			if (j == f.y && i == f.x) //display fruit
				cout<<"*";
			else {
				bool f = 0;
				for (int k=0;k<s.visit.size();k++) {//display snake
					if (s.visit[k].first == i && s.visit[k].second == j) {
						if (k == s.visit.size()-1)
							cout<<"^";
						else 
							cout<<"#";
						f = 1;
						break;
					}
				}
				if (!f)
				cout<<" ";
			}
		}
		cout<<"$\n";
	}
	for (int i=0;i<width+2;i++) cout<<'$';
	cout<<"\n";
}

void logic () {
	if (f.x == s.x && f.y == s.y) {//if snake hit the fruit
		s.size++;
		int n = s.visit.size();
		int i = s.visit[n-2].first;
		int j = s.visit[n-2].second;
		if (s.y == j + 1) {
			s.visit.push_back({s.x,s.y+1});
			s.y++;
		}
		else if (s.y == j - 1) {
			s.visit.push_back({s.x,s.y-1});
			s.y--;
		}
		else if (s.x == i + 1) {
			s.visit.push_back({s.x+1,s.y});
			s.x++;
		}
		else if (s.x == i - 1) {
			s.visit.push_back({s.x-1,s.y});
			s.x--;
		}
		f.x = rand() % height;
		f.y = rand() % width;
	}
}

bool input () {
	if (dir != -1) {
		if (dir == 0) s.x--;
		else if (dir == 1) s.y++;
		else if (dir == 2) s.y--;
		else if (dir == 3) s.x++;
	}
	if (_kbhit()) {
		dir = -1;
		switch (_getch()) {
			case 'w':
				s.x--;
				dir = 0;
				break;
			case 'd':
				s.y++;
				dir = 1;
				break;
			case 'a':
				s.y--;
				dir = 2;
				break;
			case 's':
				s.x++;
				dir = 3;
				break;
		}
	}
	s.visit.push_back({s.x,s.y});
	s.visit.erase(s.visit.begin());
	for (int i=0;i<s.visit.size();i++) {//if snake touch itself
		for (int j=i+1;j<s.visit.size();j++) {
			if ((s.visit[i].first == s.visit[j].first
			&& s.visit[i].second == s.visit[j].second)) {
				return 1;
			}
		}
	}
	return 0;
}

int main () {
	f.y = rand() % width;
	f.x = rand() % height;
	s.x = 0;s.y = 1;s.size = 2;
	s.visit.push_back({0,0});
	s.visit.push_back({0,1});
	while (1) {
		draw();
		if (input()) {
			cout<<"Game over : Score = "<<s.size-2<<"\n";
			system("pause");
			return 0;
		}
		logic();
		cout<<"Score = "<<s.size - 2<<"\n";
		Sleep(100);
	}
}
