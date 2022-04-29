#include <iostream>
#include <stack>
using namespace std;

int F(int n)
{
    if(n<=1) return 1;
    int a=n+F(n-1);
    int b=n*F(n/2);
    int c=n-2-(a+b)%2;
    int d=F(c);
    return a+b+d;
}

enum callType{a,b,d,Base};
struct call{
    int n;        //Parameter Variable
    int a,b,c,d;  //Local Variable
    int result;   //return Variable
    callType type; //recursion Type
    call(){
        n=1;
        a=1;
        b=1;
        c=0;
        d=1;
        result=0;
        type=Base;
    }
};
int iterativeF(int n){
    int result=1;
    bool enter= false;
    call c; c.n=n; c.result=-1; c.type=Base; //first call with Parameter variable
    stack<call> softStack;  //create stack
    softStack.push(c);      //push first function to stack ex if n=5  => f(5);

    while (!softStack.empty()){
        call nwCall = softStack.top(); //f(5);
        if (nwCall.n<=1)
        {
            softStack.pop(); //pop f(1)
            if (nwCall.type==b)//if element that deleted from stack is f(n/2)
            {
                call obj1 = softStack.top();
                softStack.pop(); //delete f(C)

                softStack.top().a+=softStack.top().n; //calculate (a) ----> f(2)
                softStack.top().b*=softStack.top().n; //calculate (b) ----> f(2)
                softStack.top().c=softStack.top().n-2-(softStack.top().a+softStack.top().b)%2; //calculate (c) ----> f(2)
                int N_for_d=softStack.top().c;

                obj1.n=N_for_d; //set (c) for (d=f(c))
                softStack.push(obj1); //push f(c) to stack
            }
            else if (nwCall.type==d) { enter= true;}
            continue;
        }
        else if (enter)
        {
            result=nwCall.a+nwCall.b+nwCall.d; //calculate return value for recursion function
            softStack.top().result=result; //store result in top of the stack

            softStack.pop();
            if (softStack.size()>=3 && softStack.top().type==b){
                call obj1 = softStack.top();
                softStack.pop(); //delete f(n/2) from stack to store result to (a) value in Base function

                call obj2 = softStack.top();
                softStack.pop(); //delete f(c)

                softStack.top().a = result; //store result to (a) value in Base function
                softStack.top().type=Base;

                softStack.push(obj2); //push f(c)
                softStack.push(obj1); //push f(n/2)
                enter= false;
            } else if (softStack.size()>=2 && softStack.top().type==d){
                call obj1 = softStack.top();
                softStack.pop(); //delete f(C

                softStack.top().b = result;  //store result to (b) value in Base function
                softStack.top().type=Base;
                softStack.top().a+=softStack.top().n; //calculate (a) ----> f(n)
                softStack.top().b*=softStack.top().n; //calculate (b) ----> f(n)
                softStack.top().c=softStack.top().n-2-(softStack.top().a+softStack.top().b)%2; //calculate (c) ----> f(n)
                int N_for_d=softStack.top().c;

                softStack.push(obj1); //push f(c) to stack
                softStack.top().n=N_for_d;//set (c) for (d=f(c))

                enter= false;
            } else if (!softStack.empty() && softStack.top().type==Base){
                softStack.top().d=result; //set result for (d) for f(n)
                enter= true;
            }
            continue;
        }

        call c1; c1.type=a; c1.n=nwCall.n-1;  c1.result=-1;// create call f(n-1)
        call c2; c2.type=b; c2.n=nwCall.n/2;  c2.result=-1;// create call f(n/2)
        call c3; c3.type=d; //create call f(c)

        softStack.push(c3); //push f(C)
        softStack.push(c2); //push f(n/2)
        softStack.push(c1); //push f(n-1)
    }
    return result;
}
int main() {
    int n=20;
    cout<<F(n)<<endl;
    cout<<iterativeF(n)<<endl;
    return 0;
}