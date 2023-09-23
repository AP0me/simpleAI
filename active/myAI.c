
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomIntList(int* x, int numRandomIntegers, int minValue, int maxValue, int seed){
  srand(seed);
  for (int i = 0; i < numRandomIntegers; i++) {
    int randomInt = (rand() % (maxValue - minValue + 1)) + minValue;
    x[i]=randomInt;
  }
}
int dataGen(int* x, int x_len){
  int result = 0;
  for(int i=0; i<x_len; i++){
    if(x[i]%2==0){ result+=1;    }
    else         { result+=x[i]; }
  }
  return result;
}

void applyLayer(int lay1_len, int lay2_len, int lay1[lay1_len], int* lay2, int transform12[lay2_len][lay1_len], int bias){
  for(int lay2i=0; lay2i<lay2_len; lay2i++){
    for(int lay1i=0; lay1i<lay1_len; lay1i++){
      lay2[lay2i] += lay1[lay1i]*transform12[lay2i][lay1i]+bias;
    }
    lay2[lay2i] = lay2[lay2i]/(10*lay1_len);
  }
}

void fillWithRandom(int lay1_len, int lay2_len, int transform12[lay2_len][lay1_len]){
  for(int lay2i=0; lay2i<lay2_len; lay2i++){
    for(int lay1i=0; lay1i<lay1_len; lay1i++){
      randomIntList(&transform12[lay2i][0], lay1_len, 0, 10, transform12[lay2i][0]);
}}}

int main(){
  int x_len=10; int x[x_len];
  randomIntList(&x[0], x_len, 0, 10, 69);
  int dataOut = dataGen(x, x_len);

  //model
  int eps=10;
  //train_wxy
  int y_len=2; int y[y_len];
  int w_xy[y_len][x_len]; int bias_xy=0;
  int z_len=1; int z[z_len];
  int w_yz[z_len][y_len]; int bias_yz=0;

  fillWithRandom(x_len, y_len, w_xy);
  fillWithRandom(y_len, 1, w_yz);//C is stupid turns z_len=1 to z_len=61 so just put z_len's value in second argument

  for(int trainIterInt=0; trainIterInt<15; trainIterInt++){
    for(int train_wxyY=0; train_wxyY<y_len; train_wxyY++){
        for(int train_wxyX=0; train_wxyX<x_len; train_wxyX++){
          applyLayer(x_len, y_len, x, &y[0], w_xy, bias_xy);
          applyLayer(y_len, z_len, y, &z[0], w_yz, bias_yz);
          unsigned long costNoMod = (z[0]-dataOut)*(z[0]-dataOut);
          w_xy[train_wxyY][train_wxyX]+=eps;

          applyLayer(x_len, y_len, x, &y[0], w_xy, bias_xy);
          applyLayer(y_len, z_len, y, &z[0], w_yz, bias_yz);
          unsigned long costMod = (z[0]-dataOut)*(z[0]-dataOut);
          if(costMod<costNoMod){}
          else{ w_xy[train_wxyY][train_wxyX]+=-2*eps; }
  }}}


  int testDataLen=10; int testData[testDataLen]; int i=0; float error=0; int dataGenVar;
  for(int k=0; k<1000; k++){
    randomIntList(&testData[0], testDataLen, 0, 10, testData[0]);

    applyLayer(10, y_len, testData, &y[0], w_xy, bias_xy);
    applyLayer(y_len, z_len, y, &z[0], w_yz, bias_yz);
    dataGenVar = dataGen(testData, testDataLen);
    error = ( error + 100*(z[0]+dataGenVar)/dataGenVar )/2;
  }
  printf("error %%: %f\n", error);
}

