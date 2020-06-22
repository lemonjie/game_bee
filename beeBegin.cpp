// -changed--------------------------------------------------
// HideCursor() / Setcursor(bool visible, DWORD size);		-
// Player(class) name="Guest"								-
// SetChoosePlayerFrame()'s underline						-
// class All (new)											-
// void PrintBackHive(int yStart, int yEnd) (push out)		-
// void PrintCover() (changed)								-
// void PrintPreSet() all (new)								-
// void PrintPreSetName(Player *player1) all (new)			-
// void PrintPreSetUnderline(int ifLogin) all (new)			-
// PreSet (change name)										-
// void PreSet(Player *player1) all (changed)				-
// Player.name string (changed)								-
// PreStory	(new)											-
//-----------------------------------------------------------
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#define PLAYER_POSITION_X 86
#define PLAYER1_POSITION_Y 2
#define PLAYER2_POSITION_Y 6
#define HIVE_SIZE_X 4
#define HIVE_SIZE_Y 14
#define CHOOSE_LOGIN 1
#define ENTER 13
#define SPACE 32
#define ESC 27
#define DIRECTION_KEY 224
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;

void gotoxy(int x, int y);
//void HideCursor();
void Setcursor(bool visible, DWORD size);

class Player {
private:
	int x, y;		//position
	string name;	//player name
	int score;

public:
	Player(int inX, int inY) : x(inX), y(inY), score(0) {
		name.assign("guest");
	}
	void SetName() {
		cin >> name;
		Print();
	}
	void Print() {
		gotoxy(x, y);
		cout << "--------------";
		gotoxy(x, y + 1);
		cout <<"| "<< name;
		gotoxy(x + 13, y + 1);
		cout << "|";
		gotoxy(x, y+2);
		cout << "| Score : " << score;		// bee->GetScore()
		gotoxy(x + 13, y + 2);
		cout << "|";
		gotoxy(x, y + 3);
		cout << "--------------";
	}

	void AddScore(int add) {
		score = score + add;
		Print();
	}
	int GetScore() {
		return score;
	}
};

class Npc {
protected:
	int x, y;
	string name;
	char icon[3][3];
public:
	virtual void Chat() = 0;
	void PrintIcon() {
		for (int i = 0; i < 3; i++) {
			gotoxy(x, y + i);
			cout << icon[i][0] << icon[i][1] << icon[i][2];
		}
	}
	void PrintChatFrame() {
	    char temp = ' ';
		for (int j = 20; j < 30; j++) {
			gotoxy(0, j);
			if((j==20)||(j==29)){
                temp = '=';
			}
			else{
                temp = ' ';
			}
			for (int i = 0; i < 100; i++) {
				cout << temp;
			}
		}
		gotoxy(4, 22);
		cout << " " << name;
		gotoxy(4, 23);
		cout << "==========";
	}
	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}
};
class NpcVillager : public Npc{
public:
	NpcVillager() {
		x = 26, y = 23;
		name = "Villiager";
		icon[0][0] = ' ', icon[0][1] = 'O', icon[0][2] = ' ';
		icon[1][0] = '\\', icon[1][1] = 'I', icon[1][2] = '/';
		icon[2][0] = ' ', icon[2][1] = '^', icon[2][2] = ' ';
		PrintIcon();
	}
	void Chat() {
		PrintChatFrame();
		string story0;
		string story1;
        ifstream test("villager.txt");
        //test.open();
        while(getline(test, story0)){
            for(int j = 24; j < 29; j++){
                    gotoxy(0, j);
                    for(int i = 0; i < 100; i++){
                        cout << " ";
                    }
            }
            gotoxy(30,24);
            cout << story0 << endl;
            if(getline(test, story1)){
                gotoxy(30,25);
                cout << story1 << endl;
            }
            if(_getch() == ESC){
                break;
            }
        }
        test.close();
	}
};
class NpcTank : public Npc{
public:
	NpcTank() {
		x = 92, y = 9;
		name = "Tank";
		icon[0][0] = ' ', icon[0][1] = 'I', icon[0][2] = ' ';
		icon[1][0] = '[', icon[1][1] = '_', icon[1][2] = ']';
		icon[2][0] = 'o', icon[2][1] = 'o', icon[2][2] = 'o';
		PrintIcon();
	}
	void Chat() {
		PrintChatFrame();
		string story0;
		string story1;
        ifstream test("tank.txt");
        //test.open();
        while(getline(test, story0)){
            for(int j = 24; j < 29; j++){
                    gotoxy(0, j);
                    for(int i = 0; i < 100; i++){
                        cout << " ";
                    }
            }
            gotoxy(30,24);
            cout << story0 << endl;
            if(getline(test, story1)){
                gotoxy(30,25);
                cout << story1 << endl;
            }
            if(_getch() == ESC){
                break;
            }
        }
        test.close();
	}
};
class NpcHoney : public Npc{
public:
	NpcHoney() {
		x = 8, y = 5;
		name = "Honey";
		icon[0][0] = ' ', icon[0][1] = '_', icon[0][2] = ' ';
		icon[1][0] = '(', icon[1][1] = '_', icon[1][2] = ')';
		icon[2][0] = ' ', icon[2][1] = ' ', icon[2][2] = ' ';
		PrintIcon();
	}
	void Chat() {
		PrintChatFrame();
		string story0;
		string story1;
        ifstream test("honey.txt");
        //test.open();
        while(getline(test, story0)){
            for(int j = 24; j < 29; j++){
                    gotoxy(0, j);
                    for(int i = 0; i < 100; i++){
                        cout << " ";
                    }
            }
            gotoxy(30,24);
            cout << story0 << endl;
            if(getline(test, story1)){
                gotoxy(30,25);
                cout << story1 << endl;
            }
            if(_getch() == ESC){
                break;
            }
        }
        test.close();
	}
};

class PreGm {
private:

	int everyone[100][30];
	Npc* npcAddress[100][30];

public:

	PreGm() {

		int fullHive[23][2] = { {5,1},{5,25},{12,3},{12,27},{19,25},{26,27},{33,25},{40,23},{40,27},{47,25},{54,27},
								{61,25},{68,23},{68,27},{75,21},{75,25},{82,15},{82,19},{82,23},{82,27},{89,17},{89,21},{89,25} };
		int halfHive[6][2] = { {0,3},{0,27},{96,15},{96,19},{96,23},{96,27} };
		int npcHere[3][2] = { {26,23},{89,9},{5,5} };	//villager, tank. honey

		for (int i = 0; i < 100; i++) {		//all
			for (int j = 0; j < 30; j++) {
				everyone[i][j] = 0;
				npcAddress[i][j] = 0;
			}
		}
		for (int i = 0; i < 23; i++) {		//full hive
			for (int j = 0; j < 4; j++) {
				everyone[fullHive[i][0] + j][fullHive[i][1]] = 1;
			}
		}
		for (int i = 0; i < 6; i++) {		//half hive
			for (int j = 0; j < 2; j++) {
				everyone[halfHive[i][0] + j][halfHive[i][1]] = 1;
			}
		}
		for (int i = 0; i < 3; i++) {		//npchere
			for (int j = 0; j < 4; j++) {
				everyone[npcHere[i][0] + j][npcHere[i][1]] = 10;
			}
		}
		everyone[npcHere[0][0] + 3][npcHere[0][1]] = 11;
		everyone[npcHere[1][0]][npcHere[1][1]] = 11;
		everyone[npcHere[2][0]][npcHere[2][1]] = 11;
	}

	void SetNpcAddress(Npc* npc) {
		if ((npc->GetX() % 7) == 5) {
			npcAddress[npc->GetX() + 3][npc->GetY()] = npc;
		}
		else {
			npcAddress[npc->GetX()-3][npc->GetY()] = npc;
		}
	}

	int ControlMove(int direction, int placeNow, int placeFixed) {
		//move prePlayer
		int placeNext;
		switch (direction) {
		case LEFT:
			if (placeNow > 0) {
				if (everyone[placeNow - 1][placeFixed] % 10) {
					return 100 * (placeNow - 1) + placeFixed;	// 100*x + y -> xxyy
				}
				else if (everyone[placeNow - 4][placeFixed - 2] % 10) {
					return 100 * (placeNow - 4) + (placeFixed - 2);
				}
				else if (everyone[placeNow - 4][placeFixed + 2] % 10) {
					return 100 * (placeNow - 4) + (placeFixed + 2);
				}
			}
			return 100 * placeNow + placeFixed;
		case RIGHT:
			if (placeNow < 100 - 1) {
				if (everyone[placeNow + 1][placeFixed] % 10) {
					return 100 * (placeNow + 1) + placeFixed;	// 100*x + y -> xxyy
				}
				else if (placeNow < 100 - 4) {
					if (everyone[placeNow + 4][placeFixed + 2] % 10) {
						return 100 * (placeNow + 4) + (placeFixed + 2);
					}
					else if (everyone[placeNow + 4][placeFixed - 2] % 10) {
						return 100 * (placeNow + 4) + (placeFixed - 2);
					}
				}
			}
			return 100 * placeNow + placeFixed;

		case UP:
			if (placeNow >= (0 + 4)) {
				placeNext = placeNow - 4;
				while (!(everyone[placeFixed][placeNext] % 10)) {
					placeNext -= 4;
					if (placeNext < 0) {
						return placeNow;
					}
				}
			}
			else {
				return placeNow;
			}
			break;
		case DOWN:
			if (placeNow <= (29 - 4)) {
				placeNext = placeNow + 4;
				while (!(everyone[placeFixed][placeNext] % 10)) {
					placeNext += 4;
					if (placeNext > 29) {
						return placeNow;
					}
				}
			}
			else {
				return placeNow;
			}
			break;
		}
		return placeNext;
	}

	int ControlChat(int x, int y) { //change it
		if (everyone[x][y] / 10) {
			npcAddress[x][y]->Chat();
			return 1;
		}
		else {
			return 0;
		}
	}
};

class PrePlayer {
private:
	int x, y;
	char icon[3][3];
public:
	PrePlayer() {
		x = 84;
		y = 23;
		icon[0][0] = ' ', icon[0][1] = 'O', icon[0][2] = ' ';
		icon[1][0] = '/', icon[1][1] = 'A', icon[1][2] = '\\';
		icon[2][0] = ' ', icon[2][1] = '^', icon[2][2] = ' ';
		PrintIcon();
	}
	void Go(int direction, PreGm *preGm) {
		for (int i = 0; i < 3; i++) {
			gotoxy(x, y + i);
			cout << "   ";
		}
		if ((direction == UP) || (direction == DOWN)) {
			y = preGm->ControlMove(direction, y, x);
		}
		else {	// LEFT RIGHT
			int tempXY;
			tempXY = preGm->ControlMove(direction, x, y);
			x = tempXY / 100;
			y = tempXY % 100;
		}
		PrintIcon();
	}
	void PrintIcon() {
		for (int i = 0; i < 3; i++) {
			gotoxy(x, y + i);
			cout << icon[i][0] << icon[i][1] << icon[i][2];
		}
	}
	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}
};

class Begin{
private:
	int hive[HIVE_SIZE_X][HIVE_SIZE_Y] = { {0,0,0,0,0,1,1,1,1,1,1,0,0,0},			//     oooooo
										   {0,0,0,0,1,0,0,0,0,0,0,1,0,0},			//    o      o
										   {1,1,1,1,0,0,0,0,0,0,0,0,1,1},			//oooo        oo
										   {0,0,0,0,1,0,0,0,0,0,0,1,0,0} };			//hive
	int backHive[100][30];															//hive background
	char choosePlayerFrame[49][5];													//frame of choosing login / guest

public:
	Begin() {
		SetHive();
		SetChoosePlayerFrame();
		PrintCover();
	}
	~Begin() {
		system("cls");
	}

	//刻蜂巢背景 / 選擇玩家名稱的框框
	void SetHive() {

		//背景全設為蜂巢
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 30; j++) {
				backHive[i][j] = hive[j%HIVE_SIZE_X][i%HIVE_SIZE_Y];
			}
		}

		//刻蜂巢凸出位置
		//左上
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 9; j++) {
				if (backHive[i][j]) {
					backHive[i][j]++;
				}
			}
		}
		backHive[19][8]--; backHive[18][7]--;
		for (int i = 24; i < 34; i++) {
			for (int j = 0; j < 3; j++) {
				if (backHive[i][j]) {
					backHive[i][j]++;
				}
			}
		}
		//下
		for (int i = 0; i < 100; i++) {
			for (int j = 24; j < 30; j++) {
				if (backHive[i][j]) {
					backHive[i][j]++;
				}
			}
		}
		for (int i = 25; i < 47; i++) {
			for (int j = 22; j < 24; j++) {
				if (backHive[i][j]) {
					backHive[i][j]++;
				}
			}
		}
		for (int i = 67; i < 100; i++) {
			for (int j = 14; j < 24; j++) {
				if (backHive[i][j]) {
					backHive[i][j]++;
				}
			}
		}
		for (int i = 67; i < 80; i++) {
			for (int j = 14; j < 20; j++) {
				if (backHive[i][j]) {
					backHive[i][j]--;
				}
			}
		}
		backHive[67][21]--;
		for (int i = 87; i < 97; i++) {
			for (int j = 8; j < 13; j++) {
				if (backHive[i][j]) {
					backHive[i][j]++;
				}
			}
		}
	}
	void SetChoosePlayerFrame() {
		for (int i = 0; i < 49; i++) {
			if (i == 49 / 2) {
				for (int j = 0; j < 5; j++) {
					choosePlayerFrame[i][j] = ' ';
				}
				continue;
			}
			choosePlayerFrame[i][0] = '_';
			choosePlayerFrame[i][1] = ' ';
			choosePlayerFrame[i][2] = ' ';
			choosePlayerFrame[i][3] = '_';
			if (i < 49 / 2) {
				choosePlayerFrame[i][4] = '=';
			}
			else {
				choosePlayerFrame[i][4] = '-';
			}
		}
	}

	//印封面
	void PrintBackHive(int yStart, int yEnd) {
		for (int i = 0; i < 100; i++) {
			for (int j = yStart; j < yEnd; j++) {
				gotoxy(i, j);
				if (backHive[i][j] == 2) {
					cout << "\\";
				}
				else{
                    cout << " ";
				}
			}
		}
	}
	void PrintCover() {

		PrintBackHive(0, 30);

		//印標題
		gotoxy(48, 14);
		cout << "Bee";
		gotoxy(38, 17);
		cout << "Press any key to continue.";
		_getch();
	}

	//印第二頁
	void PrintPreSet() {
		for (int i = 0; i < 49; i++) {
			for (int j = 0; j < 5; j++) {
				gotoxy(25 + i, 12 + j);
				cout << choosePlayerFrame[i][j];
			}
		}
		gotoxy(25 + 10, 14);
		cout << "Login";
		gotoxy(25 + 10 + 23 + 1, 14);
		cout << "Guest";
		gotoxy(25, 17);
		cout << "                                                 ";
		gotoxy(25, 18);
		cout << "Just use up, down, left, right and space to control.";
		gotoxy(25, 19);
		cout << "Then press enter to go.";
	}
	void PrintPreSetName(Player *player1) {
		gotoxy(35, 14);
		for (int i = 35; i < 65; i++) {
			cout << " ";
		}
		gotoxy(25 + 49 / 2, 12);
		cout << "_";
		gotoxy(25 + 49 / 2, 15);
		cout << "_";
		gotoxy(25, 16);
		for (int i = 0; i < 49; i++) {
			cout << "=";
		}
		gotoxy(25 + 1, 14);
		Setcursor(1, 10);
		cout << "Name (in 10 words) : ";
		player1->SetName();
		Setcursor(0, 0);
	}
	void PrintPreSetUnderline(int ifLogin) {
		char baselineLogin, baselineGuest;
		if (ifLogin) {
			baselineLogin = '=';
			baselineGuest = '-';
		}
		else {
			baselineLogin = '-';
			baselineGuest = '=';
		}
		gotoxy(25, 16);
		for (int i = 0; i < 24; i++) {
			cout << baselineLogin;
		}
		cout << " ";
		for (int i = 0; i < 24; i++) {
			cout << baselineGuest;
		}
	}

	//set player name/ no name(guest) and pre-story
	void PreSet(Player *player1) {

		int ifLogin = CHOOSE_LOGIN;
		int key;

		PrintPreSet();

		PrePlayer *prePlayer = new PrePlayer();
		PreGm *preGm = new PreGm();
		NpcVillager *npcVillager = new NpcVillager();
		preGm->SetNpcAddress(npcVillager);
		NpcTank *npcTank = new NpcTank();
		preGm->SetNpcAddress(npcTank);
		NpcHoney *npcHoney = new NpcHoney();
		preGm->SetNpcAddress(npcHoney);

		while (1) {
			if (_kbhit()) {
				switch (key = _getch()) {
				case ENTER:
					if (ifLogin) {
						PrintPreSetName(player1);
					}
					else {
						player1->Print();
					}
					return;
				case SPACE:
					if (preGm->ControlChat(prePlayer->GetX(), prePlayer->GetY())) {
						PrintBackHive(20, 30);
						npcVillager->PrintIcon();
						prePlayer->PrintIcon();
					}
					break;
				case  DIRECTION_KEY:
					switch (key = _getch()) {
					case UP:
						prePlayer->Go(UP, preGm);
						break;
					case DOWN:
						prePlayer->Go(DOWN, preGm);
						break;
					case LEFT:
						prePlayer->Go(LEFT, preGm);
						break;
					case RIGHT:
						prePlayer->Go(RIGHT, preGm);
						break;
					}
					ifLogin = !ifLogin;		//choose login or guest
					PrintPreSetUnderline(ifLogin);
				}
			}
		}
	}
};

int main() {

	Setcursor(0, 0);
	//HideCursor();

	Begin *begin = new Begin();
	Player *player1 = new Player(PLAYER_POSITION_X, PLAYER1_POSITION_Y);
	begin->PreSet(player1);

	_getch();
	delete begin;

	gotoxy(0, 30);
	return 0;
}

void gotoxy(int x, int y){
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = x; scrn.Y = y;
	SetConsoleCursorPosition(hOuput, scrn);
}

/*
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
*/

void Setcursor(bool visible, DWORD size) {		// set bool visible = 0 - invisible, bool visible = 1 - visible
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (size == 0) {
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}
