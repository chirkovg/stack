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

const size_t STSTACKSIZE = 10;

template <typename data_t>
class mystack_t
{
public:
    mystack_t();
    mystack_t(size_t size);
    ~mystack_t();
    bool push(data_t val);
    data_t pop();
    bool ok();
    void dump();
    sterr geterror();
    friend std::ostream& operator << (std::ostream& out, const mystack_t<data_t>& st);
private:
    data_t* data;
    size_t count;
    size_t  size;
    sterr error;
};

template <typename data_t>
mystack_t <data_t>::mystack_t():
data  (new data_t[STSTACKSIZE]),
count (0),
size (STSTACKSIZE),
error(NOERROR)
{
    if(!data)
    {
        size = -1;
        count = -1;
        error = MEMORYERROR;
    }
    else
        memset(data,0,sizeof(data_t)*STSTACKSIZE);
    ok();
}


template <typename data_t>
mystack_t<data_t>::mystack_t(size_t size):
data(new data_t[size]),
count(0),
size (size),
error(NOERROR)
{
    if (!data)
    {
        size = -1;
        count = -1;
        error = MEMORYERROR;
    }
    else
        memset(data, 0, sizeof(data_t) * size);
    ok();
}

template <typename data_t>
mystack_t <data_t>:: ~mystack_t()
{
    if (ok())
    {
        delete[] this -> data;
        this -> data = nullptr;
        count = -1;
        size = -1;
    }
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
            error = MEMORYERROR;
            return false;
        }
        //for (int i = 0; i < count; i++) newdata[i] = data[i];
        memcpy(newdata, data, size*sizeof(data_t));
        delete[] data;
        data = newdata;
        size = newsize;
    }
    data[count++] = newelem;
    return ok();
}



/*template<>
 void mystack_t<double>::dump()
 {
 FILE* dump = fopen("stackdump.txt", "w");
 assert(dump);
 fprintf(dump, "Stack Dump\n");
 fprintf(dump, "Stack_Ok = %d\n", ok());
 fprintf(dump, "Stack_error = %d\n", geterror());
 fprintf(dump, "Size of Stack = %zu\n", size);
 fprintf(dump, "Elements Count = %lu\n", count);
 fprintf(dump, "Elements:\n");
 for(int i = 0; i < size; i++)
 {
 fprintf(dump, "%3.3lg\t%p\n", data[i], data + i);  //!!!
 }
 fprintf(dump, "End of Dump\n");
 fclose(dump);
 }
 
 template<>
 void mystack_t<int>::dump()
 {
 FILE* dump = fopen("stackdump.txt", "w+");
 assert(dump);
 fprintf(dump, "Stack Dump\n");
 fprintf(dump, "Stack_Ok = %d\n", ok());
 fprintf(dump, "Stack_error = %d\n", geterror());
 fprintf(dump, "Size of Stack = %zu\n", size);
 fprintf(dump, "Elements Count = %lu\n", count);
 fprintf(dump, "Elements:\n");
 for(int i = 0; i < size; i++)
 {
 fprintf(dump, "%3d\t%p\n", data[i], data + i);  //!!!
 }
 fprintf(dump, "End of Dump\n");
 fclose(dump);
 }
 
 template<typename data_t>
 void mystack_t<data_t>::dump()
 {
 FILE* dump = fopen("stackdump.txt", "w");
 assert(dump);
 fprintf(dump, "Stack Dump\n");
 fprintf(dump, "Stack_Ok = %d\n", ok());
 fprintf(dump, "Stack_error = %d\n", geterror());
 fprintf(dump, "Size of Stack = %zu\n", size);
 fprintf(dump, "Elements Count = %d\n", count);
 fprintf(dump, "Elements:\n");
 for(int i = 0; i < size; i++)
 {
 fprintf(dump, "%p\n", data + i);  //!!!
 }
 fprintf(dump, "End of Dump\n");
 fclose(dump);
 }*/


template <typename data_t>
data_t mystack_t<data_t>::pop()
{
    if(!ok()) return 0;
    if(count == 0)
    {
        error = NOELEMENTS;
        return 0;
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
sterr mystack_t<data_t>::geterror()
{
    return error;
}

template <typename data_t>
std::ostream& operator << (std::ostream& output, const mystack_t<data_t>& st)
{
    output << "Stack Dump\n";
    output << "Stack_ok = " << st.ok() << '\n';
    output << "Stack_error = " << st.geterror() << '\n';
    output << "Size of stack = " << st.size << '\n';
    output << "Curent position = " << st.count << '\n';
    if (st.size >= 0 && st.count >= 0)
    {
        output << "Elements:\n";
        for (size_t curpos = 0; curpos < st.size; curpos++)
        {
            output << st.data[curpos] << '\t' << st.data + curpos;
        }
    }
    return output;
}

template<typename data_t>
void mystack_t<data_t>::dump()
{
    std::ofstream out("dump.txt");
    assert(out);
    out << this;
    out.close();
}




#endif


