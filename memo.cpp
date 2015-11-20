#include <iostream>
#include <functional>
#include <map>

int factorial(int n){
      std::cout << "called" << std::endl;
      if(n == 1)
	return 1;
      return (n * factorial(n-1));
}

//Version 3
template<class R, class A>
std::function <R (A)> memoize(std::function<R (A)> f){
  std::function <R (A)> memf;
  memf = [&f](A n){
    static std::map<A, R> cache;
    if(cache.find(n) != cache.end()){
      return cache[n];
    }

    R a = f(n);
    cache.insert(std::pair<A, R>(n, a));
    return a;
  };
  return memf;
}

//Version 4
template<class R, class... A>
std::function <R (A...)> memoizem(std::function<R (A...)> f){
  std::function <R (A...)> memf;
  memf = [&f](A... args){
    static std::map<std::tuple<A...>, R> cache;
    std::tuple<A...> t (args...);
    if(cache.find(t) != cache.end()){
      return cache[t];
    }

    R a = f(args...);
    cache.insert(std::pair<std::tuple<A...>, R>(t, a));
    return a;
  };
  return memf;
}

int add(int x, int y){
  std::cout << "called" << std::endl;
  return x+y;
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

  //Version 2
  std::function <int (int)> memfactr;
  memfactr = [&memfactr](int n){
    static std::map<int, int> cache;
    if(cache.find(n) != cache.end()){
      return cache[n];
    }

    std::function <int (int)> factorial = [&memfactr](int n){
      std::cout << "called" << std::endl;
      if(n == 1)
	return 1;
      return (n * memfactr(n-1));
    };

    int a = factorial(n);
    cache.insert(std::pair<int, int>(n, a));
    return a;
  };

  //Version 3
  std::function<int (int)> memfactt = memoize((std::function<int(int)>)factorial);

  //Version 4
  std::function<int (int, int)> addm = memoizem((std::function<int(int, int)>)add);

  //Tests for 1
  std::cout << "Version 1: No templates - does not work with recursion" << std::endl;
  std::cout << memfact(5) << std::endl << std::endl;
  std::cout << memfact(10) << std::endl << std::endl;
  std::cout << memfact(6) << std::endl << std::endl;
  std::cout << memfact(10) << std::endl << std::endl;

  //Tests for 2
  std::cout << "Version 2: No templates for target function - works with recursion" << std::endl;
  std::cout << memfactr(5) << std::endl << std::endl;
  std::cout << memfactr(10) << std::endl << std::endl;
  std::cout << memfactr(6) << std::endl << std::endl;
  std::cout << memfactr(10) << std::endl << std::endl;

  //Tests for 3
  std::cout << "Version 3: Using templates for single argument and returned value - does not work with recursion" << std::endl;
  std::cout << memfactt(5) << std::endl << std::endl;
  std::cout << memfactt(10) << std::endl << std::endl;
  std::cout << memfactt(6) << std::endl << std::endl;
  std::cout << memfactt(10) << std::endl << std::endl;

  //Tests for 4
  std::cout << "Version 4: Templates for multiple arguments - does not work with recursion" << std::endl;
  std::cout << addm(5, 6) << std::endl;
  std::cout << addm(5, 6) << std::endl;
  return 0;
}
