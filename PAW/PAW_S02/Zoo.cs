using System;
using System.Collections.Generic;

namespace PAW_S02
{
    class Zoo: ICloneable
    {
        private string denumire;
        private List<Animal> animale;
        //private ArrayList animale; // asta mai e o varianta generica
        //private Animal[] animale; // even better, trebuie alocat spatiu ಥ_ಥ

        public Zoo()
        {
            denumire = "Baneasa";
            animale = new List<Animal>();
        }

        public Zoo(string denumire, List<Animal> animale)
        {
            this.denumire = denumire;
            // this.animale = animale; // shallow copy
            this.animale = new List<Animal>(animale);
        }

        public string Denumire { get => denumire; set => denumire = value; }
        internal List<Animal> Animale { get => animale; set => animale = value; }

        public object Clone()
        {
            Zoo clona = (Zoo)MemberwiseClone(); // daca nu are colectie sau vector
            List<Animal> animaleClona = new List<Animal>();
            foreach (var a in animale)
            {
                animaleClona.Add(a.Clone() as Animal);
            }
            clona.Animale= animaleClona;
            return clona;
        }

        public override string ToString()
        {
            string res = "Zoo " + denumire + " are urmatoarele animale " + Environment.NewLine;
            foreach (var animal in animale)
            {
                res += animal.ToString() + Environment.NewLine;
            }
            return res;
        }
    }
}
