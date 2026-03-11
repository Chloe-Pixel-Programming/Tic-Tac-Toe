/* ITC220 Original Work Statement
	Course - ITC220 Programming II
	Project - Tic-Tac-Toe
	Author - Chloe Campbell
	Term - Sp26
	Due Date - 02/20/2026
	Revision Date -
	Known issues or problems -

	Statement of Original Work and Works Cited materials - edit this
	I, Chloe Campbell, certify this code is my own unique work,
	any and all exceptions are clearly commented as such with appropriate references
	or links to the source of the code incorporated in my solution.
	I used the course textbook, lectures and instructor to help prepare this code.

In addition, the following resources were valuable in completing this project:

Web Resources:

ASCII Art
https://patorjk.com/software/taag/#p=display&f=Tinker-Toy&t=X&x=none&v=4&h=4&w=80&we=false

Youtube video on Tic-Tac-Toe C++ project (I only watched the first five minutes or so don't ask me what else it covers)
https://www.youtube.com/watch?v=mNvIqaRFBts

Figure out how to check for win conditions
https://www.reddit.com/r/cpp_questions/comments/771exe/how_to_check_rows_and_columns_for_three_in_a_row/

Pass a 2D array in a function
https://www.geeksforgeeks.org/cpp/pass-2d-array-parameter-to-functions-in-cpp/

learn about srand() and rand()
https://www.geeksforgeeks.org/cpp/rand-and-srand-in-ccpp/


*/


#include <iostream>
#include <iomanip>

using namespace std;

void pause();
bool check_if_over(char board[][3], bool& game_over, int num_turn, const char X_CHAR, const char O_CHAR); // Determines if the game is over
void print_board(char board[3][3], const char X_CHAR, const char O_CHAR); // Prints the Tic-Tac-Toe board
void swap_tile(char board[3][3], const char X_CHAR, const char O_CHAR); // Swaps tile in Tic-Tac-Toe board with X or O from blank tile
int cpu_move(int& player_choice, bool correct_input, int difficulty_choice);
void refresh_screen(); // Clears the screen and prints the header so terminal isn't one long stream
bool play_again(bool& game_over, char board[3][3], char& char_player, char X_CHAR, char O_CHAR);
void clear_board(char board[3][3]); // For when the board needs reset to ' '
int get_players(int& num_player);
int select_difficulty(int& difficulty_choice);
void place_mark(char board[3][3], int row, int col, int num_player, char char_player, 
				int difficulty_choice, const char X_CHAR, const char O_CHAR);

int main() {

	srand(time(0));

	char board[3][3]{
		{' ',' ',' '},
		{' ',' ',' '},
		{' ',' ',' '},
	};

	const char X_CHAR = 'X';
	const char O_CHAR = 'O';
	char char_player = 'X';
	
	int row = NULL;
	int col = NULL;
	int count = 0;
	int num_turn = 0;
	int num_player = 0;
	int player_choice = 0;
	int difficulty_choice = 0;

	bool game_over = false;

	while (!game_over) {

	game_over = false;

	num_turn = 0;

	refresh_screen();

	get_players(num_player);

	if (num_player == 1) {
	
		select_difficulty(difficulty_choice);

	}
	
	while (!game_over && num_player == 1) {   // Single player mode

		refresh_screen();

		print_board(board, X_CHAR, O_CHAR);

		place_mark(board, row, col, num_player, char_player, difficulty_choice, X_CHAR, O_CHAR);
			
		check_if_over(board, game_over, num_turn, X_CHAR, O_CHAR);

			if (!game_over) {

				char_player = (char_player == X_CHAR) ? O_CHAR : X_CHAR;

				num_turn++;

			}
		

	}   // End Single player mode

	// Two player mode
	while (!game_over && num_player == 2) {

		refresh_screen();

		print_board(board, X_CHAR, O_CHAR);

		place_mark(board, row, col, num_player, char_player, difficulty_choice, X_CHAR, O_CHAR);

		check_if_over(board, game_over, num_turn, X_CHAR, O_CHAR);

		if (!game_over) {

			char_player = (char_player == X_CHAR) ? O_CHAR : X_CHAR;

			num_turn++;

		}
	}   // End Two player mode

	if (game_over) {


		system("cls");

		
		// Make into function
		if (num_player == 1) {

			if (char_player == X_CHAR) {

				cout << R"(                                                                                                    
               mm        mm    mm      mm  mmmmmm   mmm   mm  mmm   mm  mmmmmmmm  mmmmmm       mm        mm    
               ##        ##    ##      ##  ""##""   ###   ##  ###   ##  ##""""""  ##""""##     ##        ##    
               ##        ##    "#m ## m#"    ##     ##"#  ##  ##"#  ##  ##        ##    ##     ##        ##    
               ##        ##     ## ## ##     ##     ## ## ##  ## ## ##  #######   #######      ##        ##    
               ""        ""     ###""###     ##     ##  #m##  ##  #m##  ##        ##  "##m     ""        ""    
               mm        mm     ###  ###   mm##mm   ##   ###  ##   ###  ##mmmmmm  ##    ##     mm        mm    
               ""        ""     """  """   """"""   ""   """  ""   """  """"""""  ""    """    ""        "")" << endl;

				cout << right << setw(65) << "You win!" << endl;

			}
			else if (char_player == O_CHAR) {

				cout << R"(                                                                                          
                   mmmm                                             mmmm                                 
                 ##""""#                                           ##""##                                
                ##         m#####m  ####m##m   m####m             ##    ##  ##m  m##   m####m    ##m#### 
                ##  mmmm   " mmm##  ## ## ##  ##mmmm##            ##    ##   ##  ##   ##mmmm##   ##"     
                ##  ""##  m##"""##  ## ## ##  ##""""""            ##    ##   "#mm#"   ##""""""   ##      
                 ##mmm##  ##mmm###  ## ## ##  "##mmmm#             ##mm##     ####    "##mmmm#   ##      
                   """"    """" ""  "" "" ""    """""               """"       ""       """""    "")" << endl;

				cout << right << setw(65) << "You Lose." << endl;

			}
		}
		else if (num_player == 2) {

			cout << R"(                                                                                                    
               mm        mm    mm      mm  mmmmmm   mmm   mm  mmm   mm  mmmmmmmm  mmmmmm       mm        mm    
               ##        ##    ##      ##  ""##""   ###   ##  ###   ##  ##""""""  ##""""##     ##        ##    
               ##        ##    "#m ## m#"    ##     ##"#  ##  ##"#  ##  ##        ##    ##     ##        ##    
               ##        ##     ## ## ##     ##     ## ## ##  ## ## ##  #######   #######      ##        ##    
               ""        ""     ###""###     ##     ##  #m##  ##  #m##  ##        ##  "##m     ""        ""    
               mm        mm     ###  ###   mm##mm   ##   ###  ##   ###  ##mmmmmm  ##    ##     mm        mm    
               ""        ""     """  """   """"""   ""   """  ""   """  """"""""  ""    """    ""        "")" << endl;

			if (char_player == X_CHAR) {

				cout << right << setw(72) << "Player 1 is the Winner!" << endl;

			}
			else if (char_player == O_CHAR) {

				cout << right << setw(72) << "Player 2 is the Winner!" << endl;

			}
		}
	}

	play_again(game_over, board, char_player, X_CHAR, O_CHAR);

}

	pause();


	return (0);

}

	


void pause()
{ // function to freeze the screen, waiting for a keypress.
	char junk;
	cin.ignore(65233, '\n');
	cout << "\nPress enter to continue...";
	cin.get(junk);
} // End pause()

bool check_if_over(char board[][3], bool& game_over, int num_turn, const char X_CHAR, const char O_CHAR) {

	// Check win state in colums
	for (int j = 0; j < 3; j++) {

		if (board[0][j] == X_CHAR && (board[0][j] == board[1][j] && board[0][j] == board[2][j])) {
			return(game_over = true);
		}
		else if (board[0][j] == O_CHAR && (board[0][j] == board[1][j] && board[0][j] == board[2][j])) {
			return(game_over = true);
		}
	}

	// Check win state in rows
	for (int i = 0; i < 3; i++) {

		if ((board[i][0] == X_CHAR || board[i][0] == O_CHAR) && (board[i][0] == board[i][1] && board[i][0] == board[i][2])) {
			return(game_over = true);
		}
	}

	// Check win state in diagonal left to right "\"
	if ((board[0][0] == X_CHAR || board[0][0] == O_CHAR) && (board[0][0] == board[1][1] && board[0][0] == board[2][2])) {
		return(game_over = true);
	}

	// Check win state in diagnonal right to left "/"
	if (board[0][2] == X_CHAR && (board[0][2] == board[1][1] && board[0][2] == board[2][0])) {
		return(game_over = true);
	}
	else if (board[0][2] == O_CHAR && (board[0][2] == board[1][1] && board[0][2] == board[2][0])) {
		return(game_over = true);
	}

	if (num_turn == 8 && !game_over) {
		return(game_over = true);
	}
}   // End check_if_over();

void print_board(char board[3][3], const char X_CHAR, const char O_CHAR) {

	cout << right << setw(74) << " ___________________________" << endl;
	cout << right << setw(75) << "/ _______  _______  _______ \\" << endl;

	// Swaps blank tiles with X or O tile
	swap_tile(board, X_CHAR, O_CHAR);


	cout << right << setw(75) << "\\___________________________/" << endl;

}   // End print_board()

void swap_tile(char board[3][3], const char X_CHAR, const char O_CHAR) {

	const int art_size = 4;

	const string  x_string[art_size]{ " o   o ",
									  "  \\ /  ",
									  "  / \\  ",
									  " o   o ", };

	const string o_string[art_size]{  "  o-o  ",
									  " o   o ",
									  " o   o ",
									  "  o-o  ", };

	const string blank_string[art_size]{ "       ",
										  "       ",
										  "       ",
										  "       ", };

	string upper_left[art_size]{ "       ",
								 "   1   ",
								 "       ",
								 "       ", };

	string upper_middle[art_size]{ "       ",
								   "   2   ",
								   "       ",
								   "       ", };

	string upper_right[art_size]{ "       ",
								  "   3   ",
								  "       ",
								  "       ", };

	string middle_left[art_size]{ "       ",
								  "   4   ",
								  "       ",
								  "       ", };

	string middle_middle[art_size]{ "       ",
									"   5   ",
									"       ",
									"       ", };

	string middle_right[art_size]{ "       ",
								   "   6   ",
								   "       ",
								   "       ", };

	string lower_left[art_size]{ "       ",
								 "   7   ",
								 "       ",
								 "       ", };

	string lower_middle[art_size]{ "       ",
								   "   8   ",
								   "       ",
								   "       ", };

	string lower_right[art_size]{ "       ",
								  "   9   ",
								  "       ",
								  "       ", };
	
	for (int j = 0; j < art_size; j++) {

		if (board[0][0] == X_CHAR) {
			upper_left[j] = x_string[j];
		}
		else if (board[0][0] == O_CHAR) {
			upper_left[j] = o_string[j];
		}

		if (board[0][1] == X_CHAR) {
			upper_middle[j] = x_string[j];
		}
		else if (board[0][1] == O_CHAR) {
			upper_middle[j] = o_string[j];
		}

		if (board[0][2] == X_CHAR) {
			upper_right[j] = x_string[j];
		}
		else if (board[0][2] == O_CHAR) {
			upper_right[j] = o_string[j];
		}

		cout << right << setw(48) << "||" << upper_left[j] << "||" << upper_middle[j] << "||" << upper_right[j] << "||" << endl;

	}

	cout << right << setw(48) << "||" << "_______" << "||" << "_______" << "||" << "_______" << "||" << endl;

	for (int j = 0; j < art_size; j++) {

		if (board[1][0] == X_CHAR) {
			middle_left[j] = x_string[j];
		}
		else if (board[1][0] == O_CHAR) {
			middle_left[j] = o_string[j];
		}

		if (board[1][1] == X_CHAR) {
			middle_middle[j] = x_string[j];
		}
		else if (board[1][1] == O_CHAR) {
			middle_middle[j] = o_string[j];
		}

		if (board[1][2] == X_CHAR) {
			middle_right[j] = x_string[j];
		}
		else if (board[1][2] == O_CHAR) {
			middle_right[j] = o_string[j];
		}

		cout << right << setw(48) << "||" << middle_left[j] << "||" << middle_middle[j] << "||" << middle_right[j] << "||" << endl;
	}

	cout << right << setw(48) << "||" << "_______" << "||" << "_______" << "||" << "_______" << "||" << endl;

	for (int j = 0; j < art_size; j++) {

		if (board[2][0] == X_CHAR) {
			lower_left[j] = x_string[j];
		}
		else if (board[2][0] == O_CHAR) {
			lower_left[j] = o_string[j];
		}

		if (board[2][1] == X_CHAR) {
			lower_middle[j] = x_string[j];
		}
		else if (board[2][1] == O_CHAR) {
			lower_middle[j] = o_string[j];
		}

		if (board[2][2] == X_CHAR) {
			lower_right[j] = x_string[j];
		}
		else if (board[2][2] == O_CHAR) {
			lower_right[j] = o_string[j];
		}

		cout << right << setw(48) << "||" << lower_left[j] << "||" << lower_middle[j] << "||" << lower_right[j] << "||" << endl;
	}

	cout << right << setw(48) << "||" << "_______" << "||" << "_______" << "||" << "_______" << "||" << endl;

}   // End swap_tile();

int cpu_move(int& player_choice, bool correct_input, int difficulty_choice) {

	int random = rand();

	if (!correct_input) {

		int random = rand();
	
	}

		if (difficulty_choice == 1) {

			// If random number is even
			if (random % 2 == 0) {

				random = (random % 42);

				if (random >= 35 || random < 5) {
					player_choice = 9;
				}
				else if (random >= 25) {
					player_choice = 7;
				}
				else if (random >= 15) {
					player_choice = 5;
				}
				else if (random >= 5) {
					player_choice = 3;
				}
				else {
					player_choice = 1;
				}

			}
			else {
				random = random % 67;

				if (random >= 65 || random < 15) {
					player_choice = 8;
				}
				else if (random >= 55) {
					player_choice = 6;
				}
				else if (random >= 35) {
					player_choice = 4;
				}
				else if (random >= 25) {
					player_choice = 2;
				}
				else {
					player_choice = 1;
				}
			}
		}
		else if (difficulty_choice == 2) {

			// If random number is even
			if (random % 2 == 0) {

				random = (random % 42);

				if (random >= 40 || random < 10) {
					player_choice = 9;
				}
				else if (random >= 30) {
					player_choice = 7;
				}
				else if (random >= 20) {
					player_choice = 5;
				}
				else if (random >= 10) {
					player_choice = 3;
				}
				else {
					player_choice = 1;
				}

			}
			else {
				random = random % 67;

				if (random >= 60 || random < 10) {
					player_choice = 8;
				}
				else if (random >= 50) {
					player_choice = 6;
				}
				else if (random >= 30) {
					player_choice = 4;
				}
				else if (random >= 20) {
					player_choice = 2;
				}
				else {
					player_choice = 1;
				}
			}
		}
		else if (difficulty_choice == 3) {

			player_choice = (random % 9) + 1;

	}

	return (player_choice);
}   // End cpu_move();

void refresh_screen() {

	system("cls");

	cout << R"(                                                                                                              
      mmmmmmmm     ##                         mmmmmmmm                                mmmmmmmm                     
      """##"""     ""                         """##"""                                """##"""                     
         ##      ####      m#####m               ##      m#####m   m#####m               ##      m####m    m####m  
         ##        ##     ##"    "               ##      " mmm##  ##"    "               ##     ##"  "##  ##mmmm## 
         ##        ##     ##         #####       ##     m##"""##  ##         #####       ##     ##    ##  ##"""""" 
         ##     mmm##mmm  "##mmmm#               ##     ##mmm###  "##mmmm#               ##     "##mm##"  "##mmmm# 
         ""     """"""""    """""                ""      """" ""    """""                ""       """"      """""  
                                                                                                              
                                                                                                              )" << endl;
}

void place_mark(char board[3][3], int row, int col, int num_player, char char_player, 
				int difficulty_choice, const char X_CHAR, const char O_CHAR) {

	bool correct_input = false;

	int player_choice = 0;
	int count = 0;

	while (!correct_input) {

		// So we can ask the player for where they want the mark, if this isn't the first time ask nicely
		if (count <= 0) {

			if (num_player == 1) {
			
				if (char_player == X_CHAR) {

					cout << '\n' << right << setw(84) << "Player 1 Please select a space from the grid: ";
					cin >> player_choice;

				}
				else if (char_player == O_CHAR) {

					player_choice = cpu_move(player_choice, correct_input, difficulty_choice);

				}

			}
			else if (num_player == 2) {
				if (char_player == X_CHAR) {

					cout << '\n' << right << setw(84) << "Player 1 Please select a space from the grid: ";
					cin >> player_choice;

				}
				else if (char_player == O_CHAR) {

					cout << '\n' << right << setw(84) << "Player 2 Please select a space from the grid: ";
					cin >> player_choice;

				}
			}
		}
		else {

			if (num_player == 1) {

				if (char_player == X_CHAR) {

					cout << '\n' << right << setw(98) << "Not a valid move, please select an empty tile number listed on the grid : ";
					cin >> player_choice;

				}
				else if (char_player == O_CHAR) {

					player_choice = cpu_move(player_choice, correct_input, difficulty_choice);

				}
			}
			else if (num_player == 2) {
			
				cout << '\n' << right << setw(98) << "Not a valid move, please select an empty tile number listed on the grid : ";
				cin >> player_choice;

			}
		}

		if (player_choice >= 1 && player_choice <= 9) {

			switch (player_choice) {

			case 1: row = 0, col = 0;
				break;
			case 2: row = 0, col = 1;
				break;
			case 3: row = 0, col = 2;
				break;
			case 4: row = 1, col = 0;
				break;
			case 5: row = 1, col = 1;
				break;
			case 6: row = 1, col = 2;
				break;
			case 7: row = 2, col = 0;
				break;
			case 8: row = 2, col = 1;
				break;
			case 9: row = 2, col = 2;
				break;

			default: row = NULL, col = NULL;

			}

			if (board[row][col] == ' ') {

				correct_input = true;

				board[row][col] = char_player;

			}
		}
		else {

			correct_input = false;

			cin.clear();
			cin.ignore(65233, '\n');

			refresh_screen();

			print_board(board, X_CHAR, O_CHAR);

			count++;

		}
	}
}   // End place_mark();

bool play_again(bool& game_over, char board[3][3], char& char_player, char X_CHAR, char O_CHAR) {

	char play_again;

	if (game_over) {

		print_board(board, X_CHAR, O_CHAR);

		cout << right << setw(75) << "Would you like to play again?" << endl;
		cout << right << setw(64) << "Y or N" << endl;
		cout << right << setw(61) << ' ';

		cin >> play_again;

		while ((play_again != 'y' && play_again != 'Y') && (play_again != 'n' && play_again != 'N')) {

			print_board(board, X_CHAR, O_CHAR);

			cout << right << setw(75) << "Would you like to play again?" << endl;
			cout << right << setw(64) << "Y or N" << endl;
			cout << right << setw(61) << ' ';

			cin >> play_again;
		}

		if (play_again == 'y' || play_again == 'Y') {

			game_over = false;

			char_player = (char_player == X_CHAR) ? O_CHAR : X_CHAR;

			clear_board(board);


		}
		else if (play_again == 'n' || play_again == 'N') {
			
			game_over = true;

		}
	}

	return (game_over);

}   // End play_again();

void clear_board(char board[3][3]) {

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			board[i][j] = ' ';
		}
	}
}   // End clear_board();

int get_players(int& num_player) {

	cout << right << setw(69) << "How many players?" << endl;
	cout << right << setw(66) << "Enter 1 or 2" << endl;
	cout << right << setw(59) << ' ';
	cin >> num_player;

	refresh_screen();

	while (num_player != 1 && num_player != 2) {

		cin.clear();
		cin.ignore(65233, '\n');

		refresh_screen();

		cout << right << setw(69) << "How many players?" << endl;
		cout << right << setw(66) << "Enter 1 or 2" << endl;
		cout << right << setw(59) << ' ';
		cin >> num_player;

		refresh_screen();

	}

	return (num_player);

}

int select_difficulty(int& difficulty_choice) {

	bool good_choice = false;

	while (!good_choice) {

		cout << right << setw(75) << "Please select a difficulty:" << endl;
		cout << right << setw(69) << "Easy: Enter 1 " << endl;
		cout << right << setw(69) << "Normal: Enter 2 " << endl;
		cout << right << setw(69) << "Nightmare: Enter 3 " << endl;
		cout << right << setw(60) << ' ';

		cin >> difficulty_choice;

		if (difficulty_choice == 1 || difficulty_choice == 2 || difficulty_choice == 3) {

			good_choice = true;
		}
		else {

			cin.clear();
			cin.ignore(65233, '\n');

			refresh_screen();

		}
	}

	return (difficulty_choice);

}   // End select_difficulty();