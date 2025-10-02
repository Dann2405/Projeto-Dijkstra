#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 999999; // usamos isso como infinito mesmo, funciona

// tira os espacos das pontas - arquivo sempre vem com sujeira
string limpar(string s) {
    while (!s.empty() && (s[0] == ' ' || s[0] == '\t')) {
        s.erase(0, 1);
    }
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\n' || s.back() == '\r')) {
        s.pop_back();
    }
    return s;
}

// le o json do arquivo e monta o grafo
// sim, to parseando na mao, funciona pro nosso caso
map<string, map<string, int>> carregarGrafo(string arquivo) {
    map<string, map<string, int>> g;
    ifstream f("grafos/" + arquivo);
    
    if (!f.is_open()) {
        cout << "deu ruim ao abrir o arquivo\n";
        return g;
    }
    
    string linha;
    string noAtual = "";
    
    while (getline(f, linha)) {
        linha = limpar(linha);
        
        if (linha.empty() || linha == "{" || linha == "}") continue;
        
        // detecta o inicio de um no (ex: "A": {)
        if (linha.find("\":") != string::npos && linha.find("{") != string::npos) {
            int p1 = linha.find("\"");
            int p2 = linha.find("\"", p1 + 1);
            noAtual = linha.substr(p1 + 1, p2 - p1 - 1);
            g[noAtual] = map<string, int>();
        }
        // pega as arestas (ex: "B": 4)
        else if (linha.find("\":") != string::npos && !noAtual.empty()) {
            int p1 = linha.find("\"");
            int p2 = linha.find("\"", p1 + 1);
            string dest = linha.substr(p1 + 1, p2 - p1 - 1);
            
            int pos = linha.find(":", p2);
            int fim = linha.find_first_of(",}", pos);
            string num = limpar(linha.substr(pos + 1, fim - pos - 1));
            
            g[noAtual][dest] = stoi(num);
        }
    }
    
    f.close();
    return g;
}

// dijkstra classico com fila de prioridade
// complexidade O((V + E) log V) que ta otimo pra maioria dos casos
pair<vector<string>, int> menorCaminho(map<string, map<string, int>>& g, string ori, string dest) {
    map<string, int> d; // distancias
    map<string, string> ant; // pra reconstruir o caminho depois
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    
    // inicializa tudo com infinito
    for (map<string, map<string, int>>::iterator it = g.begin(); it != g.end(); ++it) {
        d[it->first] = INF;
    }
    
    d[ori] = 0;
    pq.push(make_pair(0, ori));
    
    while (!pq.empty()) {
        int dist = pq.top().first;
        string u = pq.top().second;
        pq.pop();
        
        // ja achou o melhor caminho pro destino, pode parar
        if (u == dest) break;
        
        // se essa distancia ja ta desatualizada, pula
        if (dist > d[u]) continue;
        
        // relaxa as arestas
        for (map<string, int>::iterator it = g[u].begin(); it != g[u].end(); ++it) {
            string v = it->first;
            int peso = it->second;
            int nova = d[u] + peso;
            
            if (nova < d[v]) {
                d[v] = nova;
                ant[v] = u;
                pq.push(make_pair(nova, v));
            }
        }
    }
    
    vector<string> caminho;
    
    // nao achou caminho
    if (d[dest] == INF) {
        return make_pair(caminho, -1);
    }
    
    // reconstroi o caminho de tras pra frente
    string atual = dest;
    while (atual != ori) {
        caminho.push_back(atual);
        atual = ant[atual];
    }
    caminho.push_back(ori);
    reverse(caminho.begin(), caminho.end());
    
    return make_pair(caminho, d[dest]);
}

int main() {
    cout << "=== Dijkstra - Menor Caminho ===" << endl << endl;
    
    string arquivo;
    cout << "Arquivo do grafo (ex: grafo.json): ";
    getline(cin, arquivo);
    
    map<string, map<string, int>> grafo = carregarGrafo(arquivo);
    
    if (grafo.empty()) {
        cout << "Nao consegui carregar o grafo" << endl;
        return 1;
    }
    
    cout << "Carregado com sucesso: " << grafo.size() << " nos" << endl << endl;
    
    // lista os nos disponiveis
    cout << "Nos disponiveis: ";
    for (map<string, map<string, int>>::iterator it = grafo.begin(); it != grafo.end(); ++it) {
        cout << it->first << " ";
    }
    cout << endl << endl;
    
    string ori, dest;
    
    // valida origem
    while (true) {
        cout << "Origem: ";
        getline(cin, ori);
        ori = limpar(ori);
        
        if (grafo.count(ori)) break;
        cout << "Esse no nao existe, tenta de novo" << endl;
    }
    
    // valida destino
    while (true) {
        cout << "Destino: ";
        getline(cin, dest);
        dest = limpar(dest);
        
        if (grafo.count(dest)) break;
        cout << "Esse no nao existe, tenta de novo" << endl;
    }
    
    cout << endl << "Rodando o algoritmo..." << endl << endl;
    
    pair<vector<string>, int> resultado = menorCaminho(grafo, ori, dest);
    vector<string> caminho = resultado.first;
    int custo = resultado.second;
    
    if (custo == -1) {
        cout << "Nao existe caminho entre esses nos" << endl;
    } else {
        cout << "Caminho encontrado: ";
        for (size_t i = 0; i < caminho.size(); i++) {
            cout << caminho[i];
            if (i < caminho.size() - 1) cout << " -> ";
        }
        cout << endl;
        cout << "Custo total: " << custo << endl;
    }
    
    return 0;
}