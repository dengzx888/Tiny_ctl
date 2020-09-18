#include <stdio.h>
#include "tctl_allocator.h"
#include "tctl_object.h"
#include "tctl_common.h"
#include "tctl_iterator.h"
#include "tctl_vector.h"
#include "tctl_list.h"
#include <stdlib.h>

bool cmp(int *a, int *b)
{
    return *a > *b;
}

int main(void)
{
    vector v;
    init_vector(&v, 0, sizeof(int), NULL);
    printf("%p", &v);
    for (int i = 0; i < 10; i++) {
        int temp = i;
        THIS(&v).push_back(&temp);
    }
    for (ITER_TYPE(int) it = NEW_ITER(THIS(&v).begin()); *it != *THIS(&v).end(); ITER(it).increment()) {
        printf("%d\n", **it);
    }
    putchar('\n');
}

// list测试
/*
int main(void)
{
    list l;
    init_list(&l, sizeof(int));
    int temp = 1;
    for (int i = 0; i < 10; i++) {
        THIS(&l).push_back(&i);
    }
    for (int i = 0; i < 5; i++) {
        THIS(&l).pop_back();
    }
    int temp1 = 20;
    THIS(&l).pop_front();
    THIS(&l).push_front(&temp1);
    list_iter iter = *(list_iter*)THIS(&l).begin();
    THIS(&l).insert(&iter, &temp);
    printf("first\n");
    for (ITER_TYPE(int) it = NEW_ITER(THIS(&l).begin()); *it != *THIS(&l).end(); ITER(it).increment()) {
        printf("%d\n", **it);
        //THIS(&l).insert(*it, &temp);
    }
    THIS(&l).remove(&temp1);
    temp1 = 4;
    THIS(&l).push_back(&temp1);
    printf("second\n");
    for (ITER_TYPE(int) it = NEW_ITER(THIS(&l).begin()); *it != *THIS(&l).end(); ITER(it).increment()) {
        printf("%d\n", **it);
    }
    THIS(&l).unique();
    printf("third\n");
    ITER_TYPE(int) r_it = NEW_ITER(THIS(&l).end());
    ITER(r_it).decrement();
    printf("%d\n", *(int*)ITER(r_it).decrement());
    for (; *r_it != *THIS(&l).end(); ITER(r_it).decrement()) {
        printf("%d\n", **r_it);
    }
    list l2;
    init_list(&l2, sizeof(int));
    for (int i = 10; i < 20; i++)
        THIS(&l2).push_back(&i);
    printf("splice\n");
    THIS(&l).splice(THIS(&l).begin(), &l2, THIS(&l2).begin(), THIS(&l2).end());
    for (ITER_TYPE(int) it = NEW_ITER(THIS(&l).begin()); *it != *THIS(&l).end(); ITER(it).increment()) {
        printf("%d\n", **it);
    }
    printf("reverse\n");
    THIS(&l).reverse();
    for (ITER_TYPE(int) it = NEW_ITER(THIS(&l).begin()); *it != *THIS(&l).end(); ITER(it).increment()) {
        printf("%d\n", **it);
    }
    printf("front%d\n", *(int*)THIS(&l).front());
    printf("back%d\n", *(int*)THIS(&l).back());
    printf("size:%d\n", THIS(&l).size());
    printf("merge\n");
    list l1;
    list l3;
    init_list(&l1, sizeof(int));
    init_list(&l3, sizeof(int));
    for (int i = 0; i < 10; i++) {
        THIS(&l1).push_back(&i);
        THIS(&l3).push_back(&i);
    }
    THIS(&l1).merge(&l3, cmp);
    for (ITER_TYPE(int) it = NEW_ITER(THIS(&l1).begin()); *it != *THIS(&l1).end(); ITER(it).increment())
        printf("%d\n", **it);
    printf("sort\n");
    THIS(&l).clear();
    for (int i = 0; i < 10000; i++) {
        temp = (int)random();
        THIS(&l).push_back(&temp);
    }
    THIS(&l).sort(cmp);
    for (ITER_TYPE(int) it = NEW_ITER(THIS(&l).begin()); *it != *THIS(&l).end(); ITER(it).increment()) {
        printf("%d\n", **it);
    }
    for (int i = 1; i < 10000; i++) {
        if (*(int*)THIS(&l).at(i) < *(int*)THIS(&l).at(i - 1)) {
            printf("bad\n");
            break;
        }
    }
    destory_list(&l);
    return 0;
}
*/
