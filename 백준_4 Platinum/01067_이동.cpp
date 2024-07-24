#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

// #define double long double

void FFT(vector<complex<double>>& poly, complex<double> w){

  if(poly.size() == 1) return;

  vector<complex<double>> even(poly.size() / 2), odd(poly.size() / 2);
  for(int i = 0; i < poly.size(); i++){
    if(i % 2 == 0) even[i / 2] = poly[i];
    else odd[i / 2] = poly[i];
  }

  FFT(even, w * w);
  FFT(odd, w * w);

  complex<double> wT(1, 0);
  for(int i = 0; i < poly.size() / 2; i++){
    poly[i] = even[i] + wT * odd[i];
    poly[poly.size() / 2 + i] = even[i] - wT * odd[i];
    wT *= w;
  }
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<int> X(N), Y(N);
  for(int i = 0; i < N; i++)
    cin >> X[i];
  for(int i = 0; i < N; i++)
    cin >> Y[i];  
  
  int polySize = 1;
  while(polySize < (3 * N)) polySize *= 2;


  vector<complex<double>> polyA(polySize, complex<double>(0, 0)), polyB(polySize, complex<double>(0, 0));

  for(int i = 0; i < N; i++){
    polyA[i] = complex<double>(X[i], 0);
    polyA[N + i] = complex<double>(X[i], 0);
  }
  for(int i = 0; i < N; i++)
    polyB[i] = complex<double>(Y[N - i - 1], 0);
  
  complex<double> w(cos(2 * acos(-1) / polySize), sin(2 * acos(-1) / polySize));

  FFT(polyA, w);
  FFT(polyB, w);

  vector<complex<double>> polyC(polySize);

  for(int i = 0; i < polySize; i++)
    polyC[i] = polyA[i] * polyB[i];
  
  complex<double> wC(w.real(), -w.imag());

  FFT(polyC, wC);
  for(int i = 0; i < polySize; i++){
    polyC[i] /= polySize;
    polyC[i] = complex<double>(round(polyC[i].real()), round(polyC[i].imag()));
  }
  
  int ans = 0;
  for(int i = N - 1; i <= 2 * N - 2; i++)
    ans = max(ans, (int)(polyC[i].real()));
  
  cout << ans;

  return 0;
}