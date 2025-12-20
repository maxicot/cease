# cease

`cease` is a simplistic C23 library for monadic error-handling.
Refer to `include/cease.h` for documentation.

### Installation

Can be installed with CMake using `FetchContent`.

First, specify its installation in `CMakeLists.txt`:

```
include(FetchContent)

FetchContent_Declare(
    cease
    GIT_REPOSITORY https://github.com/maxicot/cease.git
    GIT_TAG main
)

FetchContent_MakeAvailable(cease)
```

Then it can be treated as a normal library in your CMakeLists.
After you've linked it, you merely need to include it in your C code:

```c
#include "cease.h"
```

### Usage

A simple usage example:

```c
#include "cease.h"

// The return type is `int`
ResultMonad divide(int a, int b) {
    if (b == 0) {
        return result_error(EDOM);
    }

    int result = a / b;
    return result_from_unallocated(&result, sizeof(result));
}

int main() {
    result_unwrap(divide(1, 0)); // panics
}
```
