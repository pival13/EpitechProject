
#ifndef REF_PTR_HPP_
#define REF_PTR_HPP_

#include <cstddef>
#include <list>
#include "BaseComponent.hpp"

class RefPtr
{
    public:
        RefPtr(BaseComponent *rawPtr=nullptr);
        RefPtr(RefPtr const &other);
        RefPtr &operator=(RefPtr const &other);
        ~RefPtr();

        BaseComponent *get() const;

    private:
        BaseComponent *_rawPtr;
        static std::list<BaseComponent *> list;
};

#endif // REF_PTR_HPP_
