namespace PAW_S02
{
    class Girafa : Animal
    {
        private int inaltime;
        private char sex;

        public Girafa() : base()
        {
            inaltime = 0;
            sex = 'F';
        }

        public Girafa(int varsta, string nume, float greutate, int inaltime, char sex) : base(varsta, nume, greutate)
        {
            this.inaltime = inaltime;
            this.sex = sex;
        }

        public int Inaltime { get => inaltime; set => inaltime = value; }
        public char Sex { get => sex; set => sex = value; }

        //public int Inaltime
        //{
        //    get
        //    {
        //        return inaltime;
        //    }
        //    set
        //    {
        //        if (value > 0)
        //        {
        //            inaltime = value;
        //        }
        //    }
        //}

        //public char Sex
        //{
        //    get
        //    {
        //        return sex;
        //    }
        //    set
        //    {
        //        if (value != null && !value.Equals(String.Empty))
        //        {
        //            sex = value;
        //        }
        //    }
        //}

        public override string ToString()
        {
            return base.ToString() + " si inaltime " + inaltime + " si sexul " + sex;
        }
    }
}
