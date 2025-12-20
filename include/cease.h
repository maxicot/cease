#pragma once
#include <errno.h>
#include <stddef.h>
#define RESULT_OK 0
#define RESULT_NONE -1

/// A monad for error-handling.
/// Contains an `errno`-compatible `status` field.
/// The `value` field is a pointer to a heap-allocated value.
/// Note that it's type-unsafe and memory-unsafe.
/// The user must at all times be informed at what type `value` points.
typedef struct ResultMonad {
    int status;
    void* value;
} ResultMonad;

/// Construct a `ResultMonad` from a pointer to a heap-allocated value
ResultMonad result_from_allocated(const void* value);

/// Allocate `size` bytes on the heap and copy bytes from `value` into it.
/// Yields `ENOMEM` in case `malloc` returns a null pointer.
ResultMonad result_from_unallocated(const void* value, size_t size);

/// Return a `ResultMonad` with a null-pointer and the given `error_code` as the error.
ResultMonad result_error(int error_code);

/// Terminate the program in case `status` is not `RESULT_OK`.
/// Return the pointer to the value otherwise.
/// Note that properly handling the error instead is advised.
void* result_unwrap(ResultMonad result);

/// Check whether `status` is `RESULT_OK`.
bool result_is_ok(ResultMonad result);

/// Apply the given function to `value` in case `status` is `RESULT_OK`.
/// Return the original result otherwise.
ResultMonad result_map(ResultMonad result, void* (*morphism)(void*));
