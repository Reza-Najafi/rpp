#ifndef GUARD_MLOPEN_ALLOCATOR_HPP
#define GUARD_MLOPEN_ALLOCATOR_HPP

#include <cassert>

#include <hip/rpp/common.hpp>
#include <hip/rpp/errors.hpp>
#include <hip/rpp/manage_ptr.hpp>
#include <rpp.h>

namespace rpp {

struct AllocatorDeleter
{
    rppDeallocatorFunction deallocator;
    void* context;

    template <class T>
    void operator()(T* x) const
    {
        assert(deallocator != nullptr);
        if(x != nullptr)
        {
            deallocator(context, x);
        }
    }
};
struct Allocator
{
    rppAllocatorFunction allocator;
    rppDeallocatorFunction deallocator;
    void* context;

    using ManageDataPtr =
        std::unique_ptr<typename std::remove_pointer<Data_t>::type, AllocatorDeleter>;

    ManageDataPtr operator()(std::size_t n) const
    {
        assert(allocator != nullptr);
        assert(deallocator != nullptr);
        auto result = allocator(context, n);
        if(result == nullptr && n != 0)
        {
            RPP_THROW("Custom allocator failed to allocate memory for buffer size " +
                         std::to_string(n) + ": ");
        }
        return ManageDataPtr{DataCast(result), AllocatorDeleter{deallocator, context}};
    }
};

} // namespace rpp

#endif
