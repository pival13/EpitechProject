#include "ex05/DroidFactory.hpp"
#include "ex05/Carrier.hpp"
int main()
{
    Droid *d = new Droid("Bob");
    Supply s(Supply::Types::Wreck, 1, &d);
    Supply s1(Supply::Types::Silicon, 1000);
    Supply s2(Supply::Types::Iron, 1000);
    DroidFactory f(5);

    f << s1 << s2 << s;
    std::cout << f << std::endl;
    f >> d;
    std::cout << f << std::endl;
    std::cout << *d << std::endl;
}