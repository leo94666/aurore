#include "queue.h"


const obj_class_t  g_queue_class={
        .vtable=NULL,
        .base_class=NULL,
        .constructor_cb=queue_constructor,
        .instance_size=sizeof(queue_obj_t),
        .class_name="queue"
};

void queue_constructor(obj_t *obj, obj_constructor_args_t *args) {
    queue_constructor_args_t *queue_args = (queue_constructor_args_t *)args;

    if (obj)
    {
        queue_obj_t *ret = (queue_obj_t *)obj;
        ret->item_size = *(queue_args->item_size);
        ret->queue_length = 0;
    }
}



void queue_delete(queue_obj_t *obj) {

}

/**
 *
 * @param obj
 * @param node
 * @return
 */
bool queue_add(queue_obj_t *obj, const queue_item_t *node) {
    return 0;
}

