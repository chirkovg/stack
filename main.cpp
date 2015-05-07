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
    mystack_t<double> st(10);
    st.push(15.3);
    st.push(100);
    st.push(3.14);
    st.pop();
    st.dump("dump1.txt");
}

