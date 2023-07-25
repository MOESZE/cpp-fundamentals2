#include <iostream>
#include <cstdlib>
#include<limits>

using namespace std;
class horse
{
  private:
  string name;
  string rider;
  int maxRunningDistPerSecond;
  int DistanceTraveled;
  int RaceWon;
  public:
  horse(string hname, string rname)
  {
    name = hname;
    rider = rname;
    maxRunningDistPerSecond = rand()%100+1;
    DistanceTraveled = 0;
    RaceWon = 0;
  }
  int distanceCover()
  {
    return DistanceTraveled;
  }
  void runOneSecond()
  {
    DistanceTraveled += maxRunningDistPerSecond;
  }
  void win()
  {
    RaceWon += 1;
  }
  int hasWon()
  {
    return RaceWon;
  }
  void sendToStart()
  {
    DistanceTraveled = 0;
  }
  string getHorseName()
  {
    return name;
  }
  void displayHorse(int goalLength)
  {
  if(DistanceTraveled > goalLength)
    {
    cout << "|";
    for(int i = 0; i < goalLength; i++)
    cout << " ";
    cout << "|>" << rider << endl;
    }
  else
    {
    cout << "|";
    for(int i = 0; i < goalLength; i++)
    {
      if(i == DistanceTraveled)
    {
      cout << ">";
    }
      else
      {
      cout << " ";
      }
    }
    cout << "|" << name << ", ridden by " << rider << endl;
  }
};

int main()
{
  int number_horses;
  cout << "How many horses are in the race: ";
  do
  {
    cin >> number_horses;
  }
  while(number_horses <= 0 &&(cout << "Please enter a valid number of horses: "));
  horse * arr[number_horses];
  string hname;
  string rname;
  cin.ignore(std::numeric_limits<std::streamsize>::max());
  for(int i = 0; i < number_horses; i++)
  {
    cout << "Please give me the name of the horse " << i+1 << ":";
    getline(cin, hname);
    cout << "Please give me the name of the rider " << i+1 << ":";
    getline(cin, rname);
    arr[i] = new horse(hname, rname);
  }
  int goalLength;
  char ch;
  int winner = -1;
  bool flag = false;
  int nuOfRaces = 1;
  bool start = true;
  do
  {
    if(start)
    {
      cout << "Please enter the distance of the race: ";
      do
      {
        cin >> goalLength;
      }
      while(goalLength <= 0 && (cout << "Please enter a valid distance of race: "));
      cout << "The start: " << endl;
      for(int i = 0; i < number_horses; i++)
      arr[i] -> displayHorse(goalLength);
      start = false;
    }
    else
    {
      for(int i=0; i < number_horses; i++)
      {
        arr[i] -> runOneSecond();
        arr[i] -> displayHorse(goalLength);
        int x = arr[i] -> distanceCover();
        if(x > goalLength)
        {
          flag = true;
          winner = i;
        }
      }
      if(flag)
      {
        arr[winner] -> win();
        for(int i = 0; i < number_horses; i++)
        {
          cout << arr[i] -> getHorseName() << "has won " << arr[i] -> hasWon() << "/" << nuOfRaces << "races" << endl;
          arr[i] -> sendToStart();
          start = true;
        }
        nuOfRaces++;
      }
    }
    cout << "Do you wish to continue(y/n)?: ";
    cin >> ch;
  }
  while (ch == 'y' || ch == 'Y');
 return 0; 
}
};