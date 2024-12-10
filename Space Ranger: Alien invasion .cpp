#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<string>
#include<iomanip>
#include<Windows.h>// for system related and cursor related 
#include<conio.h>// for getch and kbhit
#include<ctime>// for time related work like end the game if time ends

using namespace std;
const int ROWS = 30, COLS = 30;// global variables so every function can access them to increase readibility 
const int MAXEnemies = 10;
const int MAXasteroids = 15;
const int lives = 3;

void updateScoreAndLevel(int& score, int& level, int& lives, int& distance, int& timeremaining);
void spanAsteroid(char gameMap[ROWS][COLS], int& asteroidCount);// movement functions
void spanEnemy(char gameMap[ROWS][COLS], int& enemyCount);
void moveEnemies(char gameMap[ROWS][COLS]);
void EnemyShoot(char gameMap[ROWS][COLS]);
void moveAsteroid(char gameMap[ROWS][COLS],int& lives);
void MoveEnemyBullet(char gameMap[ROWS][COLS], int& lives);
void drawBoss(char gameMap[ROWS][COLS], int x, int y);



void Entername();
void SetCursorPosition(int x, int y);// function alternative for clear screen to avoid flickering and just update the game map 
void gameMapinitialize(char gameMap[ROWS][COLS]);
void displayMapOnce(char gameMap[ROWS][COLS], int& score, int& level);//display the map once
void redrawMap(char gameMap[ROWS][COLS]);
void HideConsoleCursor();

void level1(char gameMap[ROWS][COLS], int& shipx, int& shipy, int& score, int& level, int& lives);// level functions
void level2(char gameMap[ROWS][COLS], int& shipx, int& shipy, int& score, int& level, int& lives);

void displayBossHealth(int& bosshealth);// game object
void drawShip(char gameMap[ROWS][COLS], int& x, int& y);
void shootBullet(char gameMap[ROWS][COLS], int& shipx, int& shipy);
void clearShip(char gameMap[ROWS][COLS], int& x, int& y);
void MoveBullet(char gameMap[ROWS][COLS], int& score);

void mainMenu(int&);// main menu
void Playgame();
void instruction();
void highScores();
void invalid();
void credit();
void exit();

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
	
	cin >> a;// refrence variable for choice in main menu 

	cout << setfill('=') << setw(60) << " " << endl;// last line of border
	_getch();// stay on sceen for 2 second time 
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




void highScores()
{
	system("CLS");
	cout << setfill('=') << setw(60) << " " << endl;// initial lines 
	cout << setfill(' ') << left << setw(20) << " " << setw(15) << "HIGH SCORES" << endl;
	cout << right << setfill('=') << setw(60) << " " << endl << endl;
	/// //high scores 
	cout << setfill(' ') << setw(10) << " " << "1. PLAY GAME " << endl;   // 
	cout << setfill(' ') << setw(10) << " " << "2. INSTRUCTIONS " << endl;
	cout << setfill(' ') << setw(10) << " " << "3. HIGH SCORES " << endl;
	cout << setfill(' ') << setw(10) << " " << "4. PLAY GAME " << endl;   //
	cout << setfill(' ') << setw(10) << " " << "5. INSTRUCTIONS " << endl;
	cout << setfill(' ') << setw(10) << " " << "6. HIGH SCORES " << endl;
	cout << setfill(' ') << setw(10) << " " << "7. INSTRUCTIONS " << endl;
	cout << setfill(' ') << setw(10) << " " << "8. HIGH SCORES " << endl;
	cout << setfill(' ') << setw(10) << " " << "9. INSTRUCTIONS " << endl;
	cout << setfill(' ') << setw(10) << " " << "10. HIGH SCORES " << endl;

	cout << setfill('=') << setw(60) << " " << endl;
	cout << setfill(' ') << setw(10) << " " << "Press any key to return to MAIN MENU ";
	int a = _getch();
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

	int spaceShipx = COLS / 2, spaceShipy = ROWS - 2; // Initial ship position
	Entername();
	HideConsoleCursor();

	// Level 1: Normal gameplay
	level1(gameMap, spaceShipx, spaceShipy, score, level, lives);

	// Transition to Level 2: Boss stage
	if (lives > 0) { // Only proceed if the player has lives left
		level2(gameMap, spaceShipx, spaceShipy, score, level, lives);
	}

	system("CLS");
	if (lives > 0) {
		cout << "Congratulations! You completed the game.\n";
	}
	else {
		cout << "Game Over! Better luck next time.\n";
	}

	Sleep(3000);
}









void Entername() {
	system("CLS");
	string name;
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
	//cout << setfill(' ') << setw(10) << "SCORE:" << score << setfill(' ') << setw(10) << "Level :" << level;

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






void level1(char gameMap[ROWS][COLS], int& shipx, int& shipy, int& score, int& level, int& lives) {
	time_t startTime = time(0);
	const int  TIME_LIMIT = 90;
	int distance = 0;
	int asteroidCount = 0;
	int enemyCount = 0;
	static int remainingTimelevel1;
	gameMapinitialize(gameMap);
	displayMapOnce(gameMap, score, lives);// displays map for the first time mainly the boundary
	drawShip(gameMap, shipx, shipy);//update  the space ship on to the map


	bool gameFlag = true;
	while (gameFlag)
	{

		time_t currentTime = time(0);
		int elapsedTime = (int)difftime(currentTime, startTime);
		remainingTimelevel1 = TIME_LIMIT - elapsedTime;
		distance = distance + 2;
		updateScoreAndLevel(score, level, lives, distance, remainingTimelevel1);



		if (remainingTimelevel1 <= 0||lives==0) {
			gameFlag = false; // Time is up, stop the game
			break;
		}


		// Handle user input
		if (_kbhit()) {
			char key = _getch();

			if (key == 'a' && shipx > 2) { // Move left if within bounds
				clearShip(gameMap, shipx, shipy);
				shipx--;
				drawShip(gameMap, shipx, shipy);
			}
			else if (key == 'd' && shipx < COLS - 3) { // Move right if within bounds
				clearShip(gameMap, shipx, shipy);
				shipx++;
				drawShip(gameMap, shipx, shipy);
			}
			else if (key == ' ') {
				shootBullet(gameMap, shipx, shipy);
			}
			else if (key == 'q') { // Quit the game
				gameFlag = false;
				break;
			}
		}

		if (enemyCount <= 10)
		{
			spanEnemy(gameMap, enemyCount);
		}
		if (asteroidCount <= 15)
		{
			spanAsteroid(gameMap, asteroidCount);
		}

		MoveBullet(gameMap, score);
		EnemyShoot(gameMap);
		moveEnemies(gameMap);
		MoveEnemyBullet(gameMap, lives);

		moveAsteroid(gameMap,lives);
		redrawMap(gameMap);


		Sleep(160);
	}

	if (score >= 400)
	{
		gameFlag = false; // End Level 1
		cout << "Level Complete! Prepare for the Boss Stage...\n";
		Sleep(2000); // Pause before transitioning
	}



}





void redrawMap(char gameMap[ROWS][COLS]) {

	SetCursorPosition(0, 0); // Reset cursor to the top-left
	for (int i = 0; i < ROWS - 1; i++) {
		for (int j = 0; j < COLS - 1; j++) {
			cout << gameMap[i][j];
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
	cout << "Time reamining " << timeremaining << endl;
	SetCursorPosition(0, 0);
}

void displayBossHealth(int& bosshealth)
{
	SetCursorPosition(COLS + 5, 6); // Place boss health display at a fixed location
	cout << "Score: " << bosshealth;
}




void spanEnemy(char gameMap[ROWS][COLS], int& enemyCount) {
	while (true) {
		int enemyx = rand() % 28;
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
		int asteroidx = rand() % 30;
		int asteroidy = rand() % 20;
		while (asteroidx == 0 || asteroidy == 0)
		{
			asteroidx++;
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





void moveAsteroid(char gameMap[ROWS][COLS],int& lives)
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






void MoveBullet(char gameMap[ROWS][COLS], int& score)
{
	for (int i = 1; i < ROWS - 1; i++)
	{

		for (int j = 1; j < COLS - 1; j++)
		{
			if (gameMap[i][j] == '+')
			{
				if (gameMap[i - 1][j] == ' ')
				{
					gameMap[i][j] = ' ';
					gameMap[i - 1][j] = '+';
				}
				else if (gameMap[i - 1][j] == 'E' || gameMap[i - 1][j] == '@')
				{
					gameMap[i][j] = ' ';
					gameMap[i - 1][j] = ' ';
					score = score + 50;
				}
				else if (gameMap[i - 1][j] == '!')
				{
					gameMap[i][j] = ' ';
					gameMap[i - 1][j] = ' ';

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
				for (int k = i + 1; k < ROWS; k++)
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
	gameMap[y][x] = 'B';    // Boss center
	gameMap[y][x - 1] = '<'; // Left wing
	gameMap[y][x + 1] = '>'; // Right wing
}




void moveBoss(char gameMap[ROWS][COLS], int& x, int y, int& direction) {
	// Clear current position
	gameMap[y][x] = ' ';
	gameMap[y][x - 1] = ' ';
	gameMap[y][x + 1] = ' ';

	// Update position
	if (x <= 2 || x >= COLS - 3) {
		direction *= -1; // Reverse direction at boundaries
	}
	x += direction;

	// Draw boss at new position
	drawBoss(gameMap, x, y);
}

void bossShoot(char gameMap[ROWS][COLS], int x, int y) {
	if (gameMap[y + 1][x] == ' ') {
		gameMap[y + 1][x] = '!';
	}
}


void detectBossHit(char gameMap[ROWS][COLS], int x, int y, int& health, int& score) {
	// Check boss's grid cells for bullets
	if (gameMap[y][x] == '+' || gameMap[y][x - 1] == '+' || gameMap[y][x + 1] == '+') {
		health--; // Reduce boss health
		score += 100; // Increase score
		// Clear bullet
		gameMap[y][x] = ' ';
		gameMap[y][x - 1] = ' ';
		gameMap[y][x + 1] = ' ';
	}
}






void level2(char gameMap[ROWS][COLS], int& shipx, int& shipy, int& score, int& level, int& lives) {
	int bossHealth = 20; // Boss requires 20 hits to defeat
	int bossX = COLS / 2, bossY = 2; // Initial boss position
	int bossDirection = 1; // 1 = right, -1 = left
	int bossShootTimer = 0; // Controls how often the boss fires

	time_t startTime = time(0);// start time of level boss
	const int  TIME_LIMIT = 90;
	int distance = 0;
	int asteroidCount = 0;
	int enemyCount = 0;
	static int remainingTimelevel2;
	gameMapinitialize(gameMap);
	displayMapOnce(gameMap, score, lives);
	drawShip(gameMap, shipx, shipy); // Draw player ship
	updateScoreAndLevel(score, level, lives, distance, remainingTimelevel2);
	displayBossHealth(bossHealth);
	//updateScoreAndLevel(score,level,lives,distance, int& timeremaining);
	drawBoss(gameMap, bossX, bossY); // Draw boss on the map

	bool gameFlag = true;
	while (gameFlag) {
		time_t currentTime = time(0);
		int elapsedTime = (int)difftime(currentTime, startTime);
		remainingTimelevel2 = TIME_LIMIT - elapsedTime;
		distance = distance + 2;
		updateScoreAndLevel(score, level, lives, distance, remainingTimelevel2);
		displayBossHealth(bossHealth);
		// Handle user input for player ship
		if (_kbhit()) {
			char key = _getch();
			if (key == 'a' && shipx > 2) { // Move left
				clearShip(gameMap, shipx, shipy);
				shipx--;
				drawShip(gameMap, shipx, shipy);
			}
			else if (key == 'd' && shipx < COLS - 3) { // Move right
				clearShip(gameMap, shipx, shipy);
				shipx++;
				drawShip(gameMap, shipx, shipy);
			}
			else if (key == ' ') {
				shootBullet(gameMap, shipx, shipy); // Fire a bullet
			}
			else if (key == 'q') { // Quit the game
				gameFlag = false;
				break;
			}
		}

		// Move the boss
		moveBoss(gameMap, bossX, bossY, bossDirection);

		// Handle boss shooting
		bossShootTimer++;
		if (bossShootTimer >= 10) { // Fire every 10 frames
			bossShoot(gameMap, bossX, bossY);
			bossShootTimer = 0;
		}

		// Move bullets and check for hits
		MoveBullet(gameMap, score);
		MoveEnemyBullet(gameMap, lives);
		detectBossHit(gameMap, bossX, bossY, bossHealth, score);

		// Check win/lose conditions
		if (bossHealth <= 0) {
			gameFlag = false;
			cout << "You defeated the boss! Congratulations!\n";
			break;
		}
		if (lives <= 0) {
			gameFlag = false;
			cout << "Game Over! You ran out of lives.\n";
			break;
		}

		// Redraw map
		redrawMap(gameMap);
		Sleep(160);
	}
}


