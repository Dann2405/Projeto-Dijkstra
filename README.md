# Algoritmo de Dijkstra - Busca com Custo Uniforme

Projeto desenvolvido como trabalho para a disciplina de Projeto e Análise de Algoritmos, utilizando C++. O objetivo deste programa é implementar o algoritmo de Dijkstra para encontrar o caminho de menor custo entre dois pontos em um grafo ponderado. O algoritmo realiza a leitura de um arquivo contendo a estrutura do grafo em formato JSON, solicita ao usuário os nós de origem e destino, e retorna o menor caminho possível junto com seu custo total.

## Funcionalidades

- Lê arquivos de grafo em formato JSON (parser manual)
- Valida se os nós informados pelo usuário existem no grafo
- Calcula o menor caminho usando Dijkstra com fila de prioridade
- Reconstrói e exibe o caminho completo com o custo total

## Estruturas de dados

- `map<string, map<string, int>>` - Grafo como mapa de adjacências
- `map<string, int>` - Distâncias mínimas (inicializadas com INF = 999999)
- `map<string, string>` - Predecessores pra reconstruir o caminho
- `priority_queue` - Min-heap pra sempre pegar o nó com menor distância

## Requisitos

- Compilador C++ com suporte a C++11/14 (testado com g++)
- Windows, Linux ou macOS

## Estrutura de pastas

```
projeto-dijkstra/
│
├── dijkstra.cpp          # Código-fonte principal
├── .gitignore            # Ignorar arquivos/pastas
├── README.md             # Este arquivo de documentação
│
├── documentacao/         # Pasta contendo documentação do projeto
│   ├── relatorio.pdf     # Relatório técnico completo
│   └── fluxograma.png    # Fluxograma do algoritmo
│
└── grafos/               # Pasta para armazenar arquivos de grafo
    ├── grafo.json
```

## Formato do arquivo JSON

```json
{
  "A": {
    "B": 4,
    "C": 2
  },
  "B": {
    "A": 4,
    "C": 5,
    "D": 10
  },
  "C": {
    "A": 2,
    "B": 5,
    "D": 3
  },
  "D": {
    "B": 10,
    "C": 3,
    "E": 7
  },
  "E": {
    "D": 7,
    "F": 1
  },
  "F": {
    "E": 1
  }
}
```

**Estrutura:**
- Cada chave é um nó (ex: "A", "B")
- Dentro de cada nó, os vizinhos com seus custos
- Os números são os pesos das arestas

Você pode criar múltiplos arquivos de grafo (grafo1.json, grafo2.json, etc.) e armazená-los na pasta `grafos/` para facilitar a organização dos testes.

## Como compilar

Abra o terminal no diretório onde se encontra o arquivo fonte (`dijkstra.cpp`) e execute o comando:

```bash
g++ -o dijkstra dijkstra.cpp
```

Este comando irá gerar o executável `dijkstra.exe` (Windows) ou `dijkstra` (Linux/macOS).

## Como executar

**Windows:**
```bash
.\dijkstra
```

**Linux/macOS:**
```bash
./dijkstra
```

## Exemplo de uso

```
=== Dijkstra - Menor Caminho ===

Arquivo do grafo (ex: grafo.json): grafo.json
Carregado com sucesso: 6 nos

Nos disponiveis: A B C D E F

Origem: A
Destino: F

Rodando o algoritmo...

Caminho encontrado: A -> C -> D -> E -> F
Custo total: 13
```

**Breakdown dos custos:**
- A → C: 2
- C → D: 3
- D → E: 7
- E → F: 1
- **Total: 13**

## Validações implementadas

O programa possui validações para os seguintes casos:

1. **Arquivo não encontrado:** Exibe mensagem de erro e encerra o programa.
2. **Nó de origem invalido:** Solicita nova entrada até que um nó válido seja informado.
3. **Nó de destino invalido:** Solicita nova entrada até que um nó válido seja informado.
4. **Caminho inexistente:** Informa ao usuário que não há conexão entre os nós especificados.

## Complexidade

- **Tempo:** O((V + E) log V) com a fila de prioridade
  - V = número de vértices
  - E = número de arestas
- **Espaço:** O(V) pras estruturas auxiliares

A fila de prioridade garante que sempre pegamos o nó com menor distância em tempo logarítmico.

## Limitações

- **Pesos negativos:** Dijkstra não funciona com arestas negativas (precisaria Bellman-Ford)
- **Parser:** Feito especificamente pro formato JSON mostrado, variações podem quebrar
- **Compatibilidade:** Usa C++11/14 por compatibilidade, evitamos features do C++17
- **Infinito:** Usamos 999999 como constante de infinito, suficiente pra casos práticos

## Referências

CORMEN, Thomas H.; LEISERSON, Charles E.; RIVEST, Ronald L.; STEIN, Clifford. **Algoritmos: Teoria e Prática.** 3. ed. Rio de Janeiro: Elsevier, 2012.

RUSSELL, Stuart J.; NORVIG, Peter. **Inteligência Artificial: Uma Abordagem Moderna.** 4. ed. Rio de Janeiro: GEN LTC, 2022.

## Autores

- Daniel Soares Oliveira Santos
- Gustavo Mendes Lima
