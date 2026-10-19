#pragma once

typedef struct BinaryTree {
    void* data;
    int height;
    struct BinaryTree* left;
    struct BinaryTree* right;
} BinaryTree;

typedef int (*CompareFn)(const void* a, const void* b);

BinaryTree* create_node(void* data);
void tree_free(BinaryTree* root);
BinaryTree* tree_insert(BinaryTree* root, void* data, CompareFn compare);
BinaryTree* tree_delete(BinaryTree* root, void* data, CompareFn compare);

BinaryTree* tree_search_avl(BinaryTree* root, void* data, CompareFn compare);
BinaryTree* tree_search_linear(BinaryTree* root, void* data, CompareFn compare);

#define MAX_NODES 20

typedef struct Graph {
    int num_nodes;
    int adj_matrix[MAX_NODES][MAX_NODES];
    int time_matrix[MAX_NODES][MAX_NODES];
    int toll_matrix[MAX_NODES][MAX_NODES];
} Graph;

Graph* create_graph(int num_nodes);
void print_graph(Graph* g);
void dijkstra(Graph* g, int start, int end, int criteria);
