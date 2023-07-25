#include <iostream>
#include <string>
#include <cctype>

using namespace std;

struct Word
{
  string english;
  string piglatin;
};
Word * splitSentence(const string word, int& size);
void convertToPigLatin(Word wordArr[], int size);
void displayPigLatin(const Word wordArr[], int size);

int main()
{
  int size = 1;
  string temporary;
  Word * sepPtr;
  
  cout << "Please enter a string to convert to PigLatin: " << endl;
  getline(cin, temporary);

  sepPtr = splitSentence(temporary, size);
  convertToPigLatin(sepPtr, size);
  displayPigLatin(sepPtr, size);
  return 0;
}

Word * splitSentence(const string words, int& size)
{
  int index = 0, countWords;
  bool eraseChar, check;
  string transfer;
  Word * wordPtr = NULL;
  
  for(int i = 0; i < words.length(); i++)
  {
    if(isalpha(words[i]))
    {
      transfer += words[i];
    }
    else if(isspace(words[i]))
    {
      transfer += words[i];
    }
  }
  do
  {
    eraseChar = false;
    if(isspace(transfer[0]))
    {
      transfer.erase(index, 1);
      eraseChar = true;
    }
  }
  while(eraseChar == true);
  transfer += '*';
  eraseChar = true;

  while(eraseChar == true)
  {
    eraseChar = false;
    countWords = transfer.length();

    for(int i = 0; i < countWords; i++)
    {
      transfer[i] = tolower(transfer[i]);
      if(transfer[i] == '*')
      {
        if(isspace(transfer[i-1]))
        {
          transfer.erase(i-1, 1);
          eraseChar = true;
          break;
        }
        transfer.erase(i, 1);
        eraseChar = true;
        break;
      }
      if(isspace(transfer[i]))
      {
        if(isspace(transfer[i+1]))
        {
          transfer.erase(i, 1);
          eraseChar = true;
          break;
        }
      }
    }
  }
  transfer += " ";
  countWords = transfer.length();

  for(int i = 0; i < countWords; i++)
  {
    if(isspace(transfer[i]))
    {
      size++;
    }
  }
  size--;

  wordPtr = new Word[size];

  for(int j = 0; j < size; j++)
  {
    check = false;
    for(int k = index; k < countWords; k++)
    {
      if(isspace(transfer[k]))
      {
        for(int l = index; l < k; l++)
        {
          wordPtr[j].english += transfer[l];
          check = true;
        }
      }
      if(check)
      {
        index = k + 1;
        break;
      }
    }
  }
  return wordPtr;
}

void convertToPigLatin(Word wordArr[], int size)
{
  const int vowelSize = 5;
  int loopsMade = 0;
  bool vowelFound;
  string vowel = "aeiou";

  do
  {
    vowelFound = false;
    for(int i = 0; i < vowelSize; i++)
    {
      if((wordArr[loopsMade]).english[0] == vowel[i])
      {
        vowelFound = true;
        break;
      }
    }
    if(vowelFound == true)
    {
      wordArr[loopsMade].piglatin = wordArr[loopsMade].english;
      wordArr[loopsMade].piglatin += "way";
    }
    else
    {
      wordArr[loopsMade].piglatin = wordArr[loopsMade].english;
      wordArr[loopsMade].piglatin.erase(0, 1);
      wordArr[loopsMade].piglatin += (wordArr[loopsMade].english)[0];
      wordArr[loopsMade].piglatin += "ay";
    }
    loopsMade++;
  }
  while(loopsMade < size);
}
  void displayPigLatin(const Word wordArr[], int size)
  {
    cout << "Output: " << endl;
    for(int i = 0; i < size; i++)
    {
      cout << wordArr[i].piglatin << " ";
    }
    cout << endl;
  }
