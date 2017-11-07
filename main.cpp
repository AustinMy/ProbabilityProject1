#include <cmath>
#include <iostream>
#include <vector>
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

int xprev = 1000;
//The random generator was not x-1 but the subscript -1 therefore it makes sense that we start
//from the seed at i =0 and each time we ask for a number i is incremented
double random(){
  xprev = (MUL*xprev+INC)%MOD;
  return (double)xprev/MOD;
}


class Variable{
  public:
    double value;
    double probability;
    Variable();
};


// F is expCDF with E[X] = 12
// event X is talk time
double inverseCDF(double prob){
  double res = -meanX*log(1-prob);
  if(res > 25){
    return inverseCDF(random());
  }
  return res;
}

int main(){
  
  double w[150];                  // initializing time array
  for (int i = 0; i < 150; i++)
    w[i]=0;
  
  double p = 0;                   // used for probabilities
   
  for (int i = 0; i < 150; i++){
    for (int j = 0; j < 4; j++){
      p = random();   // to prevent patterns
      cout << p << " : " << i << " : " << j << endl;
      w[i] += dial + end;         // constant for all calls

      if (p >= isBusy+isUnavailable){ // call is answered
	      w[i] += inverseCDF(random());  
	      break;                    // no need to loop anymore
      }
      cout<< p<< endl;
      if (p < isBusy){             // is busy
        cout<< busy <<endl;
	      w[i] += busy;
      }
      else{                        // is unavaiable
        cout<< unavailable << endl;
	      w[i] += unavailable;      
      }
    }
  }
  for(int i = 0; i< 150; i++){
    cout<< w[i] <<endl;
  }
  return 0;
}
