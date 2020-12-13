// BruteForce.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>

#include "Czas.h"
#include "Manager.h"
#include <conio.h>
#include "INIReader.h"


using std::cout;
using std::cin;
using namespace std;
//using namespace chrono;

//etap 0,1,2,3
int readedSize; // rozmiar tabeli (do odczytu)
int* readedAllVisitedVertex; //tablica odwiedzonych wierzchołków (do odczytu)
int** allVertex; // macierz zawierająca wszystkie odległości pomiędzy wierzchołkami
int* allVisitedVertex; //tablica odwiedzonych wierzchołków
int choice; // wybor w konsoli
int optimumSize; // najmniejsza odleglosc (pobierana z pliku)
int lenght = 0; //aktualna dlugosc ciagu (zmienia sie po iteracji algorytmu)

//Zachlanny



//etap 1 
int* vectorsToChoose; //tablica z wektorami które wybieram rekurencyjnie
int permutation = 0;
//string matrixFile = "tsp_6_1.txt";
//string csvfileName = "test.csv";
int percentOfMistake;

//BruteForce
int smallerLenght; //aktualnie najmniejsza znaleziona dlugosc ciagu
int* shortestPath; //najkrotsza sciezka

int licz = 0;


void autoInicial()//wszystko co trzeba zrobić do poprawnego dzialania BF
{
	allVisitedVertex = new int[readedSize + 1];
	vectorsToChoose = new int[readedSize + 1];
	lenght = 0;
	smallerLenght = 10000;

	shortestPath = new int[readedSize + 1];

	int x = rand() % readedSize;
	allVisitedVertex[0] = x;
}


int licznik = 0;
void bruteForceOnArray(int rozmiar, int permutacja) //algorytm bruteForce
{
	for (int i = 0; i < rozmiar; i++)
	{
		//pseudokod:
//1.Stworz tablice wyboru
//2.Wybierz odpowiedni wierzcholek
//3.dodaj go do wybranych na odpowiednim miejscu
//4.Powtórz 1-3 

		//Stworzenie tablicy wyboru
		int x = 0;
		for (int i = 0; i < readedSize; i++)
		{
			bool isInTable = false;
			for (int j = 0; j < permutacja; j++)
			{
				if (i == allVisitedVertex[j])
				{
					isInTable = true;
					break;
				}
				else isInTable = false;
			}
			if (isInTable == false)
			{
				vectorsToChoose[x] = i;
				x++;
			}
		}

		allVisitedVertex[permutacja] = vectorsToChoose[i];


		//Oblicz dlugosc ciągu
#pragma region ObliczDlugosc
		if (rozmiar == 1)
		{
			licznik++;
			allVisitedVertex[readedSize] = allVisitedVertex[0];

			//Oblicz dlugosc ciągu
			lenght = 0;
			for (int j = 1; j < readedSize + 1; j++)
			{
				lenght = lenght + allVertex[allVisitedVertex[j]][allVisitedVertex[j - 1]];
			}

			if (lenght < smallerLenght)
			{
				for (int j = 0; j < readedSize + 1; j++)
				{
					shortestPath[j] = allVisitedVertex[j];
				}

				//cout << endl << "Znalazlem krotsza droge: ";
				/*for (int a = 0; a < sizee + 1; a++)
				{
					cout << allVisitedVertex[a] << " ";
				}*/
				smallerLenght = lenght;
				//cout << "    Aktualna najkrotsza dlugosc ciagu: " << smallerLenght;
			}
		}
#pragma endregion

		if (rozmiar > 1)
		{
			bruteForceOnArray(rozmiar - 1, permutacja + 1);
		}
	}
}



void afterBruteForce(int numer,string czas, int optimumSize, string optimum)
{
	//cout << endl << endl << "Podsumowanie:" << endl;
	//cout << endl << "Ile razy doszedl do liscia: " << licznik;
	cout << "Nr badania: " << numer+1 << " Najkrotsza znaleziona sciezka:";
	for (int i = 0; i < readedSize + 1; i++)
	{
		cout << shortestPath[i] << " ";
	}
	cout << "   Dlugosc: " << smallerLenght;
	cout << "   Optimum: " << optimumSize;
	cout << "   Sciezka optimum: " << optimum;
	percentOfMistake = (smallerLenght - optimumSize) / optimumSize * 100;
	cout  << "    % bledu: " << percentOfMistake << "%";
	cout << "  Czas: " << czas << endl;

}

string createPath() {
	string path="";

	for (int i = 0; i < readedSize + 1; i++)
	{
		
		string test = to_string(shortestPath[i]);
		path.append(test);
		if(i != readedSize) path.append("-");
	}
	return path;
}


//Funkcje do zapisu danych
void addCsvDescription(string csvFileName)
{
	fstream fout;
	fout.open(csvFileName, ios::out | ios::app);
	fout << "File name" << ", " << "Time(s)" << ", " << "Best path" << ", " << "Path lenght" << ", " << "Optimum" << ", " << "Best path" << ", " << "% of mistake\n";
	fout.close();
}

void autoSaveBruteForce(string time, string csvFileName, string matrixFile, string optimumPath2, int optimumSize)
{
	fstream fout;
	fout.open(csvFileName, ios::out | ios::app);

	if (optimumSize != 0) percentOfMistake = (smallerLenght - optimumSize) / optimumSize * 100;
	else percentOfMistake = -1;

	fout << matrixFile << ", " << time << ", " << createPath() << ", " << smallerLenght << ", " << optimumSize << ", " << optimumPath2<< ", " << percentOfMistake << "\n";
	fout.close();
}


int main(int argc, char *argv[])
{
	string iniFile;
	cout << "Podaj nazwe pliku inicjalizujacego lub nacisnij wpisz 1 aby wczytac plik test.ini\n";
	cin >> iniFile;

	if (iniFile == "1") iniFile = "test.ini";

	string* matrixFile; //tablica plikow
	int* optimumSize; //tablica optimow
	int* iloscPowtorzen; //tablica powtorzen
	string* optimumPath; //tablica sciezek
	string csvFile; // plik do zapisu
	int iniFileSize, breakTime; //zmienne pomocnicze

	Manager m; //utworzenie obiektu zarzadzajacy pozostalymi plikami
	
	// funkcja loadFromIniFile zwraca wszystkie wartosci pobrane z pliku inicjalizujacego
	tie(matrixFile, optimumSize, iloscPowtorzen, optimumPath, csvFile, iniFileSize, breakTime) = m.loadFromIniFile(iniFile); 

	if (breakTime == 0) return 0; //przerwanie programmu w przypadku bledu

	for (int i = 0; i < iniFileSize; i++) //petla wykonuje sie tyle razy ile wczytano plikow
	{
		if (optimumSize[i] == 0) break; //jesli nie znalazla optimum to sie przerwie
		
		cout << "\n\nRozpoczynam prace nad plikiem: " << matrixFile[i]
			<< ":  optimum: " << optimumSize[i]
			<< "   ilosc powtorzen: " << iloscPowtorzen[i] << endl << endl;

		Czas c;
		addCsvDescription(csvFile); // na poczatku dodanie do pliku csv naglowka
		for (int j = 0; j < iloscPowtorzen[i]; j++)
		{
			tie(readedSize, allVertex) = m.komiwojazerZPliku(matrixFile[i]); //wczytanie macierzy z pliku
			autoInicial(); //wybranie poczatkowego wierzcholka
			c.czasStart(); //rozpoczecie liczenia czasu algorytmu/metoy
			bruteForceOnArray(readedSize - 1, permutation + 1); // metoda brute force
			c.czasStop(); //zakonczenie liczenia czasu algorytmu/metody
			string time = to_string(c.czasWykonania() * 0.001); //obliczenie czasu wykonywania
			autoSaveBruteForce(time, csvFile, matrixFile[i], optimumPath[i], optimumSize[i]); //zapis wyniku do pliku
			afterBruteForce(j, time, optimumSize[i], optimumPath[i]); //wyświetla na konsoli wyniki cząstkowe
		}
	}

	return 0;
}
