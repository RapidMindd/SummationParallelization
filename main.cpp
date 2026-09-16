#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

class Clicker {
public:
  Clicker():
    start_(std::chrono::steady_clock::now())
  {}
  double millisec() const
  {
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::steady_clock;
    const auto t = steady_clock::now();
    return duration_cast< milliseconds >(t - start_).count();
  }
private:
  std::chrono::time_point< std::chrono::steady_clock > start_;
};

constexpr size_t quantity = 1'000'000'000;

std::vector< size_t > generate()
{
  std::vector< size_t > nums(quantity);
  for (size_t i = 0; i < quantity; ++i) {
    nums[i] = i;
  }
  return nums;
}

size_t summator(const std::vector< size_t >& data, size_t start, size_t count)
{
  size_t sum = 0;
  for (size_t i = 0; i < count; ++i) {
    sum += data[start + i];
  }
  return sum;
}

int main(int argc, char* argv[])
{
  if (argc != 2) {
    return 1;
  }
  int thread_count = 0;
  try {
    thread_count = std::stoi(argv[1]);
  } catch (std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  if (thread_count <= 0) {
    return 1;
  }
  auto data = generate();
  //std::this_thread::sleep_for(std::chrono::seconds(10));
  std::vector< std::future< size_t > > threads;
  size_t step = quantity / thread_count;
  size_t remainder = quantity % thread_count;
  Clicker cl;
  double start = cl.millisec();
  int i = 0;
  for (; i < thread_count - 1; ++i) {
    threads.push_back(std::async(std::launch::async, summator, std::ref(data), step * i, step));
  }
  threads.push_back(
      std::async(std::launch::async, summator, std::ref(data), step * i, step + remainder));
  size_t sum = 0;
  for (auto& thread: threads) {
    sum += thread.get();
  }
  double end = cl.millisec();
  std::cout << end - start << "\n";
  std::cout << sum << "\n";
}
