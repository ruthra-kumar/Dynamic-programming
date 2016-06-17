//finding primes between 1 and 10000 using seive of eratosthenes
#include <iostream>
#include <vector>
//set upper limit with this defnition
#define LIMIT 10000
using namespace std;

int main(int argc,char *argv[])
{
    vector<bool> Primes(LIMIT+1,1);
    for(long long i=2; i<=LIMIT; ++i)
    {
        if(Primes.at(i)){
            long long Number = i;
            for(long long j=(Number+Number); j<=LIMIT; j+=Number)
            {
                Primes[j] = 0;
            }
        }
    }
    return 0;
}
