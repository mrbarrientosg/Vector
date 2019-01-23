//
//  vector.h
//  Vector
//
//  Created by Matias Barrientos on 1/22/19.
//  Copyright © 2019 Matias Barrientos. All rights reserved.
//

#ifndef vector_h
#define vector_h

typedef struct vector vector;

typedef void (*vector_release_object_callback)(void *object);

typedef int (*vector_compare_callback)(const void *v1, const void *v2);

extern vector *vector_init (vector_release_object_callback release);

extern void vector_append (vector *v, const void *data);

extern void vector_insert_at (vector *vector, const void *data, unsigned long idx);

extern void *vector_remove_at (vector *vector, unsigned long idx);

extern void *vector_remove (vector *vector, const void *data, vector_compare_callback compare);

extern void *vector_get_at (vector *vector, unsigned long idx);

extern unsigned long vector_size (vector *vector);

extern void vector_sort (vector *vector, vector_compare_callback compare);

extern void *vector_bsearch (vector *vector, const void *key, vector_compare_callback compare);

extern void *vector_search (vector *vector, const void *key, vector_compare_callback compare);

extern void *vector_first (vector *vector);

extern void *vector_last (vector *vector);

extern void vector_release (vector **vector);

#endif /* vector_h */
