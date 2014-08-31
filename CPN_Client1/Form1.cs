using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace CPN_Client1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Application.Idle += this.idleListener;
        }

        [DllImport("kernel32", EntryPoint = "LoadLibrary", SetLastError = true)]
        static extern IntPtr LoadLibrary(string lpLibName);
        [DllImport("kernel32", EntryPoint = "GetProcAddress", SetLastError = true)]
        static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);
        [DllImport("kernel32", EntryPoint = "FreeLibrary", SetLastError = true)]
        static extern bool FreeLibrary(IntPtr hModule);

#if DEBUG
        //../../../../bin/Win32/Debug/
        [DllImport("..\\..\\..\\bin\\Win32\\Debug\\CrossProcessNotificationClient.dll", EntryPoint = "g_regist", CharSet = CharSet.Unicode)]
        static extern bool g_regist(string channel, int bufSize);

        [DllImport("..\\..\\..\\bin\\Win32\\Debug\\CrossProcessNotificationClient.dll", EntryPoint = "g_sendMessage", CharSet = CharSet.Unicode)]
        static extern bool g_sendMessage(string channel, byte[] content, int bufSize);

        [DllImport("..\\..\\..\\bin\\Win32\\Debug\\CrossProcessNotificationClient.dll", EntryPoint = "g_getRespons", CharSet = CharSet.Unicode)]
        static extern bool getRespons(IntPtr token, IntPtr content, out int bufSIze);

        [DllImport("..\\..\\..\\bin\\Win32\\Debug\\CrossProcessNotificationClient.dll", EntryPoint = "g_unload", CharSet = CharSet.Unicode)]
        static extern void g_unload();
#else
                //../../../../bin/Win32/Debug/
        [DllImport("..\\..\\..\\bin\\Win32\\Release\\CrossProcessNotificationClient.dll", EntryPoint = "g_regist", CharSet = CharSet.Unicode)]
        static extern bool g_regist(string channel, int bufSize);

        [DllImport("..\\..\\..\\bin\\Win32\\Release\\CrossProcessNotificationClient.dll", EntryPoint = "g_sendMessage", CharSet = CharSet.Unicode)]
        static extern bool g_sendMessage(string channel, byte [] content, int bufSize);

        [DllImport("..\\..\\..\\bin\\Win32\\Release\\CrossProcessNotificationClient.dll", EntryPoint = "g_getRespons", CharSet = CharSet.Unicode)]
        static extern bool getRespons(IntPtr token, IntPtr content, out int bufSIze);

        [DllImport("..\\..\\..\\bin\\Win32\\Release\\CrossProcessNotificationClient.dll", EntryPoint = "g_unload", CharSet = CharSet.Unicode)]
        static extern void g_unload();
#endif


        private void start_client_Click(object sender, EventArgs e)
        {
            string token = this.TextBox_HandleTOken.Text;
            int bufSIze = 1; //1kb
            bool ret = g_regist(token, bufSIze);
            Console.WriteLine(ret);
        }

        private void stop_client_Click(object sender, EventArgs e)
        {
            g_unload();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //referesh
            int bufSIze = -1;
            IntPtr pToken = Marshal.AllocHGlobal(8 * 2 * sizeof(Byte));
            IntPtr pCOntent = Marshal.AllocHGlobal((1 << 10) * sizeof(Byte));
            bool funcRet = getRespons(pToken, pCOntent, out bufSIze);
            if (funcRet)
            {
                byte[] token = new byte[8 * 2 * sizeof(Byte)];
                byte[] content = new byte[bufSIze * sizeof(Byte)];
                Marshal.Copy(pCOntent, content, 0, bufSIze);
                this.label1_content.Text = System.Text.Encoding.Unicode.GetString(content);
            }
        }

        private void button2_send_Click(object sender, EventArgs e)
        {
            string token = this.textBox2_toTOken.Text;
            char[] chrArr = this.textBox3_content.Text.ToCharArray();
            byte[] content = new byte[chrArr.Length * sizeof(char)];
            System.Buffer.BlockCopy(chrArr, 0, content, 0, chrArr.Length * sizeof(char));

            int bufSIze = content.Length;
            g_sendMessage(token, content, bufSIze);
        }

        private void idleListener(Object sender, EventArgs e)
        {
            //Console.WriteLine("...");
            button1_Click(null, null);
        }
    }
}

