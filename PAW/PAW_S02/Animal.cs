﻿using System;

namespace PAW_S02
{
    class Animal : ICloneable, IComparable
    {
        private int varsta;
        private string nume;
        private float greutate;

        public Animal()
        {
            varsta = 0;
            nume = "Anonim";
            greutate = 0.0f;
        }

        public Animal(int varsta, string nume, float greutate)
        {
            this.varsta = varsta;
            this.nume = nume;
            this.greutate = greutate;
        }

        public object Clone()
        {
            return MemberwiseClone();
        }

        public int Varsta
        {
            get { return varsta; }
            set
            {
                if (value > 0)
                {
                    varsta = value;
                }
            }
        }
        public string Nume
        {
            get { return nume; }
            set
            {
                if (value != null && !value.Equals(string.Empty))
                {
                    nume = value;
                } 
            }
        }        
        public float Greutate
        {
            get { return greutate; }
            set
            {
                if (value > 0.0f)
                {
                    greutate = value;
                } 
            }
        }
        public override string ToString()
        {
            return "Animalul " + nume + " are varsta " + varsta + " si greutatea " + greutate;
        }

        public int CompareTo(object obj)
        {
            if (greutate > ((Animal)obj).greutate)
            {
                return 1;
            }
            if (greutate < ((Animal)obj).greutate)
            {
                return -1;

            }
            return string.Compare(nume, ((Animal)obj).nume);
        }
    }
}
