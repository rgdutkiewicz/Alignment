// DPAlignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>

//TESTING: modifying AddFitting branch of repository

const int n = 15;
const int m = 15;
const int a = 5; //# of characters in alphabet (plus one for blank)

bool Global = true;

using namespace std;

int max(int a, int b, int c)
{
	int max;

	if (Global)
		max = -100000000;
	else
		max = 0;

	if (a > max)
		max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;

	return max;
}

int dpAlignment(int table[n][m], string v, string w)
{
	int bestscore = 0;

	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < m; j++)
		{
			if (v[i] == w[j])
				table[i][j] = max(table[i - 1][j] - 1, table[i][j - 1] - 1, table[i - 1][j - 1] + 1);
			else
				table[i][j] = max(table[i - 1][j] - 1, table[i][j - 1] - 1, table[i - 1][j - 1] - 1);

			if (table[i][j] > bestscore)
				bestscore = table[i][j];
		}
	}

	if (Global)
		bestscore = table[n - 1][m - 1];

	return bestscore;
}

void printTable(int table[n][m])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << setw(4) << table[i][j];
		}
		cout << endl;
	}
}

void printScore(int table[a][a])
{
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < a; j++)
		{
			cout << setw(4) << table[i][j] << "  ";
		}
		cout << endl;
	}
}


int main()
{
	string v = "vCGTTATTATATGGC";
	string w = "wTTACGTATCGATTA";

	if (Global)
		cout << "Global Alignment" << endl;
	else
		cout << "Local Alignment" << endl;

	int x;

	int table[n][m] = {};
	int score[a][a] = {};

	for (int i = 0; i < n; i++)
	{
		if (Global)
			table[i][0] = i * -1;
		else
			table[i][0] = 0;
	}
	for (int j = 0; j < m; j++)
	{
		if (Global)
			table[0][j] = j * -1;
		else
			table[0][j] = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == j)
				score[i][j] = 1;
			else
				score[i][j] = -1;
		}
	}

	cout << "Best alignment has score: " << dpAlignment(table, v, w) << endl;;

	printTable(table);

	cin >> x;

	return 0;
}

