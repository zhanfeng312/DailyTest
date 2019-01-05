using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace demo02
{
    class Program
    {
        static void Main(string[] args)
        {
            #region 这里写明代码的备注信息
            //Console.WriteLine("Hello World!");
            #endregion

            #region if比较
            //int x = 11, y = 12;
            //if (x == y)
            //{
            //    Console.WriteLine("equal!");
            //}
            //else
            //{
            //    Console.WriteLine("not equal!");
            //}
            #endregion

            //类型转换
            //隐式转换 不需要代码，系统自动完成
            int intX = 18;
            double doX;
            doX = intX;
            Console.WriteLine(doX);

            //显示转换 需要写代码
            string strX = "12", strY = "12.88";
            //字符串转int、double
            //intX = Convert.ToInt32(strX);
            //doX = Convert.ToDouble(strY);
            intX = int.Parse(strX);
            doX = double.Parse(strY);            
            Console.WriteLine(intX);
            Console.WriteLine(doX);

            //int、double 转字符串
            intX = 1000;
            doX = 12.8888;
            strX = intX.ToString();
            strY = doX.ToString();
            Console.WriteLine(strX);
            Console.WriteLine(strY);
        }
    }
}
