#include <iostream>
#include <string>
#include "rice/Class.hpp"
#include "rice/Array.hpp"
#include "rice/Constructor.hpp"
#include "rice/Data_Type.hpp"

using namespace Rice;
class LedDataSet {
  public:
  LedDataSet(){
    memset(&matrix, 0x00, sizeof(matrix));
  }

  ~LedDataSet(){
  }

  void setMatrix(Array a){
    int cnt = 0;
    Array::const_iterator aI = a.begin();
    Array::const_iterator aE = a.end();

    while (aI != aE and cnt < 16) {
      matrix[cnt] = std::atoi((*aI).to_s().c_str());
      ++aI;
      cnt++;
    }
  }

  Array getMatrix(void){
    Array result;
    for(int i=0; i<16; i++){ result.push(matrix[i]); }
    return result;
  }

  private:
  int matrix[16];
};

extern "C" {
  void Init_LedDataSet() {
    Data_Type<LedDataSet> led = define_class<LedDataSet>("LedDataSet")
     .define_constructor(Constructor<LedDataSet>())
     .define_method("matrix",  &LedDataSet::getMatrix)
     .define_method("matrix=", &LedDataSet::setMatrix);
  }
}
