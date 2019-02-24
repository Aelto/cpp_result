#include <iostream>

#include "result.h"

using result::Result, result::Ok, result::Err;
using std::cout, std::endl, std::string, std::cin;

Result<int> read_number() {
  int n = 0;
  cout << "n: ";
  cin >> n;

  return Ok(n);
};

int main() {
  {
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

    cout << result << endl; // prints 20 if input is lower than 5, or input * 2
  }

  {
    const char * error_message = "error";
    int result = Err<int>(error_message)
      .and(Ok(10))
      .unwrap_or(50);

    cout << result << endl; // will print 50
  }
  
  return 0;
}