#include "clock.hpp"
#include <thread>

namespace gs {
  namespace util {

    Clock::Clock() : currentFrameRate(0.0f), currentUncappedFrameRate(0.0f) {}

    Clock::~Clock() {}

    void Clock::begin() {
      S = std::chrono::high_resolution_clock::now();
    }

    void Clock::end() {
      E = std::chrono::high_resolution_clock::now();
      difference = std::chrono::duration_cast<Duration>(E - S);
    }

    void Clock::wait(unsigned int framerate) {
      float targetDuration = framesToMilliseconds(framerate);
      float actualDuration = difference.count();
      
      currentUncappedFrameRate = millisecondsToFrames(actualDuration);

      if (actualDuration < targetDuration) {
        std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(targetDuration - actualDuration));
        currentFrameRate = static_cast<float>(framerate);
      } else {
        currentFrameRate = currentUncappedFrameRate;
      }
    }

    float Clock::getFrameRate() const {
      return currentFrameRate;
    }

    float Clock::getUncappedFrameRate() const {
      return currentUncappedFrameRate;
    }

    float Clock::framesToMilliseconds(unsigned int framerate) {
      return 1000.0f / static_cast<float>(framerate);
    }

    float Clock::millisecondsToFrames(float duration) {
      return 1000.0f / duration;
    }

  } // namespace util
} // namespace gs
