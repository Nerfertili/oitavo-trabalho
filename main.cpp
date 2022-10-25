// Grafos - Lista de adjacência

#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <random>
#include <vector>

using namespace std;
typedef int TipoItem;
class grafo_matriz {
public:
  vector<vector<int>> tab;
  vector<int> header;
  vector<int> rows;
  grafo_matriz(vector<int> vertices) {
    rows = vertices;
    vector<int> header = {-2};
    for (int i = 0; i < vertices.size(); i++) {
      header.push_back(vertices.at(i));
    }
    vector<int> row = header;
    tab.push_back(row);
    int row_ind = 0;
    for (int i = 0; i < vertices.size(); i++) {
      row = {};
      for (int w = 0; w < vertices.size(); w++) {
        if (w == 0) {
          row.push_back(vertices.at(row_ind));
          row_ind++;
        } else {
          row.push_back(0);
        }
      }
      tab.push_back(row);
    }
  }
  void adicionarAresta(int v1, int v2) {
    int v1_ind;
    int v2_ind;
    for (int i = 0; i < rows.size(); i++) {
      if (rows.at(i) == v1)
        v1_ind = i;
      if (rows.at(i) == v2)
        v2_ind = i;
    }
    tab.at(v2_ind + 1).at(v1_ind) = 1;
  }
  vector<vector<int>> get_tab() { return tab; }
};
class grafo_lista {
public:
  vector<int> vert;
  vector<vector<int>> adj;
  grafo_lista(vector<int> vert_) {
    vert = vert_;
    for (int i = 0; i < vert_.size(); i++) {
      adj.push_back({});
    }
  }
  void adicionarAresta(int v1, int v2) {
    int index;
    for (int i = 0; i < vert.size(); i++) {
      if (vert.at(i) == v1)
        index = i;
    }
    adj.at(index).push_back(v2);
  }
  vector<int> get_vert() { return vert; }
  vector<vector<int>> get_adj() { return adj; }
};
int dis() {
  int aleatorio = 1 + rand() % 1000;
  return aleatorio;
}
int dis_2() {
  int aleatorio = 1 + rand() % 3;
  return aleatorio;
}
int dis_3() {
  int aleatorio = 1 + rand() % 10000;
  return aleatorio;
}
int main() {
  auto inicio = std::chrono::high_resolution_clock::now();
  auto resultado = std::chrono::high_resolution_clock::now() - inicio;
  long long liliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(resultado).count();

  vector<int> role;
  for (int i = 0; i < 10000; i++) {
    role.push_back(dis());
  }

  grafo_lista grafo({});
  array<long long, 50> tempos;
  for (int j = 0; j < 50; j++) {
    inicio = std::chrono::high_resolution_clock::now();

    grafo_lista grafo(role);
    for (int i = 0; i < 10000; i++) {
      for (int u = 0; u < dis_2(); u++) {
        grafo.adicionarAresta(role[i], role[dis_3()]);
      }
    }
    resultado = std::chrono::high_resolution_clock::now() - inicio;
    liliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(resultado)
            .count();
    tempos.at(j) = liliseconds;
    ofstream fw("lista_adjacencias.txt");
    vector<vector<int>> adj = grafo.get_adj();
    for (int w = 0; w < 10000; w++) {
      fw << role[w] << " ";
      for (int k = 0; k < adj.at(w).size(); k++) {
        fw << adj.at(w).at(k) << " ";
      }
      fw << "\n";
    }
  }
  for (int j = 1; j < 50; j++) {
    tempos.at(0) = tempos.at(0) + tempos.at(j);
  }
  cout << "o tempo que levou para a execução da lista é : " << tempos[0] / 50
       << " milisegundos" << endl;
  // open file for writing
  array<long long, 50> tempos_2;
  for (int j = 0; j < 50; j++) {
    inicio = std::chrono::high_resolution_clock::now();

    grafo_matriz grafo_2(role);
    for (int i = 0; i < 10000; i++) {
      for (int u = 0; u < dis_2(); u++) {
        grafo_2.adicionarAresta(role[i], role[dis_3()]);
      }
    }

    resultado = std::chrono::high_resolution_clock::now() - inicio;
    liliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(resultado)
            .count();
    tempos_2.at(j) = liliseconds;
    ofstream fw_2("vtabela_adjacencias.txt");
    vector<vector<int>> tab = grafo_2.get_tab();
    for (int w = 0; w < tab.size(); w++) {
      for (int k = 0; k < tab.at(w).size(); k++) {
        fw_2 << tab.at(w).at(k) << "\t";
      }
      fw_2 << "\n";
    }
  }
  for (int j = 1; j < 50; j++) {
    tempos_2.at(0) = tempos_2.at(0) + tempos_2.at(j);
  }
  cout << "o tempo que levou para a execução da matriz é : " << tempos[0] / 50
       << " milisegundos" << endl;
  cout << "PROFESSOR NAO QUER FUNCIONAR DE JEITO NENHUM COM 100 000 ENTAO "
          "COLOQUEI MENOS"
       << endl;
}