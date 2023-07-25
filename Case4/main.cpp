#include<iostream>
#include<string>
using namespace std;

class DelimiterStack {
  private:
  struct DelimiterNode {
    char character;
    int lineNumber;
    int charCount;
    DelimiterNode *next;
  };
  DelimiterNode* top;
  public:
  DelimiterStack(){
    top = NULL;
  }
  ~DelimiterStack()
  {
    DelimiterNode* desNode = NULL;
    DelimiterNode* desNext = NULL;
    desNode = top;
    while (desNode) {
      desNext = desNode->next;
      delete desNode;
      desNode = desNext;
    }
  }
  void push(char, int, int);
  void popDelimiter(char&, int&, int&);
  bool isEmpty();
};

int main()
{
  DelimiterStack mydelistack;

  int lineCounter = 0;
  int charCounter;
  int arrLength = 0;
  int* numChar = new int[arrLength];
  char* delimArr = new char[arrLength];
  int* refNumChar = new int[arrLength];
  int refLineCounter = 0;
  char* refDelimArr = new char[arrLength];

  string currentLine = "";
  do{
    lineCounter++;
    charCounter = 0;
    arrLength = 0;

    getline(cin, currentLine);
    int length = currentLine.length();
    
    int position = 0;
    bool pop = false;

    int index = 0;

    if (currentLine != "DONE")
    {
      while (index < length)
      {
        position++;

        if ((currentLine[index] == '{') || (currentLine[index] == '}') || (currentLine[index] == '(') || (currentLine[index] == ')') || (currentLine[index] == '[') || (currentLine[index] == ']'))
        {
          arrLength++;
          numChar[index] = position;
          delimArr[index] = currentLine[index];
          index++;
        }
        else{
          currentLine.erase(index, 1);
          length--;
        }
      }
      for (int i = 0; i < arrLength; i++)
      {
        if ((currentLine[i] == '{') || (currentLine[i] == '(') || (currentLine[i] == '['))
        {
          mydelistack.push(delimArr[i], lineCounter, numChar[i]);
        }
        for (int i = 0; i < arrLength; i++)
        refDelimArr[i] = delimArr[i];
        refLineCounter = lineCounter;
        for (int i = 0; i < arrLength; i++)
        refNumChar[i] = numChar[i];
        if (currentLine[i] == '}')
        {
          if (mydelistack.isEmpty())
          pop = false;
          else{
            pop = true;
            mydelistack.popDelimiter(refDelimArr[i], refLineCounter, refNumChar[i]);
          }
          if (pop)
          {
            if (refDelimArr[i] == '{');
            else
            {
              cout << "Mismatched delimiter: " << refDelimArr[i] << " found at line " << refLineCounter << ", " << "char " << refNumChar[i] << " does not match " << delimArr[i] << " found at line " << lineCounter << ", " << "char " << numChar[i] << endl;
            }
          }
          else{
            cout << "Right delimiter " << delimArr[i] << " had no left delimiter; found at " << "line " << lineCounter << ", " << "char " << numChar[i] << endl;
          }
        }
        else if (currentLine[i] == ')')
        {
          if (mydelistack.isEmpty())
          pop = false;
          else{
            pop = true;
            mydelistack.popDelimiter(refDelimArr[i], refLineCounter, refNumChar[i]);
          }
          if (pop)
          {
            if (refDelimArr[i] == '(');
            else{
              cout << "Mismatched delimiter: " << refDelimArr[i] << " found at line " << refLineCounter << ", " << "char " << refNumChar[i] << " does not match " << delimArr[i] << " found at line " << lineCounter << ", " << "char " << numChar[i] << endl;
            }
          }
          else{
            cout << "Right delimiter " << delimArr[i] << " had no left delimiter; found at " << "line " << lineCounter << ", " << "char " << numChar[i] << endl;
          }
        }
        else if (currentLine[i] == ']')
        {
          if (mydelistack.isEmpty())
          pop = false;
          else{
            pop = true;
            mydelistack.popDelimiter(refDelimArr[i], refLineCounter, refNumChar[i]);
          }
          if (pop)
          {
            if (refDelimArr[i] == '[');
            else{
              cout << "Mismatched delimiter: " << refDelimArr[i] << " found at line " << refLineCounter << ", " << "char " << refNumChar[i] << " does not match " << delimArr[i] << " found at line " << lineCounter << ", " << "char " << numChar[i] << endl;
            }
          }
          else{
            cout << "Right delimiter " << delimArr[i] << " had no left delimiter; found at " << "line " << lineCounter << ", " << "char " << numChar[i] << endl;
          }
        }
      }
    }
  }
  while (currentLine != "DONE");
  bool stackEndEmpty;
  if (mydelistack.isEmpty())
  {
    stackEndEmpty = true;
  }
  else{
    stackEndEmpty = false;
  }

  int counter = 0;
  while (!stackEndEmpty)
  {
    mydelistack.popDelimiter(refDelimArr[counter], refLineCounter, refNumChar[counter]);
    cout << endl << "There was a left delimiter: " << refDelimArr[counter] << " at line " << refLineCounter << ", char " << refNumChar[counter] << " that had no right delimter.";
    counter++;
    stackEndEmpty = mydelistack.isEmpty();
  }
  delete[] numChar;
  numChar = nullptr;
  
  delete[] delimArr;
  delimArr = nullptr;
  
  delete[] refNumChar;
  refNumChar = nullptr;

  delete[] refDelimArr;
  refDelimArr = nullptr;

  return 0;
}

void DelimiterStack::push(char ch, int line, int cCount)
{
  DelimiterNode* newNode = new DelimiterNode;

  newNode->character = ch;
  newNode->lineNumber = line;
  newNode->charCount = cCount;

  if (isEmpty())
  {
    top = newNode;
    newNode->next = NULL;
  }
  else{
    newNode->next = top;
    top = newNode;
  }
}

void::DelimiterStack::popDelimiter(char& ch, int& line, int& cCount)
{
  DelimiterNode *temp;

  if (isEmpty())
  cout << "The stack is empty." << endl;
  else{
    ch = top->character;
    line = top->lineNumber;
    cCount = top->charCount;
    temp = top->next;

    delete top;
    top = temp;
  }
}

bool DelimiterStack::isEmpty()
{
  bool empty;
  if (top == NULL)
  {
    return true;
  }
  else{
    return false;
  }
}