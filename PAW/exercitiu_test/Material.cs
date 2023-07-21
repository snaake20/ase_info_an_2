using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.ConstrainedExecution;
using System.Text;
using System.Threading.Tasks;

namespace PregatireTest1
{
	//Clasa elementara este serializabila, contine cel putin definirea unui constructor, supradefineste metoda ToString(), iar peste campurile private se mapeaza proprietati.
	[Serializable]
	public class Material
	{
		private int id;
		private string denumire;
		private float pret;

        public Material()
        {
			id = 0;
			denumire = string.Empty;
            pret = 0.0f;
        }

        public Material(int id, string denumire, float pret)
        {
			this.id = id;
			this.denumire = denumire;
            this.pret = pret;
        }

        public string Denumire { get => denumire; set => denumire = value; }
		public float Pret { get => pret; set => pret = value; }
		public int Id { get => id; set => id = value; }

		public override string ToString()
		{
			return id + " materialul " + denumire + " are pretul " + pret;
		}
	}
}
