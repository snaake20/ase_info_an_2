using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.OleDb;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;

namespace Profesor
{
	public partial class FormP : Form
	{
		Profesor[] profesori = new Profesor[]
		{
			new Profesor(1, "Ciurea", 1500.69),
			new Profesor(2, "Doinea", 1400)
		};

		public FormP()
		{
			InitializeComponent();
		}

		private void FormP_Load(object sender, EventArgs e)
		{
			foreach (var prof in profesori) { 
				DGVProfesori.Rows.Add(prof.Marca.ToString(),prof.Nume,prof.Salariu.ToString());
			}
		}

		private void BTNCalculSalarii_Click(object sender, EventArgs e)
		{
			double res = 0;
			foreach (var prof in profesori)
			{
				res += prof;
			}
			MessageBox.Show("Salariile tuturor profesorilor sunt in valoare de " + res);
		}

		private void FormP_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.E && e.Alt)
			{
				Close();
			}
		}

		private void BTNSaveDB_Click(object sender, EventArgs e)
		{
			try
			{
				var conn = new OleDbConnection("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=Profesor.accdb");

				conn.Open();

				var tableName = "tblProfesor";

				//var comm = conn.CreateCommand();
				//comm.CommandText = $"CREATE TABLE {tableName} (MARCA NUMBER NOT NULL, NUME TEXT NOT NULL, SALARIU NUMBER NOT NULL )";
				//comm.ExecuteNonQuery();

				for (int i = 0; i < DGVProfesori.Rows.Count -1;  i++)
				{
					var cmd = new OleDbCommand($"INSERT INTO {tableName} VALUES (" + DGVProfesori.Rows[i].Cells[0].Value + ",'" + DGVProfesori.Rows[i].Cells[1].Value + "'," + DGVProfesori.Rows[i].Cells[2].Value + ")", conn);
					cmd.ExecuteNonQuery();
				}


				conn.Close();
			
			} catch (Exception ex)
			{
				MessageBox.Show(ex.Message + Environment.NewLine + ex.StackTrace);
			}
		}

		private void printDocument1_PrintPage(object sender, System.Drawing.Printing.PrintPageEventArgs e)
		{
			for (int i = 0; i< DGVProfesori.Rows.Count - 1; i++)
			{
				e.Graphics.DrawString($"{DGVProfesori.Rows[i].Cells[0].Value},{DGVProfesori.Rows[i].Cells[1].Value},{DGVProfesori.Rows[i].Cells[2].Value}", new Font(FontFamily.GenericSansSerif, 12), Brushes.Black, new Point(50, (i+1)*50));
			}
		}

		private void button1_Click(object sender, EventArgs e)
		{
			if (printPreviewDialog1.ShowDialog() == DialogResult.OK) {
				printDocument1.Print();
			}
		}

		private void BTNSaveXML_Click(object sender, EventArgs e)
		{
			SaveFileDialog dlg = new SaveFileDialog();
			dlg.Filter = "XML FILE|*.xml";
			if (dlg.ShowDialog() == DialogResult.OK)
			{
				MemoryStream ms = new MemoryStream();

				XmlTextWriter xml = new XmlTextWriter(ms, Encoding.UTF8);

				xml.Formatting = Formatting.Indented;

				xml.WriteStartDocument();

				xml.WriteStartElement("Profesori");

				for (int i = 0; i < DGVProfesori.Rows.Count -1 ; i++)
				{
					xml.WriteStartElement("Profesor");
					xml.WriteAttributeString("marca", DGVProfesori.Rows[i].Cells[0].Value.ToString());
					xml.WriteAttributeString("nume", DGVProfesori.Rows[i].Cells[1].Value.ToString());
					xml.WriteAttributeString("salariu", DGVProfesori.Rows[i].Cells[2].Value.ToString());
					xml.WriteEndElement();
				}

				xml.WriteEndElement();

				xml.WriteEndDocument();

				xml.Close();

				string xmlString = Encoding.UTF8.GetString(ms.ToArray());
				ms.Close();
				StreamWriter sw = new StreamWriter(dlg.FileName);

				sw.Write(xmlString);
				sw.Close();
			}
		}
	}
}