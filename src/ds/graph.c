#include "ds.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 999999

Graph* create_graph(int num_nodes) {
    if (num_nodes <= 0 || num_nodes > MAX_NODES) return NULL;

    Graph* g = (Graph*) malloc(sizeof(Graph));
    if (g == NULL) return NULL;

    g->num_nodes = num_nodes;

    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            if (i == j) {
                g->adj_matrix[i][j] = 0;
                g->time_matrix[i][j] = 0;
                g->toll_matrix[i][j] = 0;
            } else {
                g->adj_matrix[i][j] = INF;
                g->time_matrix[i][j] = INF;
                g->toll_matrix[i][j] = INF;
            }
        }
    }
    return g;
}

void print_graph(Graph* g) {
    if (g == NULL) return;

    printf("\n=== MATRIZ DE ADJACENCIA (DISTANCIA / KM) ===\n    ");
    for (int i = 0; i < g->num_nodes; i++) printf("[%d] ", i);
    printf("\n");
    for (int i = 0; i < g->num_nodes; i++) {
        printf("[%d] ", i);
        for (int j = 0; j < g->num_nodes; j++) {
            if (g->adj_matrix[i][j] == INF) printf("INF ");
            else printf("%-3d ", g->adj_matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n=== MATRIZ DE TEMPO (MINUTOS) ===\n    ");
    for (int i = 0; i < g->num_nodes; i++) printf("[%d] ", i);
    printf("\n");
    for (int i = 0; i < g->num_nodes; i++) {
        printf("[%d] ", i);
        for (int j = 0; j < g->num_nodes; j++) {
            if (g->time_matrix[i][j] == INF) printf("INF ");
            else printf("%-3d ", g->time_matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n=== MATRIZ DE PEDAGIOS (CUSTO EM R$) ===\n    ");
    for (int i = 0; i < g->num_nodes; i++) printf("[%d] ", i);
    printf("\n");
    for (int i = 0; i < g->num_nodes; i++) {
        printf("[%d] ", i);
        for (int j = 0; j < g->num_nodes; j++) {
            if (g->toll_matrix[i][j] == INF) printf("INF ");
            else printf("%-3d ", g->toll_matrix[i][j]);
        }
        printf("\n");
    }
}

void dijkstra(Graph* g, int start, int end, int criteria) {
    if (g == NULL || start < 0 || start >= g->num_nodes || end < 0 || end >= g->num_nodes) {
        printf("\nErro: Nós inválidos para cálculo de rota!\n");
        return;
    }

    int n = g->num_nodes;
    int dist[MAX_NODES];
    int visited[MAX_NODES];
    int parent[MAX_NODES];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min = INF, u = -1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[v] < min) {
                min = dist[v];
                u = v;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            int weight = INF;

            if (criteria == 0) {
                weight = g->adj_matrix[u][v];
            } else if (criteria == 1) {
                weight = g->time_matrix[u][v];
            } else if (criteria == 2) {
                weight = g->toll_matrix[u][v];
            } else if (criteria == 3) {
                if (g->adj_matrix[u][v] != INF) {
                    weight = (int)(g->adj_matrix[u][v] * 0.4 + g->time_matrix[u][v] * 0.4 + g->toll_matrix[u][v] * 0.2);
                }
            }

            if (!visited[v] && weight != INF && dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    if (dist[end] == INF) {
        printf("\nNão há caminho disponível entre o nó %d e o nó %d!\n", start, end);
        return;
    }

    printf("\n========================================\n");
    printf("         RESULTADO DA ROTA (GPS)        \n");
    printf("========================================\n");
    printf("Origem: %d -> Destino: %d\n", start, end);
    printf("Custo total acumulado: %d\n", dist[end]);
    printf("Caminho mínimo: ");

    int path[MAX_NODES];
    int curr = end;
    int idx = 0;

    while (curr != -1) {
        path[idx++] = curr;
        curr = parent[curr];
    }

    for (int i = idx - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\n========================================\n");
}
