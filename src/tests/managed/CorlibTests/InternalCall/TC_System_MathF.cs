using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CorlibTests.InternalCall
{
    internal class TC_System_MathF : GeneralTestCaseBase
    {

        [UnitTest]
        public void Abs2()
        {
            float a = -5.5f;
            float b = Math.Abs(a);
            Assert.Equal(5.5, b);
        }

        [UnitTest]
        public void Sin1()
        {
            float a = System.MathF.Sin(MathF.PI / 2);
            Assert.Equal(1.0, a);
        }
    }
}
