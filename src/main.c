#include <stdio.h>
#include <stdlib.h>
#include "ds.h"
#include "utils.h"

int main(void) {
    BinaryTree* root = NULL;
    Graph* graph = NULL;
    int option = 0;
    int value = 0;

    while (1) {
        clear_screen();
        printf("=======================================\n");
        printf("   SISTEMA DE ESTRUTURAS NAO LINEARES  \n");
        printf("=======================================\n");
        printf(" [APS 1 - Arvore AVL]                  \n");
        printf(" 1. Inserir Elemento na AVL            \n");
        printf(" 2. Remover Elemento da AVL            \n");
        printf(" 3. Percorrer Passo a Passo (Em-Ordem) \n");
        printf(" 4. Visualizar Arvore Atual            \n");
        printf(" 5. Executar Benchmark de Buscas       \n");
        printf("---------------------------------------\n");
        printf(" [APS 2 & Desafio 2 - GPS / Grafos]    \n");
        printf(" 6. Criar / Configurar Grafo (Matriz)  \n");
        printf(" 7. Visualizar Matrizes do Grafo       \n");
        printf(" 8. Calcular Rota (GPS / Dijkstra)     \n");
        printf("---------------------------------------\n");
        printf(" 0. Sair                               \n");
        printf("=======================================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &option) != 1) break;
        if (option == 0) break;

        switch (option) {
            case 1: {
                printf("Digite o valor inteiro para INSERIR: ");
                scanf("%d", &value);
                int* new_val = (int*) malloc(sizeof(int));
                *new_val = value;
                root = tree_insert(root, new_val, compare_ints);
                printf("\nValor %d inserido com sucesso!\n", value);
                printf("\nEstrutura Apos Insercao:\n");
                print_tree(root, print_int);
                printf("\nPressione Enter para continuar...");
                getchar(); getchar();
                break;
            }
            case 2: {
                printf("Digite o valor inteiro para REMOVER: ");
                scanf("%d", &value);
                root = tree_delete(root, &value, compare_ints);
                printf("\nProcesso de remocao concluido!\n");
                printf("\nEstrutura Apos Remocao:\n");
                print_tree(root, print_int);
                printf("\nPressione Enter para continuar...");
                getchar(); getchar();
                break;
            }
            case 3: {
                if (root == NULL) {
                    printf("\nA arvore esta vazia!\n");
                    printf("\nPressione Enter para continuar...");
                    getchar(); getchar();
                } else {
                    getchar();
                    traverse_inorder_step_by_step(root, root);
                    printf("\nPercurso finalizado!\n");
                    printf("Pressione Enter para continuar...");
                    getchar();
                }
                break;
            }
            case 4: {
                clear_screen();
                printf("=== ESTRUTURA ATUAL DA ARVORE ===\n\n");
                print_tree(root, print_int);
                printf("\nPressione Enter para continuar...");
                getchar(); getchar();
                break;
            }
            case 5: {
                run_benchmark();
                break;
            }
            case 6: {
                int n_nodes, u, v, dist, time, toll;
                clear_screen();
                printf("=== CRIACAO DO GRAFO (MATRIZ DE ADJACENCIA) ===\n");
                printf("Digite o numero de nos (max %d): ", MAX_NODES);
                scanf("%d", &n_nodes);

                if (n_nodes <= 0 || n_nodes > MAX_NODES) {
                    printf("Numero de nós invalido!\n");
                    printf("Pressione Enter para continuar...");
                    getchar(); getchar();
                    break;
                }

                graph = create_graph(n_nodes);

                printf("\nQuantas Arestas/Conexoes deseja cadastrar? ");
                int edges;
                scanf("%d", &edges);

                for (int i = 0; i < edges; i++) {
                    printf("\n--- Aresta %d ---\n", i + 1);
                    printf("Origem (0 a %d): ", n_nodes - 1);
                    scanf("%d", &u);
                    printf("Destino (0 a %d): ", n_nodes - 1);
                    scanf("%d", &v);
                    printf("Distancia (km): ");
                    scanf("%d", &dist);
                    printf("Tempo (minutos): ");
                    scanf("%d", &time);
                    printf("Custo de Pedagio (R$): ");
                    scanf("%d", &toll);

                    if (u >= 0 && u < n_nodes && v >= 0 && v < n_nodes) {
                        graph->adj_matrix[u][v] = dist;
                        graph->adj_matrix[v][u] = dist; // Grafo não direcionado
                        graph->time_matrix[u][v] = time;
                        graph->time_matrix[v][u] = time;
                        graph->toll_matrix[u][v] = toll;
                        graph->toll_matrix[v][u] = toll;
                    } else {
                        printf("Indices invalidos! Aresta ignorada.\n");
                    }
                }

                printf("\nGrafo criado com sucesso!\n");
                printf("Pressione Enter para continuar...");
                getchar(); getchar();
                break;
            }
            case 7: {
                clear_screen();
                if (graph == NULL) {
                    printf("Nenhum grafo criado ainda! Utilize a opcao 6 primeiro.\n");
                } else {
                    print_graph(graph);
                }
                printf("\nPressione Enter para continuar...");
                getchar(); getchar();
                break;
            }
            case 8: {
                clear_screen();
                if (graph == NULL) {
                    printf("Nenhum grafo criado ainda! Utilize a opcao 6 primeiro.\n");
                    printf("\nPressione Enter para continuar...");
                    getchar(); getchar();
                    break;
                }

                int start, end, criteria;
                printf("=== SIMULADOR DE GPS (DIJKSTRA) ===\n");
                print_graph(graph);

                printf("\nDigite o no de ORIGEM: ");
                scanf("%d", &start);
                printf("Digite o no de DESTINO: ");
                scanf("%d", &end);

                printf("\nEscolha o criterio de navegacao:\n");
                printf(" [0] Menor Distancia (km)\n");
                printf(" [1] Menor Tempo (minutos)\n");
                printf(" [2] Menor Custo de Pedagio (R$)\n");
                printf(" [3] Mix Personalizado (Equilibrado)\n");
                printf("Opcao escolhida: ");
                scanf("%d", &criteria);

                dijkstra(graph, start, end, criteria);

                printf("\nPressione Enter para continuar...");
                getchar(); getchar();
                break;
            }
            default:
                printf("\nOpcao invalida!\n");
                getchar(); getchar();
                break;
        }
    }

    tree_free(root);
    if (graph) free(graph);
    return 0;
}
