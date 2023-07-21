using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pizzeria
{
	public class ComandaPizza
	{
		private string nume;
		private string blat;
		private int durataRealizare;
		private List<Topping> topping;

		public ComandaPizza(string nume, string blat, int durataRealizare, List<Topping> topping)
		{
			this.nume = nume;
			this.blat = blat;
			this.durataRealizare = durataRealizare;
			this.topping = topping;
		}

		public string Nume { get => nume; set => nume = value; }
		public string Blat { get => blat; set => blat = value; }
		public int DurataRealizare { get => durataRealizare; set => durataRealizare = value; }
		public List<Topping> Topping { get => topping; set => topping = value; }

		public Topping this[int index]
		{
			get
			{
				if (topping == null && index >= 0 && index <= Topping.Count)
				{
					return Topping[index];
				}
				else { return null; }
			}
		}

		public static bool operator <(ComandaPizza c, ComandaPizza p)
		{
			return c.CalculCostPizza() < p.CalculCostPizza();
		}
		
		public static bool operator >(ComandaPizza c, ComandaPizza p)
		{
			return c.CalculCostPizza() > p.CalculCostPizza();
		}

		public float CalculCostPizza()
		{
			float res = 0.0f;

			if (Topping != null)
			{
				res += Topping.Select(t => t.Cantitate * t.Pret).Sum();
			}

			return res;
		}

		public override string ToString()
		{
			return $"{nume} {durataRealizare} {string.Join(",", Topping.Select(t => t.ToString()))}";
		}
	}
}
