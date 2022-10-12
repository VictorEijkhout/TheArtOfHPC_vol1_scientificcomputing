#include <iostream>
#include <atomic>
#include <thread>
#include <array>

class SideProcessor
{
public:
  SideProcessor()
    : dataArr{}
  {
  };

  void start() {
    processingRequested = true;
  };

  bool isStarted() {
    return processingRequested;
  };

  bool isDone() {
    return !processingRequested;
  };

  void finish() {
    processingRequested = false;
  }

  void run(std::atomic<bool>* exitRequested) {
    while(!(*exitRequested)) {
      // Spin on the flag.
      while(!(isStarted()) && !(*exitRequested)) {
      }
      if (*exitRequested) {
	// If we were asked to spin down, break out of the loop.
	break;
      }

      // Process
      processData();

      // Flag that we're done.
      finish();
    }
  };

private:
  std::atomic<bool> processingRequested;

#ifdef PAD_ALIGNMENT
  std::array<bool, 64> padding;
#endif

  std::array<int, 100> dataArr;

  void processData() {
    // Add 1 to every element a bunch of times.
    std::cout << "Processing data." << std::endl;
    for (unsigned int i = 0; i < 10000000; ++i) {
      for (unsigned int j = 0; j < 100; ++j) {
	dataArr[j] += 1;
      }
    }
    std::cout << "Done processing." << std::endl;
  };
};

int main() {
  std::atomic<bool> exitRequested;
  exitRequested = false;

  SideProcessor sideProcessor;
  std::thread processThreadObj = std::thread(&SideProcessor::run,
					     &sideProcessor, &exitRequested);

  // Spinlock while the thread is doing work.
  std::cout << "Starting processing." << std::endl;
  sideProcessor.start();
  while (!(sideProcessor.isDone())) {
  }

  // Spin the thread down.
  std::cout << "Waiting for thread to spin down." << std::endl;
  exitRequested = true;
  processThreadObj.join();

  std::cout << "Done." << std::endl;

  return 0;
}
