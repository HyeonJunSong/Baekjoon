#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

void FFT(vector<complex<double>>& poly, complex<double> w){

  if(poly.size() == 1) return;

  vector<complex<double>> even(poly.size() / 2);
  vector<complex<double>> odd(poly.size() / 2);

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
  return;
}

vector<complex<double>> multiply(vector<complex<double>>& polyA, vector<complex<double>>& polyB){
  int polySize = 1;
  while(polySize <= polyA.size() + polyB.size()) polySize *= 2;

  polyA.resize(polySize, complex<double>(0, 0));
  polyB.resize(polySize, complex<double>(0, 0));

  complex<double> w(cos(2 * M_PI / polySize), sin(2 * M_PI / polySize));

  FFT(polyA, w);
  FFT(polyB, w);

  vector<complex<double>> polyC(polySize);
  for(int i = 0; i < polySize; i++)
    polyC[i] = polyA[i] * polyB[i];
  
  FFT(polyC, complex<double>(w.real(), -w.imag()));
  for(int i = 0; i < polySize; i++){
    polyC[i] /= polySize;
    polyC[i] = complex<double>(round(polyC[i].real()), round(polyC[i].imag()));
  }

  return polyC;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  vector<complex<double>> ifPrime(1000001, complex<double>(1, 0));
  ifPrime[0] = complex<double>(0, 0);
  ifPrime[1] = complex<double>(0, 0);

  for(int i = 2; i <= 1000000; i++){
    if(ifPrime[i].real() == 0) continue;
    for(int j = i * 2; j <= 1000000; j += i){
      if(ifPrime[j].real() == 1)
        ifPrime[j] = complex<double>(0, 0);
    }
  }

  int primeCnt = 0;
  vector<long long> primes(78498);
  for(int i = 0; i <= 1000000; i++)
    if(ifPrime[i].real())
      primes[primeCnt++] = i;

  vector<complex<double>> ifSemiPrime(1000001, complex<double>(0, 0));
  for(auto iter1 = primes.begin(); iter1 != primes.end(); iter1++){
    for(auto iter2 = iter1; iter2 != primes.end(); iter2++){
      if((*iter1) * (*iter2) > 1000000) break;
      if((*iter1) * (*iter2) % 2 == 1) continue;
      ifSemiPrime[(*iter1) * (*iter2)] = complex<double>(1, 0);
    }
  }
  ifPrime[2] = complex<double>(0, 0);

  vector<complex<double>> Lehmer = multiply(ifPrime, ifSemiPrime);

  int T;
  cin >> T;
  for(int t = 0; t < T; t++){
    int inp;
    cin >> inp;
    cout << (int)(Lehmer[inp].real()) << "\n";
  }


  return 0;
}