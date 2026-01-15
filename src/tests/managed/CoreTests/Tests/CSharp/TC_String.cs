namespace Tests.CSharp
{
    class TC_String : GeneralTestCaseBase
    {
        [UnitTest]
        public void EmptyString()
        {
            string s = string.Empty;
            Assert.NotNull(s);
            Assert.Equal(0, s.Length);
        }
    }
}
