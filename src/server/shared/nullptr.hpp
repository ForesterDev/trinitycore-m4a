#pragma once

// requires GCC
#ifdef __GNUC__
// requires GCC version older than 4.6
#if __GNUC__ < 4 || __GNUC__ == 4 && __GNUC_MINOR__ < 6

#include <cstddef>
#include <type_traits>

namespace std
{
    struct _M_clear_type;

    class nullptr_t
    {   // typedef for decltype(nullptr)
    public:
        operator _M_clear_type *() const
        {   // return null pointer
            return NULL;
        }

        template<class _ty>
            operator _ty *() const
        {   // return null pointer
            return 0;
        }

        template<class _ty1, class _ty2>
            operator _ty1 _ty2::*() const
        {   // return null member pointer
            return 0;
        }
    };

    template<>
        struct is_integral<nullptr_t>
        : public true_type
    {   // make function work with nullptr_t
    };
}

#define nullptr ::std::nullptr_t()

#endif  // __GNUC__ < 4 || __GNUC__ == 4 && __GNUC_MINOR__ < 6
#endif  // __GNUC__
