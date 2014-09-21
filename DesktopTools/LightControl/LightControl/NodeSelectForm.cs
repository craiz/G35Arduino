using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LightControl
{
    public partial class NodeSelectForm : Form
    {
        private CheckBox[] checkBoxes;

        private uint nodeID;
        public uint NodeID
        {
            get { return nodeID; }
            set 
            {
                bool isOn;

                for (int i = 0; i < 32; i++)
                {
                    isOn = (value & 1) == 1;
                    checkBoxes[i].Checked = isOn;
                    value >>= 1;
                }
            }
        }

        private void SetNode(uint node, bool on)
        {
            uint changedNodeID = 1;
            changedNodeID <<= (int)(node - 1);
            if (on)
            {
                nodeID |= changedNodeID;
            }
            else
            {
                nodeID &= ~changedNodeID;
            }
        }


        public NodeSelectForm()
        {
            InitializeComponent();

            checkBoxes = new CheckBox[32];
            checkBoxes[0] = checkBox1;
            checkBoxes[1] = checkBox2;
            checkBoxes[2] = checkBox3;
            checkBoxes[3] = checkBox4;
            checkBoxes[4] = checkBox5;
            checkBoxes[5] = checkBox6;
            checkBoxes[6] = checkBox7;
            checkBoxes[7] = checkBox8;
            checkBoxes[8] = checkBox9;
            checkBoxes[9] = checkBox10;
            checkBoxes[10] = checkBox11;
            checkBoxes[11] = checkBox12;
            checkBoxes[12] = checkBox13;
            checkBoxes[13] = checkBox14;
            checkBoxes[14] = checkBox15;
            checkBoxes[15] = checkBox16;
            checkBoxes[16] = checkBox17;
            checkBoxes[17] = checkBox18;
            checkBoxes[18] = checkBox19;
            checkBoxes[19] = checkBox20;
            checkBoxes[20] = checkBox21;
            checkBoxes[21] = checkBox22;
            checkBoxes[22] = checkBox23;
            checkBoxes[23] = checkBox24;
            checkBoxes[24] = checkBox25;
            checkBoxes[25] = checkBox26;
            checkBoxes[26] = checkBox27;
            checkBoxes[27] = checkBox28;
            checkBoxes[28] = checkBox29;
            checkBoxes[29] = checkBox30;
            checkBoxes[30] = checkBox31;
            checkBoxes[31] = checkBox32;
        }

        private void checkBox_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox checkBox = sender as CheckBox;
            if (checkBox != null)
            {
                SetNode(uint.Parse((string)checkBox.Tag), checkBox.Checked);
            }
        }

        private void btnAll_Click(object sender, EventArgs e)
        {
            NodeID = 0xFFFFFFFF;
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            NodeID = 0;
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
        }
    }
}
