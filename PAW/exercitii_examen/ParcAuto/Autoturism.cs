using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ParcAuto
{
	internal class Autoturism : Vehicul, ICloneable
	{
		private int nrUsi;

		private bool areRoataDeRezerva;

		public Autoturism(char categorie, string nrMatricol, double kilometraj, int nrUsi, bool areRoataDeRezerva) : base(categorie, kilometraj, nrMatricol)
		{
			this.nrUsi = nrUsi;
			this.areRoataDeRezerva = areRoataDeRezerva;
		}

		public int NrUsi { get => nrUsi; set => nrUsi = value; }
		public bool AreRoataDeRezerva { get => areRoataDeRezerva; set => areRoataDeRezerva = value; }

		public new object Clone()
		{
			return MemberwiseClone();
		}
	}
}
