using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vagon
{
	[Serializable]
	public class Vagon
	{
		private int codV;
		private String descriereTip;
		private int capacitate;

		public Vagon(int codV, string descriereTip, int capacitate)
		{
			this.codV = codV;
			this.descriereTip = descriereTip;
			this.capacitate = capacitate;
		}

		public int CodV { get => codV; set => codV = value; }
		public string DescriereTip { get => descriereTip; set => descriereTip = value; }
		public int Capacitate { get => capacitate; set => capacitate = value; }
	}
}
