#include <iostream>
#include <stack>
using namespace std;

int F(int n)
{
    if(n<=1) return 1;
    int a=n+F(n-1);//f(2)
    int b=n*F(n/2); //f(1)
    int c=n-2-(a+b)%2;//f(c)
    int d=F(c);
    return a+b+d;
}
enum kindOf_Function{Function_a,Function_b,Function_d};
struct call{
    int n;        //Parameter Variable
    int a,b,c,d;  //Local Variable
    int return_value;  //return Variable
    kindOf_Function type; //recursion Type
    call(){
        n=1;
        a=0;
        b=0;
        c=0;
        d=0;
        return_value=0;
    }
};
int iterativeF(int n){ //f(3)
    int result=0;
    bool enter= false;
    call base_function; base_function.n=n; //first call with Parameter variable
    stack<call> softStack;  //create stack
    softStack.push(base_function);      //push first function to stack ex if n=5  => f(5);

    while (!softStack.empty()){
        call nwCall = softStack.top(); //f(2);
        if (nwCall.n<=1)
        {
            call obj=softStack.top();
            softStack.pop();
            if (softStack.empty()) result=1;
            else if (obj.type==Function_a){
                softStack.top().a=softStack.top().n+1;//a=3
            }else if (obj.type==Function_b){
                softStack.top().b=softStack.top().n;
                softStack.top().c=softStack.top().n-2-(softStack.top().a+softStack.top().b)%2;
            }else if (obj.type==Function_d){
                softStack.top().d=1;
                enter= true ;
            }
            continue;
        }
        else if (enter){//f(2)
            softStack.top().return_value=softStack.top().a+softStack.top().b+softStack.top().d;
            result=softStack.top().return_value;
            if (softStack.size()==1) { softStack.pop(); continue; }

            call obj=softStack.top();//f(2)
            softStack.pop();
            if (obj.type==Function_a){
                softStack.top().a=softStack.top().n+result;
                enter= false;
            }else if (obj.type==Function_b){
                softStack.top().b=softStack.top().n*result;
                softStack.top().c=softStack.top().n-2-(softStack.top().a+softStack.top().b)%2;
                enter= false;
            }else if (obj.type==Function_d){
                enter= true;
                softStack.top().d=result;
            }
            continue;
        }
        call c;
        if (nwCall.a==0){
            c.type=Function_a;
            c.n=nwCall.n-1;//f(n-1)
        } else if (nwCall.b==0){
            c.type=Function_b;
            c.n=nwCall.n/2;
        }else if (nwCall.d==0){
            c.type=Function_d;
            c.n=nwCall.c;
        }
        softStack.push(c);
    }
    return result;
}
int main()
{
    for (int i = 1; i <= 20; i++) {
        cout<<"i = "<<F(i)<<"    ";
        cout<<"i = "<<iterativeF(i)<<endl;
    }
    return 0;
}