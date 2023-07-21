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
	public partial class FormP : Form
	{
		List<ComandaPizza> comenzi = new List<ComandaPizza>
		{
			new ComandaPizza("nnn", "pan", 20, new List<Topping>
			{
				new Topping("pepperoni", 15, 10, 1)
			}),
			new ComandaPizza("ppp", "pufos", 30, new List<Topping>
			{
				new Topping("pepperoni", 15, 10, 1)
			}),
			new ComandaPizza("ccc", "clasic", 20, new List<Topping>
			{
				new Topping("pepperoni", 15, 10, 1)
			}),
			new ComandaPizza("zzz", "secret", 20, new List<Topping>
			{
				new Topping("pepperoni", 15, 10, 1)
			}),

		};
		public FormP()
		{
			InitializeComponent();
		}

		private void afisareComenziToolStripMenuItem_Click(object sender, EventArgs e)
		{
			var afisare = new AfisareComenzi(comenzi);
			afisare.Show();
		}
	}
}
