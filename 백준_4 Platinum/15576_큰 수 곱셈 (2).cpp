#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <string>

using namespace std;

void FFT(vector<complex<double>>& f, complex<double> w){
  if(f.size() == 1) return;

  vector<complex<double>> odd(f.size() / 2), even(f.size() / 2);
  for(int i = 0; i < f.size(); i++){
    if(i % 2 == 0) even[i / 2] = f[i];
    else odd[i / 2] = f[i];
  }

  FFT(odd, w * w);
  FFT(even, w * w);

  complex<double> wp = complex<double>(1, 0); 
  for(int i = 0; i < f.size() / 2; i++){
    f[i] = even[i] + wp * odd[i];
    f[f.size() / 2 + i] = even[i] - wp * odd[i];
    wp *= w;
  }
  
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  string A, B;
  cin >> A >> B;

  if(A == "0" || B == "0"){
    cout << 0;
    return 0;
  }
  
  int polySize = 1;
  while(polySize < A.size() + B.size()) polySize *= 2;

  //다항식 초기화
  vector<complex<double>> polyA(polySize, complex<double>(0, 0)), polyB(polySize, complex<double>(0, 0));

  for(int i = 0; i < A.size(); i++)
    polyA[i] = complex<double>((double)(A[A.size() - i - 1] - '0'), 0);

  for(int i = 0; i < B.size(); i++)
    polyB[i] = complex<double>((double)(B[B.size() - i - 1] - '0'), 0);
  
  //n-th root of unity
  complex<double> w(cos(2 * M_PI / polySize), sin(2 * M_PI / polySize));

  //푸리에 변환
  FFT(polyA, w);
  FFT(polyB, w);

  //곱
  vector<complex<double>> polyC(polySize);
  for(int i = 0; i < polySize; i++)
    polyC[i] = polyA[i] * polyB[i];

  //역변환
  complex<double> wC(w.real(), -1 * w.imag());
  FFT(polyC, wC);

  for(int i = 0; i < polySize; i++){
    polyC[i] /= complex<double>(polySize, 0);
    polyC[i] = complex<double>(round(polyC[i].real()), round(polyC[i].imag()));
  }

  
  vector<int> ans(polyC.size());
  for(int i = 0; i < polyC.size(); i++)
    ans[i] = polyC[i].real();
  
  for(int i = 0; i < ans.size(); i++){
    if(ans[i] > 0){
      if(i == ans.size() - 1) ans.push_back(0);
      ans[i + 1] += ans[i] / 10;
      ans[i] %= 10;
    }
  }

  for(auto iter = ans.rbegin(); iter != ans.rend(); iter++){
    if(*iter == 0) continue;
    for(auto iter2 = iter; iter2 != ans.rend(); iter2++)
      cout << *iter2;
    break;
  }


  return 0;
}