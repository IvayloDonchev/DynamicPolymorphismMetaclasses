#include <iostream>
#include <vector>

class Vehicle {
public:
	//virtual ~Vehicle();
	virtual void Accelerate() const = 0;
};

class Car : public Vehicle {
	virtual void Accelerate() const override;
};

class Truck : public Vehicle {
	virtual void Accelerate() const override;
};

namespace LibOne {
	class Base {
	public:
		virtual void Foo() {};
	};
}

namespace LibTwo {
	class Other : public LibOne::Base{
	public:
		virtual void Foo() {};
	};
}


int main()
{
	LibOne::Base* b = new LibTwo::Other{};

	Vehicle *vehicle = new Car{};
	vehicle->Accelerate();
	delete vehicle;
	vehicle = new Truck{};
	vehicle->Accelerate();
	std::vector<Vehicle*> vehicles{
		new Car{}, 
		new Truck{}, 
		new Truck{}, 
		new Car{} 
	};
	for (auto&& v : vehicles){
		v->Accelerate();
	}

	std::vector<void*> pv{
		new Car{}, new Truck{}, new Truck{}, new Car{} };
	for (int i = 0; i < pv.size(); ++i)
	{
		static_cast<Vehicle*>(pv[i])->Accelerate();
	}
	
}

inline void Car::Accelerate() const
{
	std::cout << "It is Car accelerating...\n";
}

inline void Truck::Accelerate() const
{
	std::cout << "It is Truck accelerating...\n";
}