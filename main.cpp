


using namespace std;


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
