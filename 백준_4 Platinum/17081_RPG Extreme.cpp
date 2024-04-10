#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cmath>

using namespace std;

class Monster{
public:
  string name;
  int off;
  int def;
  int hp;
  int maxHp;
  int exp;
};

class Item{
public:
  char type;
  int val;
  string accesory;
};

class Player{
public:
  int I;
  int J;

  int off;
  int weapon;

  int def;
  int armor;

  int hp;
  int maxHp;
  
  int level;

  int exp;
  int maxExp;

  set<string> accessories;

  bool fight(Monster& monster){

    //첫턴
    if(accessories.find("CO") != accessories.end()){
      if(accessories.find("DX") != accessories.end()){
        monster.hp -= max(1, 3 * (off + weapon) - monster.def);
        if(monster.hp <= 0)
          return true;
      } else {
        monster.hp -= max(1, 2 * (off + weapon) - monster.def);
        if(monster.hp <= 0)
          return true;
      }
    } else {
      monster.hp -= max(1, (off + weapon) - monster.def);
      if(monster.hp <= 0)
        return true;
    }

    //이후
    while(true){
      hp -= max(1, monster.off - (def + armor));
      if(hp <= 0){
        hp = 0;
        return false;
      }

      monster.hp -= max(1, (off + weapon) - monster.def);
      if(monster.hp <= 0)
        return true;
    }

  }

  bool bossFight(Monster& monster){

    if(accessories.find("HU") != accessories.end())
      hp = maxHp;

    //첫턴
    if(accessories.find("CO") != accessories.end()){
      if(accessories.find("DX") != accessories.end()){
        monster.hp -= max(1, 3 * (off + weapon) - monster.def);
        if(monster.hp <= 0)
          return true;
      } else {
        monster.hp -= max(1, 2 * (off + weapon) - monster.def);
        if(monster.hp <= 0)
          return true;
      }
    } else {
      monster.hp -= max(1, (off + weapon) - monster.def);
      if(monster.hp <= 0)
        return true;
    }

    if(accessories.find("HU") == accessories.end()){
      hp -= max(1, monster.off - (def + armor));
      if(hp <= 0){
        hp = 0;
        return false;
      }
    }

    //이후
    while(true){
      monster.hp -= max(1, (off + weapon) - monster.def);
      if(monster.hp <= 0)
        return true;

      hp -= max(1, monster.off - (def + armor));
      if(hp <= 0){
        hp = 0;
        return false;
      }
    }

  }

  void getExp(int amount){
    exp = min(exp + amount, maxExp);

    //레벨업
    if(exp == maxExp){
      maxExp += 5;
      exp = 0;
      level++;

      maxHp += 5;
      hp = maxHp;
      off += 2;
      def += 2;
    }
  }
};

map<char, pair<int, int>> dir = {
  {'L', { 0, -1}},
  {'R', { 0,  1}},
  {'U', {-1,  0}},
  {'D', { 1,  0}},
};

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  //입력
  int N, M;
  cin >> N >> M;

  vector<string> grid;
  grid = vector<string>(N);
  for(int i = 0; i < N; i++)
    cin >> grid[i];

  string S;
  cin >> S;

  int K = 0;
  int L = 0;
  pair<int, int> initLoc;

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      switch(grid[i][j]){
        case 'M':
        case '&':
          K++;
          break;
        case 'B':
          L++;
          break;
        case '@':
          initLoc.first = i;
          initLoc.second = j;
          break;
      }
    }
  }

  vector<vector<int>> idxGrid;
  idxGrid = vector<vector<int>>(N, vector<int>(M));

  vector<Monster> monsters;
  monsters = vector<Monster>(K);
  for(int k = 0; k < K; k++){
    int R, C;
    cin >> R >> C;
    R--;C--;
    
    cin >> monsters[k].name;
    cin >> monsters[k].off;
    cin >> monsters[k].def;
    cin >> monsters[k].hp;
    cin >> monsters[k].exp;

    monsters[k].maxHp = monsters[k].hp;
    idxGrid[R][C] = k;
  }

  vector<Item> items;
  items = vector<Item>(L);
  for(int l = 0; l < L; l++){
    int R, C;
    cin >> R >> C;
    R--; C--;

    cin >> items[l].type;
    if(items[l].type == 'O')
      cin >> items[l].accesory;
    else
      cin >> items[l].val;
    
    idxGrid[R][C] = l;
  }

  //수행
  
  Player player;

  player.I = initLoc.first;
  player.J = initLoc.second;
  player.hp = 20;
  player.maxHp = 20;
  player.off = 2;
  player.weapon = 0;
  player.def = 2;
  player.armor = 0;
  player.level = 1;
  player.exp = 0;
  player.maxExp = 5;

  grid[player.I][player.J] = '.';

  int passedTurn = -1;
  string result;

  for(auto s = 0; s < S.size(); s++){
    int nextI = player.I + dir[S[s]].first;
    int nextJ = player.J + dir[S[s]].second;

    if(N <= nextI || nextI < 0
    || M <= nextJ || nextJ < 0){
      nextI = player.I;
      nextJ = player.J;
    };

    switch(grid[nextI][nextJ]){
      case '#':
        if(grid[player.I][player.J] == '^'){
          if(player.accessories.find("DX") != player.accessories.end())
            player.hp = max(0, player.hp - 1);
          else
            player.hp = max(0, player.hp - 5);
          
          if(player.hp == 0){

            if(player.accessories.find("RE") != player.accessories.end()){
              player.accessories.erase("RE");
              player.I = initLoc.first;
              player.J = initLoc.second;
              player.hp = player.maxHp;
            } else {
              player.I = -1;
              passedTurn = s + 1;
              result = "YOU HAVE BEEN KILLED BY SPIKE TRAP..";
            }

          }
        }
        break;

      case '.':
        player.I = nextI;
        player.J = nextJ;
        break;

      case 'B':
        switch(items[idxGrid[nextI][nextJ]].type){
          case 'W':
            player.weapon = items[idxGrid[nextI][nextJ]].val;
          break;
          case 'A':
            player.armor = items[idxGrid[nextI][nextJ]].val;
          break;
          case 'O':
            if(player.accessories.size() < 4)
              player.accessories.insert(items[idxGrid[nextI][nextJ]].accesory);
          break;
        }
        player.I = nextI;
        player.J = nextJ;
        grid[nextI][nextJ] = '.';
        break;

      case '^':
        player.I = nextI;
        player.J = nextJ;
        if(player.accessories.find("DX") != player.accessories.end())
          player.hp = max(0, player.hp - 1);
        else
          player.hp = max(0, player.hp - 5);
        
        if(player.hp == 0){

          if(player.accessories.find("RE") != player.accessories.end()){
            player.accessories.erase("RE");
            player.I = initLoc.first;
            player.J = initLoc.second;
            player.hp = player.maxHp;
          } else {
            player.I = -1;
            passedTurn = s + 1;
            result = "YOU HAVE BEEN KILLED BY SPIKE TRAP..";
          }

        }
        break;

      case '&':
        if(player.fight(monsters[idxGrid[nextI][nextJ]])){
          grid[nextI][nextJ] = '.';
          player.I = nextI;
          player.J = nextJ;

          if(player.accessories.find("HR") != player.accessories.end())
            player.hp = min(player.hp + 3, player.maxHp);
          
          if(player.accessories.find("EX") != player.accessories.end())
            player.getExp((int)((float)(monsters[idxGrid[nextI][nextJ]].exp) * 1.2));
          else
            player.getExp(monsters[idxGrid[nextI][nextJ]].exp);

        }else{

          if(player.accessories.find("RE") != player.accessories.end()){
            player.accessories.erase("RE");
            player.I = initLoc.first;
            player.J = initLoc.second;
            player.hp = player.maxHp;

            monsters[idxGrid[nextI][nextJ]].hp = monsters[idxGrid[nextI][nextJ]].maxHp;
          } else {
            player.I = -1;
            passedTurn = s + 1;
            result = "YOU HAVE BEEN KILLED BY " + monsters[idxGrid[nextI][nextJ]].name + "..";
          }
        }
        break;

      case 'M':
        if(player.bossFight(monsters[idxGrid[nextI][nextJ]])){
          grid[nextI][nextJ] = '.';
          player.I = nextI;
          player.J = nextJ;

          if(player.accessories.find("HR") != player.accessories.end())
            player.hp = min(player.hp + 3, player.maxHp);
          
          if(player.accessories.find("EX") != player.accessories.end())
            player.getExp((int)((float)(monsters[idxGrid[nextI][nextJ]].exp) * 1.2));
          else
            player.getExp(monsters[idxGrid[nextI][nextJ]].exp);
          
          passedTurn = s + 1;
          result = "YOU WIN!";
        }else{

          if(player.accessories.find("RE") != player.accessories.end()){
            player.accessories.erase("RE");
            player.I = initLoc.first;
            player.J = initLoc.second;
            player.hp = player.maxHp;

            monsters[idxGrid[nextI][nextJ]].hp = monsters[idxGrid[nextI][nextJ]].maxHp;
          } else {

            player.I = -1;
            passedTurn = s + 1;
            result = "YOU HAVE BEEN KILLED BY " + monsters[idxGrid[nextI][nextJ]].name + "..";
          }
        }
        break; 
    }

    if(passedTurn != -1) break;
  }

  if(player.I != -1)
    grid[player.I][player.J] = '@';

  for(auto e: grid)
    cout << e << "\n";
  
  if(passedTurn == -1)
    passedTurn = S.size();

  cout << "Passed Turns : " << passedTurn << "\n";
  cout << "LV : " << player.level << "\n";
  cout << "HP : " << player.hp << "/" << player.maxHp << "\n";
  cout << "ATT : " << player.off << "+" << player.weapon << "\n";
  cout << "DEF : " << player.def << "+" << player.armor << "\n";
  cout << "EXP : " << player.exp << "/" << player.maxExp << "\n";

  if(result.size() == 0)
    cout << "Press any key to continue.";
  else
    cout << result;


  return 0;
}