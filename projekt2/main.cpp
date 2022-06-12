#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
//#include <windows.h>
#include <chrono>
#include <thread>
#include <fstream>

#include "zbiory.h"
//#include "mst.h"
//#include "algorithms.cpp"
#include "algorithms.h"

using namespace std;

int edges, vertex;
string filename;
bool type;

/*
MSTree drzewoPrim; // drzewoPrim MST
Queue kolejka; // kolejka priorytetowa
MSTree graf; // caly graf z pliku
DSStruct zbior;
*/
Algorithms algorytmy;
//DSNode *Z;


void MSTReadFromFile(string filename /*bool type*/)
{
	fstream file;
	file.open(filename);

	if (file.good() == true)
	{
		Edge e;
		TNode* p;

		file >> edges >> vertex;

		// ***************************
		algorytmy.kolejka.addEdges(edges);           // Kolejka priorytetowa oparta na kopcu
		algorytmy.graf.addNode(vertex);               // Graf

		algorytmy.graf.zeros_matrix(vertex);

		for (int i = 0; i < edges; i++)
		{

			file >> e.v1 >> e.v2 >> e.weight; // Odczytujemy kolejne krawędzie grafu
			algorytmy.graf.addEdge(e);
            algorytmy.kolejka.push(e);
			algorytmy.graf.addToMatrix(e.v1, e.v2);
		}

		file.close();
	}
	else cout << "Error opening file!!!" << endl;
}

void mst_menu()
{
	int density, nodes;
	int opt = 0;
	type = false;

	do
	{
		cout << "===== MENU =====" << endl;
		cout << "1. Wczytaj z pliku" << endl;
		cout << "2. Wygeneruj graf losowo" << endl;
		cout << "3. Wyswietl listowo i macierzowo" << endl;
		cout << "4. Algorytm Prima " << endl;
		cout << "5. Algorytm Kruskala " << endl;
		cout << "6. Pomiary " << endl;
		cout << "0. Cofnij do menu " << endl;

		cin >> opt;
		switch (opt)
		{
		case 1:
			// wczytywanie grafu z pliku
			cout << "Wprowadz nazwe zbioru: " << endl;
			cin >> filename;
			MSTReadFromFile(filename);
			break;

		case 2: // generowanie losowego grafu
			cout << "Wprowadz gestosc grafu w procentach:" << endl;
			cin >> density;
			cout << "Wprowadz ilosc wierzcholkow grafu:" << endl;
			cin >> vertex;
			algorytmy.Random_graph_Generator(density, vertex);
			break;

		case 3: // wyswietlanie listowo i macierzowo
			cout << "Wyswietlenie listowo:" << endl;
			algorytmy.graf.print_list();
			cout << endl << "Wyswietlanie macierzowo: " << endl;
			algorytmy.graf.print_matrixMST(vertex);
			break;

		case 4: //algorytm Prima 
			cout << "Algorytm Prima:" << endl;
			algorytmy.Prim(vertex);
			break;

		case 5: //algorytm Kruskala
			cout << "Algorytm Kruskala:" << endl;
			algorytmy.Kruskal(vertex);
			break;

		case 6: //pomiary
			float avg1 = 0, avg2 = 0, avg3 = 0;
			cout << "Pomiary:" << endl;
			int d = 20;
			int nn = 10;

			fstream Timefile;
			string fileTimeName = "Time.csv";
			Timefile.open(fileTimeName, ios::out | ios::app);
			Timefile << endl << "Pomiary Prim" << endl;

			for (int i = 0; i < 50; i++)
			{
				algorytmy.Random_graph_Generator(d, nn);

				auto t1 = std::chrono::high_resolution_clock::now(); // czas start
				algorytmy.Prim(vertex);
				
				auto t2 = std::chrono::high_resolution_clock::now();
				avg1 += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
			}
			avg1 = avg1 / 50;
			cout << d << " " << nn << endl << "Sredni czas Prim [ns]: " << avg1 << endl;
			Timefile << endl << "Gestosc: "<< d << " Wierzcholki: " << nn << endl;
			Timefile << "Czas: "<<avg1<<endl;

			d = 60;
			avg2 = 0;
			for (int i = 0; i < 50; i++)
			{
				algorytmy.Random_graph_Generator(d, nn);
				
				auto t1 = std::chrono::high_resolution_clock::now(); // czas start
				algorytmy.Prim(vertex);
				
				auto t2 = std::chrono::high_resolution_clock::now();
				avg1 += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
			}
			avg2 = avg2 / 50;
			cout << d << " " << nn << endl << "Sredni czas Prim [us]: " << avg2 << endl;
			Timefile <<"Gestosc: "<< d << " Wierzcholki: " << nn << endl;
			Timefile << "Czas: "<< avg2 << endl;

			d = 99;
			avg3 = 0;
			for (int i = 0; i < 50; i++)
			{
				algorytmy.Random_graph_Generator(d, nn);
				//start = read_QPC(); // poczatek pomiaru
				auto t1 = std::chrono::high_resolution_clock::now(); // czas start
				algorytmy.Prim(vertex);
				//elapsed = read_QPC() - start; // koniec pomiaru
				auto t2 = std::chrono::high_resolution_clock::now();
				avg1 += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
			}
			avg3 = avg3 / 50;
			cout << d << " " << nn << endl << "Sredni czas Prim [us]: " << avg3 << endl;
			Timefile <<"Gestosc: "<< d << " Wierzcholki: " << nn << endl;
			Timefile << "Czas: "<< avg1 << endl;

			break;
		}

	} while (opt != 0);
}

void shortest_way_menu()
{
	int opt = 0;

	cout << "===== MENU =====" << endl;
	cout << "1. Wczytaj z pliku" << endl;
	cout << "2. Wygeneruj graf losowo" << endl;
	cout << "3. Wyswietl listowo i macierzowo" << endl;
	cout << "4. Algorytm Dijkstry " << endl;
	cout << "0. Cofnij do menu " << endl;

	do
	{
		switch (opt)
		{
		case 1:
			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			break;

		}

	} while (opt != 0);
}

void menu()
{
	int option = 0;

	do
	{
		cout << "===== MENU =====" << endl;
		cout << "1. Wyznaczanie minimalnego drzewa rozpinajacego (MST)" << endl;
		cout << "2. Wyznaczanie najkrotszej sciezki w grafie" << endl;
		cout << "0. Wyjscie  " << endl;

		cin >> option;

		switch (option)
		{
		case 1:
			mst_menu();
			break;

		case 2:
			shortest_way_menu();
			break;
		}

	} while (option != 0);
}


int main()
{
    menu();
	return 0;
}


