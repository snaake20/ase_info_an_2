using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GroupingCountSum
{
	public class Candidat
	{
		private int codCandidat;
		private string numeCandidat;
		private float medieConcurs;
		private int[] vectorOptiuni;

		public Candidat(int codCandidat, string numeCandidat, float medieConcurs, int[] vectorOptiuni)
		{
			this.codCandidat = codCandidat;
			this.numeCandidat = numeCandidat;
			this.medieConcurs = medieConcurs;
			this.vectorOptiuni = vectorOptiuni;
		}

		public int CodCandidat { get => codCandidat; set => codCandidat = value; }
		public string NumeCandidat { get => numeCandidat; set => numeCandidat = value; }
		public float MedieConcurs { get => medieConcurs; set => medieConcurs = value; }
		public int[] VectorOptiuni { get => vectorOptiuni; set => vectorOptiuni = value; }
	}
}
