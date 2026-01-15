using test;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tests.Instruments.Objs
{
    internal class TC_isinst : GeneralTestCaseBase
    {
        [UnitTest]
        public void int_1()
        {
            object o = 1;
            Assert.True(o is int);
        }

        [UnitTest]
        public void int_2()
        {
            object o = 1;
            Assert.False(o is long);
        }

        [UnitTest]
        public void int_3()
        {
            object o = null;
            Assert.False(o is int);
        }

        [UnitTest]
        public void int_4()
        {
            object o = 1;
            Assert.False(o is string);
        }

        class A
        {

        }

        class B : A, IEnumerable, IEnumerable<int>
        {
            public IEnumerator<int> GetEnumerator()
            {
                throw new NotImplementedException();
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                throw new NotImplementedException();
            }
        }

        [UnitTest]
        public void class_1()
        {
            object o = new B();
            Assert.True(o is A);
        }

        [UnitTest]
        public void class_2()
        {
            object o = new A();
            Assert.False(o is B);
        }

        [UnitTest]
        public void class_3()
        {
            object o = new B();
            Assert.True(o is object);
        }

        [UnitTest]
        public void class_4()
        {
            object o = new B();
            Assert.False(o is string);
        }

        [UnitTest]
        public void class_5()
        {
            object o = new B();
            Assert.True(o is IEnumerable);
        }

        [UnitTest]
        public void class_6()
        {
            object o = new B();
            Assert.True(o is IEnumerable<int>);
        }

        [UnitTest]


        public void class_7()
        {
            object o = new B();
            Assert.False(o is IEnumerable<string>);
        }

        [UnitTest]
        public void nullable_int_1()
        {
            object o = 1;
            Assert.True(o is int?);
        }

        [UnitTest]
        public void nullable_int_2()
        {
            object o = 1;
            Assert.False(o is long?);
        }

        [UnitTest]
        public void nullable_int_3()
        {
            object o = null;
            Assert.False(o is int?);
        }
    }
}
