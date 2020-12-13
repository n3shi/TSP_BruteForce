#pragma once
#include <string>
#include <tuple>
#include <iostream>

using namespace std;

class Manager {
	public:
		std::tuple<int, int**, int> beginningFile(); //po inicjacji zwraca macierz i wielkosc macierzy
		std::tuple<int, int**> TSPFromFile(string nazwa);// zwraca z wybranego pliku macierz i wielkosc
		void printMatrix(string alfabet[], int readedSize, int** allVertex); // wyswietla macierz
		void menu();
		std::tuple<string*, int*, int*, string*, string, int, int>loadFromIniFile(string iniFile);
};