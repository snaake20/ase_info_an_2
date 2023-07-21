using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PregatireTest1
{
	public partial class ModalMaterial : Form
	{
		Magazie magazie;
		int? id;
		int index = -1;
		public ModalMaterial(Magazie m, int? i)
		{
			InitializeComponent();
			magazie = m;
			id = i;
			if (id == null)
			{
				BtnActiune.Text = "Adauga";
			}
			else
			{
				for (int idx = 0; idx < magazie.Materiale.Length; idx++)
				{
					if (magazie.Materiale[idx].Id == id)
					{
						index = idx;
						textBox1.Text = id.ToString();
						textBox1.Enabled = false;
						textBox2.Text = magazie.Materiale[idx].Denumire;
						textBox3.Text = magazie.Materiale[idx].Pret.ToString();
					}
				}
				BtnActiune.Text = "Editeaza";
			}
		}

		public Magazie Magazie { get => magazie; set => magazie = value; }

		private void BtnActiune_Click(object sender, EventArgs e)
		{
			if (id == null)
			{
				Material material = new Material(Convert.ToInt32(textBox1.Text), textBox2.Text, float.Parse(textBox3.Text));
				magazie += material;
			}
			else
			{
				magazie.Materiale[index].Denumire = textBox2.Text;
				magazie.Materiale[index].Pret = float.Parse(textBox3.Text);
			}
			Close();
		}
	}
}
