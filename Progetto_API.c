#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define BUFFERSIZE 2500

typedef struct TopKHeap {
    int value;
    int graph_index;
} TopKHeap;

int dijkstra(int *offsets, int *edges, int *weights, int nodes);

void heapify(TopKHeap *A, int i, int heapSize);

int heapInsert(TopKHeap *heap, int key, int index, int heapsize);

int extractMinimum(int *dist, int dim, int *q);

int main() {

    char buffer[BUFFERSIZE], *p, *l;

    int parameters[2]; //0 -> nodes, 1 -> topk

    short indexes_dim = 0, zerocounter = 0, nas = 0;
    int i, col = 0, j = 0, k = 1, graph_index = -1;

    int *offsets = NULL, *edges = NULL, *weights = NULL;

    TopKHeap *topkHeap = NULL;
    int topkHeapSize = 0, dijkvalue;

    while ((fgets(buffer, BUFFERSIZE, stdin)) != NULL) {
        p = buffer;
        while (*p && indexes_dim < 2) {
            if (isdigit(*p)) {
                parameters[indexes_dim] = strtol(p, &p, 10);
                indexes_dim++;
            } else p++;
        }
        if (nas == 0) {
            topkHeap = malloc(parameters[1] * sizeof(TopKHeap));
            nas++;
        }
        while (*p && indexes_dim >= 2) {
            if (*p == 'A') {
                edges = malloc(parameters[0] * parameters[0] * sizeof(int));
                weights = malloc(parameters[0] * parameters[0] * sizeof(int));
                graph_index++;
                offsets = malloc((parameters[0] + 1) * sizeof(int));
                offsets[0] = 0;
                for (i = 0; i < parameters[0]; i++) {
                    if ((fgets(buffer, BUFFERSIZE, stdin)) != NULL) {
                        l = buffer;
                        while (*l) {
                            if (isdigit(*l)) {
                                if (*l != 48) {
                                    weights[j] = strtol(l, &l, 10);
                                    edges[j] = col;
                                    j++;
                                } else if (i == 0 && *l == 48) zerocounter++;
                                col++;
                            }
                            l++;
                        }
                        offsets[k] = j;
                        k++;
                        col = 0;
                    }
                }
                if (zerocounter == 4) {
                    zerocounter = 0;
                    dijkvalue = 0;
                } else {
                    zerocounter = 0;
                    dijkvalue = dijkstra(offsets, edges, weights, parameters[0]);
                }
                j = 0;
                k = 1;
                free(offsets);
                free(edges);
                free(weights);

                if (topkHeapSize < parameters[1]) {
                    topkHeapSize = heapInsert(topkHeap, dijkvalue, graph_index, topkHeapSize);
                } else if (dijkvalue < topkHeap[0].value) {
                    topkHeap[0].value = dijkvalue;
                    topkHeap[0].graph_index = graph_index;
                    heapify(topkHeap, 0, topkHeapSize);
                }

                p = p + 14;
            } else if (*p == 'T') {
                if (topkHeapSize == 0) printf("\n");
                else {
                    for (i = 0; i < topkHeapSize; i++) {
                        if (i == topkHeapSize - 1) printf("%d\n", topkHeap[i].graph_index);
                        else printf("%d ", topkHeap[i].graph_index);
                    }
                }
                p = p + 5;
            }
            p++;
        }
    }
    free(topkHeap);
    return 0;

}

void heapify(TopKHeap *A, int i, int heapsize) {
    int l, r, largest, tmpv, tmpi;
    l = (2 * i) + 1;
    r = (2 * i + 1) + 1;
    if (l < heapsize && A[l].value > A[i].value) {
        largest = l;
    } else largest = i;
    if (r < heapsize && A[r].value > A[largest].value) {
        largest = r;
    }
    if (largest != i) {
        tmpv = A[i].value;
        tmpi = A[i].graph_index;
        A[i].value = A[largest].value;
        A[i].graph_index = A[largest].graph_index;
        A[largest].value = tmpv;
        A[largest].graph_index = tmpi;
        heapify(A, largest, heapsize);
    }
}

int heapInsert(TopKHeap *heap, int key, int index, int heapsize) {
    int i;
    TopKHeap tmp;
    heapsize++;
    i = heapsize - 1;
    heap[i].value = key;
    heap[i].graph_index = index;
    while (i > 0 && heap[(i - 1) / 2].value < key) {
        tmp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = tmp;
        i = (i - 1) / 2;
    }

    return heapsize;
}

int dijkstra(int *offsets, int *edges, int *weights, int nodes) {
    int dist[nodes], q[nodes], v, u, result = 0, i, alt, qsize;

    for (v = 0; v < nodes; v++) {
        if (v == 0) {
            dist[v] = 0;
        } else {
            dist[v] = INT_MAX;
        }
        q[v] = v;
    }

    qsize = nodes;

    while (qsize > 0) {
        u = extractMinimum(dist, nodes, q);
        if (u < nodes && dist[u] != INT_MAX) {
            result = result + dist[u];
        } else return result;
        q[u] = -1;
        qsize--;
        for (i = offsets[u]; i < offsets[u + 1]; i++) {
            v = edges[i];
            alt = dist[u] + weights[i];
            if (alt < dist[v]) {
                dist[v] = alt;
            }
        }
    }
    return result;
}

int extractMinimum(int *dist, int dim, int *q) {
    int min = INT_MAX, i, res = INT_MAX;

    for (i = 0; i < dim; i++) {
        if (dist[i] < min && q[i] != -1) {
            min = dist[i];
            res = i;
        }
    }
    return res;
}
