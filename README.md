# cpp_result
simple c++ header-only implementation of rust's std::result type 

# Using cpp_result
Add the `#include` statement for the [result.h](/include/result.h) file in your code like below:
```cpp
#include "cpp_result/include/result.h"
```

# Examples
> the full examples code can be found in the [src/main.cpp](/src/main.cpp) file

```cpp
#include "result.h"

using result::Result, result::Ok, result::Err;
using std::cout, std::endl;

Result<int> read_number();

int main() {
   int result = read_number()
  .and_then([](int n) {
    if (n > 5) {
      return Ok(n);
    }

    const char * too_small = "value must be greater than 5";
    return Err<int>(too_small);
  })
  .or_else([](auto & err) {
    cout << "an error occured: " << err << ", defaulting to 10" << endl;

    return Ok(10);
  })
  ._and_then(Ok(x * 2)) // `_and_then` macro. Expands to: and_then([&](auto x) { return Ok(x * 2); })
  .unwrap_or(-1);

  cout << result << endl; // prints 20 if `read_number` return value is lower than 5, or `read_number() * 2`. 

  return 0;
}
```

or a simpler example
```cpp
const char * error_message = "error";
int result = Err<int>(error_message)
  .and(Ok(10))
  .unwrap_or(50);

cout << result << endl; // will print 50
```