using System.Collections.Generic;

IVehicle vehicle = new Car();
vehicle.Accelerate();
vehicle = new Truck();
vehicle.Accelerate();
List<IVehicle> vehicles = new() {
    new Car(), 
    new Truck(),
    new Truck(),
    new Car() 
};
foreach (var v in vehicles)
{
    v.Accelerate();
}

Console.WriteLine((vehicle as Car)?.doors); // vehicle is not a Car here
Truck? truck = vehicle as Truck;
truck?.Accelerate();
Console.WriteLine("-----------------------------------------");


public interface IVehicle
{
    void Accelerate();
}

public class Vehicle
{
    public virtual void Accelerate()
    {
        Console.WriteLine("Vehicle accelerating");
    }
}

public class Car : IVehicle
{
    public readonly int doors = 4;
    public Car(int doors=4)
    {
        this.doors = doors;
    }
    public void Accelerate()
    {
        Console.WriteLine("Car accelerating");
    }
}

public class Truck : IVehicle
{
    public void Accelerate()
    {
        Console.WriteLine("Truck accelerating");
    }
}