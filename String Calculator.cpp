/**
 * @file BigInt.cpp
 *
 * @author <a href="mailto:amirhhakimnejad@gmail.com">Amirhossein Hakimnejad</a>
 * @date May 5, 2018
 * @date June 19, 2018
 */

#include <iostream>
#include <vector>

using std::string;

void vectorshower(std::vector<string> vc)
{
  for(int i = 0; i < vc.size(); i++)
  {
    if(vc.at(i) != "(" || vc.at(i) != ")")
      std::cout << vc.at(i) << " ";
  }
  std::cout << "\n";
}

int getPrior(char c)
{
  if(c == '*' || c == '/')
    return 2;
  if(c == '+' || c == '-')
    return 1;
}

bool isOperator(string c)
{
  return c == "+" || c == "-" || c == "*" || c == "/";
}

bool isOperator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isOperand(string c)
{
  if(!(isOperator(c)))
    return (c != ")") && (c != "(");
  return false;
}

int calculateWithSign(char c, int a, int b)
{
  switch(c)
  {
    case '+':
      return (a + b);
    case '-':
      return (a - b);
    case '*':
      return (a * b);
    case '/':
      return (a / b);
  }
}

int postfixCalculator(std::vector<string> postfixes)
{
  std::vector<int> operands;
  int a = 0, b = 0, c = 0;
  for(int i = 0; i < postfixes.size(); i++)
  {
    if(isOperand(postfixes[i]))
      operands.push_back(std::stoi(postfixes[i]));
    else
    if(operands.size()>1)
    {
      b = operands.back();
      operands.pop_back();
      a = operands.back();
      operands.pop_back();
      c = calculateWithSign(postfixes[i][0], a, b);
      operands.push_back(c);
    }
  }
  return operands[0];
}

std::vector<string> convertToPostfix(std::vector<string> infix)
{
  std::vector<string> operators;
  std::vector<string> postfixes;

  for(int i = 0; i < infix.size(); i++)
  {
    if(isOperand(infix[i]))
      postfixes.push_back(infix[i]);

    else if(infix[i] == "(")
    {
      operators.push_back(infix[i]);
    }

    else if(infix[i] == ")")
    {
      while(!operators.empty() && operators.back()[0] !=  '(')
      {
        postfixes.push_back(string(1, operators.back()[0]));
        operators.pop_back();
      }
      operators.pop_back();
    }

    else if(isOperator(infix[i]))
    {
      while (!operators.empty() && operators.back()[0] != '(' && getPrior(operators.back()[0]) >= getPrior(infix[i][0]))
      {
        postfixes.push_back(string(1, operators.back()[0]));
        operators.pop_back();
      }
      operators.push_back(infix[i]);
    }
  }

  while (operators.size()!=0)
  {
    postfixes.push_back(string(1, operators.back()[0]));
    operators.pop_back();
  }
  return postfixes;
}

std::vector<string> tokenizer(string str)
{
  string tempstr="";
  std::vector<string> vc;
  for(int i = 0; i < str.length(); i++)
  {
    if(str[i]==' ')
      continue;
    if(str[i]=='('||str[i]==')')
    {
      tempstr = str[i];
      vc.push_back(tempstr);
      tempstr = "";
      continue;
    }

    if(isOperator(str[i]))
    {
      tempstr = "";
      tempstr += str[i];
      vc.push_back(tempstr);
      tempstr = "";
    }
    else
    {
      while(i < str.length())
      {
        tempstr += str[i];
        i++;
        if(isOperator(str[i])||str[i]=='('||str[i]==')')
        {
          i--;
          break;
        }
      }
      vc.push_back(tempstr);
      tempstr = "";
    }
  }
  return vc;
}

int main(void)
{
  string s = "7+(9*6-4/2)-20/4";
  vectorshower(tokenizer(s));
  vectorshower(convertToPostfix(tokenizer(s)));
  std::vector<string> inf;
  std::cout << postfixCalculator(convertToPostfix(tokenizer(s)));
  return 0;
}