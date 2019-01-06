using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace demo06
{
    public partial class FormLogin : Form
    {
        public FormLogin()
        {
            InitializeComponent();
        }

        private void buttonEnter_Click(object sender, EventArgs e)
        {
            login();
        }

        private void FormLogin_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData == Keys.Return)
            {
                login();
            }
        }

        private void login()
        {
            string strName = "", strPassword = "";
            strName = textBoxName.Text.Trim();
            strPassword = textBoxPwd.Text.Trim();

            if (strName == "" && strPassword == "")
            {
                MessageBox.Show("用户名和密码不能为空!");
            }
            else if (strName == "" || strPassword == "")
            {
                MessageBox.Show("用户名或密码不能为空!");
            }
            else
            {
                if (strName != "admin")
                {
                    MessageBox.Show("不存在用户名!");
                }
                else if (strPassword != "abc")
                {
                    MessageBox.Show("密码不正确!");
                }
                else
                {
                    MessageBox.Show("登录成功!");
                }
            }
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
