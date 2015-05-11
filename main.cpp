//
//  main.cpp
//  Stack
//
//  Created by Григорий Чирков on 04.03.15.
//  Copyright (c) 2015 Григорий Чирков. All rights reserved.
//
#include "mystack.h"

int main()
{
    mystack_t<int> st;
    st.push(5);
    st.push(10);
    int res = st.pop();
    st.dump("/Users/chirkovg/stack");
    std::cout << res << '\n';
    res = st.pop();
    std::cout << res;
}

