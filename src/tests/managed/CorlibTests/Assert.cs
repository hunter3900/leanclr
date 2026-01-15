//using System;

//namespace test
//{
//    class Assert
//    {
//        public static void Fail()
//        {
//            throw new Exception($"Assert.Fail:");
//        }

//        public static void Fail(string message)
//        {
//            throw new Exception($"Assert.Fail:");
//            //throw new Exception($"Assert.Fail: {message}");
//        }

//        public static void IsTrue(bool condition)
//        {
//            if (!condition)
//            {
//                throw new Exception($"Assert.IsTrue failed");
//                //throw new Exception($"Assert.IsTrue failed");
//            }
//        }

//        public static void IsFalse(bool condition)
//        {
//            if (condition)
//            {
//                throw new Exception($"Assert.IsFalse failed");
//            }
//        }

//        public static void True(bool condition)
//        {
//            if (!condition)
//            {
//                throw new Exception($"Assert.IsTrue failed");
//            }
//        }

//        public static void False(bool condition)
//        {
//            if (condition)
//            {
//                throw new Exception($"Assert.IsFalse failed");
//            }
//        }

//        public static void Null(object obj)
//        {
//            if (obj != null)
//            {
//                throw new Exception($"Assert.NNull failed: object is not null");
//            }
//        }

//        public static void NotNull(object obj)
//        {
//            if (obj == null)
//            {
//                throw new Exception($"Assert.NotNull failed: object is null");
//            }
//        }

//        public static void Equal(bool a, bool b)
//        {
//            if (a != b)
//            {
//                throw new Exception($"Assert.Equal failed:");
//                //throw new Exception($"Assert.Equal failed: {a} != {b}");
//            }
//        }

//        public static void Equal(int a, int b)
//        {
//            if (a != b)
//            {
//                throw new Exception($"Assert.Equal failed:");
//                //throw new Exception($"Assert.Equal failed: {a} != {b}");
//            }
//        }

//        public static void Equal(long a, long b)
//        {
//            if (a != b)
//            {
//                throw new Exception($"Assert.Equal failed:");
//                //throw new Exception($"Assert.Equal failed: {a} != {b}");
//            }
//        }

//        public static void Equal(float a, float b)
//        {
//            if (float.IsNaN(a) && float.IsNaN(b))
//            {
//                return;
//            }
//            if (a != b)
//            {
//                throw new Exception($"Assert.Equal failed:");
//                //throw new Exception($"Assert.Equal failed: {a} != {b}");
//            }
//        }

//        public static void Equal(double a, double b)
//        {
//            if (double.IsNaN(a) && double.IsNaN(b))
//            {
//                return;
//            }
//            if (a != b)
//            {
//                throw new Exception($"Assert.Equal failed:");
//                //throw new Exception($"Assert.Equal failed: {a} != {b}");
//            }
//        }

//        public static void Equal(Type a, Type b)
//        {
//            if (a != b)
//            {
//                throw new Exception($"Assert.Equal failed:");
//                //throw new Exception($"Assert.Equal failed: {a} != {b}");
//            }
//        }

//        public static void Equal(string a, string b)
//        {
//            if (a != b)
//            {
//                throw new Exception($"Assert.Equal failed:");
//                //throw new Exception($"Assert.Equal failed: {a} != {b}");
//            }
//        }

//        public unsafe static void Equal(int* a, int* b)
//        {
//            if (a != b)
//            {
//                throw new Exception($"Assert.Equal failed: ");
//                //throw new Exception($"Assert.Equal failed: {(long)a} != {(long)b}");
//            }
//        }

//        //public static void Equal(decimal a, decimal b)
//        //{
//        //    if (a != b)
//        //    {
//        //        throw new Exception($"Assert.Equal failed:");
//        //        //throw new Exception($"Assert.Equal failed: {a} != {b}");
//        //    }
//        //}

//        public static void Equal(char a, char b)
//        {
//            if (a != b)
//            {
//                throw new Exception($"Assert.Equal failed:");
//                //throw new Exception($"Assert.Equal failed: {a} != {b}");
//            }
//        }

//        public static void Equal<T>(T a, T b)
//        {
//            if (!Object.Equals(a, b))
//            {
//                throw new Exception($"Assert.Equal failed:");
//                //throw new Exception($"Assert.Equal failed: {a} != {b}");
//            }
//        }

//        public static void NotEqual(int a, int b)
//        {
//            if (a == b)
//            {
//                throw new Exception($"Assert.NotEqual failed:");
//                //throw new Exception($"Assert.NotEqual failed: {a} == {b}");
//            }
//        }

//        public static void EqualAny(object a, object b)
//        {
//            if (!Object.Equals(a, b))
//            {
//                throw new Exception($"Assert.NotEqual failed:");
//                //throw new Exception($"Assert.NotEqual failed: {a} == {b}");
//            }
//        }
//    }
//}
