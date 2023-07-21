using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Vagon
{
	public partial class FormS : Form
	{
		Tren tren;
		int cod;
		List<String> optiuni;

		public FormS(Tren t, int c, List<String> o)
		{
			InitializeComponent();
			tren = t;
			cod = c;
			optiuni = o;

			o.ForEach(optiune =>
			{
				comboBox1.Items.Add(optiune);
			});

			textBox1.Text = tren.LstVagoane.Find(vagon => vagon.CodV == cod).CodV.ToString();

			foreach (var itm in comboBox1.Items)
			{
				if (itm.Equals(tren.LstVagoane.Find(vagon => vagon.CodV == cod).DescriereTip))
				{
					comboBox1.SelectedItem = itm;
				}
			}

			textBox2.Text = tren.LstVagoane.Find(vagon => vagon.CodV == cod).Capacitate.ToString();
		}

		private void BTNUpdate_Click(object sender, EventArgs e)
		{
			if (comboBox1.Text.Equals(""))
			{
				EPFormS.SetError(comboBox1, "Nu a fost selectata una dintre optiuni");
			} else if (!optiuni.Any(o => o == comboBox1.Text))
			{
				EPFormS.SetError(comboBox1, "A fost selectata o optiune invalida");
			} else if (Convert.ToInt32(textBox2.Text) <= 0 || textBox2.Text.Equals(""))
			{
				EPFormS.SetError(textBox2, "Nu poate exista un vagon cu o capacitate nula sau negativa");
			} else
			{
				EPFormS.Clear();

				tren.LstVagoane.Find(vagon => vagon.CodV == cod).DescriereTip = comboBox1.Text;
				tren.LstVagoane.Find(vagon => vagon.CodV == cod).Capacitate = Convert.ToInt32(textBox2.Text);

				this.Close();

			}
		}
	}
}
