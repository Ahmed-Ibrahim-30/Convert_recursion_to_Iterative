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
    int n=1,a=1,b=1,c=0,d=1,result=0;
    callType type;
};
int iterativeF(int n){
    int first=-1,second=-1,third=1,result=1;
    bool enter= false;
    call c;
    c.n=n; c.result=-1; c.type=Base;
    stack<call> softStack;
    softStack.push(c); //f(5)

    while (!softStack.empty()){
        call nwCall = softStack.top(); //f(5);
        if (nwCall.n<=1)
        {
            softStack.pop();
            if (nwCall.type==a) { first=1;}
            else if (nwCall.type==b) { second=1;
                int n=softStack.top().n+1;
                int a=n+softStack.top().a;
                int b=n*softStack.top().b;
                int c=n-2-(a+b)%2;
                softStack.top().a=1;
                softStack.top().b=1;
                softStack.top().d=1;
                softStack.top().n=c;
                softStack.top().c=c;
            }
            else if (nwCall.type==d) { third=1; enter= true;}
            continue;
        }

        if (nwCall.type==a && first!=-1) //f(2)
        {
            nwCall.a+=nwCall.n; //a =3
            nwCall.b*=nwCall.n; // b=2
            nwCall.c=softStack.top().n-2-(nwCall.a+nwCall.b)%2;
            nwCall.d=third;
            result=(nwCall.a)+(nwCall.b)+(nwCall.d);
            softStack.pop();

            call obj1 = softStack.top();
            softStack.pop();

            call obj2 = softStack.top();
            obj2.a = result;
            softStack.pop();

            softStack.top().a = result;
            softStack.top().type=Base;

            softStack.push(obj2);
            softStack.push(obj1);

            second=-1;
            first=-1;
            continue;
        }
        else if (nwCall.type==b && second!=-1) //f(2)
        {
            nwCall.a+=nwCall.n; //result =3
            nwCall.b*=nwCall.n;
            result=nwCall.a+nwCall.b+nwCall.d;

            softStack.pop();

            softStack.top().b = result;

            call obj1 = softStack.top();
            softStack.pop();

            softStack.top().b = result;
            softStack.top().type=Base;
            int n=softStack.top().n;

            softStack.push(obj1);//d
            softStack.top().n=n;

            //calculate c
            int a=softStack.top().n+softStack.top().a;
            int b=softStack.top().n*softStack.top().b;
            int c=softStack.top().n-2-(a+b)%2;
            softStack.top().n=c;
            softStack.top().a=1;
            softStack.top().b=1;
            softStack.top().d=1;
            if (c>2)softStack.top().type=Base;
            enter= true;
            third=-1;
            first=-1;
            continue;
        } else if (nwCall.type==d  && third!=-1){ ////f(2)
            nwCall.a+=nwCall.n; //result =3
            nwCall.b*=nwCall.n;
            result=nwCall.a+nwCall.b+nwCall.d;

            softStack.pop();
            softStack.top().d=result;
            continue;
        }
        else if (nwCall.type==Base &&  enter)
        {
            nwCall.a+=nwCall.n; //result =3
            nwCall.b*=nwCall.n;
            result=nwCall.a+nwCall.b+nwCall.d;
            softStack.top().result=result;

            softStack.pop();
            if (softStack.size()>=3 && softStack.top().type==b){
                call obj1 = softStack.top();
                softStack.pop();

                call obj2 = softStack.top();
                obj2.a = result;
                softStack.pop();

                softStack.top().a = result;
                softStack.top().type=Base;

                softStack.push(obj2);
                softStack.push(obj1);
                enter= false;
            } else if (softStack.size()>=2 && softStack.top().type==d){
                softStack.top().b = result;
                call obj1 = softStack.top();
                softStack.pop();

                softStack.top().b = result;
                softStack.top().type=Base;
                int n=softStack.top().n;
                softStack.push(obj1);
                softStack.top().n=n;

                //calculate c
                int a=softStack.top().n+softStack.top().a;
                int b=softStack.top().n*softStack.top().b;
                int c=softStack.top().n-2-(a+b)%2;
                softStack.top().a=1;
                softStack.top().b=1;
                softStack.top().d=1;
                if (c>2)softStack.top().type=Base;
                softStack.top().n=c;
                enter= false;
            } else if (!softStack.empty() && softStack.top().type==Base){

                softStack.top().d=result;
                enter= true;
            }
            second=-1;
            first=-1;
            third=-1;
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
    int n=40;
    cout<<F(n)<<endl;
    cout<<iterativeF(n)<<endl;
    return 0;
}