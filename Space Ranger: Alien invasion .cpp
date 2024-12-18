#include <fstream> // For file handling (added)
#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<string>
#include<iomanip>
#include<limits>
#define NOMINMAX
#include<Windows.h>// for system related and cursor related 
#include<conio.h>// for getch and kbhit
#include<ctime>// for time related work like end the game if time ends



using namespace std;
const int ROWS = 30, COLS = 30;// global variables so every function can access them to increase readibility 
const int MAXEnemies = 10;
const int MAXasteroids = 15;
const int lives = 3;

void updateScoreAndLevel(int& score, int& level, int& lives, int& distance, int& timeremaining);
void saveScoreToFile(const string& name, int score); // New function prototype (File Handling)
void spanAsteroid(char gameMap[ROWS][COLS], int& asteroidCount);// movement functions
void spanEnemy(char gameMap[ROWS][COLS], int& enemyCount);
void moveEnemies(char gameMap[ROWS][COLS]);
void EnemyShoot(char gameMap[ROWS][COLS]);
void moveAsteroid(char gameMap[ROWS][COLS], int& lives);
void MoveEnemyBullet(char gameMap[ROWS][COLS], int& lives);
void drawBoss(char gameMap[ROWS][COLS], int x, int y);
void handleMultipleInputs(char gameMap[ROWS][COLS], int& shipx, int& shipy, int& shootCooldown);
void spanPOWER(char gameMap[ROWS][COLS], int& power);// power up
void movePower(char gameMap[ROWS][COLS], int& score);


void Entername(string& name);
void SetCursorPosition(int x, int y);// function alternative for clear screen to avoid flickering and just update the game map 
void gameMapinitialize(char gameMap[ROWS][COLS]);
void displayMapOnce(char gameMap[ROWS][COLS], int& score, int& level);//display the map once
void redrawMap(char gameMap[ROWS][COLS]);
void HideConsoleCursor();

void level1(char gameMap[ROWS][COLS], int& shipx, int& shipy, int& score, int& level, int& lives);// level functions
void level2(char gameMap[ROWS][COLS], int& shipx, int& shipy, int& score, int& level, int& lives, int& distance);

void displayBossHealth(int& bosshealth);// game object
void drawShip(char gameMap[ROWS][COLS], int& x, int& y);
void shootBullet(char gameMap[ROWS][COLS], int& shipx, int& shipy);
void clearShip(char gameMap[ROWS][COLS], int& x, int& y);
void MoveBullet(char gameMap[ROWS][COLS], int& score, int& enemyhealth);

void mainMenu(int&);// main menu
void Playgame();
void instruction();
void highScores();
void invalid();
void credit();
void exit();
void Endgame();

int main()// main function 
{

	system("CLS");
	int choice = 0;// choice variable
	do {
		//cin.ignore();
		mainMenu(choice);
		switch (choice)
		{
		case 1://play game
			Playgame();

			break;
		case 2:// instructions
			instruction();
			break;
		case 3:// High SCORES
			highScores();
			break;
		case 4:
			credit();
			break;
		case 5:// exit 
			exit();
			break;

		default:
			invalid();
			break;
		}
	} while (choice != 5);


	return 0;
}

void mainMenu(int& a)
{
	srand(time(0));
	system("CLS");
	///// main menu function to display the home screen 
	//cin.ignore();
	cout << setfill('=') << setw(60) << " " << endl;// initial lines and game name
	cout << setfill(' ') << left << setw(20) << " " << setw(15) << "SPACE RANGER : GAME " << endl;
	cout << right << setfill('=') << setw(60) << " " << endl << endl;
	cout << setfill(' ') << setw(5) << " " << "Welcome Sargent we are being envaded by the aliens";
	cout << endl << endl << setw(5) << " " << "YOU ARE OUR ONLY HOPE!!" << "\n\n";

	cout << setfill(' ') << setw(10) << " " << "1. PLAY GAME " << endl;   // choice menu
	cout << setfill(' ') << setw(10) << " " << "2. INSTRUCTIONS " << endl;
	cout << setfill(' ') << setw(10) << " " << "3. HIGH SCORES " << endl;
	cout << setfill(' ') << setw(10) << " " << "4. CREDITS " << endl;
	cout << setfill(' ') << setw(10) << " " << "5. QUIT " << endl << endl << endl;
	cout << setfill(' ') << setw(10) << " " << "SELECT CHOICE (1 - 5) " << endl;
	cout << setfill(' ') << setw(10) << " ";// to align the input with the menu

	while (true) {
		cin >> a;
		if (cin.fail() || a < 1 || a > 5) {
			// Clear the fail state and flush the buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			invalid();
			return;
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}

	cout << setfill('=') << setw(60) << " " << endl;// last line of border
	_getch();// stay on sceen for 2 second time 
}



// New Function: Save Score to File
void saveScoreToFile(const string& name, int score) {
	const int MAX_SCORES = 10;
	string names[MAX_SCORES];
	int scores[MAX_SCORES];
	int currentScoreCount = 0;

	// Read existing high scores
	ifstream inputFile("HighScores.txt");
	if (inputFile.is_open()) {
		// Read names and scores from file
		while (currentScoreCount < MAX_SCORES&& getline(inputFile, names[currentScoreCount])) {
			if (!(inputFile >> scores[currentScoreCount])) break;
			inputFile.ignore(); // Consume newline
			currentScoreCount++;
		}
		inputFile.close();
	}

	// Find correct position for new score
	int insertIndex = -1;
	for (int i = 0; i < currentScoreCount; i++) {
		if (score > scores[i]) {
			insertIndex = i;
			break;
		}
	}

	// If new score is better, make room and insert
	if (insertIndex != -1) {
		// Shift lower scores down
		for (int i = min(currentScoreCount, MAX_SCORES - 1); i > insertIndex; i--) {
			names[i] = names[i - 1];
			scores[i] = scores[i - 1];
		}

		// Insert new score
		names[insertIndex] = name;
		scores[insertIndex] = score;

		// Increment count if not full
		if (currentScoreCount < MAX_SCORES) {
			currentScoreCount++;
		}
	}
	// If list not full and score is lowest, append
	else if (currentScoreCount < MAX_SCORES) {
		names[currentScoreCount] = name;
		scores[currentScoreCount] = score;
		currentScoreCount++;
	}

	// Write back to file
	ofstream outputFile("HighScores.txt");
	if (outputFile.is_open()) {
		for (int i = 0; i < currentScoreCount; i++) {
			outputFile << names[i] << endl << scores[i] << endl;
		}
		outputFile.close();
	}
	else {
		cerr << "Error: Unable to open HighScores.txt for writing!" << endl;
	}
}





void instruction() {
	system("CLS");
	cout << setfill('=') << setw(60) << " " << endl;// initial lines and instruction heading
	cout << setfill(' ') << left << setw(20) << " " << setw(15) << "INSTRUCTIONS " << endl;
	cout << right << setfill('=') << setw(60) << " " << endl << endl;


	cout << setfill(' ') << setw(5) << " " << "1. Use \"A \"to move left and \"D\" to move right ." << endl;   // instructons
	cout << setfill(' ') << setw(5) << " " << "2. Press space bar to shoot laser . " << endl;
	cout << setfill(' ') << setw(5) << " " << "3. Avoid from  enemy ship attack and asteroids   " << endl;
	cout << setfill(' ') << setw(5) << " " << "4. You have initially 3 lives hitting with asteroid " << endl;
	cout << setfill(' ') << setw(5) << " " << "and enemy attack will cause your lives to decrese ." << endl;
	cout << setfill(' ') << setw(5) << " " << "5.Collect Stars to increase score ." << endl << endl;

	cout << setfill(' ') << setw(5) << " " << "NOW go and destroy those Aliens !!" << endl << endl;
	cout << setfill('=') << setw(60) << " " << endl;
	cout << setfill(' ') << setw(10) << " " << "Press any key to return to MAIN MENU ";
	int a = _getch();

}




void highScores() {
	system("CLS");
	cout << setfill('=') << setw(60) << " " << endl;
	cout << setfill(' ') << left << setw(20) << " " << setw(15) << "HIGH SCORES" << endl;
	cout << right << setfill('=') << setw(60) << " " << endl << endl;

	const int MAX_SCORES = 10;
	string names[MAX_SCORES];
	int scores[MAX_SCORES];
	int currentScoreCount = 0;

	ifstream file("HighScores.txt");
	if (file.is_open()) {
		// Read scores
		while (currentScoreCount < MAX_SCORES && getline(file, names[currentScoreCount])) {
			if (!(file >> scores[currentScoreCount])) break;
			file.ignore(); // Consume newline
			currentScoreCount++;
		}
		file.close();

		// Manual bubble sort to order scores
		for (int i = 0; i < currentScoreCount - 1; i++) {
			for (int j = 0; j < currentScoreCount - i - 1; j++) {
				if (scores[j] < scores[j + 1]) {
					// Swap names
					string tempName = names[j];
					names[j] = names[j + 1];
					names[j + 1] = tempName;

					// Swap scores
					int tempScore = scores[j];
					scores[j] = scores[j + 1];
					scores[j + 1] = tempScore;
				}
			}
		}

		// Display scores
		if (currentScoreCount > 0) {
			for (int i = 0; i < currentScoreCount; i++) {
				cout << i + 1 << ". " << names[i] << " - " << scores[i] << endl;
			}
		}
		else {
			cout << "No high scores available yet!" << endl;
		}
	}
	else {
		cout << "No high scores available yet!" << endl;
	}

	cout << setfill('=') << setw(60) << " " << endl;
	cout << setfill(' ') << setw(10) << " " << "Press any key to return to MAIN MENU ";
	_getch();
}








void credit()
{
	system("CLS");
	cout << setfill('=') << setw(60) << " " << endl;
	cout << setfill(' ') << left << setw(20) << " " << setw(15) << "CREDITS" << endl;
	cout << right << setfill('=') << setw(60) << " " << endl << endl;
	cout << "THE GAME has been created as a project for the finals of " << endl;   // 
	cout << "PF lab project.The code of the game is written by :" << endl;
	cout << "1. Ayaan Amir F24-0767 " << endl;
	cout << "2. Ahmed Siddiqui F24-0513 " << endl;

	cout << setfill('=') << setw(60) << " " << endl;
	cout << setfill(' ') << setw(10) << " " << "Press any key to return to MAIN MENU ";
	int a = _getch();

}




void invalid() {
	system("CLS");
	cout << setfill('=') << setw(60) << " " << endl;// invalid choice 
	cout << setfill(' ') << left << setw(20) << " " << setw(15) << "INVALID Choice " << endl;
	cout << right << setfill('=') << setw(60) << " " << endl << endl;
	cout << setfill(' ') << setw(5) << " " << "SELECT your choice again " << endl;
	cout << setfill('=') << setw(60) << " " << endl;
	cout << setfill(' ') << setw(10) << " " << "Press any key to return to MAIN MENU ";
	int a = _getch();

}





void exit()// exit function for game 
{
	system("CLS");
	cout << setfill('=') << setw(60) << " " << endl;
	cout << setfill(' ') << left << setw(20) << " " << setw(15) << "! Leaving the GAME SARGENT? !" << endl;
	cout << right << setfill('=') << setw(60) << " " << endl << endl;
	Sleep(2000);
}





void Playgame() {
	char gameMap[ROWS][COLS];
	int score = 0, level = 1, lives = 3;
	string playerName; // To store player's name
	int spaceShipx = COLS / 2, spaceShipy = ROWS - 2; // Initial ship position
	Entername(playerName);
	HideConsoleCursor();

	// Level 1: Normal gameplay
	level1(gameMap, spaceShipx, spaceShipy, score, level, lives);



	system("CLS");
	if (lives > 0) {
		cout << "Congratulations! You completed the game.\n";
		saveScoreToFile(playerName, score);
	}
	else {


		cout << "\t\t\n\nGAME OVER! SERGANT YOU RUN OUT OF LIVES TRY AGAIN .\t";
		Sleep(3000);
		saveScoreToFile(playerName, score);
	}

	Sleep(3000);
}









void Entername(string& name) {
	system("CLS");
	cout << setfill('=') << setw(60) << " " << endl;
	cout << setfill(' ') << left << setw(20) << " " << setw(15) << "Enter your name " << endl;
	cout << right << setfill('=') << setw(60) << " " << endl << endl;
	cout << setfill(' ') << setw(10) << " " << "-";
	cin.ignore();
	getline(cin, name);

}






void SetCursorPosition(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	SetConsoleCursorPosition(hConsole, position);
}





void gameMapinitialize(char gameMap[ROWS][COLS]) {// initializes the game boundary

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (i == 0 || i == ROWS - 1) {
				gameMap[i][j] = '*';// for upper and lower rows
			}
			else if (j == 0 || j == COLS - 1)
			{
				gameMap[i][j] = '|';// for columns 
			}
			else
			{
				gameMap[i][j] = ' ';// for the inner space 
			}
		}

	}

}






void displayMapOnce(char gameMap[ROWS][COLS], int& score, int& level) {
	system("cls");
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++) {
			cout << gameMap[i][j];
		}
		cout << endl;
	}


}






void HideConsoleCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo); // Retrieve current cursor settings
	cursorInfo.bVisible = FALSE; // Hide cursor
	SetConsoleCursorInfo(hConsole, &cursorInfo); // Apply settings
}







void drawShip(char gameMap[ROWS][COLS], int& x, int& y)
{
	gameMap[y][x] = '^';
	gameMap[y][x - 1] = '<';
	gameMap[y][x + 1] = '>';



}




void clearShip(char gameMap[ROWS][COLS], int& x, int& y)
{
	gameMap[y][x] = ' ';
	gameMap[y][x - 1] = ' ';
	gameMap[y][x + 1] = ' ';
}



void handleMultipleInputs(char gameMap[ROWS][COLS], int& shipx, int& shipy) {
	static bool keyStates[256] = { false }; // Key state tracker

	// Capture key presses
	while (_kbhit()) {  // Allow for multiple keys to be registered
		char key = _getch();
		keyStates[key] = true; // Mark the key as pressed
	}

	// Movement Handling
	if (keyStates['a'] && shipx > 2) { // Move left
		clearShip(gameMap, shipx, shipy);
		shipx--;
		drawShip(gameMap, shipx, shipy);
	}
	if (keyStates['d'] && shipx < COLS - 3) { // Move right
		clearShip(gameMap, shipx, shipy);
		shipx++;
		drawShip(gameMap, shipx, shipy);
	}

	// Shooting Handling
	if (keyStates[' ']) { // Shoot
		shootBullet(gameMap, shipx, shipy);
	}

	// Clear key states of keys that are no longer pressed
	for (int i = 0; i < 256; ++i) {
		if (GetAsyncKeyState(i) == 0) {  // Check if key is released
			keyStates[i] = false;
		}
	}
}






void level1(char gameMap[ROWS][COLS], int& shipx, int& shipy, int& score, int& level, int& lives) {
	time_t startTime = time(0);
	int TIME_LIMIT = 80;
	int distance = 0;
	int asteroidCount = 0;
	int enemyCount = 0;
	int powerCount = 0;
	static int remainingTimelevel1;
	int bosshealth = 20;
	gameMapinitialize(gameMap);
	displayMapOnce(gameMap, score, lives); // Display map for the first time
	drawShip(gameMap, shipx, shipy); // Draw the player's ship

	bool gameFlag = true;
	while (gameFlag) {

		// **Time Calculations**
		time_t currentTime = time(0);
		int elapsedTime = (int)difftime(currentTime, startTime);
		remainingTimelevel1 = TIME_LIMIT - elapsedTime;
		distance += 2;

		// **Update Game Info**
		updateScoreAndLevel(score, level, lives, distance, remainingTimelevel1);

		// **End Conditions**
		if (remainingTimelevel1 <= 0 || lives == 0) {
			gameFlag = false; // End the game if time is up or player loses all lives
			break;
		}

		// **Handle Player Input**
		handleMultipleInputs(gameMap, shipx, shipy);

		// **Spawn Enemies and Asteroids**
		if (enemyCount <= 10)
			spanEnemy(gameMap, enemyCount);
		if (asteroidCount <= 15)
			spanAsteroid(gameMap, asteroidCount);
		if (rand() % 20 == 10)
		{
			if (powerCount <= 10)
				spanPOWER(gameMap, powerCount);
		}
		// **Update Game Entities**
		MoveBullet(gameMap, score, bosshealth);
		EnemyShoot(gameMap);
		moveEnemies(gameMap);
		MoveEnemyBullet(gameMap, lives);
		moveAsteroid(gameMap, lives);
		movePower(gameMap, score);
		// **Redraw Map**
		redrawMap(gameMap);

		// **Frame Delay**
		Sleep(160); // Control frame speed for playability

		// **Level Complete Check**
		if (score >= 450 || distance >= 2500) {
			gameFlag = false; // End Level 1
			cout << "Level Complete! Prepare for the Boss Stage...\n";
			Sleep(2000); // Pause before transitioning
		}
	}


	if (lives < 0 || remainingTimelevel1 == 0)

	{
		Endgame();
	}
	else
	{
		level2(gameMap, shipx, shipy, score, level, lives, distance);
	}
}



void Endgame()
{

	system("CLS");

	cout << "\n\n\t\t  YOU LOST LOSER. YOU RUN OUT OF TIME TRY AGAIN.BE QUICK  \t";
	Sleep(4000);
	main();
}







void redrawMap(char gameMap[ROWS][COLS]) {

	SetCursorPosition(0, 0); // Reset cursor to the top-left
	for (int i = 0; i < ROWS - 1; i++) {
		for (int j = 0; j < COLS - 1; j++) {
			if (gameMap[i][j] == '^') {
				cout << "\033[31m" << gameMap[i][j] << "\033[0m"; // Red for spaceship
			}
			else if (gameMap[i][j] == '<' || gameMap[i][j] == '>') {
				cout << "\033[32m" << gameMap[i][j] << "\033[0m"; // Green for spaceship parts
			}
			else if (gameMap[i][j] == '@') { // Assuming 'A' represents enemies
				std::cout << "\033[35m" << gameMap[i][j] << "\033[0m"; // magenta for asteroids
			}
			else if (gameMap[i][j] == '!') { // Assuming '!' represents enemies
				cout << "\033[36m" << gameMap[i][j] << "\033[0m"; // Blue for enemie bullet
			}
			else if (gameMap[i][j] == '+') { // Assuming '+' represents enemies
				cout << "\033[31m" << gameMap[i][j] << "\033[0m"; // red for our bullets
			}
			else if (gameMap[i][j] == 'E') { // Assuming 'E' represents enemies
				cout << "\033[33m" << gameMap[i][j] << "\033[0m"; // yellow for enemies
			}
			else if (gameMap[i][j] == ':') { // Assuming ':' represents boss enemies
				cout << "\033[32m" << gameMap[i][j] << "\033[0m"; // green for enemies
			}
			else if (gameMap[i][j] == '=') { // Assuming '=' represents boss enemies
				cout << "\033[34m" << gameMap[i][j] << "\033[0m";
			}
			else if (gameMap[i][j] == '_') { // Assuming '_' represents boss enemies
				cout << "\033[35m" << gameMap[i][j] << "\033[0m";
			}
			else {
				cout << gameMap[i][j]; // Default for other characters
			}
		}
		cout << endl;
	}
}







void updateScoreAndLevel(int& score, int& level, int& lives, int& distance, int& timeremaining) {
	SetCursorPosition(COLS + 5, 1); // Place score display at a fixed location
	cout << "Score: " << score;
	SetCursorPosition(COLS + 5, 2); // Place level display at a fixed location
	cout << "Level: " << level;
	SetCursorPosition(COLS + 5, 3); // Place lives display at a fixed location
	cout << "Lives: " << lives;
	SetCursorPosition(COLS + 5, 4); // Place distance display at a fixed location
	cout << "Distance: " << distance << endl;
	SetCursorPosition(COLS + 5, 5); // Place distance display at a fixed location
	cout << "Time remaining " << timeremaining << endl;
	SetCursorPosition(0, 0);
}







void displayBossHealth(int& bosshealth)
{
	SetCursorPosition(COLS + 5, 6); // Place boss health display at a fixed location
	cout << "BOSS HEALTH: " << bosshealth;
}







void spanEnemy(char gameMap[ROWS][COLS], int& enemyCount) {
	while (true) {
		int enemyx = rand() % 25;
		int enemyy = rand() % 17;
		if (enemyx == 0 || enemyy == 0)
		{
			enemyx++;
			enemyy++;
		}
		if (gameMap[enemyy][enemyx] == ' ') {
			SetCursorPosition(enemyy, enemyx);
			gameMap[enemyy][enemyx] = 'E';
			enemyCount++;
			break;
		}
	}
}









void spanAsteroid(char gameMap[ROWS][COLS], int& asteroidCount)
{

	while (true) {
		int asteroidx = rand() % 28;
		int asteroidy = rand() % 18;
		while (asteroidx == 1 || asteroidx == ROWS - 2)
		{
			asteroidx = asteroidx + 2;
			asteroidy++;
		}
		if (gameMap[asteroidy][asteroidx] == ' ')
		{
			SetCursorPosition(asteroidy, asteroidx);
			gameMap[asteroidy][asteroidx] = '@';
			asteroidCount++;
			break;
		}
	}
}
void spanPOWER(char gameMap[ROWS][COLS], int& power)// power up
{

	while (true) {
		int powerx = rand() % 28;
		int poweryy = rand() % 18;
		while (powerx == 1 || powerx == ROWS - 2)
		{
			powerx = powerx + 2;
			poweryy++;
		}
		if (gameMap[poweryy][powerx] == ' ')
		{
			SetCursorPosition(poweryy, powerx);
			gameMap[poweryy][powerx] = '\"';
			power++;
			break;
		}
	}
}









void shootBullet(char gameMap[ROWS][COLS], int& shipx, int& shipy)
{
	if (gameMap[shipy - 1][shipx] = ' ')
	{
		gameMap[shipy - 1][shipx] = '+';
	}
}









void moveEnemies(char gameMap[ROWS][COLS])
{
	for (int i = 1; i < ROWS - 2; i++)
	{
		for (int j = COLS - 2; j >= 1; j--)
		{
			if (gameMap[i][j] == 'E')
			{
				if (gameMap[i][j + 1] == ' ' && j < COLS - 2)
				{
					gameMap[i][j] = ' ';
					gameMap[i][j + 1] = 'E';
				}
				else if (gameMap[i][j + 1] == 'E' && j < COLS - 2)
				{
					gameMap[i][j] = ' ';
				}
				else if (j >= COLS - 2)
				{
					gameMap[i][j] = ' ';
					gameMap[i][2] = 'E';
				}
			}

		}
	}
}









void moveAsteroid(char gameMap[ROWS][COLS], int& lives)
{
	for (int i = ROWS; i >= 1; i--)
	{

		for (int j = 1; j < COLS - 1; j++)
		{
			if (gameMap[i][j] == '@')
			{
				if (gameMap[i + 1][j] == ' ' && i <= ROWS - 2)
				{

					gameMap[i][j] = ' ';
					gameMap[i + 1][j] = '@';

				}
				else if (gameMap[i + 1][j] == '@' && i <= ROWS - 2)
				{
					gameMap[i][j] = ' ';
					gameMap[i + 1][j] = ' ';

				}
				else if (gameMap[i + 1][j] == 'E')
				{
					gameMap[i][j] = ' ';
					gameMap[i + 1][j] = ' ';
				}
				else if (gameMap[i + 1][j] == '+')
				{
					gameMap[i][j] = ' ';
					gameMap[i + 1][j] = ' ';
				}
				else if (gameMap[i + 1][j] == '^' || gameMap[i + 1][j] == '<' || gameMap[i + 1][j] == '>') { // Hit the player's ship
					gameMap[i][j] = ' '; // Remove bullet
					gameMap[i + 1][j] = ' '; // Clear ship part
					lives--; // Reduce player's lives
					Sleep(2000);
				}
				else if (i >= ROWS - 2)
				{
					gameMap[i][j] = ' ';
					gameMap[1][j] = '@';

				}
			}

		}
	}
}
void movePower(char gameMap[ROWS][COLS], int& score)
{
	for (int i = ROWS - 1; i >= 1; i--)
	{

		for (int j = 1; j < COLS - 1; j++)
		{
			if (gameMap[i][j] == '\"')
			{
				if (gameMap[i + 1][j] == ' ' && i <= ROWS - 2)
				{

					gameMap[i][j] = ' ';
					gameMap[i + 1][j] = '\"';

				}
				else if (gameMap[i + 1][j] == '\"' && i <= ROWS - 2)
				{
					gameMap[i][j] = ' ';
					gameMap[i + 1][j] = ' ';

				}
				else if (gameMap[i + 1][j] == 'E')
				{
					gameMap[i][j] = ' ';
					gameMap[i + 1][j] = ' ';
				}
				else if (gameMap[i + 1][j] == '+')
				{
					gameMap[i][j] = ' ';
					gameMap[i + 1][j] = ' ';
					score = score + 10;
				}
				else if (gameMap[i + 1][j] == '^' || gameMap[i + 1][j] == '<' || gameMap[i + 1][j] == '>') { // Hit the player's ship
					gameMap[i][j] = ' '; // Remove bullet
					gameMap[i + 1][j] = ' '; // Clear ship part
					score = score + 10;; // Reduce player's lives

				}
				else if (i >= ROWS - 2)
				{
					gameMap[i][j] = ' ';
					gameMap[1][j] = '\"';

				}
			}

		}
	}
}








void MoveBullet(char gameMap[ROWS][COLS], int& score, int& bosshealth)
{
	for (int i = 1; i < ROWS - 2; i++)
	{
		for (int j = 1; j < COLS - 2; j++)
		{
			if (gameMap[i][j] == '+')
			{
				if (gameMap[i - 1][j] == ' ')
				{
					gameMap[i][j] = ' ';
					gameMap[i - 1][j] = '+';
				}
				else if (gameMap[i - 1][j] == 'E') // Hit Enemy
				{
					gameMap[i][j] = ' ';
					gameMap[i - 1][j] = ' ';
					score = score + 50; // Score for hitting enemy
				}
				else if (gameMap[i - 1][j] == '@') // Hit Asteroid
				{
					gameMap[i][j] = ' ';
					gameMap[i - 1][j] = ' ';
					score = score + 60; // Added score for hitting asteroid
				}
				else if (gameMap[i - 1][j] == '!')
				{
					gameMap[i][j] = ' ';
					gameMap[i - 1][j] = ' ';
				}
				else if (gameMap[i - 1][j] == '_' || gameMap[i - 1][j] == ':' || gameMap[i - 1][j] == '-' || gameMap[i - 1][j] == '=')
				{
					gameMap[i][j] = ' ';
					gameMap[i - 1][j] = ' ';
					bosshealth--;
					score += 50;
				}
				else if (i == 1)
				{
					gameMap[i][j] = ' ';
				}
			}
		}
	}
}













void EnemyShoot(char gameMap[ROWS][COLS])
{
	for (int i = 0; i < ROWS - 1; i++) // Avoid last row
	{
		for (int j = 0; j < COLS; j++)
		{
			if (gameMap[i][j] == 'E') // Check for enemy
			{
				// Look below the enemy for a player's ship
				for (int k = i + 1; k < ROWS - 1; k++)
				{
					if (gameMap[k][j] == '^') // If a ship is below
					{
						if (gameMap[i + 1][j] == ' ') // Space below enemy is empty
						{
							gameMap[i + 1][j] = '!'; // Place projectile
						}
						break; // Stop checking further below
					}
				}
			}
		}
	}
}







void MoveEnemyBullet(char gameMap[ROWS][COLS], int& lives) {
	for (int i = ROWS - 2; i >= 0; i--) { // Traverse rows top to bottom (to move bullets downward)
		for (int j = 1; j < COLS - 1; j++) { // Avoid borders
			if (gameMap[i][j] == '!') { // Enemy bullet found
				char below = gameMap[i + 1][j];

				if (below == ' ') {
					gameMap[i][j] = ' '; // Clear current position
					gameMap[i + 1][j] = '!'; // Move bullet down
				}
				else if (below == '^' || below == '<' || below == '>') { // Hit the player's ship
					gameMap[i][j] = ' '; // Remove bullet
					gameMap[i + 1][j] = ' '; // Clear ship part
					lives--; // Reduce player's lives
				}
				else if (below == '@' || below == 'E') { // Collides with asteroid or enemy (optional)
					gameMap[i][j] = ' '; // Clear bullet
					gameMap[i + 1][j] = ' '; // Clear obstacle
				}
				// Boundary check
				else if (i + 1 >= ROWS - 1) {
					gameMap[i][j] = ' '; // Remove bullet at the bottom boundary
				}
			}
		}
	}
}






void drawBoss(char gameMap[ROWS][COLS], int x, int y) {
	gameMap[y][x] = '-';    // Boss center
	gameMap[y][x - 1] = ':'; // Left wing
	gameMap[y][x + 1] = ':'; // Right wing
	gameMap[y - 1][x] = '_';
	gameMap[y + 1][x] = '=';
	gameMap[y - 1][x - 1] = ':';
	gameMap[y - 1][x + 1] = ':';
}






void moveBoss(char gameMap[ROWS][COLS], int& x, int y, int& direction) {
	// Clear current position
	gameMap[y][x] = ' ';    // Boss center
	gameMap[y][x - 1] = ' '; // Left wing
	gameMap[y][x + 1] = ' '; // Right wing
	gameMap[y - 1][x] = ' ';
	gameMap[y + 1][x] = ' ';
	gameMap[y - 1][x - 1] = ' ';
	gameMap[y - 1][x + 1] = ' ';

	// Update position
	if (x <= 2 || x >= COLS - 3) {
		direction *= -1; // Reverse direction at boundaries
	}
	x += direction;

	// Draw boss at new position
	drawBoss(gameMap, x, y);
}





void bossShoot(char gameMap[ROWS][COLS], int x, int y) {
	if (gameMap[y + 2][x] == ' ') {       // Fire from the center
		gameMap[y + 2][x] = '!';
	}
	if (gameMap[y + 1][x - 1] == ' ') {   // Fire from the left wing
		gameMap[y + 1][x - 1] = '!';
	}
	if (gameMap[y + 1][x + 1] == ' ') {   // Fire from the right wing
		gameMap[y + 1][x + 1] = '!';
	}
}





void detectBossHit(char gameMap[ROWS][COLS], int x, int y, int& health, int& score)
{
	// Check boss's grid cells for bullets
	if (gameMap[y][x] == '+' || gameMap[y][x - 1] == '+' || gameMap[y][x + 1] == '+')
	{
		health--;

		cout << "Boss Hit! Health: " << health << ", Score: " << score << endl; // Debug statement
		// Clear bullet
		gameMap[y][x] = ' ';
		gameMap[y][x - 1] = ' ';
		gameMap[y][x + 1] = ' ';
	}
}



void level2(char gameMap[ROWS][COLS], int& shipx, int& shipy, int& score, int& level, int& lives, int& distance) {
	int bossHealth = 20;  // Boss requires 20 hits to defeat
	int bossX = COLS / 2, bossY = 2;  // Initial boss position
	int bossDirection = 1;  // 1 = right, -1 = left
	int powerCount = 0;
	time_t startTime = time(0);  // Start time of level boss
	int TIME_LIMIT = 90;

	int asteroidCount = 0;
	int enemyCount = 0;
	static int remainingTimelevel2;

	int frameCounter = 0;        // NEW: Frame counter to control boss fire rate
	const int bossFireRate = 15; // NEW: Boss fires every 15 frames

	gameMapinitialize(gameMap);
	displayMapOnce(gameMap, score, lives);
	drawShip(gameMap, shipx, shipy);  // Draw player ship
	/*updateScoreAndLevel(score, level, lives, distance, remainingTimelevel2);*/
	displayBossHealth(bossHealth);
	drawBoss(gameMap, bossX, bossY);  // Draw boss on the map

	bool keyStates[256] = { false };  // Track the state of each key
	bool gameFlag = true;
	int gameSpeed = 160;
	while (gameFlag)
	{
		// **Time Calculations**
		time_t currentTime = time(0);
		int elapsedTime = (int)difftime(currentTime, startTime);
		remainingTimelevel2 = TIME_LIMIT - elapsedTime;
		updateScoreAndLevel(score, level, lives, distance, remainingTimelevel2);
		distance += 2;



		displayBossHealth(bossHealth);

		// **Handle Multiple Inputs**
		while (_kbhit()) {  // Allow for multiple keys to be registered
			char key = _getch();
			keyStates[key] = true;  // Mark the key as pressed
		}

		// Movement Handling
		if (keyStates['a'] && shipx > 2) {  // Move left
			clearShip(gameMap, shipx, shipy);
			shipx--;
			drawShip(gameMap, shipx, shipy);
		}
		if (keyStates['d'] && shipx < COLS - 3) {  // Move right
			clearShip(gameMap, shipx, shipy);
			shipx++;
			drawShip(gameMap, shipx, shipy);
		}

		// Shooting Handling
		if (keyStates[' ']) {  // Shoot
			shootBullet(gameMap, shipx, shipy);
		}

		// Clear released keys
		for (int i = 0; i < 256; ++i) {
			if (GetAsyncKeyState(i) == 0) {  // Reset if the key is released
				keyStates[i] = false;
			}
		}
		if (enemyCount <= 3)
			spanEnemy(gameMap, enemyCount);
		if (asteroidCount <= 5)
			spanAsteroid(gameMap, asteroidCount);
		if (powerCount <= 7) {
			if (rand() % 20 == 10)
			{
				if (powerCount <= 7)
					spanPOWER(gameMap, powerCount);
				gameSpeed = gameSpeed - 10;
			}
		}
		// **Move the Boss**
		moveBoss(gameMap, bossX, bossY, bossDirection);


		// **Boss Shooting Based on Frame Rate**
		if (frameCounter % bossFireRate == 0) {  // Boss fires every `bossFireRate` frames
			bossShoot(gameMap, bossX, bossY);
		}

		// **Move Bullets and Check for Hits**
		MoveBullet(gameMap, score, bossHealth);
		MoveEnemyBullet(gameMap, lives);
		moveAsteroid(gameMap, lives);
		moveEnemies(gameMap);
		movePower(gameMap, score);
		EnemyShoot(gameMap);
		detectBossHit(gameMap, bossX, bossY, bossHealth, score);



		// **Check Win/Lose Conditions**
		if (bossHealth <= 0) {
			gameFlag = false;
			cout << "\t\t\n\n You defeated the boss! Congratulations!\t";
			break;
		}
		if (lives <= 0 || remainingTimelevel2 <= 0) {
			gameFlag = false;
			cout << "Game Over! You ran out of lives.\n";
			break;
		}

		// **Redraw Map**
		redrawMap(gameMap);
		Sleep(gameSpeed);  // Frame delay

		frameCounter++;  // Increment frame counter
	}
}
