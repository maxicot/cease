#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/cease.h"

ResultMonad result_from_allocated(const void* value) {
    ResultMonad result = {RESULT_OK, value};
    return result;
}

ResultMonad result_error(int error_code) {
    ResultMonad result = {error_code, nullptr};
    return result;
}

ResultMonad result_from_unallocated(const void* value, size_t size) {
    int error_code = 0;
    void* ptr = malloc(size);

    if (!ptr) {
        error_code = ENOMEM;
    }

    memcpy(ptr, value, size);

    ResultMonad result = {error_code, ptr};
    return result;
}

void* result_unwrap(ResultMonad result) {
    if (result.status == RESULT_OK) {
        return result.value;
    } else {
        fprintf(stderr, "panic: called `result_unwrap` on an error value: %d\n", result.status);
        exit(result.status);
    }
}

bool result_is_ok(ResultMonad result) {
    return result.status == RESULT_OK;
}

ResultMonad result_map(ResultMonad result, void* (*morphism)(void*)) {
    if (result.status == RESULT_OK) {
        ResultMonad new = {RESULT_OK, morphism(result.value)};
    } else {
        return result;
    }
}
