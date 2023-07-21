using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ParcAuto
{
	internal class Camion : Vehicul, ICloneable
	{
		private int nrRemorci;

		private double[] cantitateRemorca;

		public Camion(char categorie, string nrMatricol, double kilometraj, int nrRemorci, double[] cantitateRemorca) : base(categorie, kilometraj, nrMatricol)
		{
			this.nrRemorci = nrRemorci;
			this.cantitateRemorca = cantitateRemorca;
		}

		public int NrRemorci { get => nrRemorci; set => nrRemorci = value; }
		public double[] CantitateRemorca { get => cantitateRemorca; set => cantitateRemorca = value; }

		public static Camion operator+(Camion a, double d)
		{
			double[] cantitateRemorca = new double[a.NrRemorci+1];

			for (int i = 0; i < a.nrRemorci; i++)
			{
				cantitateRemorca[i] = a.cantitateRemorca[i];
			}

			cantitateRemorca[a.NrRemorci]= d;
			
			a.cantitateRemorca = cantitateRemorca;
			
			a.nrRemorci++;

			return a;
		}

		public static Camion operator+(double d, Camion a)
		{
			return a + d;
		}

		public static explicit operator double(Camion c)
		{
			return c.cantitateRemorca.Average();
		}

		public override string ToString()
		{
			string res = base.ToString() + " Este camion, are " + nrRemorci + "remorci" + Environment.NewLine + "Are urmatoarele capicitati ale remorcilor: " + Environment.NewLine;
			int i = 0;
			foreach (var capacitate in cantitateRemorca)
			{
				i++;
				res += i.ToString() + " " + capacitate.ToString();
			}
			return res;
		}
	}
}
