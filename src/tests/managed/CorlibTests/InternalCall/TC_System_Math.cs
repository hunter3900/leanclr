using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CorlibTests.InternalCall
{
    internal class TC_System_Math : GeneralTestCaseBase
    {
        // Abs
        [UnitTest]
        public void Abs1()
        {
            int a = -5;
            int b = Math.Abs(a);
            Assert.Equal(5, b);
        }

        [UnitTest]
        public void Abs2()
        {
            double a = -5.5;
            double b = Math.Abs(a);
            Assert.Equal(5.5, b);
        }

        [UnitTest]
        public void Sin1()
        {
            double a = Math.Sin(Math.PI / 2);
            Assert.Equal(1.0, a);
        }
    }
}
