#pragma once

#include <functional>
#include <ostream>
#include <type_traits>
#include <utility>

class ai_ref_count
{
public:
    ai_ref_count()
    {
        uses = 0;
    }

    void incref()
    {
        ++uses;
    }

    void decref()
    {
        --uses;
    }

    signed char use_count() const
    {
        return uses;
    }

private:
    signed char uses;
};

struct static_tag
{
};

struct const_tag
{
};

struct dynamic_tag
{
};

template<class T>
class ai_ptr
{
    typedef T *ai_ptr::*unspecified_bool_type;

public:
    typedef T element_type;

    ai_ptr()
    : ptr(nullptr), rep(nullptr)
    {
    }

    template<class U>
    ai_ptr(U *p, ai_ref_count *r)
    : ptr(nullptr), rep(nullptr)
    {
        reset(p, r);
    }

    ai_ptr(const ai_ptr &other)
    : ptr(nullptr), rep(nullptr)
    {
        reset(other);
    }

    template<class T2>
    ai_ptr(const ai_ptr<T2> &other, typename std::enable_if<std::is_convertible<T2 *, T *>::value, void>::type ** = nullptr)
    : ptr(nullptr), rep(nullptr)
    {
        reset(other);
    }

    template<class T2>
    ai_ptr(const ai_ptr<T2> &other, const static_tag &)
    : ptr(nullptr), rep(nullptr)
    {
        reset(static_cast<element_type *>(other.ptr), other.rep);
    }

    template<class T2>
    ai_ptr(const ai_ptr<T2> &other, const const_tag &)
    : ptr(nullptr), rep(nullptr)
    {
        reset(const_cast<element_type *>(other.ptr), other.rep);
    }

    template<class T2>
    ai_ptr(const ai_ptr<T2> &other, const dynamic_tag &)
    : ptr(nullptr), rep(nullptr)
    {
        element_type *ptr = dynamic_cast<element_type *>(other.ptr);
        if (ptr)
            reset(ptr, other.rep);
    }

    ai_ptr(ai_ptr &&right)
    : ptr(nullptr), rep(nullptr)
    {
        swap(right);
    }

    template<class T2>
    ai_ptr(ai_ptr<T2> &&right, typename std::enable_if<std::is_convertible<T2 *, T *>::value, void>::type ** = nullptr)
    : ptr(right.ptr), rep(right.rep)
    {
        right.ptr = nullptr;
        right.rep = nullptr;
    }

    ai_ptr &operator=(ai_ptr &&right)
    {
        ai_ptr(std::move(right)).swap(*this);
        return *this;
    }

    template<class T2>
    ai_ptr &operator=(ai_ptr<T2> &&right)
    {
        ai_ptr(std::move(right)).swap(*this);
        return *this;
    }

    ~ai_ptr()
    {
        if (rep)
            rep->decref();
    }

    ai_ptr &operator=(const ai_ptr &right)
    {
        ai_ptr(right).swap(*this);
        return *this;
    }

    template<class T2>
    ai_ptr &operator=(const ai_ptr<T2> &right)
    {
        ai_ptr(right).swap(*this);
        return *this;
    }

    void reset()
    {
        ai_ptr().swap(*this);
    }

    template<class U>
    void reset(U *p, ai_ref_count *r)
    {
        ai_ptr(p, r).swap(*this);
    }

    void swap(ai_ptr &other)
    {
        std::swap(rep, other.rep);
        std::swap(ptr, other.ptr);
    }

    T *get() const
    {
        return ptr;
    }

    T &operator*() const
    {
        return *ptr;
    }

    T *operator->() const
    {
        return ptr;
    }

    signed char use_count() const
    {
        return rep ? rep->use_count() : 0;
    }

    bool unique() const
    {
        return use_count() == 1;
    }

    operator unspecified_bool_type() const
    {
        return ptr ? &ai_ptr::ptr : nullptr;
    }

private:
    template<class T0>
    friend class ai_ptr;

    template<class T2>
    void reset(const ai_ptr<T2> &other)
    {
        reset(other.ptr, other.rep);
    }

    void reset(T *other_ptr, ai_ref_count *other_rep)
    {
        if (other_rep)
            other_rep->incref();
        if (rep)
            rep->decref();
        rep = other_rep;
        ptr = other_ptr;
    }

    T *ptr;
    ai_ref_count *rep;
};

template<class T1, class T2>
inline bool operator==(const ai_ptr<T1> &left, const ai_ptr<T2> &right)
{
    return left.get() == right.get();
}

template<class T1, class T2>
inline bool operator!=(const ai_ptr<T1> &left, const ai_ptr<T2> &right)
{
    return !(left == right);
}

template<class T1, class T2>
inline bool operator<(const ai_ptr<T1> &left, const ai_ptr<T2> &right)
{
    return std::less<decltype(false ? left.get() : right.get())>()(left.get(), right.get());
}

template<class T1, class T2>
inline bool operator>=(const ai_ptr<T1> &left, const ai_ptr<T2> &right)
{
    return !(left < right);
}

template<class T1, class T2>
inline bool operator>(const ai_ptr<T1> &left, const ai_ptr<T2> &right)
{
    return right < left;
}

template<class T1, class T2>
inline bool operator<=(const ai_ptr<T1> &left, const ai_ptr<T2> &right)
{
    return !(right < left);
}

template<class Elem, class Traits, class T>
inline std::basic_ostream<Elem, Traits> &operator<<(std::basic_ostream<Elem, Traits> &out, const ai_ptr<T> &p)
{
    return out << p.get();
}

template<class T>
inline void swap(ai_ptr<T> &left, ai_ptr<T> &right)
{
    left.swap(right);
}

template<class T1, class T2>
inline ai_ptr<T1> static_pointer_cast(const ai_ptr<T2> &other)
{
    return ai_ptr<T1>(other, static_tag());
}

template<class T1, class T2>
inline ai_ptr<T1> const_pointer_cast(const ai_ptr<T2> &other)
{
    return ai_ptr<T1>(other, const_tag());
}

template<class T1, class T2>
inline ai_ptr<T1> dynamic_pointer_cast(const ai_ptr<T2> &other)
{
    return ai_ptr<T1>(other, dynamic_tag());
}
