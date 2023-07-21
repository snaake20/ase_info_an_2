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

namespace PAW_S04
{
	public partial class Form2 : Form
	{
		List<Student> lista;
		public Form2(List<Student> students)
		{
			InitializeComponent();
			lista = students;
			foreach (Student student in lista)
			{
				textBox1.Text += student.ToString();
			}
		}

		private void salvareFisierTextToolStripMenuItem_Click(object sender, EventArgs e)
		{
			SaveFileDialog dlg = new SaveFileDialog();
			dlg.Filter = "(*.txt)|*.txt";
			if (dlg.ShowDialog() == DialogResult.OK)
			{
				StreamWriter sw = new StreamWriter(dlg.FileName);
				sw.WriteLine(textBox1.Text);
				sw.Close();
				textBox1.Clear();
			}

		}

		private void citireFisierTextToolStripMenuItem_Click(object sender, EventArgs e)
		{
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.Filter = "(*.txt)|*.txt";
			if (dlg.ShowDialog() == DialogResult.OK)
			{
				StreamReader sr = new StreamReader(dlg.FileName);
				textBox1.Text = sr.ReadToEnd();
				sr.Close();
			}
		}

		private void serializareToolStripMenuItem_Click(object sender, EventArgs e)
		{
			BinaryFormatter bf = new BinaryFormatter();

			FileStream fs = new FileStream("fisier.dat", FileMode.Create, FileAccess.Write);

			bf.Serialize(fs, lista);
			fs.Close();
			textBox1.Clear();
		}

		private void deserializareToolStripMenuItem_Click(object sender, EventArgs e)
		{
			BinaryFormatter bf = new BinaryFormatter();

			FileStream fs = new FileStream("fisier.dat", FileMode.Open, FileAccess.Read);
			List<Student> listaTemp = (List<Student>)bf.Deserialize(fs);
            foreach (Student student in listaTemp)
			{
				textBox1.Text = student.ToString();
			}
			fs.Close();
		}
	}
}
