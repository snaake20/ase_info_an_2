using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace PAW_S08
{
	public partial class Form1 : Form
	{
		List<Student> students = new List<Student>();
		public Form1()
		{
			InitializeComponent();
			incarcaDate();
			listView1.Columns.Add("Situatie");
		}

		private void btnAdaugaStudent_Click(object sender, EventArgs e)
		{
			try
			{
				int cod = Convert.ToInt32(tbCod.Text);
				string nume = tbNume.Text;
				int nota  = Convert.ToInt32(tbNota.Text);
				students.Add(new Student(cod, nume, nota));
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message);
			} finally {
				tbCod.Clear();
				tbNume.Clear();
				tbNota.Clear();
			}
		}
		private void incarcaDate()
		{
			StreamReader sr = new StreamReader("fisier.txt");
			string line;
			while ((line = sr.ReadLine()) != null)
			{
				int cod = Convert.ToInt32(line.Split(',')[0]);
				string nume = line.Split(',')[1];
				int nota = Convert.ToInt32(line.Split(',')[2]);
				students.Add(new Student(cod, nume, nota));
			}
			sr.Close();
			MessageBox.Show("Date incarcate");
		}

		private void btnAfisare_Click(object sender, EventArgs e)
		{
			listView1.Items.Clear();
			foreach(Student student in students)
			{
				ListViewItem item = new ListViewItem(student.Cod.ToString());
				item.SubItems.Add(student.Nume);
				item.SubItems.Add(student.Nota.ToString());
				item.SubItems.Add(student.Nota >= 5 ? "Promovat" : "Nepromovat");
				listView1.Items.Add(item);
			}
		}

		private void listView1_ItemChecked(object sender, ItemCheckedEventArgs e)
		{
			if (listView1.CheckedItems.Count == 2)
			{
				// uncheck the other ones
				foreach (ListViewItem item in listView1.CheckedItems)
				{
					if (item.Checked && item != e.Item)
					{
						item.Checked = false;
					}
				}
			}
			if (e.Item.Checked)
			{
				
				e.Item.BackColor = Color.Red;
				tbCod.Text = e.Item.SubItems[0].Text;
				tbNume.Text = e.Item.SubItems[1].Text;
				tbNota.Text = e.Item.SubItems[2].Text;
			} else
			{
				e.Item.BackColor = Color.Transparent;
				tbCod.Text = String.Empty;
				tbNume.Text = String.Empty;
				tbNota.Text = String.Empty;
			}
		}

		private void btnSterge_Click(object sender, EventArgs e)
		{
			foreach(ListViewItem item in listView1.Items)
			{
				if (item.Checked)
				{
					int cod = Convert.ToInt32(item.SubItems[0].Text);
					for (int i = 0; i < students.Count; i++)
					{
						if (students[i].Cod == cod)
						{
							students.RemoveAt(i);
						}
					}
					item.Remove();
				}
			}
		}

		private void stergeToolStripMenuItem_Click(object sender, EventArgs e)
		{
			foreach (ListViewItem item in listView1.Items)
			{
				if (item.Selected)
				{
					int cod = Convert.ToInt32(item.SubItems[0].Text);
					for (int i = 0; i < students.Count; i++)
					{
						if (students[i].Cod == cod)
						{
							students.RemoveAt(i);
						}
					}
					item.Remove();
				}
			}
		}

		private void btnSalvare_Click(object sender, EventArgs e)
		{
			StreamWriter sw = new StreamWriter("fisier.txt");
			foreach (Student s in students)
			{
				sw.Write(s.Cod);
				sw.Write(',');
				sw.Write(s.Nume);
				sw.Write(',');
				sw.Write(s.Nota);
				sw.WriteLine();
			}
			sw.Close();
			MessageBox.Show("Date salvate");
		}
	}
}
