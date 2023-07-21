using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Bibliografie
{
	public partial class FormP : Form
	{
		List<Carte> publicatii = new List<Carte>()
		{
			new Carte("12345", "Drama", new List<Autor>(), "Baltagul", 420.69),
			new Carte("12346", "Horror", new List<Autor>(), "IT", 69),
			new Carte("12445", "Poezie", new List<Autor>(), "Luceafarul", 500),
			new Carte("14345", "Horror", new List<Autor>(), "The Shining", 76),
		};
		List<Autor> autori = new List<Autor>
		{
			new Autor("Stephen King", "E", 69),
			new Autor("Liviu Rebreanu", "M", 420),
			new Autor("Mihai Eminescu", "R", 500),
		};

		public FormP()
		{
			InitializeComponent();
		}

		private void adaugaManualToolStripMenuItem_Click(object sender, EventArgs e)
		{

		}

		private void FormP_Load(object sender, EventArgs e)
		{
			foreach (Carte carte in publicatii)
			{
				ListViewItem item = new ListViewItem(carte.Titlu);

				item.SubItems.Add(carte.Isbn);
				item.SubItems.Add(carte.Categorie);
				item.SubItems.Add(carte.Pret.ToString());

				LVPublicatii.Items.Add(item);
			}
			foreach (Autor autor in autori)
			{
				ListViewItem item = new ListViewItem(autor.Nume);

				item.SubItems.Add(autor.GradDidactic);
				item.SubItems.Add(autor.Marca.ToString());

				LVAutori.Items.Add(item);
			}
		}

		private void LVPublicatii_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (LVPublicatii.SelectedItems.Count == 1)
			{
				textBox1.Clear();
				string ISBN = LVPublicatii.SelectedItems[0].SubItems[1].Text;
				textBox1.Text = string.Join(Environment.NewLine, publicatii.Find(carte => carte.Isbn.Equals(ISBN)).Referinte.Select(r => r.Nume));
			}
		}

		private void LVAutori_ItemDrag(object sender, ItemDragEventArgs e)
		{
			if (LVAutori.SelectedItems.Count == 1)
			{
				DoDragDrop(e.Item, DragDropEffects.Copy);
			}
		}

		private void textBox1_DragDrop(object sender, DragEventArgs e)
		{
			if (LVPublicatii.SelectedItems.Count == 1 && LVAutori.SelectedItems.Count == 1) {
				int marca = Convert.ToInt32(LVAutori.SelectedItems[0].SubItems[2].Text);
				string ISBN = LVPublicatii.SelectedItems[0].SubItems[1].Text;
				Autor autor = autori.Find(a => a.Marca.Equals(marca));
				Carte c = publicatii.Find(p => p.Isbn.Equals(ISBN));
				c += autor;
			}
		}

		private void textBox1_DragEnter(object sender, DragEventArgs e)
		{
			if (LVPublicatii.SelectedItems.Count == 1 && LVAutori.SelectedItems.Count == 1)
			{
				e.Effect = DragDropEffects.Copy;
			}
		}
	}
}
