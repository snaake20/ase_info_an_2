using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GroupingCountSum
{
	internal class Program
	{
		static void Main(string[] args)
		{
			List<Candidat> candidati = new List<Candidat>
			{
				new Candidat(1, "Alex", 9.9f, new int[] { 1, 2, 3, 4 }),
				new Candidat(2, "Edi", 8.9f, new int[] { 2, 3, 4 }),
				new Candidat(3, "Calin", 8.8f, new int[] { 2, 3, 4 , 5}),
			};
			
			Dictionary<int, List<Candidat>> candidatiGrupati = candidati.SelectMany(c => c.VectorOptiuni, (c, n) => new { Candidat = c, Optiune = n })
										 .GroupBy(cn => cn.Optiune)
										 .ToDictionary(g => g.Key, g => g.Select(cn => cn.Candidat).ToList());

            foreach (var c in candidatiGrupati)
			{
				Console.WriteLine($"Optiunea {c.Key} are {c.Value.Count} persoane inscrise");
			}

			foreach (var c in candidatiGrupati)
			{
				Console.WriteLine($"{c.Key}");
				foreach (var can in c.Value)
				{
                    Console.WriteLine($"{can.NumeCandidat}");
                }
			}

			Console.ReadLine();
        }
	}
}
