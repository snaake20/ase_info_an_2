using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PAW_S01
{
    internal class Student
    {
        public int cod;
        private string nume;
        protected float medie;

        public Student() {
            this.cod = 0;
            this.nume= "Anonim";
            this.medie = 0.0f;
        }
        public Student(int c, string n, float m) {
            this.cod = c;
            this.nume= n;
            this.medie = m;
        }
        public Student(Student s) {
            this.cod = s.cod;
            this.nume= s.nume;
            this.medie = s.medie;
        }

        public string Nume
        {
            get { return nume; }
            set { nume = value; }
        }

        public void Afisare()
        {
            Console.WriteLine("Studentul {0} are codul {1} si media {2}", nume, cod, medie);
        }

        public override string ToString()
        {
            return "Studentul " + nume + " are codul " + cod + " si media " + medie;
        }

    }
}
