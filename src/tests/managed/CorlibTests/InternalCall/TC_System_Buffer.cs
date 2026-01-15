using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace CorlibTests.InternalCall
{
    internal class TC_System_Buffer : GeneralTestCaseBase
    {
        [UnitTest]
        public void ByteLength_ByteArray()
        {
            byte[] arr = new byte[10];
            int length = Buffer.ByteLength(arr);
            Assert.Equal(10, length);
        }

        [UnitTest]
        public void ByteLength_IntArray()
        {
            int[] arr = new int[5];
            int length = Buffer.ByteLength(arr);
            Assert.Equal(20, length); // 5 integers * 4 bytes each
        }

        //[UnitTest]
        //public void ByteLength_StringArray()
        //{
        //    string[] arr = new string[3];
        //    int length = Buffer.ByteLength(arr);
        //    Assert.Equal(-1, length); // Reference types return -1
        //}

        // MemoryCopy
        [UnitTest]
        public unsafe void MemoryCopy_ByteArray()
        {
            byte[] src = new byte[] { 1, 2, 3, 4, 5 };
            byte[] dest = new byte[5];
            fixed (byte* pSrc = src)
            {
                fixed (byte* pDest = dest)
                {
                    Buffer.MemoryCopy(pSrc, pDest, dest.Length, src.Length);
                }
            }
            Assert.Equal(1, dest[0]);
            Assert.Equal(2, dest[1]);
            Assert.Equal(3, dest[2]);
            Assert.Equal(4, dest[3]);
            Assert.Equal(5, dest[4]);
        }

        // BlockCopy
        [UnitTest]
        public void BlockCopy_ByteArray()
        {
            byte[] src = new byte[] { 1, 2, 3, 4, 5 };
            byte[] dest = new byte[5];
            Buffer.BlockCopy(src, 1, dest, 2, 3);
            Assert.Equal(0, dest[0]);
            Assert.Equal(0, dest[1]);
            Assert.Equal(2, dest[2]);
            Assert.Equal(3, dest[3]);
            Assert.Equal(4, dest[4]);
        }
    }
}
