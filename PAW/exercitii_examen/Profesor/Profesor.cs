using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Profesor
{
	public class Profesor:IPremiere
	{
		private int marca;

		private string nume;

		private double salariu;

		public Profesor(int marca, string nume, double salariu)
		{
			this.marca = marca;
			this.nume = nume;
			this.salariu = salariu;
		}

		public int Marca { get => marca; set => marca = value; }
		public string Nume { get => nume; set => nume = value; }
		public double Salariu { get => salariu; set => salariu = value; }

		public static double operator+(double d, Profesor p)
		{
			return d + p.Salariu;
		}

		public void Premiaza()
		{
			salariu *= 1.3;
		}

		public override string ToString()
		{
			return $"{marca},{nume},{salariu}";

		}
	}
}
