#include <iostream>
#include <cmath>     // floor
#include <vector>

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

int main() {

    long x0, y0, a, b;
    std::vector<long> t;

    //Get 2 equations
    std::cout << "We will find the set of values of t for which x and y\n"
              << "are positive integers and represent a general solution\n"
              << " in the form x = x0 + b*t, y = y0 + a*t\n\n"
              << "Enter integer values for x0 and b: ";
    std::cin >> x0 >> b;
    std::cout << "\nEnter integer values of y0 and a: ";
    std::cin >> y0 >> a;

    t = find_Positive_Integral_Solutions(x0, y0, a, b);

    if (  t.empty()  || (*t.begin() == 666) ) {
       if (t.empty()) {
         std::cout << "There are no values of t which yield positive integral "
                   << "values for x and y\n\n";

         return 0;
       }
       else if (*t.begin() == 666)  {
         std::cout << "\nAn infinite amount of positive integral solutions (x, y) when t = "
                   << "{ ";
         for (std::vector<long>::const_iterator i = ++t.begin(); i != --t.end(); ++i)
                          std::cout << *i << ' ';

        std::cout << ".... }\n\n";
       }
    }
    else {
      std::cout << "\n\nt = { ";

      for (std::vector<long>::const_iterator i = t.begin(); i != t.end(); ++i)
            std::cout << *i << ' ';

      std::cout << "}\n\n";
    }

    std::cout << std::endl;
}
