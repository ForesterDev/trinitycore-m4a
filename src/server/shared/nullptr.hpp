#pragma once

#ifdef __GNUC__

namespace std
{
    class nullptr_t
    {   // typedef for decltype(nullptr)
    public:
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
}

#define nullptr ::std::nullptr_t()

#endif  // __GNUC__
