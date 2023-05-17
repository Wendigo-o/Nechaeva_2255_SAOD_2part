#include <iostream>

class Test {
  public:
    int value;
    Test() {
      value = 0;
      std::cout << this << " Created " << std::endl;
    }
    ~Test() {
      std::cout << this << " Deleted " << std::endl;
    }
    void get_value() {
      std::cout << this << " Value = " << val << std::endl;
    }
};

