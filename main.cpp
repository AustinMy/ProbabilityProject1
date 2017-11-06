#include <cmath>
#include <iostream>
using namespace std;

#define INC 457
#define MUL 1001
#define SEED 1000
#define MOD 1000

#define meanX 12
#define dial 6
#define busy 3
#define unavailable 25
#define end 1
#define isBusy .2d
#define isUnavailable .3d
#define redial 4   // number of times a customer is dialed in total

static int randomInt(int x){
  if (x == 0)
    return SEED;

  return (MUL*randomInt(x-1)+INC)%MOD;
}
static double random(int x){
  return (double)randomInt(x)/MOD;
}

class Variable{
  public:
    double value;
    double probability;
    public Variable();
}

class DiscreteRandomVar{
  public:
    double probabilityToVariable(double prob);
    DiscreteRandomVar();
    void addVariable(Variable var);
  
  private:
    Vector<Variable> pmf;
}
DiscreteRandomVar(){
  pmf;
}

//Note this does not order correctly so its up to us to give it lower to higher probabilities
//originall   
void addVariable(Variable var){
  pmf.push_back(var);
}

double probabilityToVariable(double prob){
  int i = 0;
  while(pmf[i].probability < prob){
    i++;
  }
  return pmf[i-1];
}

// F is expCDF with E[X] = 12
// event X is talk time
double probabilityToVariableX(double prob){
  return -meanX*log(1-p);
}

int main(){
  
  double w[150];                  // initializing time array
  for (int i = 0; i < 150; i++)
    w[i]=0;
  
  double p = 0;                   // used for probabilities
   
  for (int i = 0; i < 150; i++){
    for (int j = 0; j < 4; j++){
      p = random(4*i + j + 10);   // to prevent patterns
      w[i] += dial + end;         // constant for all calls

      if (p >= isBusy+isUnavailable){ // call is answered
	w[i] += 
	break;                    // no need to loop anymore
      }

      if (p < isBusy)             // is busy
	w[i] += busy;
      else                        // is unavaiable
	w[i] += unavailable;      
    }
  }
    
    
    
  
  return 0;
}
