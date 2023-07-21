using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.ConstrainedExecution;
using System.Security.Cryptography;
using System.Security.Principal;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TextBox;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Window;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace PregatireTest1
{
	internal static class Program

		//Sa se realizeze o aplicatie Windows Forms C# .NET pentru a realiza gestiunea materialelor dintr-o magazie.
		//Se vor defini, in acest sens, doua clase principale care implementeaza solutia problemei:
		//- una elementara, care corespunde unui material; si
		//- o alta clasa, de tip colectie, care corespunde magaziei si care reflecta materialele existente in cadrul
		//ei.
		//(1p) Clasa elementara este serializabila, contine cel putin definirea unui constructor, supradefineste metoda
		//ToString(), iar peste campurile private se mapeaza proprietati.
		//(1p) Clasa care gestioneaza magazia dispune de un constructor si de cel putin o supraincarcare a unui
		//operator pentru adaugarea de noi obiecte (materiale).
		//(2p) Pe forma principala a aplicatiei se vor vizualiza toate materialele din magazie folosind un control adecvat.
		//Prin alegerea unei optiuni din meniul de pe formularul principal, se deschide o fereastra secundara de dialog
		//care permite adaugarea / modificarea unui material din magazie.
		//(1p) Obiectele(materialele) create / modificate prin intermediul formularului secundar se salvează în obiectul
		//magazie.
		//(2p) Obiectele(materialele) afisate pe formularul principal pot fi șterse(inclusiv din magazie) cu ajutorul unui
		//meniu contextual.
		//(2p) La sfârșitul sesiunii de lucru, materialele din magazie vor fi stocate prin serializare intr-un fisier pe disc.

	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main()
		{
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			Application.Run(new MeniuPrincipal());
		}
	}
}
