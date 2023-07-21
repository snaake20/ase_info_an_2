using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PAW_S02
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Animal a1= new Animal();
            Animal a2 = new Animal(5, "Azorel", 10.5f);
            Animal a3 = a2.Clone() as Animal;
            a3.Nume = "Grivei";
            Girafa g1 = new Girafa(23, "Sophie", 120f, 2, 'F');
            Sarpe s1 = new Sarpe(10, "Kaa", 55f, true, 5);
            List<Animal> animals = new List<Animal>
            {
                a1,
                a2,
                a3,
                g1,
                s1
            };

            Zoo z1 = new Zoo("Soleil", animals);
            Zoo z2 = z1.Clone() as Zoo;
            z1.Animale.Sort();
            z2.Animale.Add(new Animal(12, "Balloo", 10f));
            z2.Animale.ForEach(a =>
            {
                a.Nume += " copie";
            });

            Console.WriteLine(z1.ToString());
            Console.WriteLine(z2.ToString());
            Console.WriteLine(z1.ToString());
            
        }
    }
}
