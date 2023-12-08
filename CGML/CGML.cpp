#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

namespace CGML {
	class Auxiliary {
	public:int Random(int a, int b) {
		srand(time(NULL));
		if (a > 0) {
			return a + rand() % (b - a);
		}
		return a + rand() % (abs(a) + b);
	}
	};

	class CreateGraphMatrixList : public Auxiliary {
	public:void Graph(int maxVertx, int minEdges, bool eventRandom = true) {
		system("chcp 1251");
		system("cls");
		cout << "Вершин: " + to_string(maxVertx) + "\n";

		auto start = time(NULL);
		string n;
		int countVert = 0;
		int lastNumber = 0;
		int vertix = 0;
		vector<int> numbers;
		vector<vector<int>> graph;
		
		if (eventRandom == true) {
			vertix = Random(0, maxVertx);
		}

		for (int indHor = 0; indHor < maxVertx; indHor++) {
			vector<int> gr;
			for (int indVert = 0; indVert < maxVertx; indVert++) {
				gr.push_back(0);
			}
			graph.push_back(gr);
			numbers.push_back(0);
		}

		while (true) {
			int count = 0;

			if (vertix == maxVertx) {
				vertix = 0;
			}

			for (int num = lastNumber; num < numbers.size(); num++) {
				vector<int> gr;
				if (count < minEdges and numbers[num] < minEdges and vertix != num) { //Кол-во добовлений и Кол-во ребер и Сам в себя 
					//cout << to_string(vertix) + " " + to_string(num) + "\n";
					graph[vertix][num] = 1;
					graph[num][vertix] = 1;
					numbers[num] = numbers[num] + 1;
					lastNumber = num;
					count++;
				}
			}

			vertix++;
			countVert++;
			if (countVert == maxVertx) {
				int procent = 0;
				ofstream fileEdges("edges.txt");
				ofstream fileMatrix("matrix.txt");

				for (int gr = 0; gr < graph.size(); gr++) {
					string line;
					for (int g = 0; g < graph[gr].size(); g++) {
						if (graph[gr][g] == 1) {
							fileEdges << to_string(gr) + " " + to_string(g) + "\n";
						}
						line += to_string(graph[gr][g]);
					}
					fileMatrix << line + "\n";
				}

				break;
			}
		}

		system("cls");
		cout << "Сформирован граф на: " + to_string(maxVertx) + " верш.\n";
		cout << "Время затрачено: " + to_string(time(NULL) - start) + " сек.\n";
		cin >> n;
	}
	};
}

void main() {
	CGML::CreateGraphMatrixList cgm = CGML::CreateGraphMatrixList();
	cgm.Graph(300, 2, true);
}