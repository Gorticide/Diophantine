// C++ program to check for solutions of diophantine equations

#include <iostream>
//#include <cmath>     // floor
#include <cstdlib>   // atof
#include <vector>
#include <utility>  // for using pair

//utility function to find the GCD of two numbers
int gcd(int a, int b) {

  int t;
  while (a)
    {
      t = a;
      a = b%a;
      b = t;
    }
  return b;
}

// This function checks if integral solutions are
// possible
bool isPossible(int a, int b, int c)
{
	return (c%gcd(a,b) == 0);
}

// Number of non-negative integer solutions to
//    a*x + b*y == c   .
int numberOfSolutions(int a, int b, int n) {

    //declaring vector of pairs
    std::vector<std::pair <int,int> > S;

    if (n == 0) {
        return 1;
    }

    // Count all positive solutions:
    int count = 0;
    for (int x = 1; x <= n / 2; x++) {
        for (int y = 1; y <= n; y++) {
            if (a*x + b*y == n) {
                S.push_back( std::make_pair(x, y) );
                count++;
                break;
            }
        }
    }
    // Printing the vector
    for (int i = 0; i < count; i++)
    {
        std::cout << "\n(x, y) = ";
        // "first" and "second" are used to access
        // 1st and 2nd element of pair respectively
        std::cout << "(" << S[i].first << ", "
             << S[i].second << ")" << std::endl;
    }

    return count;
}

//driver function
int main(int argc, char *argv[])  {

  if (argc!= 4)  {
	  std::cout << "[USE] : " << argv[0] << " <a> <b> <c> for ax + by = c";
    std::cout << "\nYou cannot have " << argc - 1 << " parameters.\n\n";
	  return -1;
  }
   int a = atoi(argv[1]);
   int b = atoi(argv[2]);
   int c = atoi(argv[3]);

	isPossible(a, b, c)? std::cout << "Possible\n\n" :
						std::cout << "Not Possible\n\n";

  isPossible(a, b, c)? std::cout << "\n\n" << numberOfSolutions(a, b, c)
                       << " positive integral solutions\n\n" :
                       std::cout << "No positive integral solutions\n\n";

	return 0;
}
