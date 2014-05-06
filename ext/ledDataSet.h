#include <pthread.h>
#include "rice/Array.hpp"

class LedDataSet {
public:
  LedDataSet();
  ~LedDataSet();
  void setMatrix(Rice::Array a);
  Rice::Array getMatrix(void);
private:
  void threadStart(void);
  static void* mainLoopLauncher(void* args);
  void mainLoop(void);
  void reset(void);
  void latch(void);

  int matrix[16];

  static const int SIN_Y  = 0;
  static const int SIN_X1 = 6;
  static const int SIN_X2 = 3;
  static const int CLOCK  = 4;
  static const int LATCH  = 5;

  static const int GPIO_LOW    = 0;
  static const int GPIO_HIGH   = 1;

  pthread_t thread_handler;  // スレッドハンドラ
  char thread_start_flg;
  pthread_mutex_t mutex;     // ミューテックス(排他処理で優先権を決めるやつ)
};
