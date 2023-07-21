﻿namespace PAW_S02
{
    internal class Sarpe: Animal
    {
        private bool esteVeninos;
        private int lungime;

        public Sarpe():base()
        {
            esteVeninos= true;
            lungime= 0;
        }

        public Sarpe(int varsta, string nume, float greutate, bool esteVeninos, int lungime): base(varsta, nume, greutate)
        {
            this.esteVeninos = esteVeninos;
            this.lungime = lungime;
        }

        public bool EsteVeninos { get => esteVeninos; set => esteVeninos = value; }
        public int Lungime { get => lungime; set => lungime = value; }

        public override string ToString()
        {
            return base.ToString() + " si lungimea " + lungime + " si este veninos " + esteVeninos;
        }
    }
}
