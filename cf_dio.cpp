#include <iostream>
#include <cmath>     // floor
#include <vector>
#include <tuple>  // for using pair

// These are needed just to "pause"
#include <istream>  // to use cin.get() so as to use function "pause"
#include <limits>   // Required for numeric_limits
#include <ios>      // Required for streamsize


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


 long* GetRationalExpansion(long numer, long denom, int NrFraction)  {

     long p = numer;
     long q = denom;
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

 std::vector<long> find_Positive_Integral_Solutions(
                long x,
                long y,
                long a,
                long b)  {

     struct Var {
               long value;
               long bound;
               char compare; // greater than: >   or   less than: <
      };

     Var t1, t2;
     std::vector<long> t;
     bool infinite(false);
     int minomax;
     char inf_dir;
     long t_min, t_max;

    if (b > 0) {
         t1.bound = std::floor(-double(x)/double(b));
         t1.value = t1.bound + 1;
         t1.compare = '>';
    }
    else if (b < 0) {
        t1.bound = std::ceil(-double(x)/double(b));
        t1.value = t1.bound - 1;
        t1.compare = '<';
    }
    if (a > 0) {
        t2.bound = std::floor(-double(y)/double(a));
        t2.value = t2.bound + 1;
        t2.compare = '>';
    }
    else if (a < 0) {
        t2.bound = std::ceil(-double(y)/double(a));
        t2.value = t2.bound - 1;
        t2.compare = '<';
    }

    if (t1.compare == t2.compare)  {  // Infinite amount of solutions
        std::cout << "\nThere are an infinite amount of positive integral solutions.\n\n";
        infinite = true;
        t.push_back(666);
        if (t1.compare == '>') {
           inf_dir = t1.compare;
           minomax = 1;
           if (t1.bound > t2.bound) t_max = t1.value;
           else if (t2.bound >= t1.bound)  t_max = t2.value;
           for (long j = t_max; j < t_max + 3; j++)
                      t.push_back(j);
        }
        else if (t1.compare == '<') {
           inf_dir = t1.compare;
           minomax = -1;
           if (t1.bound < t2.bound) t_min = t1.value;
           else if (t2.bound <= t1.bound)  t_min = t2.value;
           for (long j = t_min; j > t_min - 3; j--)
                     t.push_back(j);
       }
       t.push_back(-666);
    }
    else if (
             ( ( t1.bound < t2.bound) && (t1.compare == '<') )
           ||
             ( ( t2.bound < t1.bound) && (t2.compare == '<') )
            )
          std::cout << "\nNo value of t exists such that both x and y are "
                    << "positive integers.\n\n";

    else if (std::abs(t1.bound - t2.bound) == 1)    // and one is <, the other >
        std::cout << "\nNo integer exists between " << t1.bound << " and "
                  << t2.bound << std::endl;
    else  if (
              ( ( t1.bound < t2.bound) && (t1.compare == '>') )
            ||
              ( ( t2.bound < t1.bound) && (t2.compare == '>') )
             )
              {
                if (t1.bound > t2.bound)
                    for (int i = t2.value; i <= t1.value; i++)
                              t.push_back(i);

                else if (t2.bound > t1.bound)
                    for (int i = t1.value; i <= t2.value; i++)
                              t.push_back(i);
              }

    if (t.empty())  std::cout << "\nThere are no positive integral solutions.";

    std::cout << "\nt = { ";
    if (infinite == true) {
      for (std::vector<long>::const_iterator i = ++t.begin(); i != --t.end(); ++i)
                      std::cout << *i << ' ';
       std::cout << "... }";
    }
    else {
      for (std::vector<long>::const_iterator i = t.begin(); i != t.end(); ++i)
                    std::cout << *i << ' ';
      std::cout << "}\n\n";
    }

    if (t.empty())  {
      std::cout << "For integers t: { t " << t1.compare << ' ' << t1.bound
                << " } AND { t " << t2.compare << ' ' << t2.bound
                << " } = { }\n\n";
    }
    else {
    std::cout << "\t The interval of interest is: ";
    if (infinite == true)  {
        if (minomax == -1)
           std::cout << "{ t " << inf_dir << ' ' << t_min + 1 << " }\n\n";
        else if (minomax == 1)
           std::cout << "{ t " << inf_dir << ' ' << t_max - 1 << " }\n\n";

    }
    else if (t1.bound > t2.bound)
        std::cout << "{ " << t2.bound << " < t < " << t1.bound << " }\n\n";
    else if (t2.bound > t1.bound)
        std::cout << "{ " << t1.bound << " < t < " << t2.bound << " }\n\n";
    else if (t1.value == t2.value)
            std::cout << " { " << t1.value << " }\n\n";

    }


   return t;
 }

int gcd_count(long a, long b)    {

   long t;
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
 int gcd(long a, long b) {

   long t;
   while (a)
     {
       t = a;
       a = b%a;
       b = t;
     }
   return b;
 }

 // This function checks if integral solutions are possible
 bool isPossible(long a, long b, long c)
 {
 	return (c%gcd(a,b) == 0);
}

void myflush ( std::istream& in )
{
  in.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
  in.clear();
}

int pause ()  {

   do  {
       std::cout << std::endl << std::endl;
       std::cout << "Press ENTER  [ <-----||| ] to continue.\n";
      } while (std::cin.get() != '\n');

   return 0;
}

char sign (int var) {
  if (var > 0) return '+';
  if (var < 0) return '-';
  else return '?';
}

int main() {

//declaring vector of pairs
std::vector<std::pair <long,long> > conv;
int n, k;
long* cf;
long A, B, C, a, b, c, d, x0, y0, t;

std::vector<long> tVec;

int x = 1;
int y = -1;

int form = 0;
char more = 'Y';

/* x and y will be set to either +1 or -1 to define form:
   I will take inputs A, B, and C
   Then, depending on these values, assign value of -1 or 1 to x and y.
   if (A < 0) x = -1;
   if (B > 0) y = 1;
   find d = abs(gcd(A, B))
   c = C/d
   a = abs(A/d)
   b = abs(B/d)
*/
std::cout << "\nSolving Diophantine equations of the form A*x + B*y = C\n\n";
std::cout <<" Enter value of coefficient of x: ";
std::cin >> A;
std::cout <<" Enter value of coefficient of y: ";
std::cin >> B;
std::cout <<" Enter value of constant on right-hand side of equation: ";
std::cin >> C;

d = std::abs(gcd(A, B));

isPossible(A, B, C)? std::cout << "\nIntegral solutions are possible." :
                    std::cout << "\nNo integral solutions are possible since gcd("
                              << abs(A) << ", " << abs(B) << ") = "
                              << d << " does not divide " << C << "\n\n";

if (!isPossible(A, B, C)) return 0;

if ((C%d == 0)  && (d > 1) )  {
  c = C/d;
  a = std::abs(A/d);
  b = std::abs(B/d);
}
else {
  c = C;
  a = std::abs(A);
  b = std::abs(B);
}

if (A < 0) x = -1;
if (B > 0) y = 1;

if (x*y > 0) form = 1;
if (x*y < 0) form = 2;

if ((C%d == 0)  && (d > 1) )  {
  std::cout << "  The equation has been reduced to: "
            << x*a << "x " << sign(y) << ' ' << b << "y = " << c << "\n\n";
  }

if (form == 1) {  // x and y have same sign
  if (c < 0)  {
    if (x < 0) {   // -ax - by =  -c
      std::cout << "\nThe equation has been transformed from "
                << x*a << "x " << sign(y) << ' ' << b << "y = " << c;
      x = 1;
      y = 1;
      c *= -1;     // ax + by = c
      std::cout << " to " << x*a << "x " << sign(y) << ' ' << b << "y = " << c << "\n\n";
    }
    else {       //  ax + by = -c
      std::cout << "  Our equation is: "
                << x*a << "x " << sign(y) << ' ' << b << "y = " << c << "\n\n";
    }
  }
  else if (c > 0) {
      if (x < 0)  {   // -ax - by = c
        std::cout << "\nThe equation has been transformed from "
                  << x*a << "x " << sign(y) << ' ' << b << "y = " << c;
         x = 1;
         y = 1;
         c *= -1;  // ax + by = -c
         std::cout << " to " << x*a << "x " << sign(y) << ' ' << b << "y = " << c << "\n\n";
      }
      else     //  ax + by = c
        std::cout << "  Our equation is: "
                  << x*a << "x " << sign(y) << ' ' << b << "y = " << c << "\n\n";


      }

  }  // END FORM 1

  else if (form == 2)  {  // x and y have opposite sings
    if (c < 0)  {
      if (x < 0) {   // -ax + by =  -c
        std::cout << "\nThe equation has been transformed from "
                  << x*a << "x " << sign(y) << ' ' << b << "y = " << c;
        x = 1;
        y = -1;
        c *= -1;     // ax - by = c
        std::cout << " to " << x*a << "x " << sign(y) << ' ' << b << "y = " << c << "\n\n";
      }
      else {       //  ax - by = -c
        std::cout << "  Our equation is: "
                  << x*a << "x " << sign(y) << ' ' << b << "y = " << c << "\n\n";
      }
    }
    else if (c > 0) {
        if (x < 0)  {   // -ax + by = c
          std::cout << "\nThe equation has been transformed from "
                    << x*a << "x " << sign(y) << ' ' << b << "y = " << c;
           x = 1;
           y = -1;
           c *= -1;  // ax - by = -c
           std::cout << " to " << x*a << "x " << sign(y) << ' ' << b << "y = " << c << "\n\n";
        }
        else     //  ax - by = c
          std::cout << "  Our equation is: "
                    << x*a << "x " << sign(y) << ' ' << b << "y = " << c << "\n\n";

        }

  }  // END FORM 2

  // Create continued fraction GetRationalExpansion

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

   if (n%2 == 1)   {  // if there is an odd number of partial quotients
     if (cf[n-1] > 1) {  // if the last quotient in the cf is greater than 1
       k = n;
       long new_cf[n+1];
       new_cf[n] = 1;
       new_cf[n-1] = cf[n-1] - 1;
       for (int i = n-2; i >= 0; i--)
             new_cf[i] = cf[i];
       conv = convergents(new_cf, n+1);
       }
      else if (cf[n-1] == 1) {
       k = n - 2;
       long new_cf[n-1];
       new_cf[n-2] = cf[n-1] + 1;
       for (int i = n-3; i >= 0; i--)
              new_cf[i] = cf[i];
       conv = convergents(new_cf, n-1);
       }
    }
    else {    // There is already an even number of partial quotients in cf
      conv = convergents(cf, n);
      k = n - 1;
    }

    x0 = conv[k-1].second;   // x0 = q[n-1]
    y0 = conv[k-1].first;   // y0 = p[n - 1]

   std::cout << "conv[n-1] = " << conv[k-1].first << "/" << conv[k-1].second << "\t\t";
   std::cout << "conv[n] = " << conv[k].first << "/" << conv[k].second << "\n";
   std::cout << "\nq[n-1] = x0 = "  << x0;
   std::cout << ",\tp[n-1] = y0 = "  << y0;
   std::cout << "\t\tc*x0 = " << c*x0;
   std::cout << ",\tc*y0 = " << c*y0 << "\n";

  if (form == 1) {
    std::cout << "\nFORM: Ax + By = (+/-) C\t\t";
    std::cout << "Therefore, the general solution is:\n\n";

    std::cout << "x = " << c*x0 << " - " << b << "*t\n"
              << "y = " << a << "*t" << ' ' << sign(-c) << ' '
              << abs(c)*y0 << "\n";

    myflush ( std::cin );
    pause();

    std::cout << " To find particular solutions with only positive "
              << "integral values of x and y,\n we solve two inequalities "
              << "for t after setting right-hand sides to greater than 0.\n";
    tVec = find_Positive_Integral_Solutions(c*x0, -c*y0, a, -b);
    if (  tVec.empty()  || (*tVec.begin() == 666) ) {
       if (tVec.empty()) {
         std::cout << "There are no values of t which yield positive integral "
                   << "values for x and y\n\n";

         if (C < 0)  std::cout << "Since either x or y must be negative in order to make "
                        <<  "the sum of\n" << a << "x + " << b << "y = " << c << ", "
                        << "there are no values of t which will make both x and y "
                        << "positive integers.\n\n";
       }
       else if (*tVec.begin() == 666)  {
         std::cout << "\nAn infinite amount of positive integral solutions (x, y) when t = "
                   << "{ ";
         for (std::vector<long>::const_iterator i = tVec.begin(); i != tVec.end(); ++i)
               if ( (i != tVec.begin())  &&  (i != tVec.end())  )
                              std::cout << *i << ' ';

         std::cout << " ...... }\n\n";

       }
     }
      else {
        for (std::vector<long>::const_iterator i = tVec.begin(); i != tVec.end(); ++i)
        {
        t = *i;
        std::cout << "\nWhen t = "  << t << ", (x, y) = (" << c*x0 - b*t << ", "
                  << a*t - c*y0 << "):\t";
        std::cout << "(" << a << ")(" << c*x0 - b*t << ") + ("
                  << b << ")(" << a*t - c*y0 << ") = ("
                  << a*( c*x0 - b*t ) << ") + ("
                  << b*( a*t - c*y0 ) << ") = "
                  <<  a*( c*x0 - b*t ) + b*( a*t - c*y0 )
                  <<  std::endl;
        }
      }

      std::cout << "\nWould you like to find (x, y) for arbitrary values of t ? <Y/N> : ";
      std::cin >> more;
      while ( (more == 'Y') || (more == 'y') ) {
      std::cout << "\nx = " << c*x0 << " - " << b << "*t\n"
                << "y = " << a << "*t" << ' ' << sign(-c) << ' '
                << abs(c)*y0 << "\n";
      std::cout << "\nTo find a particular solution, enter a value for t: ";
      std::cin >> t;

      std::cout << "\nFor t = "  << t << ", (x, y) = (" << c*x0 - b*t << ", "
                << a*t - c*y0 << "):\t";
      std::cout << "(" << a << ")(" << c*x0 - b*t << ") + ("
                << b << ")(" << a*t - c*y0 << ") = ("
                << a*( c*x0 - b*t ) << ") + ("
                << b*( a*t - c*y0 ) << ") = "
                <<  a*( c*x0 - b*t ) + b*( a*t - c*y0 )
                <<  std::endl;

      std::cout << "\nWould you like to find another particular solution (x, y) ? <Y/N> : ";
      std::cin >> more;
        }

  }
  else if (form == 2)  {
    std::cout << "\nFORM: Ax - By = (+/-) C\t\t";
    std::cout << "Therefore, the general solution is:\n\n";
    std::cout << "x = " << c*x0 << " + " << b << "*t\n"
              << "y = " << c*y0 << " + " << a << "*t\n";
    myflush ( std::cin );
    pause();
    std::cout << " To find particular solutions with only positive "
              << "integral values of x and y,\n we solve two inequalities "
              << "for t after setting right-hand sides to greater than 0. \n\n";
    tVec = find_Positive_Integral_Solutions(c*x0, c*y0, a, b);
    if (  tVec.empty()  || (*tVec.begin() == 666) ) {
       if (tVec.empty()) {
         std::cout << "There are no values of t which yield positive integral "
                   << "values for x and y\n\n";

         if (C < 0)  std::cout << "Since either x or y must be negative in order to make "
                        <<  "the sum of\n" << a << "x + " << b << "y = " << c << ", "
                        << "there are no values of t which will make both x and y "
                        << "positive integers.\n\n";
        return 0;
       }
       else if (*tVec.begin() == 666)  {
         std::cout << "\nAn infinite amount of positive integral solutions (x, y) when t = "
                   << "{ ";
         for (std::vector<long>::const_iterator i = ++tVec.begin(); i != --tVec.end(); ++i)
                          std::cout << *i << ' ';

        std::cout << ".... }\n\n";
       }
     }
    else {
         for (std::vector<long>::const_iterator i = tVec.begin(); i != tVec.end(); ++i)
         {
         t = *i;
         std::cout << "\nWhen t = "  << t << ", (x, y) = (" << c*x0 + b*t << ", "
                   << c*y0 + a*t << "):\t";
         std::cout << "(" << a << ")(" << c*x0 + b*t << ") + ("
                   << -b << ")(" << c*y0 + a*t << ") = ("
                   << a*( c*x0 + b*t ) << ") + ("
                   << -b * ( c*y0 + a*t ) << ") = "
                   <<  a*( c*x0 + b*t ) + -b*( c*y0 + a*t )
                   <<  std::endl;
         }
    }

    std::cout << "\nWould you like to find (x, y) for arbitrary values of t ? <Y/N> : ";
    std::cin >> more;
    while ( (more == 'Y') || (more == 'y') )  {
      std::cout << "\nx = " << c*x0 << " + " << b << "*t\n"
                << "y = " << c*y0 << " + " << a << "*t\n";
      std::cout << "\nTo find a particular solution, enter a value for t: ";
      std::cin >> t;

      std::cout << "\nFor t = "  << t << ", (x, y) = (" << c*x0 + b*t << ", "
                << c*y0 + a*t << "):\t";
      std::cout << "(" << a << ")(" << c*x0 + b*t << ") + ("
                << -b << ")(" << c*y0 + a*t << ") = ("
                << a*( c*x0 + b*t ) << ") + ("
                << -b*( c*y0 + a*t ) << ") = "
                <<  a*( c*x0 + b*t ) - b*( c*y0 + a*t )
                <<  std::endl;
      std::cout << "\nWould you like to find another particular solution (x, y) ? <Y/N> : ";
      std::cin >> more;
      }

  }  // END FORM 2

std::cout << std::endl;
}   // END MAIN()
