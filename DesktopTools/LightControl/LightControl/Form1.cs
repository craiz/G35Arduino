using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;



namespace LightControl
{
    public partial class Form1 : Form
    {
        private SerialPort serialPort = null;
        private bool portConnected = false;

        private Utils util = new Utils();

        // This delegate enables asynchronous calls for setting 
        // the text property on a TextBox control. 
        delegate void SetTextCallback(string text);

        public Form1()
        {
            InitializeComponent();

            ComPortSelector.SelectedIndex = 2;

            cmbWaveColor.SelectedIndex = 0;
            cmbProgram.SelectedIndex = 17;
            cmbStringConfigDirection.SelectedIndex = 0;
            cmbWaveIncrements.SelectedIndex = 14;
        }

        void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort port = (SerialPort)sender;
            string data = port.ReadExisting();
            SetText(data);
        }

        private void SetText(string text)
        {
            // InvokeRequired required compares the thread ID of the 
            // calling thread to the thread ID of the creating thread. 
            // If these threads are different, it returns true. 
            if (this.txtReceived.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.txtReceived.Text += text;
            }
        }

        private Task SendCommand(string command, string nodeId)
        {
            return Task.Run(() =>
            {
                try
                {
                    byte[] bytes;
                    UTF8Encoding en = new UTF8Encoding(false, false);
                    bytes = en.GetBytes(command.ToCharArray());
                    serialPort.Write(bytes, 0, bytes.Length);
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.ToString());
                }
            });
        }

        private void btnWaveTest_Click(object sender, EventArgs e)
        {
#if false
            txtReceived.Text = "";
            
            byte[] colors = null;
            byte[] holds = null;

            colors = new byte[3];
            colors[0] = (byte)cmbColor1.SelectedIndex;
            colors[1] = (byte)cmbColor2.SelectedIndex;
            colors[2] = (byte)cmbColor1.SelectedIndex;

            holds = new byte[3];
            holds[0] = byte.Parse(txtColor1Count.Text);
            holds[1] = byte.Parse(txtColor2Count.Text);
            holds[2] = 0;

            byte colorCount = 2;
            if (cmbWave.SelectedIndex == 0)
            {
                colorCount = 3;
            }

#if false
            colorCount = 4;
            colors = new byte[colorCount];
            colors[0] = Utils.RED;
            colors[1] = Utils.GREEN;
            colors[2] = Utils.BLUE;
            colors[3] = Utils.RED;

            holds = new byte[colorCount];
            holds[0] = 1;
            holds[1] = 1;
            holds[2] = 1;
            holds[3] = 0;      
#else
            colorCount = 7;
            colors = new byte[colorCount];
            colors[0] = Utils.RED;
            colors[1] = Utils.YELLOW;
            colors[2] = Utils.GREEN;
            colors[3] = Utils.CYAN;
            colors[4] = Utils.BLUE;
            colors[5] = Utils.MAGENTA;
            colors[6] = Utils.RED;

            holds = new byte[colorCount];
            holds[0] = 1;
            holds[1] = 1;
            holds[2] = 1;
            holds[3] = 1;
            holds[4] = 1;
            holds[5] = 1;
            holds[6] = 0;
#endif
            util.Output.Clear();
            util.CreateWave(colors, holds, colorCount, (byte)(int.Parse(txtWaveRampCount.Text) - 1));
            for (int i = 0; i < util.Output.Count; i++)
            {
                SetText(util.Output[i]);
            }
#endif
        }

        private async void btnSend_Click(object sender, EventArgs e)
        {
            await SendCommand(txtSendCommand.Text, "255");
        }

        private byte GetCommandOptions()
        {
            byte options = 0;

            if (chkCommandOptionDefer.Checked)
            {
                options |= 0x01;
            }
            if (chkCommandOptionUpdate.Checked)
            {
                options |= 0x02;
            }
            if (chkCommandOptionGroup.Checked)
            {
                options |= 0x04;
            }
            return options;
        }

        private byte GetProgramOptions(bool wave)
        {
            byte options = 0;

            if (wave)
            {
                options = (byte)(cmbWaveIncrements.SelectedIndex + 1);
            }
            else
            {
                options = byte.Parse(txtProgramOptionCount.Text, System.Globalization.NumberStyles.Number);
            }
            options <<= 4;

            if (!chkProgramOptionForwardDirection.Checked)
            {
                options |= 0x01;
            }
            if (!chkProgramOptionFillImmediate.Checked)
            {
                options |= 0x02;
            }
            if (!chkProgramOptionRandom.Checked)
            {
                options |= 0x04;
            }
            if (chkProgramOptionWait.Checked)
            {
                options |= 0x08;
            }

            return options;
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (portConnected)
            {
                serialPort.Close();
                serialPort = null;
                portConnected = false;
                btnConnect.Text = "Connect";
            }
            else
            {
                serialPort = new SerialPort(ComPortSelector.Text, 57600, Parity.None, 8, StopBits.One);
                serialPort.DataReceived += serialPort_DataReceived;
                serialPort.Open();
                serialPort.DtrEnable = true;
                portConnected = true;
                btnConnect.Text = "Disconnect";
            }
        }

        private void btnSetNode_Click(object sender, EventArgs e)
        {
            NodeSelectForm form = new NodeSelectForm();
            form.NodeID = uint.Parse(txtAddress.Text);
            DialogResult result = form.ShowDialog();
            if (result == DialogResult.OK)
            {
                txtAddress.Text = form.NodeID.ToString();
            }
        }

        private void btnProgram_Click(object sender, EventArgs e)
        {
            bool isWave = cmbProgram.SelectedIndex == 17;

            txtSendCommand.Text = "";

            if (isWave)
            {
                // Color Holds (reverse order)
                for (int i = txtWaveHolds.Lines.Length - 2; i >= 0; i--)
                {
                    txtSendCommand.Text += txtWaveHolds.Lines[i] + ",";
                }

                // Colors (reverse order)
                for (int i = txtWaveColors.Lines.Length - 2; i >= 0; i--)
                {
                    txtSendCommand.Text += util.ColorTextToNumber(txtWaveColors.Lines[i]) + ",";
                }

                // Span Size
                txtSendCommand.Text += txtWaveSpan.Text + ",";

                // Distribution
                txtSendCommand.Text += txtWaveDistribution.Text + ",";

                // Pixel Count
                txtSendCommand.Text += txtWavePixelCount.Text + ",";
            }

            // Program
            txtSendCommand.Text += cmbProgram.SelectedIndex.ToString() + ",";

            // Program Options
            txtSendCommand.Text += GetProgramOptions(isWave).ToString() + ",";

            // Program Pattern
            if (isWave)
            {
                txtSendCommand.Text += (txtWaveColors.Lines.Length - 1).ToString() + ",";
            }
            else
            {
                txtSendCommand.Text += txtProgramPattern.Text + ",";
            }

            // Program Delay
            UInt16 delay;
            if (!UInt16.TryParse(txtProgramDelay.Text, out delay))
            {
                delay = 0xFFFF;
            }
            txtSendCommand.Text += delay.ToString() + ",";

            // Command Options
            txtSendCommand.Text += GetCommandOptions().ToString() + ",";

            // Command Seed
            txtSendCommand.Text += txtRandomSeed.Text + ",";

            // layout
            txtSendCommand.Text += "0,";

            // Node
            txtSendCommand.Text += txtAddress.Text;

            // Wave Command
            if (isWave)
            {
                txtSendCommand.Text += " w";
            }
            else
            {
                txtSendCommand.Text += " p";
            }
        }

        private void bntCommit_Click(object sender, EventArgs e)
        {
            //         2            1
            // <command option>,<address> c
            txtSendCommand.Text = GetCommandOptions().ToString() + ",";
            txtSendCommand.Text += txtAddress.Text + " c";
        }

        private void btnKick_Click(object sender, EventArgs e)
        {
            //         2            1
            // <command option>,<address> c
            txtSendCommand.Text = GetCommandOptions().ToString() + ",";
            txtSendCommand.Text += txtAddress.Text + " k";
        }

        private void bntOff_Click(object sender, EventArgs e)
        {
            //         2            1
            // <command option>,<address> o
            txtSendCommand.Text = GetCommandOptions().ToString() + ",";
            txtSendCommand.Text += txtAddress.Text + " o";
        }

        private void btnIdConfig_Click(object sender, EventArgs e)
        {
            byte targetStringId = byte.Parse(txtIdConfigTargetStringId.Text, System.Globalization.NumberStyles.Number);
            byte stringId = byte.Parse(txtIdConfigStringId.Text, System.Globalization.NumberStyles.Number);
            byte stringGroupA = byte.Parse(txtIdConfigStringGroupA.Text, System.Globalization.NumberStyles.Number);
            byte stringGroupB = byte.Parse(txtIdConfigStringGroupB.Text, System.Globalization.NumberStyles.Number);
            byte stringGroupC = byte.Parse(txtIdConfigStringGroupC.Text, System.Globalization.NumberStyles.Number);
            byte stringGroupD = byte.Parse(txtIdConfigStringGroupD.Text, System.Globalization.NumberStyles.Number);
            byte rfController = byte.Parse(txtIdConfigRFController.Text, System.Globalization.NumberStyles.Number);
            byte rfId = byte.Parse(txtIdConfigRFID.Text, System.Globalization.NumberStyles.Number);
            byte rfGroup = byte.Parse(txtIdConfigRFGroup.Text, System.Globalization.NumberStyles.Number);

            //       9               8                7                 6                    5                    4                    3                    2            1
            // <new rf node>,<new rf controller>,<new rf group>,<new string group D>,<new string group C>,<new string group B>,<new string group A>,<new string id>,<string id> a
            txtSendCommand.Text = String.Format("{0},{1},{2},{3},{4},{5},{6},{7},{8} a",
                                                rfId,
                                                rfController,
                                                rfGroup,
                                                stringGroupD,
                                                stringGroupC,
                                                stringGroupB,
                                                stringGroupA,
                                                stringId,
                                                targetStringId);
        }

        private void btnStringConfig_Click(object sender, EventArgs e)
        {
            byte targetStringId = byte.Parse(txtStringConfigId.Text, System.Globalization.NumberStyles.Number);
            byte physicalCount = byte.Parse(txtStringConfigPhysical.Text, System.Globalization.NumberStyles.Number);
            byte logicalCount = byte.Parse(txtStringConfigLogical.Text, System.Globalization.NumberStyles.Number);
            byte direction;
            if (cmbStringConfigDirection.SelectedIndex == 0)
            {
                direction = 1;
            }
            else
            {
                direction = 0;
            }
            UInt16 delay = UInt16.Parse(txtStringConfigDelay.Text, System.Globalization.NumberStyles.Number);

            //     5          4         3          2         1
            // <physical>,<logical>,<direction>,<delay>,<string id> l
            txtSendCommand.Text = String.Format("{0},{1},{2},{3},{4} l",
                                                physicalCount,
                                                logicalCount,
                                                direction,
                                                delay,
                                                targetStringId);
        }

        private void btnWaveAdd_Click(object sender, EventArgs e)
        {
            txtWaveColors.Text += cmbWaveColor.Items[cmbWaveColor.SelectedIndex] + Environment.NewLine;
            txtWaveHolds.Text += txtWaveHold.Text + Environment.NewLine;
        }

        private void bntWaveClear_Click(object sender, EventArgs e)
        {
            txtWaveColors.Text = "";
            txtWaveHolds.Text = "";
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
