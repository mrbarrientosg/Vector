//
//  vector.c
//  Vector
//
//  Created by Matias Barrientos on 1/22/19.
//  Copyright © 2019 Matias Barrientos. All rights reserved.
//

#include "vector.h"
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

struct vector {
    const void **array;
    unsigned long size;
    unsigned long capacity;
    vector_release_object_callback release;
};

static void
vector_growth (vector *vector) {
    if ( !((vector->size + 1) >= vector->capacity) )
        return;
    
    vector->capacity *= 2;
    
    const void **new_array = (const void **) realloc(vector->array, sizeof (const void *) * vector->capacity);
    
    assert (new_array != NULL);
    
    vector->array = new_array;
}

vector *
vector_init (vector_release_object_callback release) {
    vector *vec = (vector *) malloc (sizeof (vector));
    
    if (vec == NULL)
        return NULL;
    
    vec->size = 0;
    vec->capacity = 1;
    vec->release = release;
    vec->array = (const void **) malloc (sizeof (const void *) * 1);
    
    if (vec->array == NULL) {
        free (vec);
        return NULL;
    }
    
    return vec;
}

void
vector_append (vector *vector, const void *data) {
    vector_insert_at(vector, data, vector->size);
}

void
vector_insert_at (vector *vector, const void *data, unsigned long idx) {
    assert (vector != NULL);
    assert (idx <= vector->size);
    
    vector_growth (vector);
    
    if (idx < vector->size)
        memmove ((vector->array + (idx + 1)), vector->array + idx, sizeof (const void *) * vector->size);
    
    vector->array[idx] = data;
    vector->size++;
}

void *
vector_remove_at (vector *vector, unsigned long idx) {
    assert (vector != NULL);
    
    if (idx >= vector->size)
        return NULL;
    
    void *data = (void *) vector->array[idx];
    
    if (idx < vector->size - 1) {
        memmove (vector->array + idx, (vector->array + (idx + 1)), sizeof (const void *) * vector->size - (idx + 1));
    } else {
        vector->array[idx] = NULL;
    }
    
    if (vector->release != NULL) {
        vector->release (data);
        return NULL;
    }
    
    vector->size -= 1;
    
    return data;
}

void *
vector_remove (vector *vector, const void *data, vector_compare_callback compare) {
    assert (vector != NULL);
    
    unsigned long i;
    
    for (i = 0; i < vector->size; ++i) {
        if (compare (vector->array[i], data) == 0)
            break;
    }
    
    if (vector->size == i)
        return NULL;
    
    return vector_remove_at(vector, i);
}

void *
vector_get_at (vector *vector, unsigned long idx) {
    if (idx >= vector->size)
        return NULL;
    
    return (void *) vector->array[idx];
}

void *
vector_first (vector *vector) {
    if (vector == NULL)
        return NULL;
    
    return (void *) vector->array[0];
}

void *
vector_last (vector *vector) {
    if (vector == NULL)
        return NULL;
    
    return (void *) vector->array[(vector->size - 1)];
}


unsigned long
vector_size (vector *vector) {
    if (vector == NULL)
        return 0;
    
    return vector->size;
}

void
vector_sort (vector *vector, vector_compare_callback compare) {
    assert (vector != NULL);

    qsort (vector->array, vector->size, sizeof (const void *), compare);
}

void *
vector_bsearch (vector *vector, const void *key, vector_compare_callback compare) {
    assert (vector != NULL);
    
    const void **base = vector->array;
    const void **pivot;
    int result;
    unsigned long num = vector->size;
    
    while (num > 0) {
        pivot = base + (num >> 1);
        result = compare (key, *pivot);
        
        if (result == 0)
            return (void *)(*pivot);
        
        if (result > 0) {
            base = pivot + 1;
            num--;
        }
        num >>= 1;
    }
    
    return NULL;
}

void *
vector_search (vector *vector, const void *key, vector_compare_callback compare) {
    assert (vector != NULL);

    unsigned long i;
    
    for (i = 0; i < vector->size; ++i) {
        if (compare (vector->array[i], key) == 0)
            return (void *) vector->array[i];
    }
    
    return NULL;
}

void
vector_release (vector **vector) {
    assert (vector != NULL);
    assert (*vector != NULL);
    
    free((*vector)->array);
    free(*vector);
    *vector = NULL;
}
