
#include<bits/stdc++.h>
using namespace std;

template <typename T>
class Stack
{
private:
    T *data;
    int data_size, max_size;
    void resize_data();
public:
    Stack();
    void push(T newData);
    void pop();
    T& top();
    int stack_size();
    bool isEmpty();
    void printStack();
};

template <typename T>
void Stack<T>::printStack()
{
    for(int i=0; i<data_size; i++)
    {
        cout<<data[i]<<" ";
    }
    cout<<endl;
}

template <typename T>
Stack<T>::Stack()
{
    data_size = 0;
    max_size = 10;
    data = new T[max_size];
}

template <typename T>
void Stack<T>::resize_data()
{
    if(data_size == max_size)
    {
        T *temp_data = new T[max_size];
        for(int i=0; i<data_size; i++)
        {
            temp_data[i] = data[i];
        }
        delete []data;

        max_size = max_size*2;
        data = new T[max_size];
        for(int i=0; i<data_size; i++)
        {
            data[i] = temp_data[i];
        }
        delete []temp_data;
    }

    else if(data_size == (max_size/2)-1)
    {
        T *temp_data = new T[max_size];
        for(int i=0; i<data_size; i++)
        {
            temp_data[i] = data[i];
        }
        delete []data;

        max_size = max_size/2;
        data = new T[max_size];
        for(int i=0; i<data_size; i++)
        {
            data[i] = temp_data[i];
        }
        delete []temp_data;
    }
}

template <typename T>
void Stack<T>::push(T newData)
{
    resize_data();
    data[data_size] = newData;
    data_size++;
}

template <typename T>
void Stack<T>::pop()
{
    resize_data();
    if(isEmpty())
    {
        return;
    }
    data_size--;
}

template <typename T>
T& Stack<T>::top()
{
    return data[data_size-1];
}

template <typename T>
int Stack<T>::stack_size()
{
    return data_size;
}

template <typename T>
bool Stack<T>::isEmpty()
{
    if(data_size==0)
        return true;
    else
        return false;
}



double exptodouble(string s)
{
    bool point = false;
    int pnt_indx = 1;
    double value = 0;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='.')
        {
            point = true;
        }
        else if(point)
        {
            value = value + ((s[i]-'0')/pow(10,pnt_indx));
            pnt_indx++;
        }
        else
        {
            value = (value*10) + (s[i]-'0');
        }
    }
    return value;
}

double solve(double firstValue, double secondValue, char operatr)
{
    if(operatr == '+')
    {
        return firstValue+secondValue;
    }
    else if(operatr == '-')
    {
        return secondValue-firstValue;
    }
    else if(operatr == '*')
    {
        return firstValue*secondValue;
    }
    else if(operatr == '/')
    {
        return secondValue/firstValue;
    }
}


int main()
{
    Stack<double> valueStack;
    Stack<char> operatorStack;

    string exp;
    cout<<"Enter the expression: ";
    getline(cin, exp);

    bool valid_checker = true;

    for(int i=0; i<exp.length(); i++)
    {
        /*cout<<"Value: ";
        valueStack.printStack();
        cout<<"Op: ";
        operatorStack.printStack();*/

        if(exp[i] == '(')
        {
            operatorStack.push(exp[i]);
        }
        else if(exp[i] == ' ')
        {
            exp.erase(exp.begin()+i);
            i--;
        }

        else if(exp[i] == ')')
        {
            valid_checker = false;
            if(!operatorStack.isEmpty())
            {
                char previousOperatr = operatorStack.top();
                while(true)
                {
                    if(previousOperatr == '(')
                    {
                        valid_checker = true;
                        operatorStack.pop();
                        break;
                    }
                    else if(valueStack.stack_size()>=2)
                    {
                        double firstValue = valueStack.top();
                        valueStack.pop();

                        double secondValue = valueStack.top();
                        valueStack.pop();
                        operatorStack.pop();

                        double result = solve(firstValue, secondValue, previousOperatr);
                        valueStack.push(result);
                        previousOperatr = operatorStack.top();
                    }
                }
            }
        }

        else if(exp[i]>='0' && exp[i]<='9')
        {
            /*int value = exp[i] - '0';
            valueStack.push(value);*/
            string str_value;
            while(i<exp.length() && ((exp[i]>='0' && exp[i]<='9') || exp[i]=='.'))
            {
                str_value+=exp[i];
                i++;
            }
            double value = exptodouble(str_value);
            valueStack.push(value);
            i--;
        }

        else if(exp[i] == '-' && exp[i-1]=='(')
        {
            if(exp[i+1]>='0' && exp[i+1]<='9')
            {
                /*int value = (-1)*(exp[i+1] - '0');
                valueStack.push(value);
                i = i+2;
                operatorStack.pop();*/
                string str_value;
                while(i<exp.length()-1 && ((exp[i+1]>='0' && exp[i+1]<='9') || exp[i+1] == '.'))
                {
                    str_value+=exp[i+1];
                    i++;
                }
                if(exp[i+1]!=')')
                {
                    valid_checker = false;
                    break;
                }
                double value = (-1)* exptodouble(str_value);
                valueStack.push(value);
                i++;
                operatorStack.pop();
            }
            else
            {
                valid_checker = false;
                break ;
            }
        }

        else if(exp[i]=='+' || exp[i]=='-')
        {
            if(!operatorStack.isEmpty())
            {
                char previousOperatr = operatorStack.top();
                while((previousOperatr == '*' || previousOperatr == '/' || previousOperatr == '+' || previousOperatr == '-')&&valueStack.stack_size()>=2)
                {
                    double firstValue = valueStack.top();
                    valueStack.pop();

                    double secondValue = valueStack.top();
                    valueStack.pop();
                    operatorStack.pop();

                    double result = solve(firstValue, secondValue, previousOperatr);
                    valueStack.push(result);
                    previousOperatr = operatorStack.top();
                }
            }

            operatorStack.push(exp[i]);
        }

        else if(exp[i]=='*' || exp[i]=='/')
        {
            if(!operatorStack.isEmpty())
            {
                char previousOperatr = operatorStack.top();
                while((previousOperatr == '*' || previousOperatr == '/') && valueStack.stack_size()>=2)
                {
                    double firstValue = valueStack.top();
                    valueStack.pop();

                    double secondValue = valueStack.top();
                    valueStack.pop();
                    operatorStack.pop();


                    double result = solve(firstValue, secondValue, previousOperatr);
                    valueStack.push(result);
                    previousOperatr = operatorStack.top();
                }
            }

            operatorStack.push(exp[i]);
        }
    }

    while(!operatorStack.isEmpty() && valueStack.stack_size()>=2 && valid_checker)
    {
        /*cout<<"Value: ";
        valueStack.printStack();
        cout<<"Op: ";
        operatorStack.printStack();*/

        double firstValue = valueStack.top();
        valueStack.pop();

        double secondValue = valueStack.top();
        valueStack.pop();

        if(operatorStack.top() == '(')
        {
            valid_checker=false;
            break;
        }
        char operatr = operatorStack.top();
        operatorStack.pop();

        double result = solve(firstValue, secondValue, operatr);
        valueStack.push(result);
    }

    if(!operatorStack.isEmpty())
    {
        valid_checker = false;
    }
    else if(valueStack.stack_size()>1)
    {
        valid_checker = false;
    }


    if(valid_checker)
    {
        cout<<"Valid Expression, Computed Value: "<<valueStack.top()<<endl;
    }
    else
    {
        cout<<"Not valid!"<<endl;
    }
}
