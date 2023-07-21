using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ParcAuto
{
	public class Vehicul:ICloneable,IComparable
	{
		private char categorie;

		private string numarMatricol;

		private double kilometraj;

		public Vehicul(char categorie, double kilometraj, string numarMatricol)
		{
			this.categorie = categorie;
			this.kilometraj = kilometraj;
			this.numarMatricol = numarMatricol;
		}

		public char Categorie { get => categorie; set => categorie = value; }
		public double Kilometraj { get => kilometraj; set => kilometraj = value; }
		public string NumarMatricol { get => numarMatricol; set => numarMatricol = value; }

		public object Clone()
		{
			return MemberwiseClone();
		}

		public int CompareTo(object obj)
		{
			Vehicul vehicul = obj as Vehicul;
			if (this ==  vehicul) return 0;
			return kilometraj.CompareTo(vehicul.Kilometraj);
		}

		public override string ToString()
		{
			return "Vehiculul cu numarul matricol " + numarMatricol + " de categoria " + categorie + " are " + kilometraj + "kilometri.";
		}
	}
}
