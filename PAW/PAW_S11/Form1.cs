﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Drawing.Printing;
using System.Runtime.CompilerServices;

namespace PAW_S11
{
	public partial class Form1 : Form
	{
		double[] vect = new double[20];
		int nrElem = 0;
		bool vb = false;
		const int marg = 10;
		Graphics gr;
		Color culoare = Color.Blue;
		public Form1()
		{
			InitializeComponent();
			gr = panel.CreateGraphics();
			//gr = Graphics.FromHwnd(panel.Handle);
			
		}

		private void incarcaDateToolStripMenuItem_Click(object sender, EventArgs e)
		{
			StreamReader sr = new StreamReader("fisier.txt");

			string linie;
			
			while ((linie=sr.ReadLine()) != null)
			{
				vect[nrElem++] = Convert.ToDouble(linie);
			}
			vb = true;
			sr.Close();
			panel.Invalidate(); // determina declansarea evenimentului paint
		}

		private void panel_Paint(object sender, PaintEventArgs e)
		{
			if(vb)
			{
				Rectangle rec = new Rectangle(panel.ClientRectangle.X + marg, panel.ClientRectangle.Y + 2 * marg, panel.ClientRectangle.Width - 2 * marg, panel.ClientRectangle.Height - 3 * marg);
				Pen pen = new Pen(Color.Red, 3);
				gr.DrawRectangle(pen, rec);

				double latime = rec.Width / nrElem / 2;
				double distanta = (rec.Width - nrElem * latime) / (nrElem + 1);

				double vMax = vect.Max();

				Brush br = new SolidBrush(culoare);

				Rectangle[] recs = new Rectangle[nrElem];
				for (int i = 0; i < nrElem; i++)
				{
					recs[i] = new Rectangle((int)(rec.Location.X + (i + 1) * distanta + i * latime), (int)(rec.Location.Y + rec.Height - vect[i]/vMax* rec.Height), (int)latime, (int)(vect[i]/vMax*rec.Height));
					gr.DrawString(vect[i].ToString(), this.Font, br, (int)(recs[i].Location.X + latime / 2), recs[i].Location.Y - this.Font.Height);
				}
				gr.FillRectangles(br, recs);
				for (int i = 0; i < nrElem-1; i++)
				{
					gr.DrawLine(pen, new Point((int)(recs[i].Location.X + latime / 2), recs[i].Location.Y), new Point((int)(recs[i+1].Location.X + latime / 2), recs[i+1].Location.Y));
				}
			}
		}

		private void schimbaCuloareToolStripMenuItem_Click(object sender, EventArgs e)
		{
			ColorDialog dlg = new ColorDialog();
			if (dlg.ShowDialog() == DialogResult.OK)
			{
				culoare = dlg.Color;
			}
			panel.Invalidate();
		}

		private void pd_print(object sender, PrintPageEventArgs e)
		{
			if (vb)
			{
				gr = e.Graphics;
				Rectangle rec = new Rectangle(e.PageBounds.X + marg, e.PageBounds.Y + 2 * marg, e.PageBounds.Width - 2 * marg, e.PageBounds.Height - 3 * marg);
				Pen pen = new Pen(Color.Red, 3);
				gr.DrawRectangle(pen, rec);

				double latime = rec.Width / nrElem / 2;
				double distanta = (rec.Width - nrElem * latime) / (nrElem + 1);

				double vMax = vect.Max();

				Brush br = new SolidBrush(culoare);

				Rectangle[] recs = new Rectangle[nrElem];
				for (int i = 0; i < nrElem; i++)
				{
					recs[i] = new Rectangle((int)(rec.Location.X + (i + 1) * distanta + i * latime), (int)(rec.Location.Y + rec.Height - vect[i] / vMax * rec.Height), (int)latime, (int)(vect[i] / vMax * rec.Height));
					gr.DrawString(vect[i].ToString(), this.Font, br, (int)(recs[i].Location.X + latime / 2), recs[i].Location.Y - this.Font.Height);
				}
				gr.FillRectangles(br, recs);
				for (int i = 0; i < nrElem - 1; i++)
				{
					gr.DrawLine(pen, new Point((int)(recs[i].Location.X + latime / 2), recs[i].Location.Y), new Point((int)(recs[i + 1].Location.X + latime / 2), recs[i + 1].Location.Y));
				}
			}
		}

		private void previzualizareToolStripMenuItem_Click(object sender, EventArgs e)
		{
			PrintDocument pd = new PrintDocument();
			pd.PrintPage += new PrintPageEventHandler(pd_print);
			PrintPreviewDialog dlg = new PrintPreviewDialog();
			dlg.Document = pd;
			dlg.ShowDialog();
		}
	}
}
