#include <iostream>
#include <vector>
#include <chrono>
//#include <algorithm>
//#include <execution>
int sieve(int x);
int squarerootprimes(int x);

int main(){
	uint32_t x;
	char y;
	std::cout << "Use Sieve of Eratosthenes(E) or sqrt(S)?";
	std::cin >> y;
	std::chrono::steady_clock::time_point start;
	int p;
	if(y == 'E'){
		std::cout << "pick a number: ";
		std::cin >> x;
		std::cout << "calculating all primes under " << x << " with Sieve of Eratosthenes" << std::endl;
		start = std::chrono::steady_clock::now();
		p = sieve(x);
	}
	else if( y == 'S'){
		std::cout << "how many primes? ";
		std::cin >> x;
		std::cout << "calculating " << x << " primes via square root method" << std::endl;
		start = std::chrono::steady_clock::now();
		p = squarerootprimes(x);
	}
	else{
		std::cout << "Just type in E or S next time :)";
		return 0;
	}

	
	const auto end{std::chrono::steady_clock::now()};
	const std::chrono::duration<double> elapsed_seconds{end - start};
	std::cout << "The " << x << " prime is: " << p << std::endl;
	std::cout << "Time: " << elapsed_seconds.count() << " seconds" << std::endl;

	return 0;
}


//Sieve of Eratosthenes, shortened 50millionth from ~3 min to ~1 min
int sieve(int x){
	if(x < 2){return 0;}
	std::vector<bool> A(x+1, true);
	int root = sqrt(x);
	for(int i = 2; i <= root; ++i){
		if(A[i] == true){
			for(int j = i*i; j <= x; j += i){
				A[j] = false;
			}
		}
	}

	//get the last prime
	int r = A.size()-1;
	while(A[r] == false){
		r--;
	}
	return r;
}

int squarerootprimes(int x){
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
			if(curplace%1000000 == 0){ //this if is just to see every millionth prime, not necessary
				std::cout << curplace << " " << primes[curplace-1] << std::endl;
			}
		}
		n+=2;
	}
	return primes[x-1];
}
