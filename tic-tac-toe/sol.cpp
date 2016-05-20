/*
	Why ? :
		To learn minimax algo 
	To Do:
		1) Menu ?
		2) Minimax algo for perfect game A.I

*/
#include <iostream>
#include <cstring>

using namespace std;

int board[10];
int win_combos[][3] = {
	{ 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 },
	{ 1, 4, 7 }, { 2, 5, 8 }, { 3, 6, 9 },
	{ 1, 5, 9 }, { 3, 5, 7 }
};
int player;
int mv_cnt;

void init();
void draw();
void two_player();
bool running();

int main( int argc, char **argv ) {
	// if( argv[0][0] == '2' ) {
	// 	two_player();
	// }
	two_player();
	return 0;
}

void init() {
	memset( board, 0, sizeof board );
	player = 1;
	mv_cnt = 9;
}

void draw() {
	for( int i=1; i<=9; i++ ) {
		if( board[i] ) {
			cout << "XO"[ board[i]-1 ] << "\n|"[ i % 3 != 0 ];
		} else {
			cout << i << "\n|"[ i % 3 != 0 ];
		}
		if( i == 3 or i == 6 ) {
			cout << string( 5, '-' ) << "\n";
		}
	}
	cout << "\n";
}

bool running() {
	if( !mv_cnt ) {		
		return false;
	}
	for( int i=0; i<8; i++ ) {
		if( board[ win_combos[i][0] ] == board[ win_combos[i][1] ] 
					and
		board[ win_combos[i][1] ] == board[ win_combos[i][2] ] 
		and board[ win_combos[i][2] ] != 0 ) {
			return false;
		}
	}
	return true;
}

string determine() {
	if( !mv_cnt ) {		
		return "Tie!";
	}
	for( int i=0; i<8; i++ ) {
		if( board[ win_combos[i][0] ] == board[ win_combos[i][1] ] 
					and
		board[ win_combos[i][1] ] == board[ win_combos[i][2] ] ) {
			if( board[ win_combos[i][2] ] == 1 ) {
				return "Player 1 Wins!";
			} else {
				return "Player 2 Wins!";
			}
		}
	}
	return "Not Complete!";
}

void two_player() {
	int inp;
	bool invalid = false;
	init();
	draw();
	while( running() ) {
		while( inp < 1 or inp > 9 or board[inp] ) {
			if( invalid ) {
				cout << "Please Enter A Valid Input\n";
			}
			cout << "Player " << player << " input: ";
			cin >> inp;
			invalid = true;
			cout << "\n";
		}
		invalid = false;
		board[inp] = player;
		--mv_cnt;
		draw();
		player = player == 1 ? 2 : 1 ;
	}
	cout << determine() << "\n";
}
