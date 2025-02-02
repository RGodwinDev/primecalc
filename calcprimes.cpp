#include <iostream>
#include <vector>
#include <chrono>
//#include <algorithm>
//#include <execution>

int main(){
	uint32_t x;
	std::cout << "how many primes? ";
	std::cin >> x;
	std::cout << "calculating " << x << " primes" << std::endl;
	
	const auto start{std::chrono::steady_clock::now()};
	std::vector<uint32_t> primes(x, 0);
	
	primes[0] = 2;
	primes[1] = 3;
	primes[2] = 5;
	primes[3] = 7;
	primes[4] = 11;
	
	uint32_t n = 13;
	//uint32_t rootLoc = 0;
	uint32_t root;
	uint32_t curplace = 5;
	while(curplace <= x){
		root = sqrt(n);
		bool broke = false;
		
		//attempt at paralleling, it made 500k primes take almost as long as 10million primes
		
		//keep track of the root
		/*
		while(primes[rootLoc] < root){rootLoc++;}
		std::for_each(std::execution::par, primes.begin(), primes.begin() + rootLoc, [n, &broke](uint32_t prime){
			if(n%prime == 0){broke = true;}
		});
		*/
		
		for(uint32_t i = 0; primes[i] <= root; ++i){ //start at 2, because there's no point looking at 1 and 2.
			if(n % primes[i] == 0){
				broke = true;
				break;
			}
		}
		
		
		if(!broke){
			primes[curplace++] = n;
			if(curplace%1000000 == 0){
				std::cout << curplace << " " << primes[curplace-1] << std::endl;
			}
		}
		n+=2;
	}
	const auto end{std::chrono::steady_clock::now()};
	const std::chrono::duration<double> elapsed_seconds{end - start};
	std::cout << primes.size() << std::endl;
	std::cout << "The " << x << " prime is: " << primes[x-1] << std::endl;
	std::cout << "Time: " << elapsed_seconds.count() << " seconds" << std::endl;
	return 0;
}