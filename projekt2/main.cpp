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

int edges, vertex, startVertex;
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

void DirectReadFromFile(string filename /*bool type*/)
{
    /*fstream file;
    file.open(filename);

    if (file.good() == true)
    {
        Edge e;
        TNode* p;
        file >> edges >> vertex >> startVertex;

        // ***************************
        algorytmy.kolejka.addEdges(edges);           // Kolejka priorytetowa oparta na kopcu
        algorytmy.graf.addNode(vertex);               // Graf

        algorytmy.graf.zeros_matrix(vertex);

        for (int i = 0; i < edges; i++)
        {

            file >> e.v1 >> e.v2 >> e.weight; // Odczytujemy kolejne krawędzie grafu

            algorytmy.graf.addDirectEdge(e);
            algorytmy.kolejka.push(e);
            algorytmy.graf.addToMatrix(e.v1, e.v2);
        }

        file.close();
    }
    else cout << "Error opening file!!!" << endl;*/

    fstream file;
    file.open(filename);

    if (file.good() == true)
    {
        Edge e;
        TNode *p = new TNode;
        TNode *u = new TNode;
        //*****************
        //algorytmy.kolejkaP.addNodes(vertex);
        //*****************
        file >> edges >> vertex >> startVertex;

        // ***************************
        algorytmy.kolejka.addEdges(edges);           // Kolejka priorytetowa oparta na kopcu
        algorytmy.grafDirect.addNode(vertex);               // Graf

        algorytmy.grafDirect.zeros_matrix(vertex);

        for (int i = 0; i < edges; i++)
        {
            file >> e.v1 >> e.v2 >> e.weight; // Odczytujemy kolejne krawędzie grafu

            algorytmy.grafDirect.addDirectEdge(e, e.v1);
            algorytmy.kolejka.push(e);
            algorytmy.grafDirect.addToMatrix(e.v1, e.v2);
            //*********************************
            p->v=e.v1;
            if(p->v == u->v)
            {
                algorytmy.grafDirect.addToNodeList(p, p->v); // do sprawdzenia, co sie przesyla do funkcji
                u->v = e.v1;
            }
            //*********************************
            //p->v=e.v1;
            //p->weight = e.weight;
            //p->next = u;
            //u->v=e.v2;
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
			int nn = 1000;

			fstream Timefile;
			string fileTimeName = "Time.csv";
			Timefile.open(fileTimeName, ios::out | ios::app);
			Timefile << endl << "Pomiary Prim" << endl;

			for (int i = 0; i < 50; i++)
			{
				algorytmy.Random_graph_Generator(d, nn);

				auto t1 = std::chrono::high_resolution_clock::now(); // czas start
				algorytmy.Prim(nn);
				
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
				algorytmy.Prim(nn);
				
				auto t2 = std::chrono::high_resolution_clock::now();
				avg2 += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
			}
			avg2 = avg2 / 50;
			cout << d << " " << nn << endl << "Sredni czas Prim [ns]: " << avg2 << endl;
			Timefile <<"Gestosc: "<< d << " Wierzcholki: " << nn << endl;
			Timefile << "Czas: "<< avg2 << endl;

			d = 99;
			avg3 = 0;
			for (int i = 0; i < 50; i++)
			{
				algorytmy.Random_graph_Generator(d, nn);
				//start = read_QPC(); // poczatek pomiaru
				auto t1 = std::chrono::high_resolution_clock::now(); // czas start
				algorytmy.Prim(nn);
				//elapsed = read_QPC() - start; // koniec pomiaru
				auto t2 = std::chrono::high_resolution_clock::now();
				avg3 += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
			}
			avg3 = avg3 / 50;
			cout << d << " " << nn << endl << "Sredni czas Prim [ns]: " << avg3 << endl;
			Timefile <<"Gestosc: "<< d << " Wierzcholki: " << nn << endl;
			Timefile << "Czas: "<< avg1 << endl;

			break;
		}

	} while (opt != 0);
}

void shortest_way_menu()
{
	int opt = 0;
    int density;
    int startV=rand()%10;

	do
	{
        cout << "===== MENU =====" << endl;
        cout << "1. Wczytaj z pliku" << endl;
        cout << "2. Wygeneruj graf losowo" << endl;
        cout << "3. Wyswietl listowo i macierzowo" << endl;
        cout << "4. Algorytm Dijkstry " << endl;
        cout << "5. Pomiary " << endl;
        cout << "0. Cofnij do menu " << endl;
        cin >> opt;
		switch (opt)
		{
        case 1: // wczytywanie z pliku
            cout << "Wprowadz nazwe zbioru: " << endl;
            cin >> filename;
            DirectReadFromFile(filename);
            break;

        case 2: // losowy graf
            cout << "Wprowadz gestosc grafu w procentach:" << endl;
            cin >> density;
            cout << "Wprowadz ilosc wierzcholkow grafu:" << endl;
            cin >> vertex;
            algorytmy.Random_Directgraph_Generator(density, vertex);
            break;

        case 3: // wyswietl listowo/macierzowo
            cout << "Wyswietlenie listowo:" << endl;
            algorytmy.grafDirect.print_list();
            cout << endl << "Wyswietlanie macierzowo: " << endl;
            algorytmy.grafDirect.print_matrix(vertex);
            break;

        case 4: // Dijkstra
            algorytmy.Dijkstra_and_print(vertex, startVertex);
            break;

        case 5: // pomiary
            float avg1 = 0, avg2 = 0, avg3 = 0;
            cout << "Pomiary:" << endl;
            int d = 20;
            int nn = 1000;

            fstream Timefile;
            string fileTimeName = "TimeDijkstra.csv";
            Timefile.open(fileTimeName, ios::out | ios::app);
            Timefile << endl << "Pomiary Dijkstra" << endl;

            for (int i = 0; i < 50; i++)
            {
                algorytmy.Random_Directgraph_Generator(d, nn);

                auto t1 = std::chrono::high_resolution_clock::now(); // czas start
                algorytmy.Dijkstra(nn, startV);

                auto t2 = std::chrono::high_resolution_clock::now();
                avg1 += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            }
            avg1 = avg1 / 50;
            cout << d << " " << nn << endl << "Sredni czas Dijkstra [ns]: " << avg1 << endl;
            Timefile << endl << "Gestosc: "<< d << " Wierzcholki: " << nn << endl;
            Timefile << "Czas: "<<avg1<<endl;

            d = 60;
            avg2 = 0;
            for (int i = 0; i < 50; i++)
            {
                algorytmy.Random_Directgraph_Generator(d, nn);

                auto t1 = std::chrono::high_resolution_clock::now(); // czas start
                algorytmy.Dijkstra(nn, startV);

                auto t2 = std::chrono::high_resolution_clock::now();
                avg2 += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            }
            avg2 = avg2 / 50;
            cout << d << " " << nn << endl << "Sredni czas Dijkstra [ns]: " << avg2 << endl;
            Timefile <<"Gestosc: "<< d << " Wierzcholki: " << nn << endl;
            Timefile << "Czas: "<< avg2 << endl;

            d = 99;
            avg3 = 0;
            for (int i = 0; i < 50; i++)
            {
                algorytmy.Random_Directgraph_Generator(d, nn);
                //start = read_QPC(); // poczatek pomiaru
                auto t1 = std::chrono::high_resolution_clock::now(); // czas start
                algorytmy.Dijkstra(nn, startV);
                //elapsed = read_QPC() - start; // koniec pomiaru
                auto t2 = std::chrono::high_resolution_clock::now();
                avg3 += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            }
            avg3 = avg3 / 50;
            cout << d << " " << nn << endl << "Sredni czas Dijkstra [ns]: " << avg3 << endl;
            Timefile <<"Gestosc: "<< d << " Wierzcholki: " << nn << endl;
            Timefile << "Czas: "<< avg1 << endl;
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


