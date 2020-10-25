// Реализация на динамичен полиморфизъм без наследяване
#include <iostream>
#include <vector>

struct vtable {
	void (*speak)(void* ptr);
	void (*destroy_)(void* ptr);
	void* (*clone_)(void* ptr);
	void* (*move_clone_)(void* ptr);
};

template<class T>
constexpr vtable vtable_for{
	[](void* ptr) {static_cast<T*>(ptr)->speak(); },
	[](void* ptr) {delete static_cast<T*>(ptr); },
	[](void* ptr)->void*
	{ return new T(*static_cast<T*>(ptr)); },
	[](void* ptr)->void*
	{return new T(std::move(*static_cast<T*>(ptr))); }
};

struct animal {
	void* t_;
	vtable const* vtable_;

	template<class T>
	animal(T const& t) :
		t_(new T(t)),
		vtable_(&vtable_for<T>)
	{}
	
	animal(const animal& rhs) :
		t_(rhs.vtable_->clone_(rhs.t_)),
		vtable_(rhs.vtable_)
	{}
	
	animal(animal&& rhs) noexcept : 
		t_(rhs.vtable_->move_clone_(rhs.t_)),
		vtable_(rhs.vtable_)
	{}

	animal& operator=(animal const& rhs) {
		t_ = rhs.vtable_->clone_(rhs.t_);
		vtable_ = rhs.vtable_;
		return *this;
	}

	animal& operator=(animal&& rhs) noexcept {
		t_ = rhs.vtable_->move_clone_(rhs.t_);
		vtable_ = rhs.vtable_;
		return *this;
	}

	void speak() {vtable_->speak(t_);}
	~animal() { vtable_->destroy_(t_); }
};

struct cat {
	void speak() {
		std::cout << "It is a cat speaking...\n";
	}
};

struct dog {
	void speak() {
		std::cout << "It is a dog speaking...\n";
	}
};

int main()
{
	animal a = cat{};
	a.speak();
	a = dog{};
	a.speak();

	animal b{ a };
	b.speak();
	std::cout << "------------------\n";
	std::vector<animal> animals{ cat{}, dog{}, dog{} };
	for (auto&& a : animals)
		a.speak();

}
