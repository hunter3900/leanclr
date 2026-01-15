using test;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tests.Instruments.Objs
{
    internal class TC_castclass : GeneralTestCaseBase
    {
        public static T CastClass<T>(object o)
        {
            return (T)o;
        }

        [UnitTest]
        public void object_1()
        {
            object o = "abc";
            string s = (string)o;
            Assert.Equal("abc", s);
        }

        //[UnitTest]
        //public void object_2()
        //{
        //    object o = 1;
        //    Assert.ExpectException<InvalidCastException>();
        //    string s = (string)o;
        //    Assert.Fail();
        //}

        [UnitTest]
        public void int_1()
        {
            object o = 1;
            int x = CastClass<int>(o);
            Assert.Equal(1, x);
        }
    }
}
