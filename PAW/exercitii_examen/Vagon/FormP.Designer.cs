namespace Vagon
{
	partial class FormP
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
			this.components = new System.ComponentModel.Container();
			this.LVVagoane = new System.Windows.Forms.ListView();
			this.CodV = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.DescriereTip = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.Capacitate = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.CMLV = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.culoareToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.stergereToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.LBTren = new System.Windows.Forms.Label();
			this.LBFiltrare = new System.Windows.Forms.Label();
			this.CBTip = new System.Windows.Forms.ComboBox();
			this.LBTip = new System.Windows.Forms.Label();
			this.BTNFiltrare = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.BTNGrafic = new System.Windows.Forms.Button();
			this.CMLV.SuspendLayout();
			this.SuspendLayout();
			// 
			// LVVagoane
			// 
			this.LVVagoane.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.CodV,
            this.DescriereTip,
            this.Capacitate});
			this.LVVagoane.ContextMenuStrip = this.CMLV;
			this.LVVagoane.FullRowSelect = true;
			this.LVVagoane.HideSelection = false;
			this.LVVagoane.Location = new System.Drawing.Point(12, 29);
			this.LVVagoane.Name = "LVVagoane";
			this.LVVagoane.Size = new System.Drawing.Size(368, 248);
			this.LVVagoane.TabIndex = 0;
			this.LVVagoane.UseCompatibleStateImageBehavior = false;
			this.LVVagoane.View = System.Windows.Forms.View.Details;
			this.LVVagoane.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.LVVagoane_MouseDoubleClick);
			// 
			// CodV
			// 
			this.CodV.Text = "Cod";
			// 
			// DescriereTip
			// 
			this.DescriereTip.Text = "Tip";
			// 
			// Capacitate
			// 
			this.Capacitate.Text = "Capacitate";
			this.Capacitate.Width = 64;
			// 
			// CMLV
			// 
			this.CMLV.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.culoareToolStripMenuItem,
            this.stergereToolStripMenuItem});
			this.CMLV.Name = "CMLV";
			this.CMLV.ShowImageMargin = false;
			this.CMLV.Size = new System.Drawing.Size(93, 48);
			// 
			// culoareToolStripMenuItem
			// 
			this.culoareToolStripMenuItem.Name = "culoareToolStripMenuItem";
			this.culoareToolStripMenuItem.Size = new System.Drawing.Size(92, 22);
			this.culoareToolStripMenuItem.Text = "Culoare";
			this.culoareToolStripMenuItem.Click += new System.EventHandler(this.culoareToolStripMenuItem_Click);
			// 
			// stergereToolStripMenuItem
			// 
			this.stergereToolStripMenuItem.Name = "stergereToolStripMenuItem";
			this.stergereToolStripMenuItem.Size = new System.Drawing.Size(92, 22);
			this.stergereToolStripMenuItem.Text = "Stergere";
			this.stergereToolStripMenuItem.Click += new System.EventHandler(this.stergereToolStripMenuItem_Click);
			// 
			// LBTren
			// 
			this.LBTren.AutoSize = true;
			this.LBTren.Location = new System.Drawing.Point(9, 9);
			this.LBTren.Name = "LBTren";
			this.LBTren.Size = new System.Drawing.Size(92, 13);
			this.LBTren.TabIndex = 1;
			this.LBTren.Text = "Componenta Tren";
			// 
			// LBFiltrare
			// 
			this.LBFiltrare.AutoSize = true;
			this.LBFiltrare.Location = new System.Drawing.Point(391, 9);
			this.LBFiltrare.Name = "LBFiltrare";
			this.LBFiltrare.Size = new System.Drawing.Size(38, 13);
			this.LBFiltrare.TabIndex = 2;
			this.LBFiltrare.Text = "Filtrare";
			// 
			// CBTip
			// 
			this.CBTip.FormattingEnabled = true;
			this.CBTip.Location = new System.Drawing.Point(394, 54);
			this.CBTip.Name = "CBTip";
			this.CBTip.Size = new System.Drawing.Size(121, 21);
			this.CBTip.TabIndex = 3;
			this.CBTip.MouseClick += new System.Windows.Forms.MouseEventHandler(this.CBTip_MouseClick);
			// 
			// LBTip
			// 
			this.LBTip.AutoSize = true;
			this.LBTip.Location = new System.Drawing.Point(391, 38);
			this.LBTip.Name = "LBTip";
			this.LBTip.Size = new System.Drawing.Size(22, 13);
			this.LBTip.TabIndex = 4;
			this.LBTip.Text = "Tip";
			// 
			// BTNFiltrare
			// 
			this.BTNFiltrare.Location = new System.Drawing.Point(435, 5);
			this.BTNFiltrare.Name = "BTNFiltrare";
			this.BTNFiltrare.Size = new System.Drawing.Size(75, 23);
			this.BTNFiltrare.TabIndex = 5;
			this.BTNFiltrare.Text = "Click";
			this.BTNFiltrare.UseVisualStyleBackColor = true;
			this.BTNFiltrare.Click += new System.EventHandler(this.BTNFiltrare_Click);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(516, 9);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(35, 13);
			this.label1.TabIndex = 6;
			this.label1.Text = "Grafic";
			// 
			// BTNGrafic
			// 
			this.BTNGrafic.Location = new System.Drawing.Point(557, 5);
			this.BTNGrafic.Name = "BTNGrafic";
			this.BTNGrafic.Size = new System.Drawing.Size(75, 23);
			this.BTNGrafic.TabIndex = 7;
			this.BTNGrafic.Text = "Click";
			this.BTNGrafic.UseVisualStyleBackColor = true;
			this.BTNGrafic.Click += new System.EventHandler(this.BTNGrafic_Click);
			// 
			// FormP
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.BTNGrafic);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.BTNFiltrare);
			this.Controls.Add(this.LBTip);
			this.Controls.Add(this.CBTip);
			this.Controls.Add(this.LBFiltrare);
			this.Controls.Add(this.LBTren);
			this.Controls.Add(this.LVVagoane);
			this.Name = "FormP";
			this.Text = "Gestiune Tren";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormP_FormClosing);
			this.CMLV.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ListView LVVagoane;
		private System.Windows.Forms.ColumnHeader CodV;
		private System.Windows.Forms.ColumnHeader DescriereTip;
		private System.Windows.Forms.ColumnHeader Capacitate;
		private System.Windows.Forms.Label LBTren;
		private System.Windows.Forms.Label LBFiltrare;
		private System.Windows.Forms.ComboBox CBTip;
		private System.Windows.Forms.Label LBTip;
		private System.Windows.Forms.Button BTNFiltrare;
		private System.Windows.Forms.ContextMenuStrip CMLV;
		private System.Windows.Forms.ToolStripMenuItem culoareToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem stergereToolStripMenuItem;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button BTNGrafic;
	}
}

