namespace LightControl
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.txtReceived = new System.Windows.Forms.TextBox();
            this.btnConnect = new System.Windows.Forms.Button();
            this.btnSend = new System.Windows.Forms.Button();
            this.ComPortSelector = new System.Windows.Forms.ComboBox();
            this.txtSendCommand = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.txtWavePixelCount = new System.Windows.Forms.TextBox();
            this.btnProgram = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.txtAddress = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txtProgramDelay = new System.Windows.Forms.TextBox();
            this.btnSetNode = new System.Windows.Forms.Button();
            this.label10 = new System.Windows.Forms.Label();
            this.cmbProgram = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txtProgramOptionCount = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.chkProgramOptionWait = new System.Windows.Forms.CheckBox();
            this.chkProgramOptionRandom = new System.Windows.Forms.CheckBox();
            this.chkProgramOptionFillImmediate = new System.Windows.Forms.CheckBox();
            this.chkProgramOptionForwardDirection = new System.Windows.Forms.CheckBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.chkCommandOptionGroup = new System.Windows.Forms.CheckBox();
            this.chkCommandOptionUpdate = new System.Windows.Forms.CheckBox();
            this.chkCommandOptionDefer = new System.Windows.Forms.CheckBox();
            this.label8 = new System.Windows.Forms.Label();
            this.txtRandomSeed = new System.Windows.Forms.TextBox();
            this.txtProgramPattern = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.bntCommit = new System.Windows.Forms.Button();
            this.bntOff = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.txtIdConfigStringGroupC = new System.Windows.Forms.TextBox();
            this.label24 = new System.Windows.Forms.Label();
            this.txtIdConfigStringGroupD = new System.Windows.Forms.TextBox();
            this.label25 = new System.Windows.Forms.Label();
            this.txtIdConfigStringGroupA = new System.Windows.Forms.TextBox();
            this.label23 = new System.Windows.Forms.Label();
            this.txtIdConfigStringId = new System.Windows.Forms.TextBox();
            this.txtIdConfigStringGroupB = new System.Windows.Forms.TextBox();
            this.label16 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.txtIdConfigRFID = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.txtIdConfigRFController = new System.Windows.Forms.TextBox();
            this.txtIdConfigRFGroup = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.btnIdConfig = new System.Windows.Forms.Button();
            this.txtIdConfigTargetStringId = new System.Windows.Forms.TextBox();
            this.label17 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.txtStringConfigId = new System.Windows.Forms.TextBox();
            this.btnStringConfig = new System.Windows.Forms.Button();
            this.label19 = new System.Windows.Forms.Label();
            this.cmbStringConfigDirection = new System.Windows.Forms.ComboBox();
            this.txtStringConfigLogical = new System.Windows.Forms.TextBox();
            this.txtStringConfigPhysical = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.txtWaveColors = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.txtWaveHolds = new System.Windows.Forms.TextBox();
            this.cmbWaveColor = new System.Windows.Forms.ComboBox();
            this.txtWaveHold = new System.Windows.Forms.TextBox();
            this.btnWaveAdd = new System.Windows.Forms.Button();
            this.bntWaveClear = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.txtWaveDistribution = new System.Windows.Forms.TextBox();
            this.cmbWaveIncrements = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtWaveSpan = new System.Windows.Forms.TextBox();
            this.btnKick = new System.Windows.Forms.Button();
            this.label26 = new System.Windows.Forms.Label();
            this.txtStringConfigDelay = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // txtReceived
            // 
            this.txtReceived.Location = new System.Drawing.Point(12, 12);
            this.txtReceived.Multiline = true;
            this.txtReceived.Name = "txtReceived";
            this.txtReceived.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtReceived.Size = new System.Drawing.Size(351, 345);
            this.txtReceived.TabIndex = 0;
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(13, 376);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(75, 23);
            this.btnConnect.TabIndex = 1;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // btnSend
            // 
            this.btnSend.Location = new System.Drawing.Point(227, 377);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(75, 23);
            this.btnSend.TabIndex = 3;
            this.btnSend.Text = "Send";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // ComPortSelector
            // 
            this.ComPortSelector.FormattingEnabled = true;
            this.ComPortSelector.Items.AddRange(new object[] {
            "COM1",
            "COM3",
            "COM4"});
            this.ComPortSelector.Location = new System.Drawing.Point(94, 377);
            this.ComPortSelector.Name = "ComPortSelector";
            this.ComPortSelector.Size = new System.Drawing.Size(121, 24);
            this.ComPortSelector.TabIndex = 4;
            // 
            // txtSendCommand
            // 
            this.txtSendCommand.Location = new System.Drawing.Point(308, 379);
            this.txtSendCommand.Name = "txtSendCommand";
            this.txtSendCommand.Size = new System.Drawing.Size(307, 22);
            this.txtSendCommand.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(846, 269);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(45, 17);
            this.label3.TabIndex = 17;
            this.label3.Text = "Ramp";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(847, 296);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(44, 17);
            this.label5.TabIndex = 24;
            this.label5.Text = "Pixels";
            // 
            // txtWavePixelCount
            // 
            this.txtWavePixelCount.Location = new System.Drawing.Point(912, 293);
            this.txtWavePixelCount.Name = "txtWavePixelCount";
            this.txtWavePixelCount.Size = new System.Drawing.Size(43, 22);
            this.txtWavePixelCount.TabIndex = 23;
            this.txtWavePixelCount.Text = "0";
            // 
            // btnProgram
            // 
            this.btnProgram.Location = new System.Drawing.Point(633, 375);
            this.btnProgram.Name = "btnProgram";
            this.btnProgram.Size = new System.Drawing.Size(75, 26);
            this.btnProgram.TabIndex = 25;
            this.btnProgram.Text = "Program";
            this.btnProgram.UseVisualStyleBackColor = true;
            this.btnProgram.Click += new System.EventHandler(this.btnProgram_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(377, 8);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(60, 17);
            this.label6.TabIndex = 27;
            this.label6.Text = "Address";
            // 
            // txtAddress
            // 
            this.txtAddress.Location = new System.Drawing.Point(372, 28);
            this.txtAddress.Name = "txtAddress";
            this.txtAddress.Size = new System.Drawing.Size(100, 22);
            this.txtAddress.TabIndex = 26;
            this.txtAddress.Text = "1";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(501, 177);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(44, 17);
            this.label7.TabIndex = 29;
            this.label7.Text = "Delay";
            // 
            // txtProgramDelay
            // 
            this.txtProgramDelay.Location = new System.Drawing.Point(496, 197);
            this.txtProgramDelay.Name = "txtProgramDelay";
            this.txtProgramDelay.Size = new System.Drawing.Size(119, 22);
            this.txtProgramDelay.TabIndex = 28;
            this.txtProgramDelay.Text = "-1";
            // 
            // btnSetNode
            // 
            this.btnSetNode.Location = new System.Drawing.Point(478, 26);
            this.btnSetNode.Name = "btnSetNode";
            this.btnSetNode.Size = new System.Drawing.Size(107, 23);
            this.btnSetNode.TabIndex = 35;
            this.btnSetNode.Text = "Set Address";
            this.btnSetNode.UseVisualStyleBackColor = true;
            this.btnSetNode.Click += new System.EventHandler(this.btnSetNode_Click);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(501, 119);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(62, 17);
            this.label10.TabIndex = 36;
            this.label10.Text = "Program";
            // 
            // cmbProgram
            // 
            this.cmbProgram.FormattingEnabled = true;
            this.cmbProgram.Items.AddRange(new object[] {
            "MEOSwitchOff",
            "RawProgram",
            "MEOWhites",
            "SteadyMulti",
            "CrossOverWave",
            "ForwardWave",
            "AlternateDirectionalWave",
            "FadeInFadeOutSolidColors",
            "BidirectionalWave",
            "FadeInFadeOutMultiColors",
            "Meteorite",
            "Twinkle",
            "Rainbow",
            "MEORandomStrobe",
            "RandomFade",
            "Chase",
            "Solid",
            "Wave",
            "StrobeFill",
            "ShootingStars",
            "Dissolve"});
            this.cmbProgram.Location = new System.Drawing.Point(496, 140);
            this.cmbProgram.Name = "cmbProgram";
            this.cmbProgram.Size = new System.Drawing.Size(119, 24);
            this.cmbProgram.TabIndex = 37;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txtProgramOptionCount);
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Controls.Add(this.chkProgramOptionWait);
            this.groupBox1.Controls.Add(this.chkProgramOptionRandom);
            this.groupBox1.Controls.Add(this.chkProgramOptionFillImmediate);
            this.groupBox1.Controls.Add(this.chkProgramOptionForwardDirection);
            this.groupBox1.Location = new System.Drawing.Point(372, 230);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(243, 111);
            this.groupBox1.TabIndex = 39;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Program Options";
            // 
            // txtProgramOptionCount
            // 
            this.txtProgramOptionCount.Location = new System.Drawing.Point(60, 78);
            this.txtProgramOptionCount.Name = "txtProgramOptionCount";
            this.txtProgramOptionCount.Size = new System.Drawing.Size(100, 22);
            this.txtProgramOptionCount.TabIndex = 5;
            this.txtProgramOptionCount.Text = "0";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(8, 78);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(45, 17);
            this.label11.TabIndex = 4;
            this.label11.Text = "Count";
            // 
            // chkProgramOptionWait
            // 
            this.chkProgramOptionWait.AutoSize = true;
            this.chkProgramOptionWait.Location = new System.Drawing.Point(155, 50);
            this.chkProgramOptionWait.Name = "chkProgramOptionWait";
            this.chkProgramOptionWait.Size = new System.Drawing.Size(58, 21);
            this.chkProgramOptionWait.TabIndex = 3;
            this.chkProgramOptionWait.Text = "Wait";
            this.chkProgramOptionWait.UseVisualStyleBackColor = true;
            // 
            // chkProgramOptionRandom
            // 
            this.chkProgramOptionRandom.AutoSize = true;
            this.chkProgramOptionRandom.Checked = true;
            this.chkProgramOptionRandom.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkProgramOptionRandom.Location = new System.Drawing.Point(155, 22);
            this.chkProgramOptionRandom.Name = "chkProgramOptionRandom";
            this.chkProgramOptionRandom.Size = new System.Drawing.Size(83, 21);
            this.chkProgramOptionRandom.TabIndex = 2;
            this.chkProgramOptionRandom.Text = "Random";
            this.chkProgramOptionRandom.UseVisualStyleBackColor = true;
            // 
            // chkProgramOptionFillImmediate
            // 
            this.chkProgramOptionFillImmediate.AutoSize = true;
            this.chkProgramOptionFillImmediate.Checked = true;
            this.chkProgramOptionFillImmediate.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkProgramOptionFillImmediate.Location = new System.Drawing.Point(8, 50);
            this.chkProgramOptionFillImmediate.Name = "chkProgramOptionFillImmediate";
            this.chkProgramOptionFillImmediate.Size = new System.Drawing.Size(115, 21);
            this.chkProgramOptionFillImmediate.TabIndex = 1;
            this.chkProgramOptionFillImmediate.Text = "Fill Immediate";
            this.chkProgramOptionFillImmediate.UseVisualStyleBackColor = true;
            // 
            // chkProgramOptionForwardDirection
            // 
            this.chkProgramOptionForwardDirection.AutoSize = true;
            this.chkProgramOptionForwardDirection.Checked = true;
            this.chkProgramOptionForwardDirection.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkProgramOptionForwardDirection.Location = new System.Drawing.Point(8, 22);
            this.chkProgramOptionForwardDirection.Name = "chkProgramOptionForwardDirection";
            this.chkProgramOptionForwardDirection.Size = new System.Drawing.Size(141, 21);
            this.chkProgramOptionForwardDirection.TabIndex = 0;
            this.chkProgramOptionForwardDirection.Text = "Forward Direction";
            this.chkProgramOptionForwardDirection.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.chkCommandOptionGroup);
            this.groupBox2.Controls.Add(this.chkCommandOptionUpdate);
            this.groupBox2.Controls.Add(this.chkCommandOptionDefer);
            this.groupBox2.Location = new System.Drawing.Point(372, 56);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(243, 60);
            this.groupBox2.TabIndex = 40;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Command Options";
            // 
            // chkCommandOptionGroup
            // 
            this.chkCommandOptionGroup.AutoSize = true;
            this.chkCommandOptionGroup.Location = new System.Drawing.Point(79, 23);
            this.chkCommandOptionGroup.Name = "chkCommandOptionGroup";
            this.chkCommandOptionGroup.Size = new System.Drawing.Size(70, 21);
            this.chkCommandOptionGroup.TabIndex = 3;
            this.chkCommandOptionGroup.Text = "Group";
            this.chkCommandOptionGroup.UseVisualStyleBackColor = true;
            // 
            // chkCommandOptionUpdate
            // 
            this.chkCommandOptionUpdate.AutoSize = true;
            this.chkCommandOptionUpdate.Location = new System.Drawing.Point(155, 22);
            this.chkCommandOptionUpdate.Name = "chkCommandOptionUpdate";
            this.chkCommandOptionUpdate.Size = new System.Drawing.Size(76, 21);
            this.chkCommandOptionUpdate.TabIndex = 2;
            this.chkCommandOptionUpdate.Text = "Update";
            this.chkCommandOptionUpdate.UseVisualStyleBackColor = true;
            // 
            // chkCommandOptionDefer
            // 
            this.chkCommandOptionDefer.AutoSize = true;
            this.chkCommandOptionDefer.Location = new System.Drawing.Point(8, 22);
            this.chkCommandOptionDefer.Name = "chkCommandOptionDefer";
            this.chkCommandOptionDefer.Size = new System.Drawing.Size(65, 21);
            this.chkCommandOptionDefer.TabIndex = 0;
            this.chkCommandOptionDefer.Text = "Defer";
            this.chkCommandOptionDefer.UseVisualStyleBackColor = true;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(377, 119);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(98, 17);
            this.label8.TabIndex = 41;
            this.label8.Text = "Random Seed";
            // 
            // txtRandomSeed
            // 
            this.txtRandomSeed.Location = new System.Drawing.Point(372, 143);
            this.txtRandomSeed.Name = "txtRandomSeed";
            this.txtRandomSeed.Size = new System.Drawing.Size(100, 22);
            this.txtRandomSeed.TabIndex = 42;
            this.txtRandomSeed.Text = "0";
            // 
            // txtProgramPattern
            // 
            this.txtProgramPattern.Location = new System.Drawing.Point(372, 197);
            this.txtProgramPattern.Name = "txtProgramPattern";
            this.txtProgramPattern.Size = new System.Drawing.Size(100, 22);
            this.txtProgramPattern.TabIndex = 43;
            this.txtProgramPattern.Text = "0";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(377, 177);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(54, 17);
            this.label9.TabIndex = 44;
            this.label9.Text = "Pattern";
            // 
            // bntCommit
            // 
            this.bntCommit.Location = new System.Drawing.Point(714, 375);
            this.bntCommit.Name = "bntCommit";
            this.bntCommit.Size = new System.Drawing.Size(73, 26);
            this.bntCommit.TabIndex = 45;
            this.bntCommit.Text = "Commit";
            this.bntCommit.UseVisualStyleBackColor = true;
            this.bntCommit.Click += new System.EventHandler(this.bntCommit_Click);
            // 
            // bntOff
            // 
            this.bntOff.Location = new System.Drawing.Point(872, 375);
            this.bntOff.Name = "bntOff";
            this.bntOff.Size = new System.Drawing.Size(73, 26);
            this.bntOff.TabIndex = 46;
            this.bntOff.Text = "Off";
            this.bntOff.UseVisualStyleBackColor = true;
            this.bntOff.Click += new System.EventHandler(this.bntOff_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.groupBox6);
            this.groupBox3.Controls.Add(this.groupBox5);
            this.groupBox3.Controls.Add(this.btnIdConfig);
            this.groupBox3.Controls.Add(this.txtIdConfigTargetStringId);
            this.groupBox3.Controls.Add(this.label17);
            this.groupBox3.Location = new System.Drawing.Point(972, 28);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(175, 371);
            this.groupBox3.TabIndex = 48;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Address Config";
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.txtIdConfigStringGroupC);
            this.groupBox6.Controls.Add(this.label24);
            this.groupBox6.Controls.Add(this.txtIdConfigStringGroupD);
            this.groupBox6.Controls.Add(this.label25);
            this.groupBox6.Controls.Add(this.txtIdConfigStringGroupA);
            this.groupBox6.Controls.Add(this.label23);
            this.groupBox6.Controls.Add(this.txtIdConfigStringId);
            this.groupBox6.Controls.Add(this.txtIdConfigStringGroupB);
            this.groupBox6.Controls.Add(this.label16);
            this.groupBox6.Controls.Add(this.label21);
            this.groupBox6.Location = new System.Drawing.Point(11, 159);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(151, 172);
            this.groupBox6.TabIndex = 19;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "String Addressing";
            // 
            // txtIdConfigStringGroupC
            // 
            this.txtIdConfigStringGroupC.Location = new System.Drawing.Point(13, 132);
            this.txtIdConfigStringGroupC.Name = "txtIdConfigStringGroupC";
            this.txtIdConfigStringGroupC.Size = new System.Drawing.Size(35, 22);
            this.txtIdConfigStringGroupC.TabIndex = 17;
            this.txtIdConfigStringGroupC.Text = "0";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(62, 114);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(46, 17);
            this.label24.TabIndex = 20;
            this.label24.Text = "Grp D";
            // 
            // txtIdConfigStringGroupD
            // 
            this.txtIdConfigStringGroupD.Location = new System.Drawing.Point(63, 132);
            this.txtIdConfigStringGroupD.Name = "txtIdConfigStringGroupD";
            this.txtIdConfigStringGroupD.Size = new System.Drawing.Size(35, 22);
            this.txtIdConfigStringGroupD.TabIndex = 19;
            this.txtIdConfigStringGroupD.Text = "0";
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(12, 114);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(45, 17);
            this.label25.TabIndex = 18;
            this.label25.Text = "Grp C";
            // 
            // txtIdConfigStringGroupA
            // 
            this.txtIdConfigStringGroupA.Location = new System.Drawing.Point(11, 82);
            this.txtIdConfigStringGroupA.Name = "txtIdConfigStringGroupA";
            this.txtIdConfigStringGroupA.Size = new System.Drawing.Size(35, 22);
            this.txtIdConfigStringGroupA.TabIndex = 11;
            this.txtIdConfigStringGroupA.Text = "1";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(60, 64);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(45, 17);
            this.label23.TabIndex = 16;
            this.label23.Text = "Grp B";
            // 
            // txtIdConfigStringId
            // 
            this.txtIdConfigStringId.Location = new System.Drawing.Point(10, 38);
            this.txtIdConfigStringId.Name = "txtIdConfigStringId";
            this.txtIdConfigStringId.Size = new System.Drawing.Size(35, 22);
            this.txtIdConfigStringId.TabIndex = 7;
            this.txtIdConfigStringId.Text = "1";
            // 
            // txtIdConfigStringGroupB
            // 
            this.txtIdConfigStringGroupB.Location = new System.Drawing.Point(61, 82);
            this.txtIdConfigStringGroupB.Name = "txtIdConfigStringGroupB";
            this.txtIdConfigStringGroupB.Size = new System.Drawing.Size(35, 22);
            this.txtIdConfigStringGroupB.TabIndex = 15;
            this.txtIdConfigStringGroupB.Text = "0";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(8, 18);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(21, 17);
            this.label16.TabIndex = 8;
            this.label16.Text = "ID";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(10, 64);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(45, 17);
            this.label21.TabIndex = 12;
            this.label21.Text = "Grp A";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.txtIdConfigRFID);
            this.groupBox5.Controls.Add(this.label12);
            this.groupBox5.Controls.Add(this.label22);
            this.groupBox5.Controls.Add(this.txtIdConfigRFController);
            this.groupBox5.Controls.Add(this.txtIdConfigRFGroup);
            this.groupBox5.Controls.Add(this.label15);
            this.groupBox5.Location = new System.Drawing.Point(11, 66);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(151, 79);
            this.groupBox5.TabIndex = 18;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "RF Addressing";
            // 
            // txtIdConfigRFID
            // 
            this.txtIdConfigRFID.Location = new System.Drawing.Point(12, 43);
            this.txtIdConfigRFID.Name = "txtIdConfigRFID";
            this.txtIdConfigRFID.Size = new System.Drawing.Size(35, 22);
            this.txtIdConfigRFID.TabIndex = 2;
            this.txtIdConfigRFID.Text = "1";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(105, 23);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(29, 17);
            this.label12.TabIndex = 0;
            this.label12.Text = "Ctrl";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(54, 23);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(48, 17);
            this.label22.TabIndex = 14;
            this.label22.Text = "Group";
            // 
            // txtIdConfigRFController
            // 
            this.txtIdConfigRFController.Location = new System.Drawing.Point(106, 43);
            this.txtIdConfigRFController.Name = "txtIdConfigRFController";
            this.txtIdConfigRFController.Size = new System.Drawing.Size(35, 22);
            this.txtIdConfigRFController.TabIndex = 1;
            this.txtIdConfigRFController.Text = "30";
            // 
            // txtIdConfigRFGroup
            // 
            this.txtIdConfigRFGroup.Location = new System.Drawing.Point(59, 43);
            this.txtIdConfigRFGroup.Name = "txtIdConfigRFGroup";
            this.txtIdConfigRFGroup.Size = new System.Drawing.Size(35, 22);
            this.txtIdConfigRFGroup.TabIndex = 13;
            this.txtIdConfigRFGroup.Text = "1";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(10, 23);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(21, 17);
            this.label15.TabIndex = 9;
            this.label15.Text = "ID";
            // 
            // btnIdConfig
            // 
            this.btnIdConfig.Location = new System.Drawing.Point(44, 337);
            this.btnIdConfig.Name = "btnIdConfig";
            this.btnIdConfig.Size = new System.Drawing.Size(75, 23);
            this.btnIdConfig.TabIndex = 10;
            this.btnIdConfig.Text = "Config";
            this.btnIdConfig.UseVisualStyleBackColor = true;
            this.btnIdConfig.Click += new System.EventHandler(this.btnIdConfig_Click);
            // 
            // txtIdConfigTargetStringId
            // 
            this.txtIdConfigTargetStringId.Location = new System.Drawing.Point(11, 38);
            this.txtIdConfigTargetStringId.Name = "txtIdConfigTargetStringId";
            this.txtIdConfigTargetStringId.Size = new System.Drawing.Size(35, 22);
            this.txtIdConfigTargetStringId.TabIndex = 6;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(11, 18);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(108, 17);
            this.label17.TabIndex = 5;
            this.label17.Text = "Target String ID";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label26);
            this.groupBox4.Controls.Add(this.txtStringConfigDelay);
            this.groupBox4.Controls.Add(this.label1);
            this.groupBox4.Controls.Add(this.label13);
            this.groupBox4.Controls.Add(this.txtStringConfigId);
            this.groupBox4.Controls.Add(this.btnStringConfig);
            this.groupBox4.Controls.Add(this.label19);
            this.groupBox4.Controls.Add(this.cmbStringConfigDirection);
            this.groupBox4.Controls.Add(this.txtStringConfigLogical);
            this.groupBox4.Controls.Add(this.txtStringConfigPhysical);
            this.groupBox4.Controls.Add(this.label18);
            this.groupBox4.Location = new System.Drawing.Point(633, 13);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(322, 152);
            this.groupBox4.TabIndex = 49;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "String Config";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(81, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(64, 17);
            this.label1.TabIndex = 14;
            this.label1.Text = "Direction";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(6, 22);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(62, 17);
            this.label13.TabIndex = 13;
            this.label13.Text = "String ID";
            // 
            // txtStringConfigId
            // 
            this.txtStringConfigId.Location = new System.Drawing.Point(6, 42);
            this.txtStringConfigId.Name = "txtStringConfigId";
            this.txtStringConfigId.Size = new System.Drawing.Size(60, 22);
            this.txtStringConfigId.TabIndex = 12;
            // 
            // btnStringConfig
            // 
            this.btnStringConfig.Location = new System.Drawing.Point(37, 115);
            this.btnStringConfig.Name = "btnStringConfig";
            this.btnStringConfig.Size = new System.Drawing.Size(75, 23);
            this.btnStringConfig.TabIndex = 11;
            this.btnStringConfig.Text = "Config";
            this.btnStringConfig.UseVisualStyleBackColor = true;
            this.btnStringConfig.Click += new System.EventHandler(this.btnStringConfig_Click);
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(81, 67);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(53, 17);
            this.label19.TabIndex = 4;
            this.label19.Text = "Logical";
            // 
            // cmbStringConfigDirection
            // 
            this.cmbStringConfigDirection.FormattingEnabled = true;
            this.cmbStringConfigDirection.Items.AddRange(new object[] {
            "Forward",
            "Backward"});
            this.cmbStringConfigDirection.Location = new System.Drawing.Point(84, 40);
            this.cmbStringConfigDirection.Name = "cmbStringConfigDirection";
            this.cmbStringConfigDirection.Size = new System.Drawing.Size(59, 24);
            this.cmbStringConfigDirection.TabIndex = 3;
            // 
            // txtStringConfigLogical
            // 
            this.txtStringConfigLogical.Location = new System.Drawing.Point(84, 87);
            this.txtStringConfigLogical.Name = "txtStringConfigLogical";
            this.txtStringConfigLogical.Size = new System.Drawing.Size(59, 22);
            this.txtStringConfigLogical.TabIndex = 2;
            // 
            // txtStringConfigPhysical
            // 
            this.txtStringConfigPhysical.Location = new System.Drawing.Point(6, 87);
            this.txtStringConfigPhysical.Name = "txtStringConfigPhysical";
            this.txtStringConfigPhysical.Size = new System.Drawing.Size(59, 22);
            this.txtStringConfigPhysical.TabIndex = 1;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(6, 67);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(60, 17);
            this.label18.TabIndex = 0;
            this.label18.Text = "Physical";
            // 
            // txtWaveColors
            // 
            this.txtWaveColors.Location = new System.Drawing.Point(635, 196);
            this.txtWaveColors.Multiline = true;
            this.txtWaveColors.Name = "txtWaveColors";
            this.txtWaveColors.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtWaveColors.Size = new System.Drawing.Size(100, 173);
            this.txtWaveColors.TabIndex = 50;
            this.txtWaveColors.Text = "Blue\r\nWhite\r\nBlue\r\n ";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(632, 176);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(48, 17);
            this.label14.TabIndex = 51;
            this.label14.Text = "Colors";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(740, 176);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(44, 17);
            this.label20.TabIndex = 53;
            this.label20.Text = "Holds";
            // 
            // txtWaveHolds
            // 
            this.txtWaveHolds.Location = new System.Drawing.Point(741, 196);
            this.txtWaveHolds.Multiline = true;
            this.txtWaveHolds.Name = "txtWaveHolds";
            this.txtWaveHolds.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtWaveHolds.Size = new System.Drawing.Size(100, 173);
            this.txtWaveHolds.TabIndex = 52;
            this.txtWaveHolds.Text = "1\r\n1\r\n0\r\n ";
            // 
            // cmbWaveColor
            // 
            this.cmbWaveColor.FormattingEnabled = true;
            this.cmbWaveColor.Items.AddRange(new object[] {
            "Red",
            "Green",
            "Blue",
            "Yellow",
            "Magenta",
            "Cyan",
            "White",
            "Black"});
            this.cmbWaveColor.Location = new System.Drawing.Point(846, 176);
            this.cmbWaveColor.Name = "cmbWaveColor";
            this.cmbWaveColor.Size = new System.Drawing.Size(69, 24);
            this.cmbWaveColor.TabIndex = 54;
            // 
            // txtWaveHold
            // 
            this.txtWaveHold.Location = new System.Drawing.Point(921, 176);
            this.txtWaveHold.Name = "txtWaveHold";
            this.txtWaveHold.Size = new System.Drawing.Size(34, 22);
            this.txtWaveHold.TabIndex = 55;
            this.txtWaveHold.Text = "1";
            // 
            // btnWaveAdd
            // 
            this.btnWaveAdd.Location = new System.Drawing.Point(847, 207);
            this.btnWaveAdd.Name = "btnWaveAdd";
            this.btnWaveAdd.Size = new System.Drawing.Size(108, 23);
            this.btnWaveAdd.TabIndex = 56;
            this.btnWaveAdd.Text = "Add";
            this.btnWaveAdd.UseVisualStyleBackColor = true;
            this.btnWaveAdd.Click += new System.EventHandler(this.btnWaveAdd_Click);
            // 
            // bntWaveClear
            // 
            this.bntWaveClear.Location = new System.Drawing.Point(847, 237);
            this.bntWaveClear.Name = "bntWaveClear";
            this.bntWaveClear.Size = new System.Drawing.Size(108, 23);
            this.bntWaveClear.TabIndex = 57;
            this.bntWaveClear.Text = "Clear";
            this.bntWaveClear.UseVisualStyleBackColor = true;
            this.bntWaveClear.Click += new System.EventHandler(this.bntWaveClear_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(847, 324);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(36, 17);
            this.label2.TabIndex = 60;
            this.label2.Text = "Dist.";
            // 
            // txtWaveDistribution
            // 
            this.txtWaveDistribution.Location = new System.Drawing.Point(912, 321);
            this.txtWaveDistribution.Name = "txtWaveDistribution";
            this.txtWaveDistribution.Size = new System.Drawing.Size(43, 22);
            this.txtWaveDistribution.TabIndex = 59;
            this.txtWaveDistribution.Text = "0";
            // 
            // cmbWaveIncrements
            // 
            this.cmbWaveIncrements.FormattingEnabled = true;
            this.cmbWaveIncrements.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15"});
            this.cmbWaveIncrements.Location = new System.Drawing.Point(912, 263);
            this.cmbWaveIncrements.Name = "cmbWaveIncrements";
            this.cmbWaveIncrements.Size = new System.Drawing.Size(43, 24);
            this.cmbWaveIncrements.TabIndex = 61;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(847, 352);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 17);
            this.label4.TabIndex = 63;
            this.label4.Text = "Span";
            // 
            // txtWaveSpan
            // 
            this.txtWaveSpan.Location = new System.Drawing.Point(912, 349);
            this.txtWaveSpan.Name = "txtWaveSpan";
            this.txtWaveSpan.Size = new System.Drawing.Size(43, 22);
            this.txtWaveSpan.TabIndex = 62;
            this.txtWaveSpan.Text = "1";
            // 
            // btnKick
            // 
            this.btnKick.Location = new System.Drawing.Point(793, 375);
            this.btnKick.Name = "btnKick";
            this.btnKick.Size = new System.Drawing.Size(75, 26);
            this.btnKick.TabIndex = 64;
            this.btnKick.Text = "Kick";
            this.btnKick.UseVisualStyleBackColor = true;
            this.btnKick.Click += new System.EventHandler(this.btnKick_Click);
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(151, 21);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(44, 17);
            this.label26.TabIndex = 16;
            this.label26.Text = "Delay";
            // 
            // txtStringConfigDelay
            // 
            this.txtStringConfigDelay.Location = new System.Drawing.Point(154, 41);
            this.txtStringConfigDelay.Name = "txtStringConfigDelay";
            this.txtStringConfigDelay.Size = new System.Drawing.Size(59, 22);
            this.txtStringConfigDelay.TabIndex = 15;
            this.txtStringConfigDelay.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1164, 421);
            this.Controls.Add(this.btnKick);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.txtWaveSpan);
            this.Controls.Add(this.cmbWaveIncrements);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtWaveDistribution);
            this.Controls.Add(this.bntWaveClear);
            this.Controls.Add(this.btnWaveAdd);
            this.Controls.Add(this.txtWaveHold);
            this.Controls.Add(this.cmbWaveColor);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.txtWaveHolds);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.txtWaveColors);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.bntOff);
            this.Controls.Add(this.bntCommit);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.txtProgramPattern);
            this.Controls.Add(this.txtRandomSeed);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.cmbProgram);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.btnSetNode);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.txtProgramDelay);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.txtAddress);
            this.Controls.Add(this.btnProgram);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.txtWavePixelCount);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtSendCommand);
            this.Controls.Add(this.ComPortSelector);
            this.Controls.Add(this.btnSend);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.txtReceived);
            this.Name = "Form1";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtReceived;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.ComboBox ComPortSelector;
        private System.Windows.Forms.TextBox txtSendCommand;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtWavePixelCount;
        private System.Windows.Forms.Button btnProgram;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtAddress;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtProgramDelay;
        private System.Windows.Forms.Button btnSetNode;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.ComboBox cmbProgram;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox txtProgramOptionCount;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.CheckBox chkProgramOptionWait;
        private System.Windows.Forms.CheckBox chkProgramOptionRandom;
        private System.Windows.Forms.CheckBox chkProgramOptionFillImmediate;
        private System.Windows.Forms.CheckBox chkProgramOptionForwardDirection;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox chkCommandOptionUpdate;
        private System.Windows.Forms.CheckBox chkCommandOptionDefer;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txtRandomSeed;
        private System.Windows.Forms.TextBox txtProgramPattern;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button bntCommit;
        private System.Windows.Forms.Button bntOff;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btnIdConfig;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox txtIdConfigStringId;
        private System.Windows.Forms.TextBox txtIdConfigTargetStringId;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TextBox txtIdConfigRFID;
        private System.Windows.Forms.TextBox txtIdConfigRFController;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btnStringConfig;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.ComboBox cmbStringConfigDirection;
        private System.Windows.Forms.TextBox txtStringConfigLogical;
        private System.Windows.Forms.TextBox txtStringConfigPhysical;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox txtStringConfigId;
        private System.Windows.Forms.TextBox txtWaveColors;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.TextBox txtWaveHolds;
        private System.Windows.Forms.ComboBox cmbWaveColor;
        private System.Windows.Forms.TextBox txtWaveHold;
        private System.Windows.Forms.Button btnWaveAdd;
        private System.Windows.Forms.Button bntWaveClear;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtWaveDistribution;
        private System.Windows.Forms.ComboBox cmbWaveIncrements;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtWaveSpan;
        private System.Windows.Forms.CheckBox chkCommandOptionGroup;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.TextBox txtIdConfigRFGroup;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.TextBox txtIdConfigStringGroupA;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.TextBox txtIdConfigStringGroupC;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.TextBox txtIdConfigStringGroupD;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.TextBox txtIdConfigStringGroupB;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Button btnKick;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.TextBox txtStringConfigDelay;
    }
}

