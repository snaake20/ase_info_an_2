using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bibliografie
{
	public abstract class Publicatie
	{
		private string titlu;
		private double pret;

		protected Publicatie(string titlu, double pret)
		{
			this.titlu = titlu;
			this.pret = pret;
		}

		public string Titlu { get => titlu; set => titlu = value; }
		public double Pret { get => pret; set => pret = value; }

		public abstract string genereazaReferinta();
	}
}
