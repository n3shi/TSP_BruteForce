#include "Manager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <tuple>
#include <string>

using namespace std;

std::tuple<int, int**> Manager::TSPFromFile(string fileName)
{
	string line; //pobierana linia z pliku
	string fileName = fileName; // nazwa pliku
	string newFileName; //nazwa pliku
	fstream fileMatrix; //plik z macierz¹ 
	int readedSize;
	int** allVertex = new int* [1]; //przypisanie na sile, bo visual

	//utowrzenie nowej tablicy dynamicznej
	fileMatrix.open(fileName.c_str(), ios::in);
	int row = 0; //rz¹d macierzy
	int column = 0; // kolumna macierzy

	if (fileMatrix.good())
	{
		while (!fileMatrix.eof())
		{
			column = 0;

			if (row == 0)
			{
				getline(fileMatrix, line); // pobierz z pliku linie rozmiaru
				readedSize = atoi(line.c_str()); // przypisz rozmiar

				allVertex = new int* [readedSize];
				for (int i = 0; i < readedSize; i++)
				{
					allVertex[i] = new int[readedSize];
				}
			}
			getline(fileMatrix, line); // pobierz z pliku linie z danymi

			stringstream sin(line); //wybierz slowo z linii
			string word;
			while (sin >> word && column < readedSize) //pobieramy tyle slow jaki wpisalismy rozmiar
			{
				int liczba;
				liczba = atoi(word.c_str()); // zamien slowo na liczbe
				allVertex[row][column] = liczba;
				column++;
			}

			if ((int)row < readedSize)
				row = row + 1;
			if (row == readedSize)
			{
				row = row + 1; // gdyby byly jeszcze jakies inne linie to zeby nie nadpisalo optimum zwiekszam row o 1
			}
		}
		fileMatrix.close(); // zamykanie pliku
		//cout << endl << endl << endl << "Plik zostal zaladowany poprawnie" << endl;
	}
	else cout << "Blad ladowania pliku. Sprobuj ponownie";

	return make_tuple(readedSize, allVertex);
}


//testowa funkcja sluzaca do wyswietlenia macierzy
void Manager::printMatrix(string alfabet[], int readedSize, int** allVertex)
{
	system("cls");

	cout << endl << "   Wczytana tablica:" << endl << endl;
	for (int i = 0; i < readedSize; i++)
	{
		if (i == 0)
		{
			cout << endl;
			cout << "            ";
			for (int j = 0; j < readedSize; j++)
			{
				cout << alfabet[j] << "    "; // 4x spacja
			}
			cout << endl;
			cout << "        ";
			for (int j = 0; j < readedSize; j++)
			{
				cout << "_____"; // 5x podloga
			}
			cout << endl;
		}
		for (int j = 0; j < readedSize; j++)
		{
			if (j == 0)
				cout << "   " << alfabet[i] << "   |";


			if (allVertex[i][j] < 10)
			{
				cout << "   "; // 4 spracje
				if (allVertex[i][j] >= 0) cout << " "; // + 1 ew jakby nie byla ujemna
			}
			else if (allVertex[i][j] < 100)cout << "   "; // 4 spacje
			else if (allVertex[i][j] < 1000) cout << "  ";// 3 spacje
			else if (allVertex[i][j] < 10000) cout << " "; // 4 spacje
			else   cout << "";// 5 spacji
			cout << allVertex[i][j];
		}
		cout << endl;
	}
	cout << endl << endl;
	int a;
	cin >> a;
}


//Wykorzystanie tuple pozwala zwrocic wiecej niz jedna zmienna
std::tuple<int, int**, int> Manager::beginningFile() //Za³aduj jakiœ plik aby przyspieszyæ sprawdzanie czy dzia³a
{
	string line; //pobierana linia z pliku
	string fileName = "6.txt"; // nazwa pliku
	fstream fileMatrix; //plik z macierz¹ 

	fileMatrix.open(fileName.c_str(), ios::in);
	int row = 0; //rz¹d macierzy
	int column = 0; // kolumna macierzy

	int readedSize;
	int** allVertex = new int*[1]; //przypisanie na sile, bo visual
	int optimumSize;

	if (fileMatrix.good())
	{
		while (!fileMatrix.eof())
		{
			column = 0;

			if (row == 0)
			{
				getline(fileMatrix, line); // pobierz z pliku linie rozmiaru
				readedSize = atoi(line.c_str()); // przypisz rozmiar

				allVertex = new int* [readedSize];
				for (int i = 0; i < readedSize; i++)
				{
					allVertex[i] = new int[readedSize];

				}
			}
			getline(fileMatrix, line); // pobierz z pliku linie z danymi

			stringstream sin(line); //wybierz slowo z linii
			string word;
			while (sin >> word && column < readedSize) //pobieramy tyle slow jaki wpisalismy rozmiar
			{
				int liczba;
				liczba = atoi(word.c_str()); // zamien slowo na liczbe

				allVertex[row][column] = liczba;
				column++;
			}
			if ((int)row < readedSize)
				row = row + 1;
			
			if (row == readedSize)
			{
				row = row + 1; // gdyby byly jeszcze jakies inne linie to zeby nie nadpisalo optimum zwiekszam row o 1
				getline(fileMatrix, line); //pobierz linie z optymalnym rozwiazaniem
				optimumSize = atoi(line.c_str());
			}
		}
		fileMatrix.close(); // zamykanie pliku
		return make_tuple(readedSize, allVertex, optimumSize);
	}
}

void Manager::menu() {
	system("cls"); //TODO zamiast system cls bedzie funckja czyszczenia z biblioteki ncurses
	cout << "       Projektowanie efektywnych algorytmow\n";
	cout << "         Autor: Wojciech Ziebicki \n\n\n";
	cout << "	M E N U    G L O W N E\n\n";
	cout << "   1. Wczytywanie instancji\n";
	cout << "   2. Wyswietlenie wczytanej macierzy\n";
	cout << "   3. Brute force \n";
}

std::tuple<string*, int*, int*, string*, string, int, int>Manager::loadFromIniFile(string iniFile) {

	string line; //pobierana linia z pliku

	fstream file; //plik z macierz¹ 

	file.open(iniFile.c_str(), ios::in);
	int row = 0; //rz¹d macierzy
	int column = 0; // kolumna macierzy
	int iniFileSize = 30;

	string* matrixFile = new string [iniFileSize]; //macierz nazw plików
	int* optimumSize = new int[iniFileSize]; //macierz optymalnych odleglosci
	int* repeatVal = new int[iniFileSize]; //macierz powtorzen 
	string* optimumPath = new string[iniFileSize]; 

	for (int i = 0; i < iniFileSize; i++) {
		optimumSize[i] = 0;
	}


	if (file.good())
	{
		while (!file.eof())
		{
			column = 0;
			getline(file, line); // pobierz z pliku linie z danymi

			stringstream sin(line); //wybierz slowo z linii
			string word;
			while (sin >> word) //pobieramy tyle slow jaki wpisalismy rozmiar
			{
				int liczba;
				liczba = atoi(word.c_str()); // zamien slowo na liczbe

				if (column == 0) matrixFile[row] = word.c_str();
				else if (column == 1) repeatVal[row] = atoi(word.c_str());
				else if (column == 2) optimumSize[row] = atoi(word.c_str());
				else if (column >= 3) optimumPath[row].append(word.c_str());
				
				column++;
			}
			row = row + 1;
		}
		file.close(); // zamykanie pliku
		string csvFile = matrixFile[row-1];

		return make_tuple(matrixFile, optimumSize, repeatVal, optimumPath, csvFile, iniFileSize, 1);
	}
	else {
		cout << "blad wczytania pliku";
		string* test;
		string test3;
		int* test2;
		return make_tuple(test, test2, test2, test,test3, iniFileSize, 0);
	}


}
