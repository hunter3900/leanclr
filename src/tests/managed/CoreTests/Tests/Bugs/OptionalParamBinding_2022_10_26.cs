//using test;
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Reflection;
//using System.Text;
//using System.Threading.Tasks;

//namespace Tests.Bugs
//{

//    internal class OptionalParamBinding_2022_10_26 : GeneralTestCaseBase
//    {
//        public static int Foo(int x = 1)
//        {
//            return x;
//        }

//        public static string Foo2(string s = "abc")
//        {
//            return s;
//        }

//        public static Action Foo3(Action a = null)
//        {
//            return a;
//        }

//        [UnitTest]
//        public void invoke()
//        {
//            int x = (int)GetType().InvokeMember("Foo", BindingFlags.Public | BindingFlags.NonPublic |
//            BindingFlags.Instance | BindingFlags.Static | BindingFlags.InvokeMethod | BindingFlags.OptionalParamBinding, null, null,
//                null);
//            Assert.Equal(1, x);
//        }

//        [UnitTest]
//        public void invoke2()
//        {
//            string x = (string)GetType().InvokeMember("Foo2", BindingFlags.Public | BindingFlags.NonPublic |
//            BindingFlags.Instance | BindingFlags.Static | BindingFlags.InvokeMethod | BindingFlags.OptionalParamBinding, null, null,
//                null);
//            Assert.Equal("abc", x);
//        }

//        [UnitTest]
//        public void invoke3()
//        {
//            Action x = (Action)GetType().InvokeMember("Foo3", BindingFlags.Public | BindingFlags.NonPublic |
//            BindingFlags.Instance | BindingFlags.Static | BindingFlags.InvokeMethod | BindingFlags.OptionalParamBinding, null, null,
//                null);
//            Assert.Null(x);
//        }
//    }
//}
