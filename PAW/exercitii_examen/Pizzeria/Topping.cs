using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pizzeria
{
	public class Topping
	{
		private string denumire;
		private float pret;
		private float cantitate;
		private readonly int cod;

		public string Denumire { get => denumire; set => denumire = value; }
		public float Pret { get => pret; set => pret = value; }
		public float Cantitate { get => cantitate; set => cantitate = value; }

		public int Cod => cod;

		public Topping(string denumire, float pret, float cantitate, int cod)
		{
			this.denumire = denumire;
			this.pret = pret;
			this.cantitate = cantitate;
			this.cod = cod;
		}

		public override string ToString()
		{
			return $"{cod},{denumire},{pret},{cantitate}";
		}
	}
}
