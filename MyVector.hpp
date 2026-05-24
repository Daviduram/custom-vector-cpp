
/**
 *Name: David Ramirez
*Email: Daviduramirez@csu.fullerton.edu
*Email main: Daviduramirez27
 */


/// Your welcome
#include <assert.h>
#include <iostream>
#include <string>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <new>


typedef std::string string;
using std::cout;
namespace CPSC131::MyVector
{

	//
	template <typename T>
	class MyVector
	{
		public:
			
			/*******************
			 * Static constants
			 ******************/
			
			/// Default capacity
			static constexpr size_t DEFAULT_CAPACITY = 64;
			
			/// Minimum capacity
			static constexpr size_t MINIMUM_CAPACITY = 8;
			
			/*****************************
			 * Constructors / Destructors
			 ****************************/
			
			/// Normal constructor
			MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY)
			{
				// TODO: Your code here
				size_ = 0;
				if (capacity < MINIMUM_CAPACITY) {
					capacity =MINIMUM_CAPACITY;
				}
				capacity_ = capacity;
				elements_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));
			}
			
			/// Copy constructor
			MyVector(const MyVector& other)
			{
				// TODO: Your code here
				size_ = other.size_;
				capacity_ = other.capacity_;
				elements_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));
				for(size_t i = 0; i < size_; ++i) {
					new (&elements_[i]) T(other.elements_[i]);
				}
			}
			
			/**
			 * Destructor
			 * Cleanup here.
			 */
			~MyVector()
			{
				// TODO: Your code here
				destroy_range(0, size_);
				::operator delete(elements_);
				elements_ = nullptr;
				size_ = 0;
				capacity_ = 0;
			}
			
			/************
			 * Operators
			 ************/
			
			///	Assignment operator
			MyVector& operator=(const MyVector& rhs)
			{
				// TODO: Your code here
				destroy_range(0, size_);
				::operator delete(elements_);
				size_ = rhs.size_;
				capacity_ = rhs.capacity_;
				elements_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));
				for (size_t i = 0; i < size_; ++i) {
					new (&elements_[i]) T(rhs.elements_[i]);
				}
				return *this;
			}
			
			/// Operator overload to at()
			T& operator[](size_t index) const
			{
				// TODO: Your code here
				
				//	erase me
				return at(index);
			}
			
			/************
			 * Accessors
			 ************/
			
			/// Return a raw pointer to the elements_ array
			T* elements()
			{
				// TODO: Your code here
				
				//	erase me, nah i aint erasing but im sleepy at 11pm.
				return elements_;
			}
			
			/// Return the number of valid elements in our data
			size_t size() const
			{
				// TODO: Your code here
				
				return size_;
			}
			
			/// Return the capacity of our internal array
			size_t capacity() const
			{
				// TODO: Your code here
				
				return capacity_;
			}
			
			/**
			 * Check whether our vector is empty
			 * Return true if we have zero elements in our array (regardless of capacity)
			 * Otherwise, return false
			 */
			bool empty() const
			{
				// TODO: Your code here
				if (size_ == 0){
					return true;
				} else{
				return false;}
			}
			
			/// Return a reference to the element at an index
			T& at(size_t index) const
			{
				// TODO: Your code here
				if (index >= size_){
					throw std::out_of_range("get the right amount!");
				}
				//	erase me
				return elements_[index];
			}
			
			/***********
			 * Mutators
			 ***********/
			
			/**
			 * Reserve capacity in advance, if our capacity isn't currently large enough.
			 * Useful if we know we're about to add a large number of elements,
			 *   and we'd like to avoid the overhead of many internal changes to capacity.
			 */
			void reserve(size_t capacity)
			{
				// TODO: Your code here
				if (capacity < size_) {
					throw std::invalid_argument("reserve capacity cannot be less than size");
				}
				if (capacity <= capacity_) return;
				reallocate(capacity);
			}
			
			/**
			 * Set an element at an index.
			 * Throws range error if outside the size boundary.
			 * Returns a reference to the newly set element (not the original)
			 */
			T& set(size_t index, const T& element)
			{
				// TODO: Your code here
				if (index >= size_) {
					throw std::out_of_range("reajust your size");
				}
				elements_[index].~T();
				new (&elements_[index]) T(element);
				//	erase me
				return elements_[index];
			}
			
			/**
			 * Add an element onto the end of our vector.
			 * Returns a reference to the newly inserted element.
			 */
			T& push_back(const T& element)
			{
				// TODO: Your code here
				if (size_ == capacity_) {
					reserve(capacity_ * 2);
				}
				new (&elements_[size_]) T(element);
				size_++;
				//	erase me
				return elements_[size_ -1];
			}
			
			/**
			 * Remove the last element in our vector.
			 * Should throw std::range_error if the vector is already empty.
			 * Returns a copy of the element removed.
			 */
			T pop_back()
			{
				// TODO: Your code here
				if (size_ == 0) {
        			throw std::underflow_error("Vector is empty");
    			}
    			T value = elements_[size_ - 1];
				elements_[size_ - 1].~T();
    			--size_;
				if (size_ == 0) {
					if (capacity_ != MINIMUM_CAPACITY) {
						reallocate(MINIMUM_CAPACITY);
					}
					return value;
				}
				if (capacity_ > MINIMUM_CAPACITY && size_ < capacity_ / 3) {
					size_t newCap = capacity_ / 2;
					if (newCap < MINIMUM_CAPACITY) {
						newCap = MINIMUM_CAPACITY;
					}
					reallocate(newCap);
				}
				//	erase me
    			return value;
			}
			
			/**
			 * Insert an element at some index in our vector
			 * 
			 * Example:
			 * 	 Insert a 9 at index 2
			 *   Contents before: [6, 2, 7, 4, 3]
			 *   Contents after:  [6, 2, 9, 7, 4, 3]
			 * 
			 * Returns a reference to the newly added element (not the original).
			 */
			T& insert(size_t index, const T& element)
			{
				// TODO: Your code here
				if (index > size_) {
					throw std::out_of_range("Index out of range");
				}
				if (size_ == capacity_) {
					reserve(capacity_ * 2);
				}
				for (size_t i = size_; i > index; --i) {
					elements_[i] = elements_[i - 1];
				}
				elements_[index] = element;
				++size_;
				//erase me
				return elements_[index];
			}
			T erase(size_t index)
			{
				// TODO: Your code here
				if (index >= size_) {
					throw std::out_of_range("Index out of range");
				}
				T removed = elements_[index];
				for (size_t i = index; i < size_ - 1; ++i) {
					elements_[i] = elements_[i + 1];
				}
				--size_;
				if (size_ == 0) {
					if (capacity_ != MINIMUM_CAPACITY) {
						delete[] elements_;
						elements_ = new T[MINIMUM_CAPACITY];
						capacity_ = MINIMUM_CAPACITY;
					}
					return removed;
				}
				if (capacity_ > MINIMUM_CAPACITY && size_ < capacity_ / 3) {
					size_t newCap = capacity_ / 2;
					if (newCap < MINIMUM_CAPACITY) newCap = MINIMUM_CAPACITY;
					T* newArray = new T[newCap];
					for (size_t i = 0; i < size_; ++i) {
						newArray[i] = elements_[i];
					}
					delete[] elements_;
					elements_ = newArray;
					capacity_ = newCap;
				}
				//	erase me
				return removed;
			}
			
			/**
			 * Removes all elements (i.e., size=0 and DTORs called)
			 * 
			 * Should also reset capacity, if needed
			*/
			void clear()
			{
				// TODO: Your code here
				destroy_range(0, size_);
				size_ = 0;
				if (capacity_ != DEFAULT_CAPACITY) {
					::operator delete(elements_);
					capacity_ = DEFAULT_CAPACITY;
					elements_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));
				}
			}
		private:
			
			/// Number of valid elements currently in our vector
			size_t size_ = 0;
			
			/// Capacity of our vector; The actual size of our internal array
			size_t capacity_ = 0;
			
			/**
			 * Our internal array of elements of type T.
			 * Starts off as a null pointer.
			 */
			T* elements_ = nullptr;
			void destroy_range(size_t from, size_t to) {
				if (!elements_) return;
				for (size_t i = from; i < to; ++i) {
					elements_[i].~T();
				}
			}
			void reallocate(size_t new_cap) {
				T* new_mem = static_cast<T*>(::operator new(sizeof(T) * new_cap));
				for (size_t i = 0; i < size_; ++i) {
					new (&new_mem[i]) T(std::move(elements_[i]));
				}
				destroy_range(0, size_);
				::operator delete(elements_);
				elements_ = new_mem;
				capacity_ = new_cap;
			}
	};

}
