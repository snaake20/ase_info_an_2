using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PAW_S08
{
	class Student
	{
		private int cod;
		private string nume;
		private int nota;

        public Student(int cod, string nume, int nota)
        {
			this.cod = cod;
			this.nume = nume;
			this.nota = nota;
        }

        public int Cod { get => cod; set => cod = value; }
		public string Nume { get => nume; set => nume = value; }
		public int Nota { get => nota; set => nota = value; }

		public override string ToString()
		{
			return "Studentul " + nume + " cu codul " + cod + " are nota " + nota;
		}
	}

}
