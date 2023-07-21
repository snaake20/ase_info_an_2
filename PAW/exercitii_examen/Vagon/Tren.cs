using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Vagon
{
	public class Tren
	{
		private int codT;
		private int nrVagoane;
		private List<Vagon> lstVagoane;

        public Tren()
        {
			this.codT = 0;

			this.nrVagoane = 0;

			this.lstVagoane = new List<Vagon>();
        }

        public Tren(int codT, int nrVagoane, List<Vagon> lstVagoane)
		{
			this.codT = codT;
			this.nrVagoane = nrVagoane;
			this.lstVagoane = lstVagoane;
		}

		public int CodT { get => codT; set => codT = value; }
		public int NrVagoane { get => nrVagoane; set => nrVagoane = value; }
		public List<Vagon> LstVagoane { get => lstVagoane; set => lstVagoane = value; }

		public static Tren operator+(Tren t, Vagon v)
		{
			t.LstVagoane.Add(v);
			return t;
		}

		public static Tren operator+(Vagon v, Tren t)
		{
			return t + v;
		}

		public Vagon this[int idx]
		{
			get {
				if (lstVagoane != null && idx >= 0 && idx < LstVagoane.Count) {
					return lstVagoane[idx];
				} else { return null; }
			} 
		}

		public void citireTxt(string file)
		{
			try
			{
				var sr = new StreamReader(file);

				string line = null;

				while ((line = sr.ReadLine()) != null) {
					LstVagoane.Add(new Vagon(Convert.ToInt32(line.Split(',')[0]), line.Split(',')[1], Convert.ToInt32(line.Split(',')[2])));
				}

				sr.Close();
			} catch
			{
				MessageBox.Show("Fisierul nu a putut fi citit");
			}
		}
	}
}
