//
//  main.c
//  Vector
//
//  Created by Matias Barrientos on 1/22/19.
//  Copyright © 2019 Matias Barrientos. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int compare(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

int main(int argc, const char * argv[]) {

    vector *v = vector_init(NULL);
    
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    int v5 = 5;
    vector_append (v, &v1);
    vector_append (v, &v2);
    vector_append (v, &v3);
    vector_append (v, &v4);

//    vector_insert_at (v, &v4, 0);
    //vector_insert_at (v, &v4, 4);
    
    int *data = vector_bsearch (v, &v4, compare);
    
    printf("%d\n\n", *data);
    
    for (int i = 0; i < vector_size(v); i++) {
        data = (int *)vector_get_at(v, i);
        printf("%d\n", *data);
    }

    
//    //vector_insert_at(v, NULL, 0);
//
//    int *data = NULL;
//
//    for (int i = 0; i < 10; i++) {
//        data = malloc(sizeof(int));
//        *data = i;
//        vector_append(v, data);
//    }
//
//    for (int i = 0; i < 10; i++) {
//        data = (int *)vector_get_at(v, i);
//        printf("%d\n", *data);
//    }
//
    return 0;
}
