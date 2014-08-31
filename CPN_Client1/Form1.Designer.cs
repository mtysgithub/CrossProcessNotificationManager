namespace CPN_Client1
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
            this.stop_client = new System.Windows.Forms.Button();
            this.start_client = new System.Windows.Forms.Button();
            this.TextBox_HandleTOken = new System.Windows.Forms.TextBox();
            this.Label = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.button1_referesh = new System.Windows.Forms.Button();
            this.label1_content = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.button2_send = new System.Windows.Forms.Button();
            this.textBox3_content = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.textBox2_toTOken = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // stop_client
            // 
            this.stop_client.Location = new System.Drawing.Point(333, 58);
            this.stop_client.Name = "stop_client";
            this.stop_client.Size = new System.Drawing.Size(94, 29);
            this.stop_client.TabIndex = 0;
            this.stop_client.Text = "stop_client";
            this.stop_client.UseVisualStyleBackColor = true;
            this.stop_client.Click += new System.EventHandler(this.stop_client_Click);
            // 
            // start_client
            // 
            this.start_client.Location = new System.Drawing.Point(333, 26);
            this.start_client.Name = "start_client";
            this.start_client.Size = new System.Drawing.Size(94, 29);
            this.start_client.TabIndex = 1;
            this.start_client.Text = "start_client";
            this.start_client.UseVisualStyleBackColor = true;
            this.start_client.Click += new System.EventHandler(this.start_client_Click);
            // 
            // TextBox_HandleTOken
            // 
            this.TextBox_HandleTOken.Location = new System.Drawing.Point(2, 26);
            this.TextBox_HandleTOken.Name = "TextBox_HandleTOken";
            this.TextBox_HandleTOken.Size = new System.Drawing.Size(262, 21);
            this.TextBox_HandleTOken.TabIndex = 2;
            this.TextBox_HandleTOken.Text = "87654321";
            // 
            // Label
            // 
            this.Label.AutoSize = true;
            this.Label.Location = new System.Drawing.Point(3, 0);
            this.Label.Name = "Label";
            this.Label.Size = new System.Drawing.Size(41, 12);
            this.Label.TabIndex = 3;
            this.Label.Text = "Token:";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.Label);
            this.panel1.Controls.Add(this.stop_client);
            this.panel1.Controls.Add(this.TextBox_HandleTOken);
            this.panel1.Controls.Add(this.start_client);
            this.panel1.Location = new System.Drawing.Point(3, 12);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(444, 106);
            this.panel1.TabIndex = 4;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.button1_referesh);
            this.panel2.Controls.Add(this.label1_content);
            this.panel2.Location = new System.Drawing.Point(5, 125);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(442, 97);
            this.panel2.TabIndex = 5;
            // 
            // button1_referesh
            // 
            this.button1_referesh.Location = new System.Drawing.Point(364, 71);
            this.button1_referesh.Name = "button1_referesh";
            this.button1_referesh.Size = new System.Drawing.Size(75, 23);
            this.button1_referesh.TabIndex = 1;
            this.button1_referesh.Text = "referesh";
            this.button1_referesh.UseVisualStyleBackColor = true;
            this.button1_referesh.Click += new System.EventHandler(this.button1_Click);
            // 
            // label1_content
            // 
            this.label1_content.AutoSize = true;
            this.label1_content.Location = new System.Drawing.Point(3, 10);
            this.label1_content.Name = "label1_content";
            this.label1_content.Size = new System.Drawing.Size(35, 12);
            this.label1_content.TabIndex = 0;
            this.label1_content.Text = "empty";
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.button2_send);
            this.panel3.Controls.Add(this.textBox3_content);
            this.panel3.Controls.Add(this.label3);
            this.panel3.Controls.Add(this.textBox2_toTOken);
            this.panel3.Controls.Add(this.label2);
            this.panel3.Location = new System.Drawing.Point(5, 228);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(442, 142);
            this.panel3.TabIndex = 6;
            // 
            // button2_send
            // 
            this.button2_send.Location = new System.Drawing.Point(364, 116);
            this.button2_send.Name = "button2_send";
            this.button2_send.Size = new System.Drawing.Size(75, 23);
            this.button2_send.TabIndex = 4;
            this.button2_send.Text = "send";
            this.button2_send.UseVisualStyleBackColor = true;
            this.button2_send.Click += new System.EventHandler(this.button2_send_Click);
            // 
            // textBox3_content
            // 
            this.textBox3_content.Location = new System.Drawing.Point(4, 81);
            this.textBox3_content.Name = "textBox3_content";
            this.textBox3_content.Size = new System.Drawing.Size(188, 21);
            this.textBox3_content.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 65);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "conten:";
            // 
            // textBox2_toTOken
            // 
            this.textBox2_toTOken.Location = new System.Drawing.Point(5, 30);
            this.textBox2_toTOken.Name = "textBox2_toTOken";
            this.textBox2_toTOken.Size = new System.Drawing.Size(144, 21);
            this.textBox2_toTOken.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 14);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(23, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "to:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(451, 382);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button stop_client;
        private System.Windows.Forms.Button start_client;
        private System.Windows.Forms.TextBox TextBox_HandleTOken;
        private System.Windows.Forms.Label Label;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Label label1_content;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox2_toTOken;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBox3_content;
        private System.Windows.Forms.Button button1_referesh;
        private System.Windows.Forms.Button button2_send;
    }
}

