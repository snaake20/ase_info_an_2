using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PAW_S04
{
	[Serializable]
	public abstract class Persoana
	{
		private int cod;
		private char sex;

		protected int Cod { get => cod; set => cod = value; }
		protected char Sex { get => sex; set => sex = value; }

		public Persoana()
		{
			cod = 0;
			sex = 'F';
		}

		public Persoana(int cod, char sex)
		{
			this.cod = cod;
			this.sex = sex;
		}

		public override string ToString()
		{
			return "Persoana cu codul " + cod + " are sexul " + sex;
		}

		abstract public string spuneAnNastere();
	}
}
