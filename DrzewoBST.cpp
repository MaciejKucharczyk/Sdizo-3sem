#include <iostream>
#include "Query.cpp"

using namespace std;

struct BSTNode
{
    int data; //klucz
    BSTNode* parent; //ojciec
    BSTNode* left; //lewe dziecko 
    BSTNode* right; //prawe dziecko 
};

class BSTtree
{
public:
    void loadFromFile(string filename);
    void displayMenu();

	BSTNode* root; //korzen
	BSTNode* findNode(int data); //szukanie wezla
	BSTNode* findSuccessor(BSTNode* node); //szukanie nastepnika

	/// Dealokuje pamiêæ dla ka¿dego elementu drzewa (PostOrder).
	/// \param root - korzeñ drzewa.
	void deletePostOrder(BSTNode* root); //dealokacja pamieci
	void printTree(string prefix, const BSTNode* node, bool isLeft); //prefiks, kolejny wezel, nastepny wierzcholek isLeft - mowi czy wierzcholek
                                                                        //jest lewym dzieckiem
	BSTtree();
	~BSTtree();
	void add(int element);
	void remove(int element);
	bool find(int element);
	void printTree();
    void eksperymenty();
};

void BSTtree::displayMenu()
{
	cout << endl;
	cout << "----- Drzewo BST -----" << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Usun" << endl;
	cout << "3.Dodaj" << endl;
	cout << "4.Znajdz" << endl;
	cout << "5.Utworz losowo" << endl;
	cout << "6.Wyswietl" << endl;
	cout << "7.Test (pomiary)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}
BSTtree::BSTtree()
{
    root = nullptr;
}

BSTtree::~BSTtree()
{
    //Usuwamy kolejno wszystkie elementy w przejściu PostOrder.
    deletePostOrder(root);
}

void BSTtree::add(int element)
{
    //Tworzymy nowy węzeł i wypełniamy jego pola.
    BSTNode* node = new BSTNode();
    node->data = element;
    node->left = nullptr;
    node->right = nullptr;

    //Jeśli drzewo jest puste to nowy węzeł staje się jego korzeniem.
    if (root == nullptr) 
        root = node;
    else
    {
        //Zgodnie ze strukturą drzewa, idziemy do ostatniego węzła.
        BSTNode* next = root;
        BSTNode* lastNode = nullptr;
        while (next != nullptr)
        {
            lastNode = next;
            if (node->data < next->data) next = next->left;
            else next = next->right;
        }
        if (node->data < lastNode->data) lastNode->left = node;
        else lastNode->right = node;
        node->parent = lastNode;
    }
}

void BSTtree::remove(int element)
{
    BSTNode* removeNode = findNode(element); //Znajdujemy wskaźnik na element o poszukiwanym kluczu
    if (removeNode == nullptr) 
        return;
    if (removeNode->left == nullptr && removeNode->right == nullptr) //jezeli usuwany wierzchołek jest liściem
    {
        if (removeNode->parent != nullptr) //usuwamy wierzcholek
        {
            BSTNode* parent = removeNode->parent;

            if (parent->data > removeNode->data) //ustawienie odpowiedniego rodzica na null
                parent->left = nullptr; 
            else 
                parent->right = nullptr;
        }
        else root = nullptr;
        delete removeNode;
    }
    else if (removeNode->left != nullptr && removeNode->right == nullptr) //gdy usuwany wierzcholek ma dziecko (lewe)
    {
        //zamiana
        BSTNode* child = removeNode->left;
        removeNode->data = child->data;
        removeNode->left = child->left;
        removeNode->right = child->right;
        delete child;
    }
    else if (removeNode->left == nullptr && removeNode->right != nullptr) //gdy usuwany wierzcholek ma dziecko (prawe)
    {
        //zamiana
        BSTNode* child = removeNode->right;
        removeNode->data = child->data;
        removeNode->left = child->left;
        removeNode->right = child->right;
        delete child;
    }
    else //gdy usuwany wierzcholek ma oboje dzieci
    {
        BSTNode* successor = findSuccessor(removeNode); //szukamy nastepnika danego wezla
        removeNode->data = successor->data;  //Zamieniamy dane i przypisujemy prawe poddrzewo następnika jego rodzicowi.
        BSTNode* successorRightSubtree = successor->right;
        if (successor->data < successor->parent->data) 
            successor->parent->left = successorRightSubtree;
        else 
            successor->parent->right = successorRightSubtree;
        if (successorRightSubtree != nullptr) 
            successorRightSubtree->parent = successor->parent;
        delete successor;
    }
}

bool BSTtree::find(int element)
{
    BSTNode* next = root; //ostatni wezel (od niego zaczynamy)
    while (next != nullptr)
    {
        if (element == next->data) 
            return true;
        if (element < next->data) 
            next = next->left;
        else 
            next = next->right;
    }
    return false;
}

void BSTtree::printTree()
{
    if (root == nullptr)
    {
        cout << "Drzewo jest puste!" << std::endl;
        return;
    }
    printTree("", root, false);
}

BSTNode* BSTtree::findNode(int data)
{
    BSTNode* next = root; //ostatni wezel 
    while (next != nullptr)
    {
        if (data == next->data) 
            return next;
        if (data < next->data) 
            next = next->left;
        else 
            next = next->right;
    }
    return next;
}

BSTNode* BSTtree::findSuccessor(BSTNode* node)
{
    node = node->right; //następnik jest najmniejszym elementem prawego poddrzewa danego węzła
    BSTNode* lastNode = nullptr;
    while (node != nullptr)
    {
        lastNode = node;
        node = node->left;
    }
    return lastNode;
}

void BSTtree::deletePostOrder(BSTNode* root)
{
    //Przejście drzewa PostOrder.
    if (root != nullptr)
    {
        deletePostOrder(root->left);
        deletePostOrder(root->right);
        delete root;
    }
}

void BSTtree::printTree(std::string prefix, const BSTNode* node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──");
        std::cout << node->data << std::endl;

        printTree(prefix + (isLeft ? "│   " : "    "), node->left, true);
        printTree(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void BSTtree::loadFromFile(string filename)
{
	int lineNum = 1; // numer linii, z ktorej zczytywane sa dane
	int size, liczba; // zmienna liczba przechowuje aktualnie zczytywana liczbe
	fstream File;
	File.open(filename);
	File >> size; // pierwszy element w pliku przechowuje ilosc elementow pliku
	while (size >= lineNum)
	{
		lineNum++;
		File >> liczba;
		add(liczba);
	}
	File.close();
}

void BSTtree::eksperymenty()
{
    double avgTime1 = 0;
    double avgTime2 = 0;
    int file_size = 100000;
    cout << "Trwa wykonywanie pomiaru..." << endl;
    loadFromFile("zzLiczby100000.txt");
    cout << file_size << endl;

    int test_val = 123;
    int test_idx = 0;
    for (int i = 0; i < 2000; i++)
    {
        test_val = rand() % 1000 - 500;
        //test_idx = rand() % 1000 - 500;

        start = read_QPC(); // poczatek pomiaru 
        find(12598);
        elapsed = read_QPC() - start; // koniec pomiaru
        avgTime1 += (1000000.0 * elapsed) / frequency;

        /*start = read_QPC(); // poczatek pomiaru
        remove(test_val);
        elapsed = read_QPC() - start; // koniec pomiaru
        avgTime2 += (1000000.0 * elapsed) / frequency;*/
    }
    avgTime1 = avgTime1 / 2000;
//   	avgTime2 = avgTime2 / 2000;
    cout << "Sredni czas szukania elementu [us]: " << avgTime1 << endl;
//   	cout << "Sredni czas usuwania  elementu [us]: " << avgTime2 << endl;
}