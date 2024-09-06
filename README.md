# base64 encoding/decoding library

Header-only library written in the C++. Provides encoding and decoding functions.
Decoding can be performed in two ways: using flag variable to catch exceptions, and standard exceptions.

## Getting Started

### Dependencies

* C++20 or higher

### Example of usage

* Encoding
```
base64::encode({"base64 encoder"})
```

* Decoding with exceptions
```
base64::decode({"YmFzZTY0IGVuY29kZXI="})
```

* Decoding with flag variable
If an exception is caught, the value of the иoolean variable will be changed to false
```
bool flag;
base64::decode({"YmFzZTY0IGVuY29kZXI="}, flag)
```

## Authors
  
[@Dmitriy](punov.dv@phystech.edu)
[@Alexandr](https://github.com/aasirotkin)

## License

This project is licensed under the MIT License - see the LICENSE.md file for detail
