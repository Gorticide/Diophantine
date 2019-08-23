#include <iostream>
#include <cmath>     // floor
#include <vector>
#include <utility>  // for using pair

// This code directly implements the theorems found in
// CONTINUED FRACTIONS by CD Olds, c.1963

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


 long* GetRationalExpansion(int numer, int denom, int NrFraction)  {

     int p = numer;
     int q = denom;
     long *a = NULL;
     //std::cout << "\narray created with "  << NrFraction << " elements?\n";
     a = new long[NrFraction];

     for (int i = 0; i < NrFraction; i++)
       a[i] = 0;

     int t;
     int itr = 0;
     while (p)
       {
         t = p;
         p = q%p;
         q = t;
         if (p != 0) a[itr] = q/p;
         itr++;
       }


     return a;
     delete [] a;
     a = NULL;

 }


int gcd_count(int a, int b)    {

   int t;
   int count = 0;
   while (a)
     {
       t = a;
       a = b%a;
       b = t;
       count++;
     }
     count--;

   return count;
 }

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

 // This function checks if integral solutions are possible
 bool isPossible(int a, int b, int c)
 {
 	return (c%gcd(a,b) == 0);
 }



 int main() {

 //declaring vector of pairs
 std::vector<std::pair <long,long> > C;
 int n, k;
 long* cf;
 long a, b, c, x0, y0, t;

 std::cout << "\nSolving Diophantine equations of the form A*x + B*y = C\n\n";
 std::cout <<" Enter value of coefficient of x: ";
 std::cin >> a;
 std::cout <<" Enter value of coefficient of y: ";
 std::cin >> b;
 std::cout <<" Enter value of constant on right-hand side of equation: ";
 std::cin >> c;

 isPossible(a, b, c)? std::cout << "Integral solutions are possible:\n\n" :
           std::cout << "\nNo integral solutions are possible since gcd("
                     << abs(a) << ", " << abs(b) << ") = "
                     << std::abs(gcd(a,b)) << " does not divide "
                     << c << "\n\n";

 if (!isPossible(a, b, c)) return 0;

 if ((c%std::abs(gcd(a, b)) == 0)  && (std::abs(gcd(a, b)) > 1) )  {
   int d = std::abs(gcd(a, b));
   c /= d;
   a /= d;
   b /= d;
 }

 long numerator = abs(a);
 long denominator = abs(b);

 if (numerator < denominator)  {
   n = gcd_count(denominator, numerator);
   //std::cout << "\ngcd_count returns " << n << "\n";
   n++;
   //std::cout << "\nadjustment made to n = " << n << "\n";
   cf = GetRationalExpansion(denominator, numerator, n);

   for (int i = n-1; i > 0; i--)
      cf[i] = cf[i-1];

   cf[0] = 0;
 }
 else {
   n = gcd_count(numerator, denominator);
   //std::cout << "\ngcd_count returns " << n << "\n";
   cf = GetRationalExpansion(numerator, denominator, n);

 }

 if (c > 0)  {        // if c is a POSITIVE number
   if (n%2 == 1)   {  // if there is an odd number of partial quotients
     if (cf[n-1] > 1) {  // if the last quotient in the cf is greater than 1
       k = n;
       long new_cf[n+1];
       new_cf[n] = 1;
       new_cf[n-1] = cf[n-1] - 1;
       for (int i = n-2; i >= 0; i--)
             new_cf[i] = cf[i];
       C = convergents(new_cf, n+1);
       }
      else if (cf[n-1] == 1) {
       k = n - 2;
       long new_cf[n-1];
       new_cf[n-2] = cf[n-1] + 1;
       for (int i = n-3; i >= 0; i--)
              new_cf[i] = cf[i];
       C = convergents(new_cf, n-1);
       }
    }
    else {
      C = convergents(cf, n);
      k = n - 1;
    }
  }
  else if (c < 0)  {  // if c is a NEGATIVE number
    if (n%2 == 0)   {  // if there is an even number of partial quotients
      if (cf[n-1] > 1) {  // last quotient a_n has index "n-1"
         k = n;
         long new_cf[n+1];
         new_cf[n] = 1;
         new_cf[n-1] = cf[n-1] - 1;
         for (int i = n-2; i >= 0; i--)
                new_cf[i] = cf[i];
         C = convergents(new_cf, n+1);
        }
        else if (cf[n-1] == 1) {
           k = n - 2;
           long new_cf[n-1];
           new_cf[n-2] = cf[n-1] + 1;
           for (int i = n-3; i >= 0; i--)
                 new_cf[i] = cf[i];
           C = convergents(new_cf, n-1);
           }
        }
        else {
            C = convergents(cf, n);
            k = n - 1;
         }
   }
  x0 = C[k-1].second;   // x0 = q[n-1]
  y0 = C[k-1].first;   // y0 = p[n - 1]

 std::cout << "\nC[n-1] = " << C[k-1].first << "/" << C[k-1].second << "\t\t";
 std::cout << "C[n] = " << C[k].first << "/" << C[k].second << "\n\n";

if (c > 0) {

 if (a*b < 0) {
   std::cout << "Therefore, the general solution is:\n\n";
   std::cout << "x = " << c*x0 << " + " << abs(b) << "*t\n"
             << "y = " << c*y0 << " + " << abs(a) << "*t\n\n";

   std::cout << "To find a particular solution, enter a value for t: ";
   std::cin >> t;
   std::cout << "\nFor t = "  << t << ", (x, y) = (" << c*x0 + abs(b)*t << ", "
             << c*y0 + abs(a)*t << ")\n\n";
   std::cout << "\n(" << a << ")(" << abs(c)*x0 + abs(b)*t << ") + ("
             << b << ")(" << abs(c)*y0 + abs(a)*t << ") = ("
             << a*( abs(c)*x0 + abs(b)*t ) << ") + ("
             << b * ( abs(c)*y0 + abs(a)*t ) << ") = "
             <<  a*( abs(c)*x0 + abs(b)*t ) + b * ( abs(c)*y0 + abs(a)*t )
             <<  "\n\n";
  }
  else if (a*b > 0)  {
    std::cout << "Therefore, the general solution is:\n\n";
    std::cout << "x = " << c*x0 << " - " << abs(b) << "*t\n"
              << "y = " << a << "*t" << " - " << c*y0 << "\n\n";

    std::cout << "To find a particular solution, enter a value for t: ";
    std::cin >> t;
    std::cout << "\nFor t = "  << t << ", (x, y) = (" << c*x0 - b*t << ", "
              << a*t - c*y0 << ")\n\n";
    std::cout << "\n(" << a << ")(" << c*x0 - b*t << ") + ("
              << b << ")(" << a*t - c*y0 << ") = ("
              << a*( c*x0 + b*t ) << ") + ("
              << b * ( -a*t - c*y0 ) << ") = "
              <<  a*( c*x0 + b*t ) + b * ( -a*t - c*y0 )
              <<  "\n\n";
  }
 }
  else if (c < 0)  {

   if (a*b < 0) {
     std::cout << "Therefore, the general solution is:\n\n";
     std::cout << "x = " << abs(c)*x0 << " + " << abs(b) << "*t\n"
               << "y = " << abs(c)*y0 << " + " << abs(a) << "*t\n\n";

     std::cout << "To find a particular solution, enter a value for t: ";
     std::cin >> t;
     std::cout << "\nFor t = "  << t << ", (x, y) = ("
               << abs(c)*x0 + abs(b)*t << ", "
               << abs(c)*y0 + abs(a)*t << ")\n\n";
     std::cout << "\n(" << a << ")(" << abs(c)*x0 + abs(b)*t << ") + ("
               << b << ")(" << abs(c)*y0 + abs(a)*t << ") = ("
               << a*( abs(c)*x0 + abs(b)*t ) << ") + ("
               << b * ( abs(c)*y0 + abs(a)*t ) << ") = "
               <<  a*( abs(c)*x0 + abs(b)*t ) + b * ( abs(c)*y0 + abs(a)*t )
               <<  "\n\n";


    }
    else if (a*b > 0)  {
      std::cout << "Therefore, the general solution is:\n\n";
      std::cout << "x = " << c*x0 << " + " << abs(b) << "*t\n"
                << "y = " << -c*y0 << " - " << a << "*t\n\n";

      std::cout << "To find a particular solution, enter a value for t: ";
      std::cin >> t;
      std::cout << "\nFor t = "  << t << ", (x, y) = (" << c*x0 + b*t << ", "
                << -a*t - c*y0 << ")\n\n";
      std::cout << "\n(" << a << ")(" << c*x0 + b*t << ") + ("
                << b << ")(" << -a*t - c*y0 << ") = ("
                << a*( c*x0 + b*t ) << ") + ("
                << b * ( -a*t - c*y0 ) << ") = "
                <<  a*( c*x0 + b*t ) + b * ( -a*t - c*y0 )
                <<  "\n\n";

    }
  }
 }
