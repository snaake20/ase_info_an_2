using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PAW_S01
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("hello world");
            string nume = Console.ReadLine();
            string prenume = Console.ReadLine();
            Console.WriteLine("numele este {0} iar prenumele {1}", nume, prenume);
            // cum se declara un vector
            int[] v1 = {1,2,3};
            int[] v2 = new int[4] {1,2,3, 4};
            // ambele sunt stocate in heap

            for (int i = 0; i < v2.Length; i++)
            {
                Console.Write("{0} ", v2[i]); // scrie pe linie
            }
            Console.WriteLine(); // basically \n
            foreach (var item in v1)
            {
                Console.WriteLine(item); // cout cu endl
            }

            int[] v3 = v2; // shallow copy

            int[] v4 = new int[v2.Length];
            for (int i = 0; i < v2.Length; i++) // deep copy c++ style
            {
                v4[i] = v2[i];
            }
            int[] v5 = (int[]) v4.Clone(); // deep copy

            int[,] mat1 = new int[2,3] { { 1,2,3}, { 2,3,4} };
            for (int i = 0; i < mat1.GetLength(0); i++)
            {
                for (int j = 0; j < mat1.GetLength(1); j++)
                {
                    Console.Write("{0} ", mat1[i, j]);
                }
                Console.WriteLine();
            }
            int[][] mat2 = new int[2][];
            mat2[0] = new int[3] { 1, 2, 3 };
            mat2[1] = new int[4] { 1, 2, 3, 4 };
            for (int i = 0; i < mat2.Length; i++)
            {
                for (int j = 0; j < mat2[i].Length; j++)
                {
                    Console.Write("{0} ", mat2[i][j]);
                }
                Console.WriteLine();
            }

            Student s1 = new Student(); // apel constructor implicit
            Student s2 = new Student(123, "gigel", 9.5f);
            Student s3 = s2; // shallow copy
            Student s4 = new Student(s2); // apel constructor de copiere
            Console.WriteLine(s2);
        }
    }
}
