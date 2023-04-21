#include <stdlib.h>
#include <stdbool.h>
#include "APIParte2.h"

inline static u32 max(u32 x, u32 y) {
    return (x>y)?x:y;
}

u32 Greedy(Grafo G,u32* Orden,u32* Color) {
    u32 V = NumeroDeVertices(G);
    u32 max_color = 1;
    bool* coloured = calloc(V, sizeof(bool));   // dice si el i-esimo nodo esta coloreado
    bool* num_set = calloc(V, sizeof(bool));    // dice si el i-esimo color esta usado

    Color[Orden[0]] = 0;
    coloured[Orden[0]] = true;

    for (u32 i = 1; i < V; ++i) {
        u32 min_number = 0, max_vec = 0;
        {                                       // busca el minimo color para Orden[i]
            for (u32 j = 0; j < Grado(Orden[i],G); j++) {
                if (coloured[IndiceVecino(j,Orden[i],G)]) {
                    num_set[Color[IndiceVecino(j,Orden[i],G)]] = true;
                    max_vec = max(max_vec, Color[IndiceVecino(j,Orden[i],G)]);
                }
            }
            while (num_set[min_number]) {
                min_number++;
            }
            max_color = max(max_color, min_number);
        }
        Color[Orden[i]] = min_number;
        coloured[Orden[i]] = true;

        for (u32 j = 0; j <= max_vec; ++j)
            num_set[j] = false;
    }

    free(coloured);
    coloured = NULL;
    free(num_set);
    num_set = NULL;

    return max_color+1;
}

int compare(const void *a, const void *b) {
    int *x = (int *)a;
    int *y = (int *)b;
    return (*x - *y); // Sort in ascending order
}

char OrdenImparPar(u32 n,u32* Orden,u32* Color) {
    // funcion para comparar entre F(x)
    int compare (const void *a, const void *b) {
        u32 *x = (u32 *)a;
        u32 *y = (u32 *)b;

        if (Color[*x]%2 == Color[*y]%2)
            return (Color[*y] - Color[*x]);
        else
            if (Color[*x]%2)
                return -1;
            else
                return 1;
    }

    // ordeno los vertices con la funcion custom
    qsort(Orden, n, sizeof(u32), compare);

    return '0';
}

char OrdenJedi(Grafo G,u32* Orden,u32* Color) {
    u32* sums = calloc(NumeroDeVertices(G), sizeof(u32));
    
    // calculo F(x) para cada color
    for (u32 i = 0; i < NumeroDeVertices(G); ++i) {
        sums[Color[i]] += Grado(i,G);
    }
    for (u32 i = 1; i < NumeroDeVertices(G); ++i) {
        if (sums[i]) sums[i] *= i;
        else break;
    }
    // funcion para comparar entre F(x)
    int compare (const void *a, const void *b) {
        u32 *x = (u32 *)a;
        u32 *y = (u32 *)b;
        
        return (sums[Color[*y]] - sums[Color[*x]]);
    }

    // ordeno los vertices con la funcion custom
    qsort(Orden, NumeroDeVertices(G), sizeof(u32), compare);

    free(sums);
    sums = NULL;

    return '0';
}
