//
// Created by nacho on 10/25/2025.
//
#include <stdio.h>

#define CAP 10
#define EMPTY -1

typedef struct {
    int arrInt[CAP];
    int arrSize; /* número de elementos ocupados (>=0 && <=CAP) */
    int arrAdd;  /* suma de elementos ocupados */
} arrayLength_t;

/* Inicializa la estructura:
   - todas las posiciones a EMPTY (-1)
   - arrSize = 0, arrAdd = 0
   Devuelve 0 éxito, -1 error (puntero nulo) */
int initArray(arrayLength_t *a) {
    if (!a) return -1;
    for (int i = 0; i < CAP; ++i) a->arrInt[i] = EMPTY;
    a->arrSize = 0;
    a->arrAdd = 0;
    return 0;
}

/* Imprime la estructura en el formato pedido:
   {[el0, el1, ..., el9], arrSize, arrAdd} */
void printArr(const arrayLength_t *a) {
    if (!a) {
        printf("{[ERROR: puntero NULL], -1, -1}\n");
        return;
    }
    printf("{[");
    for (int i = 0; i < CAP; ++i) {
        printf("%d", a->arrInt[i]);
        if (i < CAP-1) printf(", ");
    }
    printf("], %d, %d}\n", a->arrSize, a->arrAdd);
}

/* Añade un elemento (valor >= 0) en la primera posición libre (EMPTY).
   Actualiza arrSize y arrAdd.
   Devuelve 0 éxito, -1 error (puntero nulo, valor negativo, array lleno) */
int addElement(arrayLength_t *a, int value) {
    if (!a) return -1;
    if (value < 0) return -1; /* decisión: aceptamos >=0, -1 reservado */
    /* buscar primera posición libre */
    int idx = -1;
    for (int i = 0; i < CAP; ++i) {
        if (a->arrInt[i] == EMPTY) { idx = i; break; }
    }
    if (idx == -1) return -1; /* array lleno */
    a->arrInt[idx] = value;
    /* actualizar arrSize: contar ocupadas o incrementar si idx == arrSize */
    /* más sencillo y robusto: recalcular arrSize como número de no-EMPTY */
    int count = 0;
    for (int i = 0; i < CAP; ++i) if (a->arrInt[i] != EMPTY) ++count;
    a->arrSize = count;
    /* actualizar suma */
    int sum = 0;
    for (int i = 0; i < CAP; ++i) if (a->arrInt[i] != EMPTY) sum += a->arrInt[i];
    a->arrAdd = sum;
    return 0;
}

/* Devuelve arrSize, o -1 si error (puntero nulo) */
int getArrSize(const arrayLength_t *a) {
    if (!a) return -1;
    return a->arrSize;
}

/* Devuelve arrAdd, o -1 si error (puntero nulo) */
int getArrAdd(const arrayLength_t *a) {
    if (!a) return -1;
    return a->arrAdd;
}

/* Devuelve elemento en posición pos si está dentro de límites y ocupado.
   Si error o posición vacía: devuelve -1 (ojo: -1 es sentinel, valores válidos son >=0). */
int getElement(const arrayLength_t *a, int pos) {
    if (!a) return -1;
    if (pos < 0 || pos >= CAP) return -1;
    if (a->arrInt[pos] == EMPTY) return -1;
    return a->arrInt[pos];
}

/* Sustituye el elemento en posición pos por value (value >= 0),
   solo si pos está en rango y actualmente ocupado (no EMPTY).
   Actualiza arrAdd en consecuencia.
   Devuelve 0 éxito, -1 error (pos fuera, pos vacía, value negativo, puntero nulo). */
int setElement(arrayLength_t *a, int pos, int value) {
    if (!a) return -1;
    if (pos < 0 || pos >= CAP) return -1;
    if (value < 0) return -1; /* decisión: aceptamos >=0 */
    if (a->arrInt[pos] == EMPTY) return -1; /* posición no ocupada */
    int old = a->arrInt[pos];
    a->arrInt[pos] = value;
    /* actualizar arrAdd rápidamente */
    a->arrAdd = a->arrAdd - old + value;
    return 0;
}

/* Vuelve a estado inicial (todo EMPTY, arrSize=0, arrAdd=0) */
int resetArr(arrayLength_t *a) {
    return initArray(a);
}

/* MAIN: realiza los apartados a)---h) del enunciado (Ejercicio 10) */
int main(void) {
    arrayLength_t al1, al2;

    /* a) declarar y b) inicializar y rellenar al1 con 0,10,20,...,90 */
    initArray(&al1);
    initArray(&al2);

    for (int i = 0; i < 10; ++i) {
        addElement(&al1, i * 10); /* 0,10,...,90 */
    }

    /* c) mostrar al1 */
    printf(" al1 tras anadir 0,10,...,90:\n");
    printArr(&al1);

    /* d) actualizar posiciones impares para almacenar 1,3,5,7,9 respectivamente
       (pos 1 <- 1, pos 3 <- 3, pos 5 <- 5, pos 7 <- 7, pos 9 <- 9) */
    setElement(&al1, 1, 1);
    setElement(&al1, 3, 3);
    setElement(&al1, 5, 5);
    setElement(&al1, 7, 7);
    setElement(&al1, 9, 9);

    /* e) mostrar de nuevo al1 */
    printf(" al1 tras actualizar impares a 1,3,5,7,9:\n");
    printArr(&al1);

    /* f) añadir al2 las posiciones pares de al1 de forma consecutiva */
    /* posiciones pares: 0,2,4,6,8 */
    for (int pos = 0; pos < CAP; pos += 2) {
        int val = getElement(&al1, pos);
        if (val != -1) addElement(&al2, val);
    }

    /* g) actualizar las posiciones finales del array de al2 para que almacenen 0..4
       Interpreto "posiciones finales" como las que ahora ocupan (0..4) ya que hay 5 elementos. */
    for (int i = 0; i < getArrSize(&al2); ++i) {
        setElement(&al2, i, i); /* posición i <- i (0..4) */
    }

    /* h) mostrar al2 */
    printf(" al2 final:\n");
    printArr(&al2);

    return 0;
}
