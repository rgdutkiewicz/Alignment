// DPAlignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>

//string length constants
const int n = 16;
const int m = 7;
const int a = 5; //# of characters in alphabet (plus one for blank)

enum alignment
{
	global = 1,
	local = 2,
	fitting = 3
};

struct best {
	int score;
	int xpos;
	int ypos;
};

using namespace std;

int max(int a, int b, int c, alignment k)
{
	int max;

	switch (k)
	{
	case global:
	case fitting:
		max = a;
		break;
	case local:
		max = 0;
		break;
	}

	if (a > max)
		max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;

	return max;
}

best dpAlignment(int table[n][m], string v, string w, alignment a)
{
	best bestscore;
	bestscore.score = 0;
	bestscore.xpos = 0;
	bestscore.ypos = 0;

	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < m; j++)
		{
			if (v[i] == w[j])
				table[i][j] = max(table[i - 1][j] - 1, table[i][j - 1] - 1, table[i - 1][j - 1] + 1, a);
			else
				table[i][j] = max(table[i - 1][j] - 1, table[i][j - 1] - 1, table[i - 1][j - 1] - 1, a);

			if (table[i][j] > bestscore.score)
			{
				bestscore.score = table[i][j];
				bestscore.xpos = i;
				bestscore.ypos = j;
			}
		}
	}

	if (a == global)
	{
		bestscore.score = table[n - 1][m - 1];
		bestscore.xpos = n;
		bestscore.ypos = m;
	}

	return bestscore;
}

void initTable(int table[n][m], alignment align)
{
	//initialize top row
	for (int i = 0; i < n; i++)
	{
		switch (align)
		{
		case global:
			table[i][0] = i * -1;
			break;
		case local:
		case fitting:
			table[i][0] = 0;
			break;
		}
	}
	//intialize top row
	for (int j = 0; j < m; j++)
	{
		switch (align)
		{
		case global:
		case fitting:
			table[0][j] = j * -1;
			break;
		case local:
			table[0][j] = 0;
			break;
		}
	}
}

void Fitting(int table[n][m], string v, string w)
{
	alignment align = fitting;

	initTable(table, align);

	dpAlignment(table, v, w, align);

	best bestglobal;
	bestglobal.score = -n;
	bestglobal.xpos = 0;
	bestglobal.ypos = m;

	for (int i = 0; i < n; i++) //search the last column
	{
		if (table[i][m-1] > bestglobal.score)
		{
			bestglobal.score = table[i][m-1];
			bestglobal.xpos = i;
		}
	}

	cout << "Best global score in last column = " << bestglobal.score << " at " << bestglobal.xpos << endl;

	//align = local;

	//initTable(table, align);

	//dpAlignment(table, v, w, align);

	//cout << "Best fit score is: " << table[bestglobal.xpos][m - 1] << endl;
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
	alignment align; //enum to differentiate alignment types
	bool typeSelect = false;
	char s;
	cout << "What sort of alignment? global(g), local(l), or fitting(f)." << endl;

	string v = "vGTAGGCTTAAGGTTA";
	string w = "wTAGATA";
	
	while (!typeSelect)
	{
		cin >> s;
		
		switch (s)
		{
		case 'g':
			align = global;
			typeSelect = true;
			break;
		case 'l':
			align = local;
			typeSelect = true;
			break;
		case 'f':
			align = fitting;
			typeSelect = true;
			break;
		default:
			cout << "That is not a recognized alignment type." << endl;
			break;
		}
	}


	switch (align)
	{
	case global:
		cout << "Global Alignment" << endl;
		break;
	case local:
		cout << "Local Alignment" << endl;
		break;
	case fitting:
		cout << "Fitting Alignment" << endl;
		break;
	}

	int table[n][m] = {};
	int score[a][a] = {};

	initTable(table, align);

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


	switch (align)
	{
	case global:
	case local:
		best bestscore = dpAlignment(table, v, w, align);

		cout << "Best alignment has score: " << bestscore.score << " in location: " << bestscore.xpos<< ", " << bestscore.ypos << endl;
		break;
	case fitting:
		Fitting(table, v, w);
		break;
	}

	printTable(table);

	system("pause");

	return 0;
}

