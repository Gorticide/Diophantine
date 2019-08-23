#include <iostream>
#include <cmath>     // floor
#include <vector>

std::vector<int> find_Positive_Integral_Solutions(
               int x0,
               int y0,
               int a,
               int b)  {

    std::vector<int> v;

    int t1 = (-x0/b);
    int t2 = (-y0/a);

    if (t1 > t2)  {
        t2 = (-y0/a) + 1;
        for (int i = t2; i <= t1; i++)
            v.push_back(i);
    }
    else if (t2 > t1)  {
        t1 = (-x0/b) + 1;
        for (int i = t1; i <= t2; i++)
            v.push_back(i);
    }

    std::cout << "t1 = " << t1;
    std::cout << "\nt2 = " << t2;

    return v;
}

int main() {

    int x0, y0, a, b;
    std::vector<int> t;
    
    //Get 2 equations
    std::cout << "We will find the set of values of t for which x and y\n" 
              << "are positive integers and represent a general solution\n"
              << " in the form x = x0 + b*t, y = y0 + a*t\n\n"
              << "Enter integer values for x0 and b: ";
    std::cin >> x0 >> b;
    std::cout << "\nEnter integer values of y0 and a: ";
    std::cin >> y0 >> a;

    t = find_Positive_Integral_Solutions(x0, y0, a, b);

    std::cout << "\n\nt = { ";

    for (std::vector<int>::const_iterator i = t.begin(); i != t.end(); ++i)
          std::cout << *i << ' ';

    std::cout << "}\n\n";

    std::cout << std::endl; 
    
    
    
    

}