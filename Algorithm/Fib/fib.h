//
//  fib.h
//  斐波拉契数列
//
//  Created by maochongxin on 2018/10/17.
//  Copyright © 2018 Maochongxin. All rights reserved.
//

#ifdef Fib
#define Fib

template <int N>
struct Fib {
    enum { value = Fib<N - 1>::value + Fib<N - 2>::value };
};

template<> struct Fib<1> {
    enum { value = 1 };
};

template<> struct Fib<2> {
    enum { value = 1 };
};
#endif
