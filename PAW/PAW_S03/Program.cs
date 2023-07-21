using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PAW_S03
{
	internal class Program
	{
		static void Main(string[] args)
		{
			var s1 = new Student();
			var s2 = new Student(123, 'M', 22, "Gigel", new int[] {7,8,9});
			var s3 = (Student)s2.Clone();
			s3 += 10;
			s3 = 10 + s3;
			s3[3] = 1;
			Console.WriteLine(s1);
			Console.WriteLine(s2);
			Console.WriteLine(s3);
			Console.WriteLine("s2 s-a nascut in: " + s2.spuneAnNastere());
			Console.WriteLine("media lui s3 este {0}", (float)s3);
			var s4 = new Student(111, 'F', 21, "CCCC", new int[] { 10, 10, 10 });
			var lista = new List<Student>
			{
				s1,
				s2,
				s3,
				s4
			};
			lista.Sort();
			foreach (Student student in lista)
			{
				Console.WriteLine(student);
			}
		}
	}
}
