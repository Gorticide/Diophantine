#include <iostream>
#include <vector>
#include <utility>  // for using pair

std::vector<std::pair <long, long> > convergents(long* arr, int size)  {

   std::vector<std::pair <long, long> > v;

    // We add 2 elements to each array to compensate
    int new_size = size + 2;
    long p[new_size], q[new_size], a[new_size];
    int i;

  //The first two convergents are 0/1 and 1/0
  // In CD Olds book, p[-1] = 0, p[0] = 1, q[-1] = 1, q[0] = 0
  // but since we cannot start array at -1,
  // p[0] <---| p[-1] = 0
  // p[1] <---| p[0] = 1
  // q[0] <---| q[-1] = 1
  // q[1] <---| q[0] = 0

  // -1 ---> 0
  // 0 ---> 1
  // 1 ---> 2  Hence, a1, which is normally a[0] now must be a[2]

  p[0] = 0; q[0] = 1;
  p[1] = 1; q[1] = 0;

  a[0] = -1;  // NOT USING !
  a[1] = -1;  // NOT USING !

 for (i = 2; i < new_size; i++)  {
      a[i] = arr[i-2];
 }

 for(i = 2; i < new_size; i++) {
   p[i] = a[i]*p[i-1] + p[i-2];
   q[i] = a[i]*q[i-1] + q[i-2];

 }

 for (i = 0; i < size; i++)
   v.push_back( std::make_pair(p[i+2], q[i+2]) );

 return v;


 }

 int main() {

 //declaring vector of pairs
 std::vector<std::pair <long,long> > C;
 long cf[6] = {2, 4, 1, 8, 1, 1};
 long a, b, c;
 a = 205;
 b = 93;
 c = 1;

 C = convergents(cf, 6);

 std::cout << "\nC[n-1] = " << C[4].first << "/" << C[4].second << "\n";
std::cout << "\nC[n] = " << C[5].first << "/" << C[5].second << " = "
          << a << "/" << b << "\n\n";


 }
