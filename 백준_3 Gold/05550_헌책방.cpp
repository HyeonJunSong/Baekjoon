#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> books(10);
vector<vector<int>> memo;

int findMaxSell(int genre, int booksLeft);

int main(){

  int N, K;
  cin >> N >> K;

  for(int i = 0; i < N; i++){
    int price, genre;
    cin >> price >> genre;
    genre--;

    books[genre].push_back(price);
  }

  for(int i = 0; i < 10; i++)
    sort(books[i].rbegin(), books[i].rend());
  
  memo = vector<vector<int>>(11, vector<int>(K + 1, -1));

  cout << findMaxSell(0, K);

  return 0;
}

int findMaxSell(int genre, int booksLeft){

  if(booksLeft == 0 || genre == 10)
    return 0;

  if(memo[genre + 1][booksLeft] == -1)
    memo[genre + 1][booksLeft] = findMaxSell(genre + 1, booksLeft);
  int maxSell = memo[genre + 1][booksLeft];
  int curGenreSell = 0;
  for(int i = 0; i < min(booksLeft, (int)(books[genre].size())); i++){
    curGenreSell += books[genre][i];
    curGenreSell += i * (i + 1);

    if(memo[genre + 1][booksLeft - i - 1] == -1)
      memo[genre + 1][booksLeft - i - 1] = findMaxSell(genre + 1, booksLeft - i - 1);
    maxSell = max(maxSell, memo[genre + 1][booksLeft - i - 1] + curGenreSell);
    curGenreSell -= i * (i + 1);
  }

  return maxSell;
}