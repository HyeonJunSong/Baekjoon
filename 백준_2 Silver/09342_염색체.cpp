#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool ifInfected(string dna){
  int i = 0;

  if('F' < dna[i])
    return false;
  else if('B' <= dna[i] && dna[i] <= 'F')
    i++;
  
  if(i >= dna.size()) return false;
  if(dna[i] != 'A') return false;
  while(dna[i] == 'A'){
    i++;
    if(i >= dna.size()) return false;
  }

  if(dna[i] != 'F') return false;
  while(dna[i] == 'F'){
    i++;
    if(i >= dna.size()) return false;
  }

  if(dna[i] != 'C') return false;
  while(dna[i] == 'C'){
    i++;
    if(i >= dna.size()) return true;
  }

  if('A' <= dna[i] && dna[i] <= 'F' && i == dna.size()){
    return true;
  }
  
  return false;
}

int main(){
  int N;
  cin >> N;

  vector<string> DNAs(N);
  for(int i = 0; i < N; i++)
    cin >> DNAs[i];
  
  for(int i = 0; i < N; i++){
    if(ifInfected(DNAs[i]))
      cout << "Infected!\n";
    else
      cout << "Good\n";
  }

  return 0;
}