using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightSimulator
{
    class LightString : List<LightBulb>
    {
        public LightString(UInt16 count)
        {
            LightBulb bulb;
            for (uint i = 0; i < count; i++)
            {
                bulb = new LightBulb();
                bulb.BulbColor = 0x0000;
                Add(bulb);
            }
        }
    }
}
