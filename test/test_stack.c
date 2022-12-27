#include "static_stack.h"

int main() {



    int item_size =10;
    int capacity=10;
    stack_obj_t *obj = NULL;
    static_stack_constructor_args_t args = { 0 };

    if ((item_size > 0) && (capacity > 0))
    {
        args.item_size = &item_size;
        args.stack_capacity = &capacity;

        obj = (stack_obj_t *)obj_class_create_obj(&g_static_stack_class, (obj_constructor_args_t *)&args);

        if ((NULL == obj) || (NULL == ((static_stack_obj_t *)obj)->array))
        {
            obj_class_delete_obj((obj_t *)obj);
            obj = NULL;
        }
    }

    log_info("type: %s", OBJECT_NAME(obj));
    //printf("type: %s", OBJECT_NAME(obj));

    log_info("push:");
    for (int i = 0; i < 10; ++i) {
        stack_push(obj, &i);
    }

    log_info("pop:");
    while (stack_size(obj)) {
        int temp = 0;
        stack_top(obj, &temp);
        log_info("pop: %d", temp);
        stack_pop(obj);
    }

    return 0;
}