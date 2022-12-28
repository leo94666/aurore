#include "static_stack.h"


int main() {


    FILE *fp = fopen("./test.txt", "w");
    log_add_fp(fp, LOG_TRACE);


    stack_obj_t *obj = static_stack_create(sizeof(int), 10);

    log_info("type: %s", OBJECT_NAME(obj));

    log_info("=========push:");
    for (int i = 0; i < 10; ++i) {
        stack_push(obj, &i);
        log_info("push:%d", i);
    }


    int temp = 0;
    stack_top(obj, &temp);
    log_info("top: %d", temp);

    log_info("=========pop:");

    while (stack_size(obj)) {
        int temp = 0;
        static_stack_top(obj, &temp);
        log_info("top: %d", temp);
        static_stack_pop(obj);
    }
    stack_delete(obj);

    return 0;
}