#include <iostream>
#include <string>
#include <wiringPi.h>
#include "ledController.h"
#include "rice/Class.hpp"
#include "rice/Constructor.hpp"
#include "rice/Data_Type.hpp"

using namespace Rice;
LedController::LedController(){
  memset(&matrix, 0x00, sizeof(matrix));

  if (wiringPiSetup() == -1) {
    throw "wiringPiSetup faild";
  }

  pinMode(SIN_Y  , OUTPUT);
  pinMode(SIN_X1 , OUTPUT);
  pinMode(SIN_X2 , OUTPUT);
  pinMode(CLOCK  , OUTPUT);
  pinMode(LATCH  , OUTPUT);

  reset();
  threadStart();
}

LedController::~LedController(){
  pthread_cancel(this->thread_handler);     // スレッドにキャンセル要求を投げる
  pthread_join(this->thread_handler, NULL); // スレッドが終了するまで待機

  reset();
}

void LedController::threadStart(void){
  std::cout << "threadStart" << std::endl;
  pthread_mutex_init(&(this->mutex), NULL);
  pthread_create(
      &(this->thread_handler),
      NULL,
      &LedController::mainLoopLauncher,
      this
      );
}

void* LedController::mainLoopLauncher(void* args){
  reinterpret_cast<LedController*>(args)->mainLoop();
  return NULL;
}

void LedController::mainLoop(void){
  std::cout << "mainloop" << std::endl;
  while(1){
    pthread_testcancel();                 // キャンセル要求が来ていたらここで終了
    pthread_mutex_lock(&(this->mutex));   // 優先権を保持するまで待機

    for(int y_cnt=0; y_cnt<16; y_cnt++){
      int mask = 1;
      int line = matrix[y_cnt];
      for(int x_cnt=0; x_cnt<16; x_cnt++){
        if(y_cnt == x_cnt){ digitalWrite(SIN_Y, GPIO_HIGH); }
        if(line & mask){
          digitalWrite(SIN_X1, 1);
          digitalWrite(SIN_X2, 0);
        }else{
          digitalWrite(SIN_X1, 0);
          digitalWrite(SIN_X2, 0);
        }

        digitalWrite(CLOCK, GPIO_HIGH);

        digitalWrite(SIN_Y, GPIO_LOW);
        digitalWrite(SIN_X1, GPIO_LOW);
        digitalWrite(SIN_X2, GPIO_LOW);

        digitalWrite(CLOCK, GPIO_LOW);

        delay(0.01);
        mask <<= 1;
      }
      latch();
    }
    pthread_mutex_unlock(&(this->mutex)); // 優先権を破棄
    delay(0.01);
  }
}

void LedController::reset(void){
  std::cout << "reset" << std::endl;
  digitalWrite(SIN_Y  , GPIO_LOW);
  digitalWrite(SIN_X1 , GPIO_LOW);
  digitalWrite(SIN_X2 , GPIO_LOW);
  digitalWrite(CLOCK  , GPIO_LOW);
  digitalWrite(LATCH  , GPIO_LOW);
}

void LedController::latch(void){
  digitalWrite(LATCH, GPIO_LOW);
  digitalWrite(LATCH, GPIO_HIGH);
}

void LedController::setMatrix(Array a){
  int cnt = 0;
  Array::const_iterator aI = a.begin();
  Array::const_iterator aE = a.end();

  while (aI != aE and cnt < 16) {
    matrix[cnt] = std::atoi((*aI).to_s().c_str());
    ++aI;
    cnt++;
  }
}

Array LedController::getMatrix(void){
  Array result;
  for(int i=0; i<16; i++){ result.push(matrix[i]); }
  return result;
}

extern "C" {
  void Init_LedController() {
    Data_Type<LedController> led = define_class<LedController>("LedController")
     .define_constructor(Constructor<LedController>())
     .define_method("matrix",  &LedController::getMatrix)
     .define_method("matrix=", &LedController::setMatrix);
  }
}
