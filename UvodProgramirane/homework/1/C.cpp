#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int main() {
	// Constants
	const int mStatsPerLevel = 2;
	const int skillPointsPerLevel = 5;

	const int pBaseHealth = 100,
				pBaseDamage = 10,
				pBaseArmor = 25,
				pBaseLuck = 5;

	const int mBaseHealth = 50,
				mBaseDamage = 5,
				mBaseArmor = 5,
				mBaseLuck = 0;
	// End Constants


	// Variables
	int pPointsHealth = 0,
		pPointsDamage = 0,
		pPointsArmor = 0,
		pPointsLuck = 0,
		pPotions = 5,
		pCurrHealth,
		skillPoints;

	int mCurrHealth,
		mLevel = 0;

	bool running;
	bool playing;
	bool inTurn;
	bool actualTurn;

	char in;
	int credits = 0;
	int repeats;
	int roll;
	int critChance;
	int fullDefenceChance;
	// End Variables


	// Initialization
	srand(time(NULL));
	running = true;
	// End Initialization


	// Game loop
	while (running) {
		cout << "Welcome to Terrabithia!\n\n";
		cout << "You are the new knight assigned to protect the kingdom.\n";
		cout << "Are you ready ?[y|n] ";

		// Handle question
		repeats = 0;
		do {
			cin >> in;
			if(cin.eof()) {
				cout << "Why are you doing this ??\n\n";
				return 0;
			}
			in = tolower(in);
			repeats++;
			if(repeats % 5 == 0) {
				cout << "C'mon already the game won't break or anything...\n";
			}
		} while(in != 'y' && in != 'n');

		if(in == 'n') {
			cout << "So get out of here coward!\n";
			break;
		}
		// End Handle question

		cout << "\n\nHere comes your first challenge!\n\n\n\n";
		playing = true;

		while(playing) {
			int outcome;
			inTurn = true;
			pCurrHealth = pBaseHealth + pPointsHealth;
			mCurrHealth = mBaseHealth + mLevel * mStatsPerLevel;

			while(inTurn) {
				int pTurnDamage = 0;
				float pTurnDefenceMultiplier = 1;
				int mTurnDamage = 0;
				float mTurnDefenceMultiplier = 1;

				// Player turn
				cout << "You are facing a monster of level " << mLevel+1 <<".\n\n";
				cout << "What are you going to do:\n";
				cout << "Show [I]nfo\n";
				cout << "[A]ttack\n";
				cout << "[D]efend\n";
				cout << "Drink [P]otion\n\n";

				cout << "E[x]it the game\n";

				cin >> in;
				if(cin.eof()) {
					cout << "Why are you doing this ??\n\n";
					return 0;
				}
				in = tolower(in);

				while (in != 'i' && in != 'a' && in != 'd' && in != 'p' && in != 'x') {
					cout << "I'm not sure what you meant :/\n";
					cin >> in;
					if(cin.eof()) {
						cout << "Why are you doing this ??\n\n";
						return 0;
					}
					in = tolower(in);
				}

				switch(in) {
					case 'i':
						//Show Stats
						actualTurn = false;
						cout << "\nYour Stats:\n";
						cout << "Health: " << pCurrHealth << "\n";
						cout << "Damage: " << pBaseDamage + pPointsDamage << "\n";
						cout << "Armor: " << pBaseArmor + pPointsArmor << "\n";
						cout << "Luck: " << pBaseLuck + pPointsLuck << "\n";
						cout << "Potions: " << pPotions << "\n";
						cout << "\nMonster Level " << mLevel + 1 << " Stats:\n";
						cout << "Health: " << mCurrHealth << "\n";
						cout << "Damage: " << mBaseDamage + mLevel * mStatsPerLevel << "\n";
						cout << "Armor: " << mBaseArmor + mLevel * mStatsPerLevel << "\n";
						cout << "Luck: " << mBaseLuck + mLevel * mStatsPerLevel << "\n";
						cout << "\n\n";
						break;
					case 'a':
						//Attack
						actualTurn = true;
						pTurnDamage = pBaseDamage + pPointsDamage;
						critChance = (pBaseLuck + pPointsLuck) / 2;
						roll = rand() % 100 + 1;
						if (critChance >= roll) {
							pTurnDamage *= 2;
							cout << "\nYou dealt a critical strike!\n";
						}
						break;
					case 'd':
						//Defend
						cout << "\nYou defend.\n";
						actualTurn = true;
						pTurnDefenceMultiplier = 0.5f;
						fullDefenceChance = (pBaseLuck + pPointsLuck) / 2;
						roll = rand() % 100 + 1;
						if (fullDefenceChance >= roll) {
							pTurnDefenceMultiplier = 0;
							cout << "\nYou successfully blocked all damage!\n";
						}
						break;
					case 'p':
						//Drink Potion
						actualTurn = pPotions > 0;
						if(actualTurn) {
							pPotions--;
							pCurrHealth = pBaseHealth + pPointsHealth;
							cout << "\nYour health has been replenished.\n";
						} else {
							cout << "\nYou don't have any potions left!\n\n";
						}
						break;
					case 'x':
						//Exit
						cout << "\nNow who will defend the kingdom??\n\n";
						return 0;
				}
				// End Player turn

				if(!actualTurn) {
					continue;
				}

				int monsterChoice = rand() % 2;
				switch (monsterChoice) {
					case 0:
						//Attack
						mTurnDamage = mBaseDamage + mLevel * mStatsPerLevel;
						critChance = (mBaseLuck + mLevel * mStatsPerLevel) / 2;
						roll = rand() % 100 + 1;
						if (critChance >= roll) {
							mTurnDamage *= 2;
							cout << "\nThe monster dealt a critical strike!\n";
						}
						break;
					case 1:
						//Defend
						cout << "\nThe monster defends.\n";
						mTurnDefenceMultiplier = 0.5f;
						fullDefenceChance = (mBaseLuck + mLevel * mStatsPerLevel) / 2;
						roll = rand() % 100 + 1;
						if (fullDefenceChance >= roll) {
							mTurnDefenceMultiplier = 0;
							cout << "\nThe monster blocked all damage!\n";
						}
						break;
				}

				if(pTurnDamage > 0) {
					int mDefense = (mBaseArmor + mLevel * mStatsPerLevel) / 2;
					int totalDamage = (pTurnDamage - (pTurnDamage * mDefense / 100))
										* mTurnDefenceMultiplier;
					cout << "\nYou attack the monster!\n";
					cout << "\nYou dealt " << totalDamage << " damage!\n";
					mCurrHealth = max(0, mCurrHealth - totalDamage);
				}

				if(mTurnDamage > 0 && mCurrHealth > 0) {
					int pDefense = (pBaseArmor + pPointsArmor) / 2;
					int totalDamage = (mTurnDamage - (mTurnDamage * pDefense / 100))
										* pTurnDefenceMultiplier;
					cout << "\nThe monster attacks you!\n";
					cout << "\nIt dealt " << totalDamage << " damage!\n";
					pCurrHealth = max(0, pCurrHealth - totalDamage);
				}

				cout << "\nYour health is " << pCurrHealth << "\n";
				cout << "The monster's health is " << mCurrHealth << "\n";

				if(mCurrHealth <= 0) {
					outcome = 0;
					inTurn = false;
				} else if (pCurrHealth <= 0) {
					outcome = 1;
					inTurn = false;
				}

				cout << "\n\n";
			}

			switch(outcome) {
				case 0:
					// Monster dead
					skillPoints = skillPointsPerLevel;
					mLevel++;
					credits++;
					roll = rand() % 2;
					cout << "\nCongratulations! You defeated a Level " << mLevel
						<< " monster!\n";
					cout << "Your health is replenished!\n";
					cout << "You get 1 credit!\n";
					cout << "You get " << skillPoints << " skill points!\n";
					if(roll == 1) {
						pPotions++;
						cout << "You also found a potion in the monster!\n";
					}

					//Skill appointment
					while(skillPoints > 0) {
						cout << "\nYou have " << skillPoints << " skill points left.\n";
						cout << "What skill do you want to improve: \n";
						cout << "[H]ealth (Current: " << pPointsHealth << ") \n";
						cout << "[D]amage (Current: " << pPointsDamage << ") \n";
						cout << "[A]rmor (Current: " << pPointsArmor << ") \n";
						cout << "[L]uck (Current: " << pPointsLuck << ") \n";
						cin >> in;
						if(cin.eof()) {
							cout << "Why are you doing this ??\n\n";
							return 0;
						}
						in = tolower(in);

						switch(in) {
							case 'h':
								pPointsHealth++;
								break;
							case 'd':
								pPointsDamage++;
								break;
							case 'a':
								pPointsArmor++;
								break;
							case 'l':
								pPointsLuck++;
								break;
							default:
								cout <<"\nCan you repeat that... \n";
								skillPoints++;
						}

						skillPoints--;
					}


					cout << "\n\n";

					break;
				case 1:
					// Player dead
					cout << "\nYou are dead!\n";
					cout << "You have " << credits << " credits.\n";
					if(credits >= 5) {
						cout << "Use 5 of them to continue?[y|n]\n";
						repeats = 0;
						do {
							cin >> in;
							if(cin.eof()) {
								cout << "Why are you doing this ??\n\n";
								return 0;
							}
							in = tolower(in);
							repeats++;
							if(repeats % 5 == 0) {
								cout << "C'mon already the game won't break or anything...\n";
							}
						} while(in != 'y' && in != 'n');

						if(in == 'n') {
							cout << "\nSo get out of here coward!\n";
							playing = false;
						} else {
							cout << "\nOkay here we go!\n\n";
							credits -= 5;
							break;
						}
					}

					cout << "Do you want to start a new game?[y|n]";
					repeats = 0;
					do {
						cin >> in;
						if(cin.eof()) {
							cout << "Why are you doing this ??\n\n";
							return 0;
						}
						in = tolower(in);
						repeats++;
						if(repeats % 5 == 0) {
							cout << "C'mon already the game won't break or anything...\n";
						}
					} while(in != 'y' && in != 'n');

					playing = false;

					if(in == 'n') {
						running = false;
						cout << "\n\"Just close your eyes… and keep your mind wide open!\" Goodbye!\n\n";
					}

					break;
			}
		}
	}
	// End Game loop
}
