using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PAW_S04
{
	public partial class Form1 : Form
	{
		List<Student> listaStud = new List<Student>();

		public Form1()
		{
			InitializeComponent();
		}

		internal List<Student> ListaStud { get => listaStud; set => listaStud = value; }

		private void btnCreare_Click(object sender, EventArgs e)
		{
			 
				form1ErrorProvider.Clear();
				try
				{
					int cod = Convert.ToInt32(tbCod.Text);
					char sex = Convert.ToChar(cbSex.Text);
					int varsta = Convert.ToInt32(tbVarsta.Text);
					string nume = tbNume.Text;
					string[] noteS = tbNote.Text.Trim().Split(',');
					int[] note = new int[noteS.Length];
					for (int i = 0; i < note.Length; i++)
					{
						note[i] = Convert.ToInt32(noteS[i]);
					}
					Student s = new Student(cod, sex, varsta, nume, note);
					//MessageBox.Show(s.ToString());
					listaStud.Add(s);
				}
				catch (Exception ex)
				{
					MessageBox.Show(ex.Message);
				}
				finally
				{
					tbCod.Clear();
					cbSex.Text = "";
					tbVarsta.Clear();
					tbNume.Clear();
					tbNote.Clear();
				}
			}
			
		}

		private void btnVizualizareStudenti_Click(object sender, EventArgs e)
		{
			Form2 form = new Form2(listaStud);
			form.Show();
		}

		private void schimbaCuloareFundalToolStripMenuItem_Click(object sender, EventArgs e)
		{
			ColorDialog dlg = new ColorDialog();
			if (dlg.ShowDialog() == DialogResult.OK)
			{
				this.BackColor = dlg.Color;
			}
		}

		private void schimbaFontToolStripMenuItem_Click(object sender, EventArgs e)
		{
			FontDialog dlg = new FontDialog();
			if (dlg.ShowDialog() == DialogResult.OK) { 
				this.Font = dlg.Font;
			}
		}
	}
}
