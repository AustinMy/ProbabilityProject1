#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


#define INC 457
#define MUL 1001
#define MOD 1000

#define meanX 12
#define dial 6
#define busy 3
#define unavailable 25
#define end 1
#define isBusy .2
#define isUnavailable .3
#define redial 4   // number of times a customer is dialed in total

double w[150];     // convenient for static methods
double probs[500];
int xprev = 1000;
//The random generator was not x-1 but the subscript -1 therefore it makes sense that we start
//from the seed at i =0 and each time we ask for a number i is incremented
double randomP(){    // renamed due to overloading
  xprev = (MUL*xprev+INC)%MOD;
  return (double)xprev/MOD;
}


class Variable{
  public:
    double value;
    double probability;
    Variable();
};

double mean(){
  double x=0;
  for (int i = 0; i < 150; i++)
    x += w[i];
  return x/150;
}

double cutOff(int range){         // Returns P[W <= range]
  double x=0;
  for (int i = 0; i < 150; i++)
    if (w[i] > range)
      break;
    else
      x++;

  return x/150;
}

double firstQuartile(){
  return w[37];
}

double thirdQuartile(){
  return w[112];
}

double median(){
  return (w[74]+w[75])/2;
}

// F is expCDF with E[X] = 12
// event X is talk time
double inverseCDF(double prob){
  double res = -meanX*log(1-prob);
    if(res > 25){
     return inverseCDF(randomP());
    }
  return res;
}

int main(){ 
                 // initializing time array
  for (int i = 0; i < 150; i++){
    w[i]=0;
  }
  for (int i =0; i<500; i++){
    probs[i]=randomP();
  }
  
  int busy_count = 0;
  int unavailable_count = 0;
  int available_count =0;  
  double p = 0;                   // used for probabilities
  int next_prob =0; 
  for (int i = 0; i < 150; i++){
    for (int j = 0; j < 4; j++){
      p = probs[next_prob++];   // to prevent patterns;
      w[i] += dial + end;         // constant for all calls

      if (p >= isBusy+isUnavailable){ // call is answered
	      w[i] += inverseCDF(randomP());  
        available_count++;
	      break;                    // no need to loop anymore
      }
      if (p < isBusy){             // is busy
	      w[i] += busy;
        busy_count++;
      }
      else{                        // is unavaiable
	      w[i] += unavailable;      
        unavailable_count++;
      }
    }
  }
  sort(w, w+150);
  cout<< "Busy: "<< busy_count <<endl;
  cout << "Unavailable: " << unavailable_count << endl;
  cout << "Available: " << available_count << endl;


  cout << "Mean: " << mean() << endl;
  cout << "Median: " << median() << endl;
  cout << "First Quartile: " << firstQuartile() << endl;
  cout << "Third Quartile: " << thirdQuartile() << endl;
  cout << "Cutoffs: " << endl;
  cout << "<= 15 " << cutOff(15) << endl;
  cout << "<= 20 " << cutOff(20) << endl;
  cout << "<= 30 " << cutOff(30) << endl;
  cout << "> 40 " << 1-cutOff(40) << endl;
  cout << "> 50 " << 1-cutOff(50) << endl;
  cout << "> 60 " << 1-cutOff(60) << endl;
  cout << "> 65 " << 1-cutOff(65) << endl;

  
  return 0;
}
