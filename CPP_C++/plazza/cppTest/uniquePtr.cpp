#include <utility>
#include <memory>
#include <iostream>

void f2(std::unique_ptr<int> a)
{
    printf("d = %p\n", a.get());
}

void f(std::unique_ptr<int> &a)
{
    printf("b (ref) = %p\n", a.get());
    std::unique_ptr<int> b = std::move(a);
    printf("b (ref) = %p; c =  %p\n", a.get(), b.get());
    f2(std::move(b));
    printf("c = %p\n", b.get());
}

int main()
{
    std::unique_ptr<int> a = std::make_unique<int>(5);//std::move(s.front());
    printf("a = %p\n", a.get());
    std::unique_ptr<int> b = std::move(a);
    printf("a = %p; b = %p\n", a.get(), b.get());
    f(b);
    printf("b = %p\n", b.get());
}