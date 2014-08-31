using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace ServerDBA
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            this.SetVisibleCore(false);
            InitializeComponent();
            //__initServer();
            Application.Idle += this.idleListener;
        }

        public void __initServer()
        {
            int procCount = 2;

            string[] tokens = new string[2];
            tokens[0] = "12345678";
            tokens[1] = "87654321";

            int[] bufSIze = new int[2];
            bufSIze[0] = bufSIze[1] = 1;

            g_regist(procCount, tokens, bufSIze);
        }

#region 服务端导出

#if DEBUG
                //D:\\Mty\\vs_proj\\NIPlayRoomV2\\CrossProcessNotificationManager
        [DllImport("..\\..\\..\\bin\\Win32\\Debug\\CrossProcessNotificationServer.dll", EntryPoint = "g_unload", CharSet = CharSet.Unicode)]
        static extern void g_unload();

        [DllImport("..\\..\\..\\bin\\Win32\\Debug\\CrossProcessNotificationServer.dll", EntryPoint = "g_regist", CharSet = CharSet.Unicode)]
        static extern bool g_regist(int procCount, string [] tokens, int [] bufSIze);
#else
        //D:\\Mty\\vs_proj\\NIPlayRoomV2\\CrossProcessNotificationManager
        [DllImport("..\\..\\..\\bin\\Win32\\Release\\CrossProcessNotificationServer.dll", EntryPoint = "g_unload", CharSet = CharSet.Unicode)]
        static extern void g_unload();

        [DllImport("..\\..\\..\\bin\\Win32\\Release\\CrossProcessNotificationServer.dll", EntryPoint = "g_regist", CharSet = CharSet.Unicode)]
        static extern bool g_regist(int procCount, string[] tokens, int[] bufSIze);
#endif
#endregion

        #region 数据段
        List<string> m_tokens = new List<string>();
        int m_bytBuffSIze = 1; //per kb.
#endregion

        private void button1_runServer_Click(object sender, EventArgs e)
        {
            string [] tokens = new string [m_tokens.Count];
            for (int i = 0; i < m_tokens.Count; ++i)
            {
                tokens[i] = m_tokens[i];
            }
            int [] bufSIzes = new int [m_tokens.Count];
            for (int i = 0; i < m_tokens.Count; ++i )
            {
                bufSIzes[i] = m_bytBuffSIze;
            }
            g_regist(m_tokens.Count, tokens, bufSIzes);
        } 

        private void button1_addToken_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(this.textBox1_token.Text))
            {
                this.label1_content.Text += "\n" + this.textBox1_token.Text;
                m_tokens.Add(this.textBox1_token.Text);
            }
        }

        private void button2_stopServer_Click(object sender, EventArgs e)
        {
            g_unload();
        }

        private void idleListener(Object sender, EventArgs e)
        {
            //Console.WriteLine("...");
        }
    }
}
