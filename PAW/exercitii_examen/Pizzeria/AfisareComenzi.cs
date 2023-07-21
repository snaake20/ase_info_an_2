using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Pizzeria
{
	public partial class AfisareComenzi : Form
	{
		List<ComandaPizza> comenzi;
		public AfisareComenzi(List<ComandaPizza> comenzi)
		{
			InitializeComponent();
			this.comenzi = comenzi;
		}

		private void AfisareComenzi_Load(object sender, EventArgs e)
		{
			var comenziAgregate =  comenzi.GroupBy(c => c.Blat).ToDictionary(g => g.Key, g=> g.Select(c => c).ToList());

			foreach (var comenziAgreg in comenziAgregate)
			{
				TreeNode parinte = new TreeNode(comenziAgreg.Key);
				TVComenzi.Nodes.Add(parinte);

				foreach (var comanda in comenziAgreg.Value)
				{

					parinte.Nodes.Add(comanda.ToString());
				}
			}

			TVComenzi.ExpandAll();
		}
	}
}
