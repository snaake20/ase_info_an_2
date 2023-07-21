using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bibliografie
{
	public class Carte: Publicatie
	{
		private string isbn;
		private string categorie;
		private List<Autor> referinte;

		public Carte(string isbn, string categorie, List<Autor> referinte, string titlu, double pret):base(titlu, pret)
		{
			this.isbn = isbn;
			this.categorie = categorie;
			this.referinte = referinte;
		}

		public string Isbn { get => isbn; set => isbn = value; }
		public string Categorie { get => categorie; set => categorie = value; }
		public List<Autor> Referinte { get => referinte; set => referinte = value; }

		public override string genereazaReferinta()
		{
			string res = "";
			if (referinte != null)
			{
				foreach (Autor autor in referinte)
				{
					res += $"{autor.Nume},";
				}
			}
			res += $"-{Titlu},{Isbn}.";
			return res;
		}

		public static Carte operator+(Carte carte, Autor a)
		{
			carte.Referinte.Add(a);
			return carte;
		}
	}
}
