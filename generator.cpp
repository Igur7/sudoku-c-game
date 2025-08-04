
#include <vector>
#include <ctime>
#include <algorithm>

class SimpleLCG{
  private:
    unsigned long long seed;
    static constexpr unsigned long long a = 6364136223846793005ULL;
    static constexpr unsigned long long c = 1ULL;
    static constexpr unsigned long long m = (1ULL << 32);
   public:
     SimpleLCG(unsigned long long seedVal = time(nullptr)): seed(seedVal) {};

     unsigned int next(){
         seed = (seed * a + c) % m;
         return static_cast<unsigned int>(seed);
     }

};

template<typename T> void shuffle(std::vector<T>& vec, SimpleLCG& rng){
  for (size_t i = vec.size() - 1; i > 0; i--){
    size_t j = rng.next() %(i+1);
    std::swap(vec[i], vec[j]);
  }
}
