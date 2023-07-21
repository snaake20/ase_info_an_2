using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PAW_S03
{
	internal class Student : Persoana, IMedia, ICloneable, IComparable
	{
		private int varsta;
		private string nume;
		private int[] note;

		public int Varsta { get => varsta; set => varsta = value; }
		public string Nume { get => nume; set => nume = value; }
		public int[] Note { get => note; set => note = value; }

		public Student() : base()
		{
			this.varsta = 0;
			this.nume = "Anonim";
			this.note = null;
		}

		public Student(int cod, char sex, int varsta, string nume, int[] note) : base(cod, sex)
		{
			this.varsta = varsta;
			this.nume = nume;
			this.note = (int[])note.Clone();
		}

		public override string ToString()
		{
			string res = base.ToString() + " varsta: " + varsta + " numele: " + nume;
			if (note == null)
			{
				return res += " si nu are note";
			}
			res += " si are notele " + Environment.NewLine;
			foreach (var item in note)
			{
				res += item.ToString();
				res += ", ";
			}
			return res;
		}

		public int this[int index]
		{
			get
			{
				if (index > 0 && index < note.Length && note != null)
					return this.note[index];
				throw new IndexOutOfRangeException();
			}
			set {
				if (index > 0 && index < note.Length && note != null && value > 0 && value < 11)
					this.note[index] = value;
			}
		}

		public static Student operator+(Student s, int nota)
		{
			int[] noteNoi = new int[s.note.Length + 1];
			for (int i = 0; i < s.note.Length; i++)
			{
				noteNoi[i] = s.note[i];
			}
			noteNoi[s.note.Length] = nota;
			s.note = noteNoi;
			return s;
		}

		public static Student operator+(int nota, Student s)
		{
			return s + nota;
		}

		public override string spuneAnNastere()
		{
			return (System.DateTime.Now.Year - varsta).ToString();
		}

		public float calculeazaMedia()
		{
			if (note == null) return 0.0f;
			float suma = 0.0f;
			foreach (var item in note)
				suma += item;
			return (float)suma / note.Length;
		}

		public static explicit operator float(Student s) {
			return s.calculeazaMedia();
		}

		public object Clone()
		{
			var clona = (Student)MemberwiseClone();
			clona.note = (int[])note.Clone();
			return clona;
		}

		public int CompareTo(object obj)
		{
			Student s = (Student)obj;
			if ((float)this > (float)s)
				return -1;
			if ((float)this < (float)s)
				return 1;
			return string.Compare(this.nume, s.nume);
		}
	}
}
