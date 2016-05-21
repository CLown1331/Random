/*	
	Author: Araf Al-Jami
	Last Edited: 21/05/16
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
int mv_cnt;

void init();
void draw();
void single_player( int player );
void two_player();
bool running();
int minimax( int player );
void player_move( int player );
void computer_move( int player );

int main( int argc, char **argv ) {
	int inp;
	bool invalid = false;
	do {
		if( invalid ) {
			cout << "Please Enter A Valid Input\n";
		}
		cout << "Enter 1 for single player or 2 for Two Player: ";
		cin >> inp;
		invalid = true;
		cout << "\n";
	} while( inp < 1 or inp > 2 );
	if( inp == 1 ) {
		invalid = false;
		do {
			if( invalid ) {
				cout << "Please Enter A Valid Input\n";
			}
			cout << "Enter 1 If You Want To Be The First Player\n";
			cout << "Else Enter 2: ";
			cin >> inp;
			cout << "\n";
		} while( inp < 1 or inp > 2 );
		single_player( inp );
	} else {
		two_player();
	}
	return 0;
}

void init() {
	memset( board, 0, sizeof board );
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

string determine( int game_type, int player ) {
	if( !mv_cnt ) {
		return "Tie!";
	}
	for( int i=0; i<8; i++ ) {
		if( board[ win_combos[i][0] ] == board[ win_combos[i][1] ]
					and
		board[ win_combos[i][1] ] == board[ win_combos[i][2] ] 
		and board[ win_combos[i][2] ] != 0 ) {
			if( board[ win_combos[i][2] ] == 1 ) {
				if( game_type == 1 ) {
					return player == 1 ? "You Win!" : "You lose!";
				} else {
					return "Player 1 Wins!";
				}
			} else {
				if( game_type == 1 ) {
					return player == 2 ? "You Win!" : "You lose!";
				} else {
					return "Player 2 Wins!";
				}
			}
		}
	}
	return "Not Complete!";
}

void two_player() {
	int inp = 0; 
	int player = 1;
	bool invalid = false;
	init();
	draw();
	while( running() ) {
		do {
			if( invalid ) {
				cout << "Please Enter A Valid Input\n";
			}
			cout << "Player " << player << " input: ";
			cin >> inp;
			invalid = true;
			cout << "\n";
		} while( inp < 1 or inp > 9 or board[inp] );
		invalid = false;
		board[inp] = player;
		--mv_cnt;
		draw();
		player = player == 1 ? 2 : 1 ;
	}
	cout << determine( 2, 0 ) << "\n";
}

void single_player( int player ) {
	init();
	draw();
	while( running() ) {
		if( mv_cnt & 1 ) {
			player == 1 ? player_move( player ) : computer_move( player );
		} else {
			player == 2 ? player_move( player ) : computer_move( player );
		}
		--mv_cnt;
		draw();
	}
	cout << determine( 1, player ) << "\n";
}

void player_move( int player ) {
	int inp = 0;
	bool invalid = false;
	do {
		if( invalid ) {
			cout << "Please Enter A Valid Input\n";
		}
		cout << "Player " << player << " input: ";
		cin >> inp;
		invalid = true;
		cout << "\n";
	} while( inp < 1 or inp > 9 or board[inp] );
	board[inp] = player;
}

void computer_move( int player ) {
	int cmp = player == 1 ? 2 : 1;
	int move = -1;
	int best = -11;
	int temp;
	for( int i=1; i<=9; i++ ) {
		if( board[i] == 0 ) {
			board[i] = cmp;
			--mv_cnt;
			temp = -minimax( player );
			board[i] = 0;
			++mv_cnt;
			if( temp > best ) {
				best = temp;
				move = i;
			}
		}
	}
	board[move] = cmp;
}

int score( int player ) {
	int enemy = player == 1 ? 2 : 1;
	for( int i=0; i<8; i++ ) {
		if( board[ win_combos[i][0] ] == board[ win_combos[i][1] ]
					and
		board[ win_combos[i][1] ] == board[ win_combos[i][2] ] ) {
			if( board[ win_combos[i][2] ] == player ) {
				return 10;
			} else if( board[ win_combos[i][2] ] == enemy ) {
				return -10;
			}
		}
	}
	return 0;
}

int minimax( int player ) {
	if( !running() ) {
			return score( player );
	}
	int enemy = player == 1 ? 2 : 1;
	int move = -1;
	int best = -11;
	int temp;
	for( int i=1; i<=9; i++ ) {
		if( board[i] == 0 ) {
			board[i] = player;
			--mv_cnt;
			temp = -minimax( enemy );
			board[i] = 0;
			++mv_cnt;
			if( temp > best ) {
				best = temp;
				move = i;
			}
		}
	}
	if( move == -1 ) {
		return 0;
	}
	return best;
}