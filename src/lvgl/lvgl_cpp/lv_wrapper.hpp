/** \file lv_wrapper.hpp
 *  \brief Thin C++ wrapper template classes around LVGL objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include <memory>
#include <lvgl.h>
#include <functional>
#include <cstring>
#include <utility>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

// /** \namespace lvgl
//  *  \brief LVGL C++ wrappers.
//  */
// namespace lvgl {

// /** \typedef template <typename Class> using RawDblArray
//  *  \brief A unique_ptr wrapping a raw double array with custom deleter.
//  *  \param Class: array type.
//  */
// template <typename Class>
// using RawDblArray = std::unique_ptr<Class*, std::function<void(Class**)>>;

// /** \brief Generates a deleter function for a double array of given type and size.
//  *  \tparam Class: array type.
//  *  \param size: array size (1st dimension).
//  *  \returns a deleter function for double arrays of given type and size.
//  */
// template <typename Class>
// std::function<void(Class**)> RawDblArrayDeleter(size_t size)
// {
//     return [size](Class** obj) {
//         std::for_each(obj, obj + size, std::default_delete<Class[]>());
//         delete[] obj;
//     };
// }

// /** \fn template <typename Class> RawDblArray<Class> make_double_array(size_t size)
//  *  \brief Creates a double array of given type and size wrapped in a unique_ptr.
//  *  \tparam Class: array type.
//  *  \param size: array size (1st dimension).
//  *  \returns unique_ptr wrapping a double array of given type.
//  */
// template <typename Class>
// RawDblArray<Class> make_double_array(size_t size)
// {
//     return RawDblArray<Class>(new Class*[size], RawDblArrayDeleter<Class>(size));
// }

// /** \fn static RawDblArray<char> str_vector_to_char_array(const std::vector<std::string> & arr)
//  *  \brief Conversion function from string vector to double char array.
//  *  \param arr: string vector.
//  *  \returns a double char array with a copy of the content of input array.
//  */
// static RawDblArray<char> str_vector_to_char_array(const std::vector<std::string>& arr)
// {
//     auto raw_arr = make_double_array<char>(arr.size());
//     for (size_t n = 0; n < arr.size(); n++) {
//         raw_arr.get()[n] = static_cast<char*>(calloc(arr[n].size() + 1, sizeof(char)));
//         std::memset(raw_arr.get()[n], 0, arr[n].size() + 1);
//         std::copy(arr[n].begin(), arr[n].end(), raw_arr.get()[n]);
//     }
//     return raw_arr;
// }

/** \typedef template <auto DeleterFunction> CustomDeleter
 *  \brief Wraps a C deleter function for use with smart pointers.
 *
 *  This relies on the behaviour of the call operator that assumes
 *  that the left-hand side argument should be a function, and therefore
 *  gets cast to function pointer. At the same time, the integral_constant
 *  instance gives the wrapped value type as its own type.
 *
 *  \tparam DeleterFunction: C deleter function.
 */
template <auto DeleterFunction>
using CustomDeleter = std::integral_constant<std::decay_t<decltype(DeleterFunction)>, DeleterFunction>;

/** \typedef template <typename WrappedType, auto DeleterFunction> LvPointer
 *  \brief A pointer that wraps an object and defines a deleter from a deleter function.
 *  \tparam WrappedType: object type.
 *  \tparam DeleterFunction: deleter function.
 */
template <typename WrappedType, auto DeleterFunction>
using LvPointer = std::unique_ptr<WrappedType, CustomDeleter<DeleterFunction>>;

/** \fn template <typename LvClass> LvClass* lv_cls_alloc()
 *  \brief Allocates memory for an object of the given type with LVGL mem_alloc.
 *  \tparam LvClass: object type.
 *  \returns pointer to allocated memory.
 */
template <typename LvClass>
LvClass* lv_cls_alloc()
{
    return static_cast<LvClass*>(lv_malloc(sizeof(LvClass)));
}

/** \brief Template class meant to wrap C LVGL objects for C++.
 *
 *  This wrapper stores a pointer to an object and provides the
 *  possibility to specify a deleter function. It is important to
 *  define a constructor that allocates memory for the C object.
 *
 *  \tparam LvClass: LVGL type.
 *  \tparam lv_deleter: deleter function.
 */
template <typename LvClass, auto lv_deleter>
class PointerWrapper {
protected:
    /** \typedef LvPointerType
     *  \brief A shorthand for the wrapped object pointer type LvPointer<LvClass, lv_deleter>
     */
    using LvPointerType = LvPointer<LvClass, lv_deleter>;

    /** \typedef LvWrapperType
     *  \brief A shorthand for the wrapper class type PointerWrapper<LvClass, lv_deleter>
     */
    using LvWrapperType = PointerWrapper<LvClass, lv_deleter>;

    /** \typedef lv_cls
     *  \brief A shorthand for LvClass available within class members.
     */
    using lv_cls = LvClass;

    /** \typedef lv_cls_ptr
     *  \brief A shorthand for LvClass* available within class members.
     */
    using lv_cls_ptr = LvClass*;

    /** \property LvPointerType lv_obj
     *  \brief Pointer to the managed C LVGL object.
     */
    LvPointerType lv_obj;

    /** \property bool owns_ptr
     *  \brief Tells if object owns LvClass pointer.
     *
     *  If true, LvClass pointer will be freed on object's destruction.
     *  If false, LvClass pointer is assumed to be owned by something else.
     */
    bool owns_ptr = true;

public:
    /** \fn PointerWrapper()
     *  \brief Default constructor.
     */
    PointerWrapper() = default;

    /** \fn ~PointerWrapper()
     *  \brief Destructor.
     */
    ~PointerWrapper()
    {
        if (!this->owns_ptr)
            this->release_ptr();
    }

    // no copy constructor and copy assignment operator
    PointerWrapper(const LvPointerType& obj) = delete;
    PointerWrapper& operator=(const LvPointerType& obj) = delete;

    /** \fn PointerWrapper(LvClass * obj, bool owns_ptr=true)
     *  \brief Wrapping function with LvClass* argument.
     *  \param obj: raw pointer to wrap.
     *  \param owns_ptr: if true, takes pointer ownership.
     */
    PointerWrapper(LvClass* obj, bool owns_ptr = true)
    {
        this->lv_obj = LvPointerType(obj);
        this->owns_ptr = owns_ptr;
    }

    /** \fn PointerWrapper(LvPointerType && obj)
     *  \brief Move-wrapping function with LvPointerType argument.
     *  \param obj: object to move.
     */
    PointerWrapper(LvPointerType&& obj)
    {
        this->lv_obj = std::move(obj);
        obj = nullptr;
    }

    /** \fn PointerWrapper(LvWrapperType && obj)
     *  \brief Move constructor.
     *  \param obj: object to move.
     */
    PointerWrapper(LvWrapperType&& obj) : lv_obj(std::exchange(obj.lv_obj, nullptr)), owns_ptr(obj.owns_ptr) {}

    /** \fn PointerWrapper & operator=(LvWrapperType && obj)
     *  \brief Move assignment operator.
     *  \param obj: object to move.
     */
    PointerWrapper& operator=(LvWrapperType&& obj)
    {
        this->lv_obj = std::swap(this->lv_obj, obj.lv_obj);
        this->owns_ptr = obj.owns_ptr;
        return *this;
    }

    /** \fn LvClass & raw()
     *  \brief Access to owned raw LvClass object.
     *  \returns a reference to the owned LvClass object.
     */
    LvClass& raw()
    {
        return *this->lv_obj.get();
    }

    /** \fn const LvClass & raw() const
     *  \brief Access to owned raw LvClass object (const version).
     *  \returns a const reference to the owned LvClass object.
     */
    const LvClass& raw() const
    {
        return *this->lv_obj.get();
    }

    /** \fn LvClass & raw_ptr()
     *  \brief Access to owned raw LvClass object (pointer version).
     *  \returns a pointer to the owned LvClass object.
     */
    LvClass* raw_ptr()
    {
        return this->lv_obj.get();
    }

    /** \fn const LvClass & raw_ptr() const
     *  \brief Access to owned raw LvClass object (const pointer version).
     *  \returns a const pointer to the owned LvClass object.
     */
    const LvClass* raw_ptr() const
    {
        return this->lv_obj.get();
    }

    /** \fn LvClass * release_ptr()
     *  \brief Releases owned pointer. After this, the instance
     *  becomes invalid and must not be used.
     *  \returns raw pointer of managed object.
     */
    LvClass* release_ptr()
    {
        return this->lv_obj.release();
    }

    /** \fn template <class T> std::shared_ptr<T> get_shared()
     *  \brief Creates an image of the managed object wrapped in a shared
     *  pointer of the given class.
     *
     *  This is a convenience function for situations where we stored objects
     *  of type T in shared_ptr and need to store or compare temporary
     *  copies of them. This can happen in callbacks such as events. Instead of
     *  storing copies of C++ wrapper objects, I prefer to create temporary
     *  objects storing the C instance. For things like animations, it is always
     *  possible to use bare C functions if speed is required.
     *  I want to stress here that creating a unique_ptr encapsulating a raw pointer
     *  that exists already and releasing raw pointer before destruction makes little
     *  sense otherwise. It's a design issue, but the other option would have been
     *  to create a program-wide storage for C++ objects to be able to reverse-map
     *  them with their content.
     *
     *  \tparam T: type of shared pointer to create.
     *  \returns shared pointer of wrapped managed object.
     */
    template <class T>
    std::shared_ptr<T> get_shared()
    {
        return std::make_shared<T>(this->raw_ptr(), false);
    }

    /** \fn bool operator==(const PointerWrapper & obj) const
     *  \brief Comparison operator.
     *  \param obj: object to compare with.
     *  \returns true if managed objects are equal.
     */
    bool operator==(const PointerWrapper& obj) const
    {
        return obj.raw_ptr() == this->raw_ptr();
    }

    /** \fn LvClass & operator*()
     *  \brief Dereference operator.
     *  \returns a reference to the managed object.
     */
    LvClass& operator*()
    {
        return *this->lv_obj;
    }

    /** \fn const LvClass & operator*() const
     *  \brief Dereference operator (const version).
     *  \returns a const reference to the managed object.
     */
    const LvClass& operator*() const
    {
        return *this->lv_obj;
    }

    /** \fn LvClass * operator->()
     *  \brief Structure dereference operator.
     *  \returns access to the managed object content.
     */
    LvClass* operator->()
    {
        return this->lv_obj.get();
    }

    /** \fn const LvClass * operator->() const
     *  \brief Structure dereference operator (const version).
     *  \returns access to the managed object content.
     */
    const LvClass* operator->() const
    {
        return this->lv_obj.get();
    }
};

/** \class GenericCallback
 *  \brief This is a base class for callback containers.
 */
struct GenericCallback {
    virtual ~GenericCallback() = default;
};

/** \class GenericVariable
 *  \brief This is a base class for variable containers.
 */
struct GenericVariable {
    virtual ~GenericVariable() = default;
};

/** \brief This is a callback container that can be stored as GenericCallback.
 *  \tparam Ret: callback return type.
 *  \tparam Args: callback arguments.
 */
template <class Ret, class... Args>
class Callback : public GenericCallback {
private:
    /** \property Ret(* fct)(Args...)
     *  \brief Pointer to the callback function held.
     */
    Ret (*fct)(Args...);

public:
    /** \fn Callback(Ret(* fct)(Args...))
     *  \brief Constructor with function parameter.
     *  \param fct: pointer to the callback function to hold.
     */
    Callback(Ret (*fct)(Args...)) : fct(fct) {}

    /** \fn void operator=(Ret(* fct)(Args...))
     *  \brief Assignment operator.
     *  \param fct: pointer to the callback function to hold.
     */
    void operator=(Ret (*fct)(Args...))
    {
        this->fct = fct;
    }

    /** \fn Ret operator()(Args... args)
     *  \brief Call operator.
     *  \param args: function arguments.
     *  \returns function result.
     */
    Ret operator()(Args... args)
    {
        return this->fct(args...);
    }
};

/** \brief This is a variable container that can be stored as GenericVariable.
 *  \tparam T: variable type.
 */
template <class T>
class Variable : public GenericVariable {
private:
    /** \property T & var
     *  \brief Reference to the managed variable.
     */
    T& var;

public:
    /** \fn Variable(T & var)
     *  \brief Constructor with variable parameter.
     *  \param var: reference to the variable to hold.
     */
    Variable(T& var) : var(var) {}

    /** \fn void operator=(const T & var)
     *  \brief Assignment operator.
     *  \param var: reference to the variable to hold.
     */
    void operator=(const T& var)
    {
        this->var = var;
    }

    /** \fn T & operator()()
     *  \brief Call operator.
     *  \returns managed variable value.
     */
    T& operator()()
    {
        return this->var;
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit