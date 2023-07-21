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
	public partial class MeniuPrincipal : Form
	{
		Magazie magazie;
		public MeniuPrincipal()
		{
			InitializeComponent();
			magazie = new Magazie();

			AddToListBox();

		}

		void AddToListBox()
		{
			foreach (Material m in magazie.Materiale)
			{
				LbMateriale.Items.Add(m.ToString());
			}
		}

		void RefreshListBox()
		{
			LbMateriale.Items.Clear();
			AddToListBox();
		}

		private void MeniuPrincipal_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.Alt && e.KeyCode == Keys.E)
			{
				Close();
			}
		}
		
		void OpenModal(int? id = null)
		{
			ModalMaterial modal = new ModalMaterial(magazie, id);
			modal.ShowDialog();
			RefreshListBox();
		}

		private void BtnAdaugareMaterial_Click(object sender, EventArgs e)
		{
			OpenModal();
		}

		private void MeniuPrincipal_FormClosed(object sender, FormClosedEventArgs e)
		{
			magazie.SaveMateriale();
		}
		private void editeazaToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (LbMateriale.SelectedItem == null) return;
			OpenModal(Convert.ToInt32(LbMateriale.SelectedItem.ToString().Split(' ')[0]));
		}

		private void stergeToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (LbMateriale.SelectedItem == null) return;
			int id = Convert.ToInt32(LbMateriale.SelectedItem.ToString().Split(' ')[0]);
			magazie.Materiale = magazie.Materiale.Where(m => m.Id != id).ToArray();
			RefreshListBox();
		}

	}
}
