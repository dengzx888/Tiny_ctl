//
// Created by xjs on 2020/9/29.
//

#include "tctl_slist.h"
#include "tctl_allocator.h"
#include "tctl_common.h"
#include "memory.h"
//private
static void __insert_after(slist *this, struct __slist_node *node, void *x)
{
    __private_slist *p_private = (__private_slist*)this->__obj_private;
    struct __slist_node *new_node = allocate(sizeof(struct __slist_node) + p_private->memb_size);
    new_node->next = node->next;
    node->next = new_node;
    memcpy(new_node->data, x, p_private->memb_size);
}

static void __erase_after(slist *this, struct __slist_node *node)
{
    __private_slist *p_private = (__private_slist*)this->__obj_private;
    struct __slist_node *old_node = node->next;
    node->next = old_node->next;
    deallocate(old_node, sizeof(struct __slist_node) + p_private->memb_size);
}

//public
static const __iterator *begin(void)
{
    slist *this = pop_this();
    __private_slist *p_private = (__private_slist*)this->__obj_private;
    p_private->start_ptr = p_private->head.next ? p_private->head.next->data : NULL;
    return (__iterator*)&p_private->start_iter;
}

static const __iterator *end(void)
{
    slist *this = pop_this();
    __private_slist *p_private = (__private_slist*)this->__obj_private;
    return (__iterator*)&p_private->finish_iter;
}

static size_t size(void)
{
    slist *this = pop_this();
    __private_slist *p_private = (__private_slist*)this->__obj_private;
    size_t count = 0;
    struct __slist_node *node = p_private->head.next;
    while (node)
    {
        node = node->next;
        count++;
    }
    return count;
}

static bool empty(void)
{
    slist *this = pop_this();
    __private_slist *p_private = (__private_slist*)this->__obj_private;
    return !p_private->head.next;
}

static void swap(slist *l)
{
    slist *this = pop_this();
    __private_slist *p_private = (__private_slist*)this->__obj_private;
    __private_slist *p_l_private = (__private_slist*)l->__obj_private;
    if (p_private->memb_size != p_l_private->memb_size)
        return;
    struct __slist_node *node = p_private->head.next;
    p_private->head.next = p_l_private->head.next;
    p_l_private->head.next = node;
}

static void *front(void)
{
    slist *this = pop_this();
    __private_slist *p_private = (__private_slist*)this->__obj_private;
    return p_private->head.next->data;
}

static void push_front(void *x)
{
    slist *this = pop_this();
    __private_slist *p_private = (__private_slist*)this->__obj_private;
    __insert_after(this, &p_private->head, x);
}

static void pop_front(void)
{
    slist *this = pop_this();
    __private_slist *p_private = (__private_slist*)this->__obj_private;
    __erase_after(this, &p_private->head);
}

static __iterator *insert_after(__iterator *iter, void *x)
{
    slist *this = pop_this();
    struct __slist_node *node = container_of(iter->val, struct __slist_node, data);
    __insert_after(this, node, x);
    return iter;
}

static __iterator *erase_after(__iterator *iter)
{
    slist *this = pop_this();
    struct __slist_node *node = container_of(iter->val, struct __slist_node, data);
    __erase_after(this, node);
    return iter;
}

static void clear(void)
{
    slist *this = pop_this();
    while (!THIS(this).empty())
        THIS(this).pop_front();
}

static void iter_increment(__iterator *p)
{
    pop_this();
    struct __slist_node *node = container_of(p->val, struct __slist_node, data);
    p->val = node->next ? node->next->data : NULL;
}

static bool iter_equal(const __iterator *it1, const __iterator *it2)
{
    return it1->val == it2->val;
}

static const __iterator_obj_func __def_slist_iter = {
        NULL,
        iter_increment,
        NULL,
        NULL,
        NULL,
        NULL,
        iter_equal
};
static const iterator_func __def_slist_iter_func = INIT_ITER_FUNC(&__def_slist_iter);
static const slist __def_slist = {
        begin,
        end,
        size,
        empty,
        swap,
        front,
        push_front,
        pop_front,
        insert_after,
        erase_after,
        clear,
};
void init_slist(slist *p_slist, size_t memb_size)
{
    *p_slist = __def_slist;
    __private_slist *p_private = (__private_slist*)p_slist->__obj_private;
    p_private->head.next = NULL;
    p_private->memb_size = memb_size;
    p_private->start_iter = __creat_iter(sizeof(__slist_iter), p_slist, memb_size, &__def_slist_iter_func);
    p_private->finish_iter = __creat_iter(sizeof(__slist_iter), p_slist, memb_size, &__def_slist_iter_func);
    p_private->finish_ptr = NULL;
    p_private->start_ptr = NULL;
}

void destory_slist(slist *p_list)
{
    THIS(p_list).clear();
}

slist creat_slist(size_t memb_size)
{
    slist sl;
    init_slist(&sl, memb_size);
    return sl;
}