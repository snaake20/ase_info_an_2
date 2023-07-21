using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.OleDb;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ParcAuto
{
	public partial class Form1 : Form
	{
		List<Vehicul> vehicule = new List<Vehicul>();

		public Form1()
		{
			InitializeComponent();
		}

		private void queryDb()
		{
			try
			{
				OleDbConnection conn = new OleDbConnection("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=vehicule.accdb");

				OleDbCommand cmd = new OleDbCommand("SELECT * FROM VEHICULE");

				conn.Open();
				cmd.Connection = conn;


				var res = cmd.ExecuteReader();
				vehicule.Clear();
				if (res.HasRows)
				{
					while (res.Read())
					{
						if (!res.IsDBNull(res.GetOrdinal("numarUsi")))
						{
							vehicule.Add(new Autoturism(Convert.ToChar(res["categorie"]), Convert.ToString(res["numarMatricol"]), Convert.ToDouble(res["kilometraj"]), Convert.ToInt32(res["numarUsi"]), Convert.ToBoolean(res["areRoataDeRezerva"])));
						}
						else
						if (!res.IsDBNull(res.GetOrdinal("nrRemorci")))
						{
							double[] cantitateRemorca = new double[Convert.ToInt32(res["nrRemorci"])];

							Convert.ToString(res["cantitateRemorca"]).Split(',').ToList().ForEach(cantitate => cantitateRemorca.Append(Convert.ToDouble(cantitate)));
							vehicule.Add(new Camion(Convert.ToChar(res["categorie"]), Convert.ToString(res["numarMatricol"]), Convert.ToDouble(res["kilometraj"]), Convert.ToInt32(res["nrRemorci"]), cantitateRemorca));
						}
						else
						{
							vehicule.Add(new Vehicul(Convert.ToChar(res["categorie"]), Convert.ToDouble(res["kilometraj"]), Convert.ToString(res["numarMatricol"])));
						}

					}
				}

				res.Close();

				conn.Close();

			}
			catch (Exception exc)
			{
				MessageBox.Show(exc.StackTrace);
			}
		}

		private void incarcaDate()
		{

			LVVehicule.Items.Clear();


			if (vehicule.Count > 0)
			{
				vehicule.ForEach(vehicul =>
				{
					var itm = new ListViewItem(vehicul.NumarMatricol);

					itm.SubItems.Add(vehicul.Categorie.ToString());
					itm.SubItems.Add(vehicul.Kilometraj.ToString());

					if (vehicul is Autoturism autoturism)
					{
						itm.SubItems.Add(autoturism.NrUsi.ToString());
						itm.SubItems.Add(autoturism.AreRoataDeRezerva ? "Da" : "Nu");
					}
					else
					if (vehicul is Camion camion)
					{
						itm.SubItems.Add("");
						itm.SubItems.Add("");
						itm.SubItems.Add(camion.NrRemorci.ToString());
						itm.SubItems.Add(string.Join(",", camion.CantitateRemorca));
					}


					LVVehicule.Items.Add(itm);
				});


			}
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			queryDb();

			incarcaDate();

		}

		private void BTNDelete_Click(object sender, EventArgs e)
		{
			if (LVVehicule.CheckedItems.Count > 0)
			{
				try
				{
					var conn = new OleDbConnection("Provider=Microsoft.ACE.OLEDB.12.0; Data Source = vehicule.accdb");

					conn.Open();

					foreach (var item in LVVehicule.CheckedItems)
					{

						var nrInmatriculare = ((ListViewItem)item).Text;

						var cmd = new OleDbCommand("DELETE FROM VEHICULE WHERE NUMARMATRICOL = '" + nrInmatriculare + "'");

						cmd.Connection = conn;

						cmd.ExecuteNonQuery();

						conn.Close();

						LVVehicule.Items.Remove((ListViewItem)item);

					}
				} catch (Exception ex)
				{
					MessageBox.Show(ex.StackTrace);
				}

				queryDb();

				incarcaDate();
			}
		}
	}
}
