IVehicle vehicle = new Car();
vehicle.Accelerate();
Console.WriteLine((vehicle as Car)?.doors);

vehicle = new Truck();
vehicle.Accelerate();



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