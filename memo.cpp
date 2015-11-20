#include <iostream>
#include <functional>
#include <map>

int factorial(int n){
      std::cout << "called" << std::endl;
      if(n == 1)
	return 1;
      return (n * factorial(n-1));
}


int main(int argc, char **argv){
  //Version 1
  std::function <int (int)> memfact = [](int n){
    static std::map<int, int> cache;
    if(cache.find(n) != cache.end()){
      return cache[n];
    }

    int a = factorial(n);
    cache.insert(std::pair<int, int>(n, a));
    return a;
  };

  //Tests for 1
  std::cout << "Version 1: No templates - does not work with recursion" << std::endl;
  std::cout << memfact(5) << std::endl << std::endl;
  std::cout << memfact(10) << std::endl << std::endl;
  std::cout << memfact(6) << std::endl << std::endl;
  std::cout << memfact(10) << std::endl << std::endl;
  return 0;
}
