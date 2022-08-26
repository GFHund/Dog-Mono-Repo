//using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace StateMachineCsTest{
    using System;
    using NUnit.Framework;
    
    [TestFixture]
    public class StateMachineCsTest{
        [Test]
        public void StateMachineCsTest_constructor(){
            StateMachineCs.StateMachine<int> sm = new StateMachineCs.StateMachine<int>();
            Assert.AreEqual(sm.getCurrentStateId(),0);
        }
    }
}