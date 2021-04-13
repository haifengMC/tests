#include<iostream>
using namespace std;

int s[3][3], tf = 0, gofirst = 1, row, column, over = 0;
bool isEnd = false;

void print()
{
	cout << "-------" << endl;
	for (int x = 0; x < 3; x++)
	{
		cout << "|";
		for (int y = 0; y < 3; y++)
		{
			if (s[x][y] == 0) cout << " ";
			else if (s[x][y] == 1) cout << "O";
			else if (s[x][y] == 2) cout << "X";
			cout << "|";
		}
		cout << endl << "-------" << endl;
	}
	cout << endl;
}

int check()
{
	for (int x = 0; x < 3; x++)
	{
		if (s[x][0] == 1 && s[x][1] == 1 && s[x][2] == 1)
		{
			cout << "You win!!!" << endl << endl;
			isEnd = true;
			return 0;
			break;
		}
	}
	for (int x = 0; x < 3; x++)
	{
		if (s[0][x] == 1 && s[1][x] == 1 && s[2][x] == 1)
		{
			cout << "You win!!!" << endl << endl;
			isEnd = true;
			return 0;
			break;
		}
	}
	for (int x = 0; x < 3; x++)
	{
		if (s[x][0] == 2 && s[x][1] == 2 && s[x][2] == 2)
		{
			cout << "You lose!" << endl << endl;
			isEnd = true;
			return 0;
			break;
		}
	}
	for (int x = 0; x < 3; x++)
	{
		if (s[0][x] == 2 && s[1][x] == 2 && s[2][x] == 2)
		{
			cout << "You lose!" << endl << endl;
			isEnd = true;
			return 0;
			break;
		}
	}
	if (s[0][0] == 1 && s[1][1] == 1 && s[2][2] == 1)
	{
		cout << "You win!!!" << endl << endl;
		isEnd = true;
		return 0;
	}
	else if (s[0][0] == 2 && s[1][1] == 2 && s[2][2] == 2)
	{
		cout << "You lose!" << endl << endl;
		isEnd = true;
		return 0;
	}
	else if (s[2][2] == 1 && s[1][1] == 1 && s[0][0] == 1)
	{
		cout << "You win!!!" << endl << endl;
		isEnd = true;
		return 0;
	}
	else if (s[2][2] == 2 && s[1][1] == 2 && s[0][0] == 2)
	{
		cout << "You lose!" << endl << endl;
		isEnd = true;
		return 0;
	}
	else
	{
		int count = 0;
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (s[x][y] == 1 || s[x][y] == 2) count++;
			}
		}
		if (count == 9)
		{
			cout << "Draw!" << endl << endl;
			isEnd = true;
			return 0;
		}
	}
}

void computer()
{
	int breaktf = 0;
	if (tf == 1)
	{
		if (s[1][1] == 0) s[1][1] = 2;
		else s[0][2] = 2;
	}
	else
	{
		if (s[1][1] == 1 && s[2][0] == 1 && s[0][2] == 2 && s[2][2] == 0) s[2][2] = 2;
		else if (s[0][0] == 2 && s[0][1] == 2 && s[0][2] == 0) s[0][2] = 2;
		else if (s[0][0] == 2 && s[0][2] == 2 && s[0][1] == 0) s[0][1] = 2;
		else if (s[0][0] == 2 && s[2][2] == 2 && s[1][1] == 0) s[1][1] = 2;
		else if (s[0][0] == 2 && s[2][0] == 2 && s[1][0] == 0) s[1][0] = 2;
		else if (s[0][0] == 2 && s[1][0] == 2 && s[2][0] == 0) s[2][0] = 2;
		else if (s[0][0] == 2 && s[1][1] == 2 && s[2][2] == 0) s[2][2] = 2;
		else if (s[0][2] == 2 && s[0][0] == 2 && s[0][1] == 0) s[0][1] = 2;
		else if (s[0][2] == 2 && s[0][1] == 2 && s[0][0] == 0) s[0][0] = 2;
		else if (s[0][2] == 2 && s[1][2] == 2 && s[2][2] == 0) s[2][2] = 2;
		else if (s[0][2] == 2 && s[2][2] == 2 && s[1][2] == 0) s[1][2] = 2;
		else if (s[0][2] == 2 && s[2][0] == 2 && s[1][1] == 0) s[1][1] = 2;
		else if (s[0][2] == 2 && s[1][1] == 2 && s[2][0] == 0) s[2][0] = 2;
		else if (s[2][0] == 2 && s[1][0] == 2 && s[0][0] == 0) s[0][0] = 2;
		else if (s[2][0] == 2 && s[0][0] == 2 && s[1][0] == 0) s[1][0] = 2;
		else if (s[2][0] == 2 && s[2][1] == 2 && s[2][2] == 0) s[2][2] = 2;
		else if (s[2][0] == 2 && s[2][2] == 2 && s[2][1] == 0) s[2][1] = 2;
		else if (s[2][0] == 2 && s[1][2] == 2 && s[1][1] == 0) s[1][1] = 2;
		else if (s[2][0] == 2 && s[1][1] == 2 && s[1][2] == 0) s[1][2] = 2;
		else if (s[2][2] == 2 && s[1][2] == 2 && s[0][2] == 0) s[0][2] = 2;
		else if (s[2][2] == 2 && s[0][2] == 2 && s[1][2] == 0) s[1][2] = 2;
		else if (s[2][2] == 2 && s[2][0] == 2 && s[2][1] == 0) s[2][1] = 2;
		else if (s[2][2] == 2 && s[2][1] == 2 && s[2][0] == 0) s[2][0] = 2;
		else if (s[2][2] == 2 && s[0][0] == 2 && s[1][1] == 0) s[1][1] = 2;
		else if (s[2][2] == 2 && s[1][1] == 2 && s[0][0] == 0) s[0][0] = 2;
		else if (s[0][1] == 2 && s[2][1] == 2 && s[1][1] == 0) s[1][1] = 2;
		else if (s[1][0] == 2 && s[1][2] == 2 && s[1][1] == 0) s[1][1] = 2;
		else if (s[1][2] == 2 && s[1][1] == 2 && s[1][0] == 0) s[1][0] = 2;
		else if (s[2][1] == 2 && s[1][1] == 2 && s[0][1] == 0) s[0][1] = 2;
		else if (s[1][0] == 2 && s[1][1] == 2 && s[1][2] == 0) s[1][2] = 2;
		else if (s[0][1] == 2 && s[1][1] == 2 && s[2][1] == 0) s[2][1] = 2;
		else if (s[0][0] == 1 && s[0][1] == 1 && s[0][2] == 0) s[0][2] = 2;
		else if (s[0][0] == 1 && s[0][2] == 1 && s[0][1] == 0) s[0][1] = 2;
		else if (s[0][0] == 1 && s[2][2] == 1 && s[1][1] == 0) s[1][1] = 2;
		else if (s[0][0] == 1 && s[2][0] == 1 && s[1][0] == 0) s[1][0] = 2;
		else if (s[0][0] == 1 && s[1][0] == 1 && s[2][0] == 0) s[2][0] = 2;
		else if (s[0][0] == 1 && s[1][1] == 1 && s[2][2] == 0) s[2][2] = 2;
		else if (s[0][2] == 1 && s[0][0] == 1 && s[0][1] == 0) s[0][1] = 2;
		else if (s[0][2] == 1 && s[0][1] == 1 && s[0][0] == 0) s[0][0] = 2;
		else if (s[0][2] == 1 && s[1][2] == 1 && s[2][2] == 0) s[2][2] = 2;
		else if (s[0][2] == 1 && s[2][2] == 1 && s[1][2] == 0) s[1][2] = 2;
		else if (s[0][2] == 1 && s[2][0] == 1 && s[1][1] == 0) s[1][1] = 2;
		else if (s[0][2] == 1 && s[1][1] == 1 && s[2][0] == 0) s[2][0] = 2;
		else if (s[2][0] == 1 && s[1][0] == 1 && s[0][0] == 0) s[0][0] = 2;
		else if (s[2][0] == 1 && s[0][0] == 1 && s[1][0] == 0) s[1][0] = 2;
		else if (s[2][0] == 1 && s[2][1] == 1 && s[2][2] == 0) s[2][2] = 2;
		else if (s[2][0] == 1 && s[2][2] == 1 && s[2][1] == 0) s[2][1] = 2;
		else if (s[2][0] == 1 && s[1][2] == 1 && s[1][1] == 0) s[1][1] = 2;
		else if (s[2][0] == 1 && s[1][1] == 1 && s[1][2] == 0) s[1][2] = 2;
		else if (s[2][2] == 1 && s[1][2] == 1 && s[0][2] == 0) s[0][2] = 2;
		else if (s[2][2] == 1 && s[0][2] == 1 && s[1][2] == 0) s[1][2] = 2;
		else if (s[2][2] == 1 && s[2][0] == 1 && s[2][1] == 0) s[2][1] = 2;
		else if (s[2][2] == 1 && s[2][1] == 1 && s[2][0] == 0) s[2][0] = 2;
		else if (s[2][2] == 1 && s[0][0] == 1 && s[1][1] == 0) s[1][1] = 2;
		else if (s[2][2] == 1 && s[1][1] == 1 && s[0][0] == 0) s[0][0] = 2;
		else if (s[0][1] == 1 && s[2][1] == 1 && s[1][1] == 0) s[1][1] = 2;
		else if (s[1][0] == 1 && s[1][2] == 1 && s[1][1] == 0) s[1][1] = 2;
		else if (s[1][2] == 1 && s[1][1] == 1 && s[1][0] == 0) s[1][0] = 2;
		else if (s[2][1] == 1 && s[1][1] == 1 && s[0][1] == 0) s[0][1] = 2;
		else if (s[1][0] == 1 && s[1][1] == 1 && s[1][2] == 0) s[1][2] = 2;
		else if (s[0][1] == 1 && s[1][1] == 1 && s[2][1] == 0) s[2][1] = 2;
		else if (s[0][0] == 1 && s[2][2] == 1 && s[1][1] == 2 && s[2][1] == 0) s[2][1] = 2;
		else if (s[0][2] == 1 && s[2][0] == 1 && s[1][1] == 2 && s[2][1] == 0) s[2][1] = 2;
		else if (s[0][0] == 1 && s[1][1] == 2 && s[0][2] == 0) s[0][2] = 2;
		else if (s[0][2] == 1 && s[1][1] == 2 && s[0][0] == 0) s[0][0] = 2;
		else if (s[2][0] == 1 && s[1][1] == 2 && s[2][2] == 0) s[2][2] = 2;
		else if (s[2][2] == 1 && s[1][1] == 2 && s[2][0] == 0) s[2][0] = 2;
		else
		{
			//cout << "here!" << endl;
			for (int x = 0; x < 3; x++)
			{
				for (int y = 0; y < 3; y++)
				{
					if (s[x][y] == 0)
					{
						s[x][y] = 2;
						breaktf = 1;
						break;
					}
				}
				if (breaktf == 1) break;
			}
		}
	}
}

int main()
{
	cout << "This is O and X" << endl;
	cout << "Made by Skyzhou" << endl;
	cout << "If you want to start, please press 0, else press 1: ";
	cin >> over;
	while (over == 0)
	{
		isEnd = false;
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++) s[x][y] = 0;
		cout << "You go first(1) or computer go first(0): ";
		cin >> gofirst;
		if (gofirst == 1) tf = 0;
		else if (gofirst == 0) tf = 1;
		print();
		while (isEnd == false)
		{
			bool inputtf = true;
			if (tf % 2 == 0)
			{
				while (inputtf)
				{
					cout << "Which place do you want to choose?" << endl;
					cout << "row: ";
					cin >> row;
					cout << "column: ";
					cin >> column;
					row--;
					column--;
					if (s[row][column] != 0)
					{
						cout << "This place can't choose, please reinput." << endl;
					}
					else inputtf = false;
				}
				s[row][column] = 1;
			}
			else computer();
			print();
			check();
			tf++;
		}
		cout << "If you want to play again, please press 0, else press 1: ";
		cin >> over;
	}
	return 0;
}