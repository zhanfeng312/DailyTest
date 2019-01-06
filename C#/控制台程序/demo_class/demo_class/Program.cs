using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace demo_class
{
    //声明一个类
    public class Car
    {
        //常量：使用const声明，不需要实例化，直接使用
        public const string brand = "BYD";

        private int seat;
        public int Seat
        {
            get { return seat; }
            set { seat = value; }
        }

        public int Count()
        {
            int x = 1, y = 2;
            return x + y;
        }

        public int Count(int x, ref int y)
        {
            y = 100;
            return x + y;
        }

        public int Count(int x, int y, out int z)
        {
            z = x + y;
            return z;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            //访问常量
            Console.WriteLine(Car.brand);

            Car car = new Car();
            car.Seat = 4;
            Console.WriteLine(car.Seat);

            Console.WriteLine("--------------------");

            int x, y, z;
            y = 2;

            Console.WriteLine(car.Count());
            Console.WriteLine(car.Count(1, ref y));//引用传递，函数内部改值，能影响到外面

            Console.WriteLine("y = " + y);

            x = 1;
            Console.WriteLine(car.Count(x, y, out z));
        }
    }
}
