#include<iostream>
#include<math.h>
#include<stack>

using namespace std;
class Rekenmachine{
    private:
        stack<double> thestack;
    public:
        Rekenmachine(){}
        void addElement(string element);
        void clear();
        void sqrt();
        void kwadraat();
        void sum();
        void minus();
        void product();
        void divide();
        void process(string input);
        void print_stack();
};

void Rekenmachine::process(string input){
    char operand = input.c_str()[0];

    switch(operand){
        case '+':
            sum();
            break;
        case '-':
            minus();
            break;
        case '*':
            product();
            break;
        case '/':
            divide();
            break;
        case 's':
            sqrt();
            break;
        case 'v':
            kwadraat();
            break;
        case 'c':
            clear();
            break;
        default:
            addElement(input);
            break;
    }
    print_stack();
}
void Rekenmachine::minus(){
    double element1 = thestack.top();
    if(element1){
        thestack.pop();
        double element2 = thestack.top();
        if(element2){
            thestack.pop();
            double verschil = element1-element2;
            thestack.push(verschil);
        }
        else{
            cout<<": ERROR: not enough elements on stack"<<endl;
            thestack.push(element1);
        }
    }
    else{
        cout<<": ERROR: not enough elements on stack"<<endl;
    }
}

void Rekenmachine::sum(){
    if(!thestack.empty()){
        double element1 = thestack.top();
        thestack.pop();
        if(!thestack.empty()){
            double element2 = thestack.top();
            thestack.pop();
            double som = element1+element2;
            thestack.push(som);
        }
        else{
            cout<<": ERROR: not enough elements on stack"<<endl;
            thestack.push(element1);
        }
    }
    else{
        cout<<": ERROR: not enough elements on stack"<<endl;
    }
}

void Rekenmachine::divide(){
    if(!thestack.empty()){
        double element1 = thestack.top();
        thestack.pop();
        if(!thestack.empty()){
            double element2 = thestack.top();
            thestack.pop();
            double quotient = element1/element2;
            thestack.push(quotient);
        }
        else{
            cout<<": ERROR: not enough elements on stack"<<endl;
            thestack.push(element1);
        }
    }
    else{
        cout<<": ERROR: not enough elements on stack"<<endl;
    }
}
void Rekenmachine::product(){
    if(!thestack.empty()){
        double element1 = thestack.top();
        thestack.pop();
        if(!thestack.empty()){
            double element2 = thestack.top();
            thestack.pop();
            double product = element1*element2;
            thestack.push(product);
        }
        else{
            cout<<": ERROR: not enough elements on stack"<<endl;
            thestack.push(element1);
        }
    }
    else{
        cout<<": ERROR: not enough elements on stack"<<endl;
    }
}

void Rekenmachine::kwadraat(){
    if(!thestack.empty()){
        double element = (double)thestack.top();
        thestack.pop();
        double product = element*element;
        thestack.push(product);
    }
    else
        cout<<": ERROR: not enoug elements on stack"<<endl;
}

void Rekenmachine::sqrt(){
    if(!thestack.empty()){
        double element = (double)thestack.top();
        thestack.pop();
        double vkw = ::sqrt(element);
        thestack.push(vkw);
    }
    else
        cout<<": ERROR: not enoug elements on stack"<<endl;
}
void Rekenmachine::clear(){
    if(!thestack.empty())
        thestack.pop();
}

void Rekenmachine::addElement(string element){
    double temp = atof(element.c_str());
    thestack.push(temp);
}

void Rekenmachine::print_stack(){
    stack<double> stack = thestack;
    
    cout<<":";
    while(!stack.empty()){
        cout<<stack.top()<<" ";
        stack.pop();
    }

    cout<<endl;
}

int main(int argc, char *argv[])
{
    Rekenmachine machine;
    cout<<"Stack calculator v0.0 (2016)"<<endl;
    string input;
    cout<<">";
    cin >> input;
    while(input!="Q"){
        machine.process(input);
        cout<<">";
        cin >> input;
    }
    cout<<"Exiting..."<<endl;
    return 0;
}
