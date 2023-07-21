using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Vagon
{
	public partial class FormP : Form
	{
		Tren tren = new Tren();
		public FormP()
		{
			InitializeComponent();

			tren.CodT = 1;

			tren.citireTxt("vagoane.txt");

			tren.NrVagoane = tren.LstVagoane.Count;


			foreach (var vagon in tren.LstVagoane)
			{
				var itm = new ListViewItem(vagon.CodV.ToString());

				itm.SubItems.Add(vagon.DescriereTip);
				itm.SubItems.Add(vagon.Capacitate.ToString());

				LVVagoane.Items.Add(itm);
			}

		}

		private void BTNFiltrare_Click(object sender, EventArgs e)
		{
			if (!CBTip.Text.Equals(""))
			{

				LVVagoane.Items.Clear();

				List<Vagon> vagoaneFiltrate = tren.LstVagoane.Where(vagon => vagon.DescriereTip.Equals(CBTip.Text)).OrderBy(vagon => vagon.Capacitate).ToList();

				foreach (var vagon in vagoaneFiltrate)
				{
					var itm = new ListViewItem(vagon.CodV.ToString());

					itm.SubItems.Add(vagon.DescriereTip);
					itm.SubItems.Add(vagon.Capacitate.ToString());

					LVVagoane.Items.Add(itm);
				}

			}
		}

		private void LVVagoane_MouseDoubleClick(object sender, MouseEventArgs e)
		{
			if (LVVagoane.SelectedItems.Count == 1) {
				int cod = Convert.ToInt32(LVVagoane.SelectedItems[0].Text);
				FormS form = new FormS(tren, cod, tren.LstVagoane.GroupBy(vagon => vagon.DescriereTip).Select(group => group.Key).ToList());
				form.ShowDialog();

				LVVagoane.Items.Clear();

				if (CBTip.Text.Equals(""))
				{
					foreach (var vagon in tren.LstVagoane)
					{
						var itm = new ListViewItem(vagon.CodV.ToString());

						itm.SubItems.Add(vagon.DescriereTip);
						itm.SubItems.Add(vagon.Capacitate.ToString());

						LVVagoane.Items.Add(itm);
					}
				} else
				{
					List<Vagon> vagoaneFiltrate = tren.LstVagoane.Where(vagon => vagon.DescriereTip.Equals(CBTip.Text)).OrderBy(vagon => vagon.Capacitate).ToList();

					foreach (var vagon in vagoaneFiltrate)
					{
						var itm = new ListViewItem(vagon.CodV.ToString());

						itm.SubItems.Add(vagon.DescriereTip);
						itm.SubItems.Add(vagon.Capacitate.ToString());

						LVVagoane.Items.Add(itm);
					}
				}

			}
		}

		private void culoareToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (LVVagoane.SelectedItems.Count == 1) {
				ColorDialog dlg = new ColorDialog();
				if (dlg.ShowDialog() == DialogResult.OK)
				{
					LVVagoane.SelectedItems[0].BackColor = dlg.Color;
				}
			}
		}

		private void stergereToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (LVVagoane.SelectedItems.Count == 1) {
				int cod = Convert.ToInt32(LVVagoane.SelectedItems[0].Text);

				tren.LstVagoane = tren.LstVagoane.Where(vagon => !vagon.CodV.Equals(cod)).ToList();

				LVVagoane.Items.Clear();

				if (CBTip.Text.Equals(""))
				{
					foreach (var vagon in tren.LstVagoane)
					{
						var itm = new ListViewItem(vagon.CodV.ToString());

						itm.SubItems.Add(vagon.DescriereTip);
						itm.SubItems.Add(vagon.Capacitate.ToString());

						LVVagoane.Items.Add(itm);
					}
				}
				else
				{
					List<Vagon> vagoaneFiltrate = tren.LstVagoane.Where(vagon => vagon.DescriereTip.Equals(CBTip.Text)).OrderBy(vagon => vagon.Capacitate).ToList();

					foreach (var vagon in vagoaneFiltrate)
					{
						var itm = new ListViewItem(vagon.CodV.ToString());

						itm.SubItems.Add(vagon.DescriereTip);
						itm.SubItems.Add(vagon.Capacitate.ToString());

						LVVagoane.Items.Add(itm);
					}
				}
			}
		}

		private void CBTip_MouseClick(object sender, MouseEventArgs e)
		{
			CBTip.Items.Clear();

			var tipuriDeVagoane = tren.LstVagoane.GroupBy(vagon => vagon.DescriereTip);

			foreach (var tip in tipuriDeVagoane)
			{
				CBTip.Items.Add(tip.Key);
			}
		}

		private void FormP_FormClosing(object sender, FormClosingEventArgs e)
		{
			try
			{
				BinaryFormatter bf = new BinaryFormatter();
				FileStream fs = new FileStream("vagoane.dat", FileMode.Create, FileAccess.Write);

				bf.Serialize(fs,tren.LstVagoane);
				fs.Close();
				MessageBox.Show("Lista a fost serializata");

			}
			catch {
				MessageBox.Show("Lista nu a putut fi serializata");
			}

		}

		private void BTNGrafic_Click(object sender, EventArgs e)
		{
			if (CBTip.Text.Equals(""))
			{
				Grafic grafic = new Grafic(tren.LstVagoane);

				grafic.ShowDialog();

			}
			else
			{
				List<Vagon> vagoaneFiltrate = tren.LstVagoane.Where(vagon => vagon.DescriereTip.Equals(CBTip.Text)).OrderBy(vagon => vagon.Capacitate).ToList();

				Grafic grafic = new Grafic(vagoaneFiltrate);

				grafic.ShowDialog();
			}
		}
	}
}
