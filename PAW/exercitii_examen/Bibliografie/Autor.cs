using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bibliografie
{
	public class Autor
	{
		private string nume;
		private string gradDidactic;
		private int marca;

		public Autor(string nume, string gradDidactic, int marca)
		{
			this.nume = nume;
			this.gradDidactic = gradDidactic;
			this.marca = marca;
		}

		public string Nume { get => nume; set => nume = value; }
		public string GradDidactic { get => gradDidactic; set => gradDidactic = value; }
		public int Marca { get => marca; set => marca = value; }
	}
}
