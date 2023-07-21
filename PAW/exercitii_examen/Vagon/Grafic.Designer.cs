namespace Vagon
{
	partial class Grafic
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
			System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
			this.ChartVagoane = new System.Windows.Forms.DataVisualization.Charting.Chart();
			((System.ComponentModel.ISupportInitialize)(this.ChartVagoane)).BeginInit();
			this.SuspendLayout();
			// 
			// ChartVagoane
			// 
			chartArea1.Name = "ChartArea1";
			this.ChartVagoane.ChartAreas.Add(chartArea1);
			legend1.Name = "Legend1";
			this.ChartVagoane.Legends.Add(legend1);
			this.ChartVagoane.Location = new System.Drawing.Point(0, 0);
			this.ChartVagoane.Name = "ChartVagoane";
			this.ChartVagoane.Size = new System.Drawing.Size(799, 451);
			this.ChartVagoane.TabIndex = 0;
			this.ChartVagoane.Text = "chart1";
			this.ChartVagoane.Click += new System.EventHandler(this.ChartVagoane_Click);
			// 
			// Grafic
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.ChartVagoane);
			this.Name = "Grafic";
			this.Text = "Grafic";
			((System.ComponentModel.ISupportInitialize)(this.ChartVagoane)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.DataVisualization.Charting.Chart ChartVagoane;
	}
}