using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Printing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace Vagon
{
	public partial class Grafic : Form
	{
		public Grafic(List<Vagon> tren)
		{
			InitializeComponent();

			var list =  tren.GroupBy(vagon => vagon.DescriereTip).Select(g => new {Tip = g.Key, Capacitate = g.Sum(vagon => vagon.Capacitate) }).ToList();

			Series series = new Series("Capacitate per Tip");
			series.ChartType = SeriesChartType.Column;

			// Add data to the series
			foreach (var item in list)
			{
				series.Points.AddXY(item.Tip, item.Capacitate);
			}

			ChartVagoane.Series.Add(series);

			ChartVagoane.Refresh();

		}

		private void ChartVagoane_Click(object sender, EventArgs e)
		{
			PrintDocument pd = ChartVagoane.Printing.PrintDocument;

			pd.PrintPage += (send, ev) => {
				ChartVagoane.Printing.PrintPaint(ev.Graphics, ev.MarginBounds);
			};

			var dlg = new PrintPreviewDialog();

			dlg.Document = pd;

			dlg.ShowDialog();
		}
	}
}
