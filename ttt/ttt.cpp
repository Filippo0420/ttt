#include <iostream>
#include <cstdlib>

using namespace std;

/*
12 10
13 3
24 7
25 4
27 8
34 12
36 26
46 17
47 15
57 6
58 16
67 13
68 14
78 9
89 11
*/



struct edge { // krawedz
	int startVertex;
	int endVertex;
	int weight;
	edge* next = nullptr;
};

struct treeElement {
	int startVertex;
	int endVertex;
	int weight;
	int treeNum;
	treeElement* next = nullptr;
};

const int NUM_OF_VERTEXES = 9;
const int NUM_OF_EDGES = 15;

void add(edge** first, edge* nextEdge) {
	if (*first == nullptr)
	{
		*first = nextEdge;
		return;
	}
	edge* i = *first;
	while (i->next != nullptr) {
		i = i->next;
	}
	i->next = nextEdge;
}

void addValue(edge** first, int* nextEdge) {
	edge* ed = new edge;
	ed->startVertex = nextEdge[0];
	ed->endVertex = nextEdge[1];
	ed->weight = nextEdge[2];
	if (*first == nullptr)
	{
		*first = ed;
		return;
	}
	edge* i = *first;
	while (i->next != nullptr) {
		i = i->next;
	}
	i->next = ed;
}

void addTreeElement(treeElement** tree, edge* edgeToAdd, int treeNumber) {
	treeElement* te = new treeElement;
	te->startVertex = edgeToAdd->startVertex;
	te->endVertex = edgeToAdd->endVertex;
	te->weight = edgeToAdd->weight;
	te->treeNum = treeNumber;

	if (*tree == nullptr) {
		*tree = te;
		return;
	}
	treeElement* i = *tree;
	while (i->next != nullptr) {
		i = i->next;
	}
	i->next = te;
}

void print(edge** first) {
	if (*first == nullptr) return;
	edge* i = *first;
	while (i != nullptr) {
		cout << "s:" << i->startVertex << "  e:" << i->endVertex << "  w:" << i->weight << endl;
		i = i->next;
	}
}

void sortEdgesByWeight(edge** first) {
	if (*first == nullptr) return;
	edge* i = *first;
	bool sort = true;
	int temp;
	while (sort) {
		i = *first;
		sort = false;
		while (i->next != nullptr) {
			if (i->weight > i->next->weight) {
				sort = true;
				temp = i->weight;
				i->weight = i->next->weight;
				i->next->weight = temp;

				temp = i->startVertex;
				i->startVertex = i->next->startVertex;
				i->next->startVertex = temp;

				temp = i->endVertex;
				i->endVertex = i->next->endVertex;
				i->next->endVertex = temp;
			}
			i = i->next;
		}
	}

}

bool elementInList(int* list, int size, int element) {
	for (int i = 0; i < size; i++) {
		if (element == list[i]) return true;
	}
	return false;
}

/*
void findTree(edge** sortedList, edge* tree, int numOfVert) {
	int* vertInTree = new int[numOfVert];
	int numOfTrees = 1;
	int** trees = new int* [numOfVert];
	for (int j = 0; j < numOfVert; j++) {
		trees[j] = new int[numOfVert];
	}
	int currentVertNum = 0;
	int price = 0;
	int firsttree, secondtree;
	edge* i = *sortedList;
	bool present = false;
	while (i->next != nullptr) {
		present = false;
		if (!elementInList(vertInTree, numOfVert, i->startVertex) &&
			!elementInList(vertInTree, numOfVert, i->endVertex)) {
			numOfTrees += 1;
		}
		if (!elementInList(vertInTree, numOfVert, i->startVertex)) {
			vertInTree[currentVertNum] = i->startVertex;
			currentVertNum += 1;
			present = true;
			// dodac numer wezla do odpowiedniego drzewa
		}
		if (!elementInList(vertInTree, numOfVert, i->endVertex)) {
			vertInTree[currentVertNum] = i->endVertex;
			currentVertNum += 1;
			present = true;
			// dodac numer wezla do odpowiedniego drzewa
		}
		if (elementInList(vertInTree, numOfVert, i->startVertex) &&
			elementInList(vertInTree, numOfVert, i->endVertex)) {
			if (firsttree != secondtree) {
				// laczenie drzew
				if (firsttree < secondtree) {
					// dodanie elementow z drugiego drzewa do pierwszego

				}
				else {
					// dodanie elementow z pierwszego drzewa do drugiego

				}
				trees[numOfTrees] = new int[numOfVert];
				numOfTrees -= 1;
			}
		}
		if (present) {
			int edgeVal[] = { i->startVertex, i->endVertex, i->weight };
			addValue(&tree, edgeVal);
			price += i->weight;
		}
		i = i->next;
	}
}
*/

void findTree(edge** sortedList, treeElement* tree, int numOfVert) {
	int** vertTree = new int* [numOfVert];
	for (int j = 0; j < numOfVert; j++) {
		vertTree[j] = new int[numOfVert];
	}
	int* vertInTree = new int[numOfVert];
	int currentVert = 0;
	int numOfTrees = 0;
	int treeNum = 1;
	bool present = false;
	edge* i = *sortedList;
	while (i != nullptr) {
		present = false;
		if (!elementInList(vertInTree, numOfVert, i->startVertex) &&
			!elementInList(vertInTree, numOfVert, i->endVertex)) {
			// nowe drzewo
			numOfTrees += 1;
		}
		if (!elementInList(vertInTree, numOfVert, i->startVertex)) {
			for (int k = 0; k < numOfTrees; k++) {
				if (elementInList(vertTree[k], numOfVert, i->startVertex)) {
					treeNum = k + 1;
					break;
				}
			}
			vertInTree[currentVert] = i->startVertex;
			currentVert += 1;
			present = true;
			// dodac numer wezla do odpowiedniego drzewa
		}
		if (!elementInList(vertInTree, numOfVert, i->endVertex)) {
			for (int k = 0; k < numOfTrees; k++) {
				if (elementInList(vertTree[k], numOfVert, i->endVertex)) {
					treeNum = k + 1;
					break;
				}
			}
			vertTree[treeNum - 1]
				vertInTree[currentVert] = i->endVertex;
			currentVert += 1;
			present = true;
			// dodac numer wezla do odpowiedniego drzewa
		}
		/*if (elementInList(vertInTree, numOfVert, i->startVertex) &&
			elementInList(vertInTree, numOfVert, i->endVertex)) {
			if (firsttree != secondtree) {
				// laczenie drzew
				if (firsttree < secondtree) {
					// dodanie elementow z drugiego drzewa do pierwszego

				}
				else {
					// dodanie elementow z pierwszego drzewa do drugiego

				}
				trees[numOfTrees] = new int[numOfVert];
				numOfTrees -= 1;
			}
		}*/
		if (present) {
			addTreeElement(&tree, i, treeNum);
		}
		i = i->next;
	}
}



int main() {
	int values[][3] = {
	{1,2,10},
	{1,3,3},
	{2,4,7},
	{2,5,4},
	{2,7,8},
	{3,4,12},
	{3,6,26},
	{4,6,17},
	{4,7,15},
	{5,7,6},
	{5,8,16},
	{6,7,13},
	{6,8,14},
	{7,8,9},
	{8,9,11}
	};

	edge* graphList = nullptr;
	treeElement* treeList = nullptr;

	for (int i = 0; i < NUM_OF_EDGES; i++) {
		addValue(&graphList, values[i]);
	}
	print(&graphList);
	cout << "\n\n\n";
	sortEdgesByWeight(&graphList);
	print(&graphList);

	findTree(&graphList, treeList, NUM_OF_VERTEXES);
	return 0;
}

