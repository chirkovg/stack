//
//  mystack.h
//  Stack
//
//  Created by Григорий Чирков on 04.03.15.
//  Copyright (c) 2015 Григорий Чирков. All rights reserved.
//

#ifndef Stack_stack_h
#define Stack_stack_h

#include <fstream>
#include <iostream>
#include <assert.h>

enum sterr {NOERROR = 0, MEMORYERROR = 1, NOELEMENTS = 2,
            WRONGCOUNTER = 3, WRONGSIZE = 4, WRONGPOINTER = 5};
#define MAXERROR WRONGPOINTER

const char* MYSTACKERROR[] = {"No error", "Error with memory allocation", "No elements to pop from stack", "The counter of stack is wrong", "Stack has wrong size", "Stack has wrong data pointer"};

const size_t STSTACKSIZE = 10;

template <typename data_t> class mystack_t;
template <typename data_t>
std::ostream& operator << (std::ostream& output, mystack_t<data_t>& st);

class stack_exception : std::exception
{
public:
    stack_exception(sterr errorarg):
    error(errorarg)
    {
        
    }
    virtual const char* what()
    {
        if (error < 0 || error > MAXERROR)
        {
            return "Error in error type";
        }
        return MYSTACKERROR[error];
    }
private:
    sterr error;
    stack_exception();
};

template <typename data_t>
class mystack_t
{
public:
    mystack_t();
    mystack_t(size_t size);
    ~mystack_t();
    bool push(data_t newelem);
    data_t pop();
    bool ok();
    void dump(const char* filename);
    void dump();
    const char* what() const;
    sterr geterror() const;
    friend std::ostream& operator << <>(std::ostream& output, mystack_t<data_t>& st);
    mystack_t<data_t> operator = (const mystack_t<data_t> source);
private:
    data_t* data;
    size_t count;
    size_t  size;
    sterr error;
};

template <typename data_t>
mystack_t <data_t>::mystack_t():
count (0),
size (STSTACKSIZE),
error(NOERROR)
{
    try
    {
        data = new data_t[STSTACKSIZE];
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "can't allocate" << STSTACKSIZE*sizeof(data_t) << "bytes for mystack_t" << std::endl;
        size = -1;
        count = -1;
        throw stack_exception(MEMORYERROR);
    }
    memset(data, 0, sizeof(data_t) * size);
    ok();
}

template <typename data_t>
mystack_t<data_t>::mystack_t(size_t size):
count(0),
size (size),
error(NOERROR)
{
    try
    {
        data = new data_t[size];
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "can't allocate" << size*sizeof(data_t) << "bytes for mystack_t" << '\n';
        size = -1;
        count = -1;
        throw stack_exception(MEMORYERROR);
    }
    memset(data, 0, sizeof(data_t) * size);
    ok();
}

template <typename data_t>
mystack_t <data_t>:: ~mystack_t()
{
    if (error != WRONGPOINTER)
    {
        delete[] (this -> data);
    }
    this -> data = nullptr;
    count = 0;
    size = 0;
}

template <typename data_t>
bool mystack_t<data_t>::push(data_t newelem)
{
    if (!ok()) return false;
    if (count == size)
    {
        data_t* newdata = NULL;
        size_t newsize = 0;
        if (size == 0)
        {
            newdata = new data_t[STSTACKSIZE];
            newsize = STSTACKSIZE;
        }
        else
        {
            newdata = new data_t[2*size];
            newsize = 2*size;
        }
        if (!newdata)
        {
            std::cerr << "can't allocate" << newsize*sizeof(data_t) << "bytes for mystack_t" << '\n';
            throw stack_exception(MEMORYERROR);
            return false;
        }
        memcpy(newdata, data, size*sizeof(data_t));
        delete[] data;
        data = newdata;
        size = newsize;
    }
    data[count++] = newelem;
    return ok();
}




template <typename data_t>
data_t mystack_t<data_t>::pop()
{
    if(!ok()) return 0;
    if(count == 0)
    {
        throw stack_exception(NOELEMENTS);
    }
    data_t result = this -> data[--count];
    if (!ok()) return 0;
    return result;
}


template <typename data_t>
bool mystack_t<data_t>::ok()
{
    if (error) return false;
    if (count > size)
    {
        error = WRONGCOUNTER;
        return false;
    }
    if (size <= 0)
    {
        error = WRONGSIZE;
        return false;
    }
    if (!data)
    {
        error = WRONGPOINTER;
        return false;
    }
    return true;
}


template <typename data_t>
sterr mystack_t<data_t>::geterror() const
{
    return error;
}

template <typename data_t>
const char* mystack_t<data_t>::what() const
{
    if (geterror() < 0 || geterror() > MAXERROR)
    {
        return "Error in error type";
    }
    return MYSTACKERROR[geterror()];
}

template <typename data_t>
std::ostream& operator << (std::ostream& output, mystack_t<data_t>& st)
{
    output << "Stack Dump\n";
    output << "Stack_addr = " << &st << '\n';
    output << "Stack_ok = " << st.ok() << '\n';
    output << "Stack_error = " << st.geterror() << ": ";
    output << st.what() << '\n';
    output << "Size of stack = " << st.size << '\n';
    output << "Curent position = " << st.count << '\n';
    output << "Elements:\n";
    for (size_t curpos = 0; curpos < st.size; curpos++)
    {
        output << st.data[curpos] << "\t\t" << st.data + curpos;
        if (curpos == st.count - 1)
        {
            output << "<=";
        }
        output << '\n';
    }
    return output;
}

template<typename data_t>
void mystack_t<data_t>::dump(const char* filename)
{
    if (!filename)
    {
        std::cerr << "Wrong filename in stack_dump";
        return;
    }
    std::ofstream output(filename);
    assert(output);
    output << *this;
    output.close();
}

template <typename data_t>
void mystack_t<data_t>::dump()
{
    std::cout << *this;
}

#endif


