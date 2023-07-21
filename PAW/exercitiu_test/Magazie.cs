using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;

namespace PregatireTest1
{
	//Clasa care gestioneaza magazia dispune de un constructor si de cel putin o supraincarcare a unui operator pentru adaugarea de noi obiecte (materiale).
	public class Magazie
	{
		Material[] materiale = new Material[0];

        public Magazie()
        {
			LoadMateriale();
		}

        public Magazie(Material[] materiale)
        {
			this.materiale = (Material[])materiale.Clone();
        }

        internal Material[] Materiale { get => materiale; set => materiale = value; }
		
		public static Magazie operator+(Magazie magazie, Material material)
		{
			Material[] materiale = new Material[magazie.materiale.Length + 1];
			for (int i = 0; i < magazie.materiale.Length; i++)
			{
				materiale[i] = magazie.materiale[i];
			}
			materiale[magazie.materiale.Length] = material;
			magazie.materiale = materiale;
			return magazie;
		}

		public static Magazie operator+(Material material, Magazie magazie)
		{
			return magazie + material;
		}
		
		public void SaveMateriale()
		{
			BinaryFormatter bf = new BinaryFormatter();
			FileStream fs = new FileStream("materiale.dat", FileMode.Create, FileAccess.Write);

			bf.Serialize(fs, materiale);

			fs.Close();
		}

		public void LoadMateriale()
		{
			BinaryFormatter bf = new BinaryFormatter();
			FileStream fs = new FileStream("materiale.dat", FileMode.Open, FileAccess.Read);

			if (fs.Length > 0)
				materiale = (Material[])bf.Deserialize(fs);

			fs.Close();
		}
	}
}
