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
    int n,a,b,c,d,result;
    callType type;
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
    call c; c.n=n; c.result=-1; c.type=Base;
    stack<call> softStack;  softStack.push(c); //f(5)

    while (!softStack.empty()){
        call nwCall = softStack.top(); //f(5);
        if (nwCall.n<=1)
        {
            softStack.pop();
            if (nwCall.type==b) {
                call obj1 = softStack.top();
                softStack.pop();

                softStack.top().a+=softStack.top().n;
                softStack.top().b*=softStack.top().n;
                softStack.top().c=softStack.top().n-2-(softStack.top().a+softStack.top().b)%2;
                int N_for_d=softStack.top().c;

                obj1.n=N_for_d;
                softStack.push(obj1);
            }
            else if (nwCall.type==d) { enter= true;}
            continue;
        }
        else if (enter)
        {
            result=nwCall.a+nwCall.b+nwCall.d;
            softStack.top().result=result;

            softStack.pop();
            if (softStack.size()>=3 && softStack.top().type==b){
                call obj1 = softStack.top();
                softStack.pop();

                call obj2 = softStack.top();
                softStack.pop();

                softStack.top().a = result;
                softStack.top().type=Base;

                softStack.push(obj2);
                softStack.push(obj1);
                enter= false;
            } else if (softStack.size()>=2 && softStack.top().type==d){
                call obj1 = softStack.top();
                softStack.pop();

                softStack.top().b = result;
                softStack.top().type=Base;
                softStack.top().a+=softStack.top().n;
                softStack.top().b*=softStack.top().n;
                softStack.top().c=softStack.top().n-2-(softStack.top().a+softStack.top().b)%2;
                int N_for_d=softStack.top().c;

                softStack.push(obj1);
                softStack.top().n=N_for_d;

                enter= false;
            } else if (!softStack.empty() && softStack.top().type==Base){
                softStack.top().d=result;
                enter= true;
            }
            continue;
        }

        call c1; c1.type=a; c1.n=nwCall.n-1;  c1.result=-1;//f(n-1)
        call c2; c2.type=b; c2.n=nwCall.n/2;  c2.result=-1;//f(n/2)
        call c3; c3.type=d;

        softStack.push(c3);
        softStack.push(c2);
        softStack.push(c1);
    }
    return result;

}
int main() {
    int n=20;
    cout<<F(n)<<endl;
    cout<<iterativeF(n)<<endl;
    return 0;
}