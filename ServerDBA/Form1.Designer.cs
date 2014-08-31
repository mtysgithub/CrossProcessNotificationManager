namespace ServerDBA
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
            this.textBox1_token = new System.Windows.Forms.TextBox();
            this.label1_content = new System.Windows.Forms.Label();
            this.button1_addToken = new System.Windows.Forms.Button();
            this.button1_runServer = new System.Windows.Forms.Button();
            this.button2_stopServer = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox1_token
            // 
            this.textBox1_token.Location = new System.Drawing.Point(13, 13);
            this.textBox1_token.Name = "textBox1_token";
            this.textBox1_token.Size = new System.Drawing.Size(203, 21);
            this.textBox1_token.TabIndex = 0;
            // 
            // label1_content
            // 
            this.label1_content.AutoSize = true;
            this.label1_content.Location = new System.Drawing.Point(13, 41);
            this.label1_content.Name = "label1_content";
            this.label1_content.Size = new System.Drawing.Size(0, 12);
            this.label1_content.TabIndex = 1;
            // 
            // button1_addToken
            // 
            this.button1_addToken.Location = new System.Drawing.Point(239, 13);
            this.button1_addToken.Name = "button1_addToken";
            this.button1_addToken.Size = new System.Drawing.Size(37, 20);
            this.button1_addToken.TabIndex = 2;
            this.button1_addToken.Text = "+";
            this.button1_addToken.UseVisualStyleBackColor = true;
            this.button1_addToken.Click += new System.EventHandler(this.button1_addToken_Click);
            // 
            // button1_runServer
            // 
            this.button1_runServer.Location = new System.Drawing.Point(364, 167);
            this.button1_runServer.Name = "button1_runServer";
            this.button1_runServer.Size = new System.Drawing.Size(75, 23);
            this.button1_runServer.TabIndex = 3;
            this.button1_runServer.Text = "运行服务器";
            this.button1_runServer.UseVisualStyleBackColor = true;
            this.button1_runServer.Click += new System.EventHandler(this.button1_runServer_Click);
            // 
            // button2_stopServer
            // 
            this.button2_stopServer.Location = new System.Drawing.Point(364, 197);
            this.button2_stopServer.Name = "button2_stopServer";
            this.button2_stopServer.Size = new System.Drawing.Size(75, 23);
            this.button2_stopServer.TabIndex = 4;
            this.button2_stopServer.Text = "停止服务器";
            this.button2_stopServer.UseVisualStyleBackColor = true;
            this.button2_stopServer.Click += new System.EventHandler(this.button2_stopServer_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(466, 418);
            this.Controls.Add(this.button2_stopServer);
            this.Controls.Add(this.button1_runServer);
            this.Controls.Add(this.button1_addToken);
            this.Controls.Add(this.label1_content);
            this.Controls.Add(this.textBox1_token);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1_token;
        private System.Windows.Forms.Label label1_content;
        private System.Windows.Forms.Button button1_addToken;
        private System.Windows.Forms.Button button1_runServer;
        private System.Windows.Forms.Button button2_stopServer;
    }
}

