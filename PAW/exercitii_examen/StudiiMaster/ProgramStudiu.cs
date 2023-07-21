using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StudiiMaster
{
	public class ProgramStudiu
	{
		private int codProgram;
		private string denumireProgram;
		private int nrLocuriBuget;
		private int nrLocuriTaxa;

		public ProgramStudiu(int codProgram, string denumireProgram, int nrLocuriBuget, int nrLocuriTaxa)
		{
			this.codProgram = codProgram;
			this.denumireProgram = denumireProgram;
			this.nrLocuriBuget = nrLocuriBuget;
			this.nrLocuriTaxa = nrLocuriTaxa;
		}

		public int CodProgram { get => codProgram; set => codProgram = value; }
		public string DenumireProgram { get => denumireProgram; set => denumireProgram = value; }
		public int NrLocuriBuget { get => nrLocuriBuget; set => nrLocuriBuget = value; }
		public int NrLocuriTaxa { get => nrLocuriTaxa; set => nrLocuriTaxa = value; }
	}
}
